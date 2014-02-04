#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <sstream>
#include "Table.h"

using namespace std;

class Database
{
private:
	vector<Table> tables;

public:
	Database();
	~Database();

	int findTableIndex(string name);
	void openTable(string filename);
	void closeTable(string tablename);
	void writeTable(string tablename);
	void showTable(string input);


};

