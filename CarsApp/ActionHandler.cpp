#include "ActionHandler.h"
#include <iostream>

using namespace std;

Parser ActionHandler::parser;

void ActionHandler::init()
{
	
}

void ActionHandler::startInterpreter()
{
	cout << "Welcome to the RDBMS interpreter." << endl;
	cout << ":: ";

	string statement;

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
}

void ActionHandler::addCar(){
	Database db = parser.getDb();
	vector< vector<string> > carData = db.findTable("cars").getTableData();
	string carID = (carData[carData.size-1][0])+1;
	string MakeID, ModelID, Mpg;
	cout << "Enter car Make: " << endl;
	cin >> MakeID;

	Table make = db.findTable("Make"); 
	

	cout << "Enter Make Id" << endl;
}