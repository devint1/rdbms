#include <sstream>
#include "Parser.h"

const string Parser::COMMAND_NAMES[] = {"OPEN", "CLOSE", "WRITE", "EXIT", "SHOW", "CREATE", "UPDATE", "INSERT", "DELETE"};

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
	if (tokens[0] != "TABLE") {
		cerr << "ERROR: Expected token \"TABLE\"" << endl;
		return;
	}
	string relationName = tokens[1];
	//Look for open parenthesis
	//Remember all of the attribute list
	//Look for closed parenthesis
	//Look for PRIMARY and KEY
	//Look for open parenthesis
	//Remember all of the primary keys
	//Look for closed parenthesis
}

void Parser::executeInsert(vector<string> tokens)
{
	if (tokens[0] != "INTO" || tokens[2] != "VALUES" || tokens[3] != "FROM")
		cerr << "Incorrect Input" << endl;
	string tablename = tokens[1];
	if (tokens[5] == "RELATION")
	{

	}

}

void Parser::evaluateQuery(string query)
{
	istringstream iss(query);
	vector<string> tokens{ istream_iterator<string>(iss), istream_iterator<string>() };
	bool isCommand = false;

	string relationName = tokens[0];

	if (tokens.size() <= 1)
	{
		cerr << "ERROR: Expected <-" << endl;
		return;
	}

	else if (tokens[1] != "<-") 
	{
		cerr << "ERROR: Expected <-" << endl;
		return;
	}

	cout << "Your input was interpreted as a query; queries are not yet implemented." << endl;
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
		try {
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
		case update:
			//not implemented
			break;
		case insert: {
			vector<string> insertTokens(tokens.begin() + 1, tokens.end());
			executeInsert(insertTokens);
			break;
		}
		case del:
			db.deleteFromTable(tokens[1], tokens[2], tokens[3]);
			break;
		default:
			cerr << "ERROR: Command not implemented." << endl;
		}
		}
		catch (exception e) {
			cerr << "ERROR: " << e.what() << endl;
		} 
		catch (...) {
			cerr << "ERROR: Unknown error." << endl;
	}
	}
 else
	cerr << "ERROR: Invalid syntax." << endl;
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
