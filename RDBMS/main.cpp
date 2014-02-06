// RDBMS.cpp : Defines the entry point for the console application.
//
#include "Database.h"

int main()
{
	Database db;
	db.openTable("cars");
	db.showTable("cars");
	system("PAUSE");
	return 0;
}

