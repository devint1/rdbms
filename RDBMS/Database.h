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
	//Update table
	void insertIntoTable(string tablename, string values[]);
	//Delete from table
	void exit();
};
