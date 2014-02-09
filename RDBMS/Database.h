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

	void openTable(string filename);
	void closeTable(string tablename); //Corey
	void writeTable(string tablename); //Corey
	void showTable(string tablename); //Devin
	void createTable(string name, string attributeNames[], string dataTypeNames[], string primaryKeyNames[]); //Devin
	void UpdateTable(string relationName, string attributeName1, string attributeData1, string conditionAttributeName, string condition); 	///MAKE SURE findtable() ACCOUNTS for not finding the relation/table used for argument.	   //Sergio

	//Insert into tab
	void deleteFromTable(string name, string attributeName, string dataName);

	//Update table
	void insertIntoTable(string tablename, string values[]);
	//Delete from table
	void exit();
};
