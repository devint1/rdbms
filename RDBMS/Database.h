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
	void createTable(string name, vector<string> attributeNames, vector<string> dataTypeNames, vector<string> primaryKeyNames); //Devin
	void UpdateTable(string relationName, string attributeName, string condition);
	void deleteFromTable(string name, string attributeName, string dataName);
	void insertIntoTable(string tablename, vector<string> values);
	void exit();
};
