#pragma once


#include <string> 

using namespace std;

class TableAttribute
{

public:

	TableAttribute(string name, string type);
	~TableAttribute();

	string getName();
	string getType();

private:

	string name;
	string type;
};

