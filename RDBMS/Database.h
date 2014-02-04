#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <sstream>

using namespace std;

class Database
{
public:
	Database();
	~Database();

	
	void openTable(string filename);
};

