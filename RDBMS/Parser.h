#pragma once

#include "Database.h"

class Parser
{
private:
	Database db;

	const static string COMMAND_NAMES[];
	const enum command {open, close, write, exit, show, create, update, insert, del};

	bool checkNumTokens(command cmd, int numTokens);

	void executeCreate(vector<string> tokens);
	
	void evaluateQuery(string query);
	void evaulateCommand(string command);
	
public:
	Parser();
	~Parser();

	void evaluateStatement(string statement);
	string remove_parens(string& s);
	vector<string> parse_parens(vector<string> input);
};

