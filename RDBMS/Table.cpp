#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Table.h"


/*Table::Table()
{
}*/

Table::Table(string name, string attributeNames[], string dataTypeNames[], string primaryKeyNames[])
{

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
	for(int i=0;i<(int)TableAttributes.size();i++)
	{
		file<<TableAttributes[i].getName()<<" "<<TableAttributes[i].getType()<<"\t";
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
