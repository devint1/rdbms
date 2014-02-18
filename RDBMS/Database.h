#pragma once
#include <string>
#include <vector>
#include "Table.h"

using namespace std;

class Database
{
private:
	vector<Table> tables;


public:
	Database();
	~Database();

	void openTable(string filename);
	void closeTable(string tablename);
	void writeTable(string tablename);
	void showTable(string tablename);
	void showTable(Table table);
	void createTable(string name, vector<string> attributeNames, vector<string> dataTypeNames, vector<string> primaryKeyNames);
	void updateTable(string relationName, string attributeNameToChange, string valueToChange, string conditionAttributeName, string conditionValue);
	void deleteFromTable(string name, string attributeName, string dataName);
	//Used in VALUES FROM (attr1, attr2, ...)
	void insertIntoTable(string tablename, vector<string> values);
	//Used in VALUES FROM RELATION
	void insertIntoTable(string tablename, Table relation);
	bool tableExists(string name);
	void addTable(Table table);
	//Helper function that returns the index of a table with a given name
	Table& findTable(string name);
};
