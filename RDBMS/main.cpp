// RDBMS.cpp : Defines the entry point for the console application.
//
#include "Database.h"

int main()
{
	Database db;
	db.openTable("cars.db");
	system("PAUSE");
	return 0;
}

