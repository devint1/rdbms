#include <sstream>
#include <algorithm>
#include <stack>
#include "Parser.h"

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

vector<string> Parser::infixToPostfix(vector<string> infixTokens)
{
	stack<string> opStack;
	vector<string> postfixTokens;
	const string OPERATORS[] = {"||", "&&", "==", "!=", "<", ">", "<=", ">="};
	const int PRECEDENCE[] = {1,1,0,0,0,0,0,0}; //Larger numbers mean higher precedence

	for (string token : infixTokens)
	{
		bool isOperator = false;

		for (int i = 0; i < sizeof(OPERATORS) / sizeof(string); ++i)
		{
			if (token == OPERATORS[i])
			{
				isOperator = true;
				break;
			}
		}

		if (isOperator)
		{
			string lastOp;

			if(!opStack.empty())
				lastOp = opStack.top();

			int lastOpPrecedence = INT_MIN;
			int currentOpPrecedence = INT_MIN;

			for (int i = 0; i < sizeof(OPERATORS) / sizeof(string); ++i)
			{
				if (OPERATORS[i] == lastOp)
					lastOpPrecedence = PRECEDENCE[i];
				if (OPERATORS[i] == token)
					currentOpPrecedence = PRECEDENCE[i];
			}

			if (lastOpPrecedence < currentOpPrecedence)
			{
				opStack.push(token);
			}
			else
			{
				bool checkOpStack = true;
				do
				{
					postfixTokens.push_back(opStack.top());
					opStack.pop();

					int nextOpPrecedence = INT_MIN;
					for (int i = 0; i < sizeof(OPERATORS) / sizeof(string) && !opStack.empty(); ++i)
					{
						if (OPERATORS[i] == opStack.top())
							nextOpPrecedence = PRECEDENCE[i];
					}

					checkOpStack = nextOpPrecedence >= currentOpPrecedence;
				} while (checkOpStack);

				opStack.push(token);
			}
		}
		else
		{
			postfixTokens.push_back(token);
		}
	}

	while (!opStack.empty())
	{
		postfixTokens.push_back(opStack.top());
		opStack.pop();
	}

	return postfixTokens;
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

	for (int i = 0; i < attributeTokens.size(); i += 2)
	{
		attributeNames.push_back(attributeTokens[i]);
		attributeTypes.push_back(attributeTokens[i + 1]);
	}

	db.createTable(relationName, attributeNames, attributeTypes, keyTokens);
}

void Parser::executeInsert(vector<string> tokens)
{
	if (tokens[0] != "INTO" || tokens[2] != "VALUES" || tokens[3] != "FROM")
		cerr << "Incorrect Input" << endl;
	//if (tokens[5] == "RELATION")
	//{
	//	// DO other thing
	//
	//}

	if (tokens.size() != 5)
		cerr << "Incorrect Input" << endl;

	string tableName = tokens[1];

	istringstream iss(tokens[4]);
	vector<string> values{ istream_iterator<string>(iss), istream_iterator<string>() };
	values[0] = remove_parens(values[0]);
	values[values.size() - 1] = remove_parens(values[values.size() - 1]);

	vector<string> newEntry;
	cerr << "ERROR: Incorrect Input" << endl;
	string tablename = tokens[1];

	if (tokens[5] == "RELATION"){}

	for (size_t i = 0; i < values.size(); i++){
		values[i] = remove_commas(values[i]);
		newEntry.push_back(values[i]);
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

void Parser::evaluateQuery(string query)
{
	istringstream iss(query);
	vector<string> tokens{ istream_iterator<string>(iss), istream_iterator<string>() };

	string relationName = tokens[0];

	infixToPostfix(tokens);

	if (tokens.size() < 3)
	{
		cerr << "ERROR: Expected <-" << endl;
		return;
	}

	else if (tokens[1] != "<-") 
	{
		cerr << "ERROR: Expected <-" << endl;
		return;
	}
	if (db.tableExists(relationName)){
		char choice = ' ';
		cout << "\nNotice: query operation will overwrite " << relationName << ", continue? (y/n)\n> ";
		cin >> choice;
		if (choice == 'n' || choice == 'N')
			return;
		else{
			//result = db.findTable(relationName);
		}
	}

	vector<string> forward;
	for (size_t i = 2; i < tokens.size(); i++)
		forward.push_back(tokens[i]);

	Table result = evaluateExpression(forward);

	cout << "Query completed" << endl;
}

void Parser::evaulateCommand(string command)
{
	istringstream iss(command);
	vector<string> tokens{ istream_iterator<string>(iss), istream_iterator<string>() };
	bool isCommand = false;
	Parser::command cmd;

	for (int i = 0; i < sizeof(COMMAND_NAMES) / sizeof(string); ++i) {
		if (tokens[0] == COMMAND_NAMES[i]) {
			cmd = (Parser::command) i;
			break;
		}
	}

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
	cerr << "ERROR: Invalid syntax." << endl;
}

Table Parser::evaluateExpression(vector<string> expr)
{
	Table result("cars");

	for (int i = 0; i < sizeof(EXPRESSION_KEYWORD_NAMES) / sizeof(string); ++i)
	{
		if (expr[0] == EXPRESSION_KEYWORD_NAMES[i])
		{
			
		}
	}

	return result;
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
