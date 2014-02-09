#pragma once

#include <iostream>
#include <string> 

using namespace std;

class TableAttribute
{

public:

	TableAttribute(string name, string type);
	~TableAttribute();

	string getName();
	string getType();

	void setName( string name);
	void setType( string type );

private:

	string name;
	string type;
};

