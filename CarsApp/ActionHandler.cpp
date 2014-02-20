#include "ActionHandler.h"
#include <iostream>

using namespace std;

Parser ActionHandler::parser;

void ActionHandler::init()
{
	parser.evaluateStatement("OPEN cars");
	parser.evaluateStatement("OPEN Make");
	parser.evaluateStatement("OPEN Model");
	parser.evaluateStatement("OPEN MakeLocation");
}

void ActionHandler::modifyCar()
{
	string carId;
	string choiceStr;
	string modifiedValue;

	cout << endl << "Car ID to modify: ";
	getline(cin, carId);

	cout << endl << "Select a value to modify:" << endl;
	cout << "1) Make" << endl;
	cout << "2) Model" << endl;
	cout << "3) Mpg" << endl << endl;
	cout << "Enter choice: ";
	getline(cin, choiceStr);

	switch (stoi(choiceStr))
	{
	case 1:
		cout << endl;
		parser.evaluateStatement("SHOW Make");
		cout << "Enter new ID: ";
		getline(cin, modifiedValue);
		parser.evaluateStatement("UPDATE cars SET (MakeID = " + modifiedValue + ") WHERE (CarID = " + carId + ")");
		break;
	case 2:
		cout << endl;
		parser.evaluateStatement("SHOW Model");
		cout << "Enter new ID: ";
		getline(cin, modifiedValue);
		parser.evaluateStatement("UPDATE cars SET (ModelID = " + modifiedValue + ") WHERE (CarID = " + carId + ")");
		break;
	case 3:
		cout << endl;
		cout << "Enter new value: ";
		getline(cin, modifiedValue);
		parser.evaluateStatement("UPDATE cars SET (Mpg = " + modifiedValue + ") WHERE (CarID = " + carId + ")");
		break;
	default:
		cerr << "ERROR: Invalid option." << endl;
		break;
	}
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