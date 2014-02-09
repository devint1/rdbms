#pragma once

#include <string>
#include <vector>
#include "TableAttribute.h"
using namespace std;

class Table
{
public:
	Table(string name, string attributeNames[], string dataTypeNames[], string primaryKeyNames[]); //Used in CREATE: need to pass the relation-name, typed-attribute-list, and PRIMARY KEY attribute-list
	Table();

	Table(string tablename); //Used in OPEN (open from file)
	~Table();

	//Getters
	string getName();

	void writeTable(); //Used in WRITE (write to file)
	void showTable(); //Used in SHOW (print to screen)
	void deleteFromTable(string attributeName, string dataName);
	int findAttributebyName(string attributeName);//Sergio
	void changeAttributeName(string attributeName, string newAttributeName); //Sergio

private:
	string name;
	vector<string> primaryKeys;
	//Array of rows
	vector< vector<string> > tableData;

	//Array of attribute data types and names
	vector<TableAttribute> tableAttributes;

};
