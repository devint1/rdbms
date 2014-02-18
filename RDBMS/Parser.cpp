#include <sstream>
#include <algorithm>
#include <stack>
#include "Parser.h"
#include "TableOperations.h"

const string Parser::COMMAND_NAMES[] = {"OPEN", "CLOSE", "WRITE", "EXIT", "SHOW", "CREATE", "UPDATE", "INSERT", "DELETE"};
const string Parser::EXPRESSION_KEYWORD_NAMES[] = { "select", "project", "rename" };

bool Parser::checkNumTokens(command cmd, int numTokens)
{
	switch (cmd)
	{
	case open:
	case close:
	case write:
	case show:
		return numTokens == 1;
	case exit:
		return numTokens == 0;
	default:
		return true; //The rest of the commands will have varying numbers of tokens
	}
}

void Parser::executeCreate(vector<string> tokens)
{
	tokens = parse_parens(tokens);

	if (tokens.size() != 6)
	{
		cerr << "ERROR: Invalid syntax." << endl;
		return;
	}
	if (tokens[0] != "TABLE") {
		cerr << "ERROR: Expected token \"TABLE\"" << endl;
		return;
	}
	string relationName = tokens[1];
	string attributeList = remove_parens(remove_commas(tokens[2]));
	if (tokens[3] != "PRIMARY") {
		cerr << "ERROR: Expected token \"PRIMARY\"" << endl;
		return;
	}
	if (tokens[4] != "KEY") {
		cerr << "ERROR: Expected token \"PRIMARY\"" << endl;
		return;
	}
	string primaryKeys = remove_parens(remove_commas(tokens[5]));

	istringstream iss(attributeList);
	vector<string> attributeTokens{ istream_iterator<string>(iss), istream_iterator<string>() };

	istringstream iss1(primaryKeys);
	vector<string> keyTokens{ istream_iterator<string>(iss1), istream_iterator<string>() };

	if (attributeTokens.size() % 2 != 0) {
		cerr << "ERROR: Invalid syntax." << endl;
		return;
	}

	vector<string> attributeNames;
	vector<string> attributeTypes;

	for (size_t i = 0; i < attributeTokens.size(); i += 2)
	{
		attributeNames.push_back(attributeTokens[i]);
		attributeTypes.push_back(attributeTokens[i + 1]);
	}

	db.createTable(relationName, attributeNames, attributeTypes, keyTokens);
}

void Parser::executeInsert(vector<string> tokens)
{
	tokens = parse_parens(tokens);

	//After parens are parsed, we should have at least 6 tokens
	if (tokens.size() < 5)
	{
		throw exception("Invalid syntax.");
	}

	if (tokens[0] != "INTO" || tokens[2] != "VALUES" || tokens[3] != "FROM")
	{
		throw exception("Expected keyword.");
	}

	string relationName = tokens[1];

	if (tokens.size() == 5)
	{	
		tokens[4] = remove_end_parens(tokens[4]);
		tokens[4] = remove_commas(tokens[4]);

		istringstream iss(tokens[4]);
		vector<string> attributesToInsertTokens{ istream_iterator<string>(iss), istream_iterator<string>() };

		db.insertIntoTable(relationName, attributesToInsertTokens);
	}
	else
	{
		if (tokens[4] != "RELATION")
			throw exception("Expected token \"RELATION\"");

		vector<string> exprTokens;

		if (tokens.size() > 6)
		{
			exprTokens = vector<string>(tokens.begin() + 5, tokens.end());
		}
		else 
		{
			tokens[5] = remove_end_parens(tokens[5]);
			istringstream iss(tokens[5]);
			exprTokens = { istream_iterator<string>(iss), istream_iterator<string>() };
		}

		db.insertIntoTable(relationName, evaluateExpression(exprTokens));
	}
}

void Parser::executeDelete(vector<string> tokens)
{
	if (tokens[0] != "FROM" || tokens[2] != "WHERE" || tokens[4] != "=")
		cerr << "ERROR: Incorrect Input" << endl;
	string tablename = tokens[1];
	string attributename = tokens[3];
	string dataname = tokens[5];
	db.deleteFromTable(tablename, attributename, dataname);
}

