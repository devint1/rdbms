#pragma once
#include <string>
#include <vector>
#include "Table.h"

using namespace std;

class Database
{
private:
	vector<Table> tables;

	Table& findTable(string name); //Helper function that returns the index of a table with a given name
public:
	Database();
	~Database();

	void openTable(string filename); //WORKS
	void closeTable(string tablename); //Corey WORKS
	void writeTable(string tablename); //Corey WORKS
	void showTable(string tablename); //Devin WORKS
	void createTable(string name, vector<string> attributeNames, vector<string> dataTypeNames, vector<string> primaryKeyNames); //Devin WORKS
	void updateTable(string relationName, string attributeNameToChange, string valueToChange, string conditionAttributeName, string conditionValue); 	///MAKE SURE findtable() ACCOUNTS for not finding the relation/table used for argument.	   //Sergio
	void deleteFromTable(string name, string attributeName, string dataName); //WORKS
	void insertIntoTable(string tablename, vector<string> values); //WORKS
	void exit();
};
