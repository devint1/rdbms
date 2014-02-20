#include "ActionHandler.h"
#include <iostream>

using namespace std;

Parser ActionHandler::parser;

void ActionHandler::init()
{
	parser.evaluateStatement("OPEN MakeLocation");
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

void ActionHandler::modifyCarLocation()
{
	string locID;
	string locName;
	cout << "Please enter location ID: ";
	cin >> locID;
	cout << "Now enter new location name: ";
	cin >> locName;
	parser.evaluateStatement("UPDATE MakeLocation SET (Location = " + locName + ") WHERE (LocationID = " + locID + ")");

}