void Parser::executeUpdate(vector<string> tokens)
{
	tokens = parse_parens(tokens);

	if (tokens.size() != 5) {
		cerr << "ERROR: Invalid syntax." << endl;
		return;
	}

	string relationName = tokens[0];
	if (tokens[1] != "SET") {
		cerr << "ERROR: Expected token \"SET\"" << endl;
		return;
	}
	string attributesToSet = remove_parens(remove_commas(tokens[2]));
	
	istringstream iss(attributesToSet);
	vector<string> attributesToSetTokens{ istream_iterator<string>(iss), istream_iterator<string>() };

	if (attributesToSetTokens.size() != 3) {
		cerr << "ERROR: Invalid syntax." << endl;
		return;
	}

	if (attributesToSetTokens[1] != "=") {
		cerr << "ERROR: Expected '='" << endl;
		return;
	}

	string attributeSetName = attributesToSetTokens[0];
	string attributeSetValue = attributesToSetTokens[2];
	
	if (tokens[3] != "WHERE") {
		cerr << "ERROR: Expected token \"WHERE\"" << endl;
		return;
	}

	string condition = remove_parens(tokens[4]);

	istringstream iss1(condition);
	vector<string> conditionTokens{ istream_iterator<string>(iss1), istream_iterator<string>() };

	if (conditionTokens.size() != 3) {
		cerr << "ERROR: Invalid syntax." << endl;
		return;
	}

	if (conditionTokens[1] != "=") {
		cerr << "ERROR: Expected '='" << endl;
		return;
	}

	string attributeConditionName = conditionTokens[0];
	string attributeConditionValue = conditionTokens[2];

	db.updateTable(relationName, attributeSetName, attributeSetValue, attributeConditionName, attributeConditionValue);
}

Table Parser::executeProject(vector<string> attributeNames, vector<string> expr)
{
	if (attributeNames.size() < 1)
		throw exception("No attributes provided.");

	Table targetTable = evaluateExpression(expr); //This will be the table we are working on
	Table result = TableOperations::project(targetTable, attributeNames[0]);
	
	//Build the table for each of the attributes provided
	for (size_t i = 1; i < attributeNames.size(); ++i)
	{
		result = TableOperations::combineTables(result, TableOperations::project(targetTable, attributeNames[i]));
	}

	return result;
}

void Parser::evaluateQuery(string query)
{
	istringstream iss(query);
	vector<string> tokens{ istream_iterator<string>(iss), istream_iterator<string>() };

	string relationName = tokens[0];

	if (tokens.size() < 2)
	{
		cerr << "ERROR: Expected <-" << endl;
		return;
	}

	else if (tokens[1] != "<-") 
	{
		cerr << "ERROR: Expected <-" << endl;
		return;
	}

	else if (tokens.size() < 3)
	{
		cerr << "ERROR: Expected expression after <-" << endl;
		return;
	}

	vector<string> exprTokens(tokens.begin() + 2, tokens.end());

	if (db.tableExists(relationName))
	{
		Table result = evaluateExpression(exprTokens);
		result.setName(relationName);
		db.findTable(relationName) = result;
	}
	else {
		Table result = evaluateExpression(exprTokens);
		result.setName(relationName);
		db.addTable(result);
	}
}

void Parser::evaulateCommand(string command)
{
	istringstream iss(command);
	vector<string> tokens{ istream_iterator<string>(iss), istream_iterator<string>() };
	Parser::command cmd;

	//Convert the command string to an enumerated form
	for (int i = 0; i < sizeof(COMMAND_NAMES) / sizeof(string); ++i) {
		if (tokens[0] == COMMAND_NAMES[i]) {
			cmd = (Parser::command) i;
			break;
		}
	}

	//If the number of tokens is valid at this point, find the command and execute it
	if (checkNumTokens(cmd, tokens.size() - 1)) {
		switch (cmd) {
		case open:
			db.openTable(tokens[1]);
			break;
		case close:
			db.closeTable(tokens[1]);
			break;
		case write:
			db.writeTable(tokens[1]);
			break;
		case exit:
			_exit(0);
			break;
		case show:
			db.showTable(tokens[1]);
			break;
		case create: {
			vector<string> createTokens(tokens.begin() + 1, tokens.end());
			executeCreate(createTokens);
			break;
		}
		case update: {
			vector<string> updateTokens(tokens.begin() + 1, tokens.end());
			executeUpdate(updateTokens);
			break;
		}
		case insert: {
			vector<string> insertTokens(tokens.begin() + 1, tokens.end());
			executeInsert(insertTokens);
			break;
		}
		case del: {
			vector<string> deleteTokens(tokens.begin() + 1, tokens.end());
			executeDelete(deleteTokens);
			break;
		}
		default:
			cerr << "ERROR: Command not implemented." << endl;
		}		
	}
 else
	{
		//The user did not follow the correct syntax for the command.
	cerr << "ERROR: Invalid syntax." << endl;
}
}

