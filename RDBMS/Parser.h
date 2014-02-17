#pragma once

#include "Database.h"

class Parser
{
private:
	Database db;

	const static string COMMAND_NAMES[];
	const static string EXPRESSION_KEYWORD_NAMES[];
	const enum command {open, close, write, exit, show, create, update, insert, del};
	const enum exprKeyword {select, project, rename};

	//Helper Functions
	bool checkNumTokens(command cmd, int numTokens);
	string remove_parens(string s);
	string remove_end_parens(string s);
	string remove_quotes(string s);
	string remove_commas(string s);
	vector<string> parse_parens(vector<string> input);

	//Executions
	void executeCreate(vector<string> tokens);
	void executeInsert(vector<string> tokens);
	void executeDelete(vector<string> tokens);
	void executeUpdate(vector<string> tokens);
	Table executeProject(vector<string> attributeNames, vector<string> expr);

	//Evaluations
	void evaluateQuery(string query);
	void evaulateCommand(string command);
	Table evaluateExpression(vector<string> expr);
	Table evaluateSelect(vector<string> expr);
public:
	Parser();
	~Parser();

	Database getDb();

	//This is the main interface between the parser and external applications
	void evaluateStatement(string statement);
};
