#pragma once

#include <string>
#include <vector>
#include "TableAttribute.h"
using namespace std;

class Table
{
public:
	Table(string name, vector<string> attributeNames, vector<string> dataTypeNames, vector<string> primaryKeyNames); //Used in CREATE: need to pass the relation-name, typed-attribute-list, and PRIMARY KEY attribute-list
	Table(string name, vector<TableAttribute> attributes, vector<string> primaryKeyNames);
	Table();

	Table(string tablename); //Used in OPEN (open from file)
	~Table();

	//Getters
	string getName();
	vector<TableAttribute> getAttributes();
	vector<string> getPrimaryKeys();
	vector< vector<string> > getTableData();

	void writeTable(); //Used in WRITE (write to file)
	void showTable(); //Used in SHOW (print to screen)
	void insert(vector<string> values); //Used in INSERT

	void deleteFromTable(string attributeName, string dataName);
	int findAttributebyName(string attributeName);//Sergio
	void changeAttributeName(string attributeName, string newAttributeName); //Sergio
	void update(int& changeAttributePos, int& conditionAttributePos, string& conditionAttributeData, string& changeAttributeData);  //Sergio  Used by Database Update.
private:
	string name;
	vector<string> primaryKeys;
	//Array of rows
	vector< vector<string> > tableData;

	//Array of attribute data types and names
	vector<TableAttribute> tableAttributes;

};
