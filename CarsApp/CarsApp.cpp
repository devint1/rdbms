#pragma once
#include "../RDBMS/Parser.h"

#include "../RDBMS/Database.h"
#include "../RDBMS/TableOperations.h"

int main(){
	
	/*
	
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
	db.openTable("makeLocations");

	TableOperations::setUnion(db.findTable("cars"), db.findTable("cars2"), "car_id");
	TableOperations::setDifference(db.findTable("cars"), db.findTable("cars2"), "car_id");
	TableOperations::setDifference(db.findTable("cars2"), db.findTable("cars2"), "car_id");
	TableOperations::setDifference(db.findTable("cars2"), db.findTable("cars"), "car_id");
	TableOperations::crossProduct(db.findTable("cars2"), db.findTable("cars"));

	string name1 = "Model";
	string name2 = "my_model";
	TableAttribute rename = TableOperations::project(db.findTable("cars"), name1);
	TableOperations::renamingAttributes(db.findTable("cars2"), name2, rename.getName());
	TableOperations::naturalJoin(db.findTable("students"), db.findTable("schoolLocations"));
	TableOperations::naturalJoin(db.findTable("cars"), db.findTable("makeLocations"));
	TableOperations::select("Model", db.findTable("cars"), "Make", "toyota");
	db.openTable("cars");
	
	system("PAUSE");*/
	
	Database db;
	db.openTable("cars");
	db.openTable("cars2");

	db.showTable(TableOperations::setDifference(db.findTable("cars2"), db.findTable("cars")));

	//TableOperations::setDifference(db.findTable("cars"), db.findTable("cars2"), "car_id");

	cout << "Welcome to the RDBMS interpreter." << endl;
	cout << ":: ";
	string statement;
	Parser parser;

	while (getline(cin, statement)) {
		try {
			parser.evaluateStatement(statement);
		}
		catch (exception e) {
			cerr << "ERROR: " << e.what() << endl;
		}
		catch (...) {
			cerr << "ERROR: Unknown error." << endl;
		}
		cout << endl << ":: ";
	}

	return 0;

}

