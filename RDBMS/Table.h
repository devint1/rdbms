#pragma once

#include <string>
#include <vector>
#include "TableAttribute.h"
using namespace std;

class Table
{
public:
	//Used in CREATE: need to pass the relation-name, typed-attribute-list, and PRIMARY KEY attribute-list
	Table(string name, vector<string> attributeNames, vector<string> dataTypeNames, vector<string> primaryKeyNames);
	Table(string name, vector<TableAttribute> attributes, vector<string> primaryKeyNames);
	Table();

	//Used in OPEN (open from file)
	Table(string tablename); 
	~Table();

	//Getters
	string getName();
	void setName(string s);
	vector<TableAttribute>& getAttributes();
	vector<string> getPrimaryKeys();
	vector< vector<string> > getTableData();
	void appendToRow(int row, vector<string> additions);
	void addAttribute(vector<TableAttribute> attributes);

	//Used in WRITE (write to file)
	void writeTable(); 
	//Used in SHOW (print to screen)
	void showTable(); 
	//Used in INSERT
	void insert(vector<string> values); 

	void deleteFromTable(string attributeName, string dataName);
	int findAttributebyName(string attributeName);
	void changeAttributeName(string attributeName, string newAttributeName);

	//Used by Database Update.
	void update(int& changeAttributePos, int& conditionAttributePos, string& conditionAttributeData, string& changeAttributeData); 
private:
	string name;
	vector<string> primaryKeys;
	//Array of rows
	vector< vector<string> > tableData;

	//Array of attribute data types and names
	vector<TableAttribute> tableAttributes;

};
