#include <sstream>
#include <algorithm>
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
		/*case update:
			//Add implementation here
			break;*/
		/*case insert:
			//Add implementation here
			break;*/
		/*case del:
			//Add implementation here
			break;*/
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
	for (string line : parse_parens(tokens))
		cout << "[" << line << "] " << endl;
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

string Parser::remove_parens(string& s) {
	s.erase(remove(s.begin(), s.end(), '\"'), s.end());
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