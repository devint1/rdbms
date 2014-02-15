#pragma once

#include "Database.h"

class Parser
{
private:
	Database db;

	const static string COMMAND_NAMES[];
	const enum command {open, close, write, exit, show, create, update, insert, del};

	//Helper Functions
	bool checkNumTokens(command cmd, int numTokens);
	vector<string> infixToPostfix(vector<string> infixTokens);

	void executeCreate(vector<string> tokens);
	void evaluateQuery(string query);
	void evaulateCommand(string command);
public:
	Parser();
	~Parser();

	Database getDb();

	void evaluateStatement(string statement);
};

