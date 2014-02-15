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
	string remove_parens(string s);
	string remove_quotes(string s);
	string remove_commas(string s);
	vector<string> parse_parens(vector<string> input);

	//Executions
	void executeCreate(vector<string> tokens);
	void executeInsert(vector<string> tokens);
	void executeDelete(vector<string> tokens);

	//Evaluations
	void evaluateQuery(string query);
	void evaulateCommand(string command);
	
public:
	Parser();
	~Parser();

	Database getDb();

	//This is the main interface between the parser and external applications
	void evaluateStatement(string statement);
};

