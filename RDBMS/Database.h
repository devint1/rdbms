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
	void closeTable(string tablename); //Corey
	void writeTable(string tablename); //Corey
	void showTable(string tablename); //Devin
	void showTable(Table table);
	void createTable(string name, vector<string> attributeNames, vector<string> dataTypeNames, vector<string> primaryKeyNames); //Devin
	void updateTable(string relationName, string attributeNameToChange, string valueToChange, string conditionAttributeName, string conditionValue); 	///MAKE SURE findtable() ACCOUNTS for not finding the relation/table used for argument.	   //Sergio
	void deleteFromTable(string name, string attributeName, string dataName); 
	void insertIntoTable(string tablename, vector<string> values); //Used in VALUES FROM (attr1, attr2, ...)
	void insertIntoTable(string tablename, Table relation); //Used in VALUES FROM RELATION
	bool tableExists(string name);
	void addTable(Table table);
	Table& findTable(string name); //Helper function that returns the index of a table with a given name
};
