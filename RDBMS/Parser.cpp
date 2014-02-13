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
	cout << "Create command is not yet implemented." << endl;
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
 else
	cerr << "ERROR: Invalid syntax." << endl;
}

Parser::Parser()
{
}


Parser::~Parser()
{
}

void Parser::evaluateStatement(string statement)
{
	istringstream iss(statement);
	vector<string> tokens{ istream_iterator<string>(iss), istream_iterator<string>() };
	bool isCommand = false;

	for (int i = 0; i < sizeof(COMMAND_NAMES) / sizeof(string); ++i)
	{
		isCommand = isCommand || tokens[0] == COMMAND_NAMES[i];
	}

	if (isCommand)
		evaulateCommand(statement);
	else
		evaluateQuery(statement);
}
