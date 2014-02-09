#pragma once
#include <string>
#include <vector>
#include "Table.h"

using namespace std;

class Database
{
private:
	vector<Table> tables;

	Table findTable(string name); //Helper function that returns the index of a table with a given name
public:
	Database();
	~Database();

	void openTable(string filename);
	void closeTable(string tablename);
	void writeTable(string tablename); //Corey
	void showTable(string tablename); //Devin
	void createTable(string name, string attributeNames[], string dataTypeNames[], string primaryKeyNames[]); //Devin
	void UpdateTable(string relationName, string attributeName, string condition);
	//Update table // Sergio 
	//Insert into table
	//Delete from table
	void exit();
};
