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
		if (lineNumber == 0)
		for (size_t i = 0; i < tokens.size(); i+=2){
			tableAttributes.push_back(TableAttribute(tokens[i],tokens[i+1]));
		}
		else{
			for (size_t j = 0; j < tokens.size(); j += 2){
				tableData[lineNumber-1].push_back(tokens[j]);
			}
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
