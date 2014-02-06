#include <fstream>
#include <iostream>
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

Table::Table(string filename)
{
	string line;
	ifstream myfile;
	int lineNumber = 0;
	myfile.open(filename.c_str());
	while (getline(myfile, line)){
		istringstream iss(line);
		vector<string> tokens{ istream_iterator<string>(iss), istream_iterator<string>() };
		cout << lineNumber << ": ";
		for (size_t i = 0; i < tokens.size(); i++){
			cout << tokens[i] << " ";
		}
		cout << endl;
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

void Table::writeTable()
{
	ofstream file;
	file.open(name+".db");
	for(int i=0;i<(int)tableAttributes.size();i++)
	{
		file<<tableAttributes[i].getName()<<" "<<tableAttributes[i].getType()<<"\t";
	}
	for(int i=0;i<(int)tableData.size();i++)
	{
		for(int j=0;j<(int)tableData[i].size();j++)
		{
			file<<tableData[i][j]<<"\t";
		}
		file<<"\n";
	}
}

void Table::showTable()
{
	for (int i = 0; i<(int)tableAttributes.size(); i++)
	{
		cout << tableAttributes[i].getName() << " " << tableAttributes[i].getType() << "\t";
	}
	for (int i = 0; i<(int)tableData.size(); i++)
	{
		for (int j = 0; j<(int)tableData[i].size(); j++)
		{
			cout << tableData[i][j] << "\t";
		}
		cout << "\n";
	}
}
