#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Table.h"
#include <iostream>
#include <fstream>

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

void Table::writeTable(){

}