Table Parser::evaluateSelect(vector<string> expr){
	string condition = expr[1];
	string tableName = expr[2];
	condition = remove_parens(condition);
	istringstream iss(condition);
	vector<string> condTokens{ istream_iterator<string>(iss), istream_iterator<string>() };
	condTokens = parse_parens(condTokens);
	
	string attrib, condOp;
	
	attrib = condTokens[0];
	condOp = condTokens[1];
	condition = remove_quotes(condTokens[2]);

	bool syntax_error = false;
	
	//if (condTokens.size() == 3) sel <- select (Make == toyota && Mpg >= 28) cars
		Table result = TableOperations::select(db.findTable(tableName), condTokens[0], condTokens[1], remove_quotes(condTokens[2]));

	int counter = 1;
	for (size_t i = 4; i < condTokens.size()+1; i++){
		switch (counter)
		{
		case 1:
			attrib = condTokens[i];
			counter++;
			break;
		case 2:
			condOp = condTokens[i];
			counter++;
			break;
		case 3:
			condition = remove_quotes(condTokens[i]);
			counter++;
			break;
		case 4:
			if (condTokens[i-4] == "&&"){
			
				syntax_error = true;
			}
			else if (condTokens[i-4] == "||"){
				result = TableOperations::setUnion(result, TableOperations::select(db.findTable(tableName), attrib, condOp, condition));
			}
			else{
				syntax_error = true;
			}
			counter = 1;
			break;
		default:
			syntax_error = true;
		}
		if (syntax_error){
			throw exception("invalid select condition syntax.");
			break;
		}
		
	}

	return result;
}

Table Parser::evaluateExpression(vector<string> expr)
{
	exprKeyword keyword = (exprKeyword) -1;

	//Find the enumerated version of the keyword string
	for (int i = 0; i < sizeof(EXPRESSION_KEYWORD_NAMES) / sizeof(string); ++i)
	{
		if (expr[0] == EXPRESSION_KEYWORD_NAMES[i])
		{
			keyword = (exprKeyword) i;
			break;
		}
	}

	//Evaluate as a keyword expression
	if (keyword > -1)
	{
		expr = parse_parens(expr);

		if (expr.size() >= 3)
		{
			//Get the inner tokens (condition or attribute list) ready for tokenization
			expr[1] = remove_end_parens(expr[1]);
			expr[1] = remove_commas(expr[1]);

			//Tokenize inner tokens
			istringstream iss(expr[1]);
			vector<string> innerTokens{ istream_iterator<string>(iss), istream_iterator<string>() };

			//Tokenize the atomic expression
			vector<string> atomicExpr;

			//If it is surrounded by parens, parse it again
			if (expr[2][0] == '(' && expr[2][expr[2].length() - 1] == ')')
			{
				expr[2] = remove_end_parens(expr[2]);

				istringstream iss2(expr[2]);
				atomicExpr = { istream_iterator<string>(iss2), istream_iterator<string>() };
			} 
			//Othwerwise we can just use everything at the end of the expression
			else
				atomicExpr = vector<string>(expr.begin() + 2, expr.end());

		switch(keyword)
		{
			case select:
				return evaluateSelect(expr);
				break;
			case project:
					return executeProject(innerTokens, atomicExpr);
			case rename:
					return TableOperations::renamingAttributes(evaluateExpression(atomicExpr), innerTokens);
		}
	}
	else
	{
			throw exception("Invalid syntax.");
		}
	}

	//Either need to evaluate as a literal, atomic expression, or operation
	else
	{
		vector<string> leftTokens;
		vector<string> rightTokens;

		//We know the expression is of the form literal op literal
		if (expr.size() == 3)
		{
			leftTokens.push_back(expr[0]);
			rightTokens.push_back(expr[2]);
		}
		else
		{
			//Need to parse the parens
			expr = parse_parens(expr);

			//If the size is not 3 after parsing, the expression must either be a literal or atomic expression
			if (expr.size() != 3)
			{
				//We should not have more than one token after parsing parens
				if (expr.size() != 1)
					throw exception("Invalid syntax.");

				//If the token is surrounded by parens, we know it is an atomic expression
				if (expr[0][0] == '(' && expr[0][expr[0].length() - 1] == ')')
				{
					expr[0] = remove_end_parens(expr[0]);
					expr = parse_parens(expr);
					return evaluateExpression(expr);
			}
				//Otherwise, we will simply treat it as a literal
				else
					return db.findTable(expr[0]);
			}

			//If we get here, we know it must be an operation. We must find out if either the left or right operand is an atomic expression
			//Atomic op atomic
			if ((expr[0][0] == '(' && expr[0][expr[0].size() - 1] == ')') && (expr[2][0] == '(' && expr[2][expr[2].size() - 1] == ')'))
			{
				expr[0] = remove_end_parens(expr[0]);
				expr[2] = remove_end_parens(expr[2]);

				istringstream iss(expr[0]);
				leftTokens = { istream_iterator<string>(iss), istream_iterator<string>() };

				istringstream iss1(expr[2]);
				rightTokens = { istream_iterator<string>(iss1), istream_iterator<string>() };
			}
			//Atomic op literal
			else if ((expr[0][0] == '(' && expr[0][expr[0].size() - 1] == ')') && (expr[2][0] != '(' && expr[2][expr[2].size() - 1] != ')'))
			{
				expr[0] = remove_end_parens(expr[0]);

				istringstream iss(expr[0]);
				leftTokens = { istream_iterator<string>(iss), istream_iterator<string>() };

				rightTokens.push_back(expr[2]);
			}
			//Literal op atomic
			else if ((expr[0][0] != '(' && expr[0][expr[0].size() - 1] != ')') && (expr[2][0] == '(' && expr[2][expr[2].size() - 1] == ')'))
			{
				expr[2] = remove_end_parens(expr[2]);

				leftTokens.push_back(expr[0]);

				istringstream iss(expr[2]);
				rightTokens = { istream_iterator<string>(iss), istream_iterator<string>() };
			}
			else
			{
				throw exception("Invalid syntax.");
			}
		}

		//Evaluate the operation
		if (expr.size() == 3)
		{
			if (expr[1].size() == 1) {
				switch (expr[1][0]) {
				case '+':
						return TableOperations::setUnion(evaluateExpression(leftTokens), evaluateExpression(rightTokens));
				case '-':
						return TableOperations::setDifference(evaluateExpression(leftTokens), evaluateExpression(rightTokens));
				case '*':
						return TableOperations::crossProduct(evaluateExpression(leftTokens), evaluateExpression(rightTokens));
				}
			}
			else if (expr[1] == "JOIN")
					return TableOperations::naturalJoin(evaluateExpression(leftTokens), evaluateExpression(rightTokens));
			else {
				//The user entered an unknown operator
				string error = "Unknown operator " + expr[1] + ".";
				throw exception(error.c_str());
			}
		}
		//We should not ever reach here
		throw exception("Invalid syntax.");
	}
	//Or here
	throw exception("Invalid syntax.");
}

