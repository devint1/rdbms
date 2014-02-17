#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "Table.h"


/*Table::Table()
{
}*/

Table::Table(string name, vector<string> attributeNames, vector<string> dataTypeNames, vector<string> primaryKeyNames) : name(name)
{
	if (attributeNames.size() != dataTypeNames.size())
		throw "Number of attributes and number of datatypes do not match.";
	else { //If we get here, we know the arrays have the same size, so it does not matter which array we get the size of
		for (size_t i = 0; i < attributeNames.size(); ++i) {
			tableAttributes.push_back(TableAttribute(attributeNames[i], dataTypeNames[i]));
		}
	}
}

Table::Table(string name, vector<TableAttribute> attributes, vector<string> primaryKeyNames) : name(name), tableAttributes(attributes), primaryKeys(primaryKeyNames)
{

}

Table::Table(string tablename)
{
	name = tablename;
	string line;
	ifstream myfile;
	int lineNumber = 0;
	myfile.open((tablename + ".db").c_str());
	if (!myfile.is_open()) {
		throw exception("File not found.");
	}
	while (getline(myfile, line)){
		istringstream iss(line);
		vector<string> tokens{ istream_iterator<string>(iss), istream_iterator<string>() };
		if (lineNumber == 0)
		for (size_t i = 0; i < tokens.size(); i+=2){
			tableAttributes.push_back(TableAttribute(tokens[i],tokens[i+1]));
		}
		else{
			tableData.push_back(tokens);
		}
		lineNumber++;
	}
	myfile.close();
}


Table::~Table()
{
}

string Table::getName() {
	return name;
}

void Table::setName(string s)
{
	name = s;
}

void Table::addAttribute(vector<TableAttribute> attributes){
	for (size_t i = 0; i < attributes.size(); i++)
		tableAttributes.push_back(attributes[i]);
}

vector<TableAttribute> Table::getAttributes(){
	return tableAttributes;
}

vector<string> Table::getPrimaryKeys(){
	return primaryKeys;
}

vector< vector<string> > Table::getTableData(){
	return tableData;
}

void Table::appendToRow(int row, vector<string> additions){
	for (size_t i = 0; i < additions.size(); i++)
	{
		tableData[row].push_back(additions[i]);
	}
}

void Table::writeTable()
{
	ofstream file;
	file.open(name + ".db");
	for (int i = 0; i < (int)tableAttributes.size(); i++)
	{
		file << tableAttributes[i].getName() << " " << tableAttributes[i].getType() << "\t";
	}
	file << endl;
	for (int i = 0; i < (int)tableData.size(); i++)
	{
		for (int j = 0; j < (int)tableData[i].size(); j++)
		{
			file << tableData[i][j] << "\t";
		}
		file << "\n";
	}
	file.close();
}

void Table::showTable()
{
	const int COL_WIDTH = 15;
	for (int i = 0; i < (int)tableAttributes.size(); ++i)
	{
		cout << setw(COL_WIDTH) << tableAttributes[i].getName();
	}
	cout << endl;
	for (int i = 0; i < (int)tableAttributes.size(); ++i)
	{
		cout << setw(COL_WIDTH) << tableAttributes[i].getType();
	}
	cout << endl;
	for (size_t i = 0; i < tableAttributes.size(); ++i)
	{
		for (int j = 0; j <= COL_WIDTH - 1; ++j)
		{
			cout << "=";
		}
	}
	cout << endl;
	for (int i = 0; i<(int)tableData.size(); i++)
	{
		for (int j = 0; j<(int)tableData[i].size(); j++)
		{
			cout << setw(COL_WIDTH) << tableData[i][j];
		}
		cout << "\n";
	}
	cout << endl;
}

void Table::insert(vector<string> values)
{
	if (values.size() == tableAttributes.size())
	{
		vector<string> vec;
		for (size_t i = 0; i < values.size(); ++i) {
			vec.push_back(values[i]);
		}
		tableData.push_back(vec);
	}
	else
	{
		throw "Number of inserted values does not match number of columns.";
	}
}

int Table::findAttributebyName(string attributeName)
{
	int position = 0;
	vector<TableAttribute>::iterator it = tableAttributes.begin();

	if (it != tableAttributes.end())		 //Checks if vector is not empty first. If it is, thus the name was not found and retunrs -1
	{
		for (it = tableAttributes.begin(); it != tableAttributes.end(); it++)
		{
			string indexedAttributeName = (*it).getName();

			if (attributeName == indexedAttributeName)
				return position;

			position++;
		}
	}
	return -1;
}

void Table::changeAttributeName(string attributeName, string newAttributeName)
{
	for (size_t i = 0; i < tableAttributes.size(); ++i) {
		if (tableAttributes[i].getName() == attributeName) {
			tableAttributes[i].setName(newAttributeName);
		}
	}
}

void Table::deleteFromTable(string attributeName, string dataName)
{
	int attributeIndex;
	for (int i = 0; i<(int)tableAttributes.size(); i++)
	{
		if (tableAttributes[i].getName() == attributeName) 
		{
			attributeIndex = i;
			break;
		}
	}
	for (int i = 0; i<(int)tableData.size(); i++)
	{
		if (tableData[i][attributeIndex] == dataName)
			tableData.erase(tableData.begin() + i);
	}
}

void Table::update(int& changeAttributePos, int& conditionAttributePos, string& conditionAttributeData, string& changeAttributeData)
{
	if ( (conditionAttributePos != -1) && (changeAttributePos != -1) ) //-1 Means attribute was not found
	{
		for (size_t i = 0; i < tableData.size(); i++)
		{
			if (tableData[i][conditionAttributePos] == conditionAttributeData)
			{
				tableData[i][changeAttributePos] = changeAttributeData;
			}
		}
	}
}
