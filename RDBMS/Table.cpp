#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "Table.h"


/*Table::Table()
{
}*/

Table::Table(string name, string attributeNames[], string dataTypeNames[], string primaryKeyNames[]) : name(name)
{
	if (sizeof(attributeNames) != sizeof(dataTypeNames))
		throw "Number of attributes and number of datatypes do not match.";
	else { //If we get here, we know the arrays have the same size, so it does not matter which array we get the size of
		int numAttributes = sizeof(attributeNames) / sizeof(string);
		for (int i = 0; i < numAttributes; ++i) {
			tableAttributes.push_back(TableAttribute(attributeNames[i], dataTypeNames[i]));
		}
	}
}

Table::Table(string tablename)
{
	name = tablename;
	string line;
	ifstream myfile;
	int lineNumber = 0;
	myfile.open((tablename + ".db").c_str());
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

vector<TableAttribute> Table::getAttributes(){
	return tableAttributes;
}

vector<string> Table::getPrimaryKeys(){
	return primaryKeys;
}

void Table::writeTable()
{
	ofstream file;
	file.open(name + ".db");
	for (int i = 0; i < (int)tableAttributes.size(); i++)
	{
		file << tableAttributes[i].getName() << " " << tableAttributes[i].getType() << "\t";
	}
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
	for (int i = 0; i < tableAttributes.size(); ++i)
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
}

void Table::insert(string values[])
{
	int numValues = sizeof(values) / sizeof(string);
	if (numValues == tableAttributes.size())
	{
		vector<string> vec;
		for (int i = 0; i < numValues; ++i) {
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
		{
			return position;
		}
		else
		{
			position++;
		}
	}
}
	else
	{
		return -1;
	}
}

void Table::changeAttributeName(string attributeName, string newAttributeName)
{
	for (vector<TableAttribute>::iterator it = tableAttributes.begin(); it != tableAttributes.end(); it++)
	{
		string indexedAttributeName = (*it).getName();

		if (attributeName == indexedAttributeName)
		{
			(*it).setName(newAttributeName);
		}
		else{}
	}
}

void Table::deleteFromTable(string attributeName, string dataName)
{
	int attributeIndex;
	for (int i = 0; i<(int)tableAttributes.size(); i++)
	{
		if (tableAttributes[i].getName() == attributeName)
			attributeIndex = i;
	}
	for (int i = 0; i<(int)tableData.size(); i++)
	{
		if (tableData[i][attributeIndex] == dataName)
			tableData[i][attributeIndex].clear();
	}
}

