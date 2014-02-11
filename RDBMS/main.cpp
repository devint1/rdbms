// RDBMS.cpp : Defines the entry point for the console application.
//
#include "Database.h"
#include "TableOperations.h";
int main()
{
	Database db;
	db.openTable("cars");
	//db.UpdateTable("cars", "")
	vector<string> vals = { "646", "Lamborghini", "Gallardo", "11" };
	db.insertIntoTable("cars", vals);
	db.deleteFromTable("cars", "Make", "ford");
	db.updateTable("cars", "Model", "Celica", "Model", "corolla");
	vector<string> attNames = { "firstName", "lastName", "email", "cars" };
	vector<string> attTypes = { "varchar(255)", "varchar(255)", "varchar(255)", "varchar(255)" };
	vector<string> primKeys = { "email" };
	db.createTable("users", attNames, attTypes, primKeys);
	db.showTable("cars");
	db.showTable("users");
	db.writeTable("users");
	db.closeTable("users");
	db.openTable("cars2");
	db.openTable("students");
	db.openTable("schoolLocations");

	TableOperations::setUnion(db.findTable("cars"), db.findTable("cars2"), "car_id");
	TableOperations::setDifference(db.findTable("cars"), db.findTable("cars2"), "car_id");
	TableOperations::setDifference(db.findTable("cars2"), db.findTable("cars2"), "car_id");
	TableOperations::setDifference(db.findTable("cars2"), db.findTable("cars"), "car_id");
	TableOperations::naturalJoin(db.findTable("students"), db.findTable("schoolLocations"));
	
	system("PAUSE");
	return 0;
}

