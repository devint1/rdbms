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
	void writeTable(string tablename);
	void showTable(string input);
	//Create table
	//Update table
	//Insert into table
	//Delete from table
	void exit();
};