Parser::Parser()
{
}


Parser::~Parser()
{
}

Database Parser::getDb()
{
	return db;
}

void Parser::evaluateStatement(string statement)
{
	if (statement.length() == 0)
		return;

	istringstream iss(statement);
	vector<string> tokens{ istream_iterator<string>(iss), istream_iterator<string>() };
	/*for (string line : parse_parens(tokens))
		cout << "[" << line << "] " << endl;*/
	bool isCommand = false;

	for (int i = 0; i < sizeof(COMMAND_NAMES) / sizeof(string); ++i)
	{
		isCommand = isCommand || tokens[0] == COMMAND_NAMES[i];
		if (isCommand) break;
	}

	if (isCommand)
		evaulateCommand(statement);
	else
		evaluateQuery(statement);
}

string Parser::remove_quotes(string s) {
	s.erase(remove(s.begin(), s.end(), '\"'), s.end());
	return s;
}

string Parser::remove_parens(string s) {
	s.erase(remove(s.begin(), s.end(), '('), s.end());
	s.erase(remove(s.begin(), s.end(), ')'), s.end());
	return s;
}

string Parser::remove_end_parens(string s) {
	if (s[0] == '(' && s[s.length() - 1] == ')')
	{
		s.erase(0, 1);
		s.erase(s.length() - 1, 1);
	}
	return s;
}

string Parser::remove_commas(string s) {
	s.erase(remove(s.begin(), s.end(), ','), s.end());
	return s;
}

int number_of_open_parens(string str){
	return count(str.begin(), str.end(), '(');
}

int number_of_close_parens(string str){
	return count(str.begin(), str.end(), ')');
}

// function returns vector with all things in parentheses in the same index
vector<string> Parser::parse_parens(vector<string> input) {
	vector<string> result;
	int count = 0;
	int pushback_index = 0;
	int end, opens, closes;
	int start = 0;
	int total = 0;
	for (size_t i = 0; i < input.size(); i++) {
		end = input[i].length() - 1;
		opens = number_of_open_parens(input[i]);
		closes = number_of_close_parens(input[i]);
		total += (opens - closes);

		if (total == 0 && (opens + closes) == 0)
			result.push_back(input[i]);

		else if (count == 0 && input[i][start] == '('){
			result.push_back(input[i]);
			pushback_index = result.size()-1;
		}
		
		else if (total == 0 && input[i][end] == ')')
			result[pushback_index] += (" " + input[i]);

		else if (total > 0)
			result[pushback_index] += (" " + input[i]);

		else if (total == 0 && opens == closes) 
			result.push_back(input[i]);
		
		count += opens;
		if (total == 0)
			count = 0;

	}
	if (count != 0)
		cout << "Error: Missmatched parentheses!\n";
	return result;
}
