#pragma once

#include <string>

using namespace std;

class Table
{
public:
	Table(string name, string attributeNames[], string dataTypeNames[], string primaryKeyNames[]); //Used in CREATE: need to pass the relation-name, typed-attribute-list, and PRIMARY KEY attribute-list
	Table();

	Table(string filename); //Used in OPEN (open from file)
	~Table();

	//Getters
	string getName();

	void writeTable(); //Used in WRITE (write to file)
private:
	string name;
	//Array of rows
	//Array of attribute names
	//Array of attribute data tyoes
	//Array of attribute properties (e.g., the length of a varchar or PRIMARY KEY)
};

