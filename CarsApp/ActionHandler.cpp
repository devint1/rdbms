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

void ActionHandler::modifyUser()
{
	string userID;
	string choice;
	string newinput;
	cout << "Enter user ID: ";
	cin >> userID;

	cout << endl << "Select a value to modify:" << endl;
	cout << "1) Username" << endl;
	cout << "2) Firstname" << endl;
	cout << "3) Lastname" << endl;
	cout << "4) Email" << endl << endl;
	cout << "Enter choice: ";
	cin >> choice;
	switch (stoi(choice))
	{
	case 1:
		cout << "Enter new Username: ";
		cin >> newinput;
		parser.evaluateStatement("UPDATE User SET (Username = " + newinput + ") WHERE (UserID = " + userID + ")");
		break;
	case 2:
		cout << "Enter new Firstname: ";
		cin >> newinput;
		parser.evaluateStatement("UPDATE User SET (Firstname = " + newinput + ") WHERE (UserID = " + userID + ")");
		break;
	case 3:
		cout << "Enter new Lastname: ";
		cin >> newinput;
		parser.evaluateStatement("UPDATE User SET (Lastname = " + newinput + ") WHERE (UserID = " + userID + ")");
		break;
	case 4:
		cout << "Enter new Email: ";
		cin >> newinput;
		parser.evaluateStatement("UPDATE User SET (Email = " + newinput + ") WHERE (UserID = " + userID + ")");
		break;
	default:
		cerr << "ERROR: Invalid option." << endl;
		break;
	}


}

void ActionHandler::deleteCar()
{
	string carId;

	cout << endl << "Enter car ID to delete: ";
	getline(cin, carId);
	parser.evaluateStatement("DELETE FROM cars WHERE CarID = " + carId + "");
}

void ActionHandler::listAllCars()
{
	parser.evaluateStatement("temp <- (cars JOIN (rename (MakeID, Make) Make)) JOIN (rename (ModelID, Model) Model)");
	parser.evaluateStatement("temp <- project (CarID, Make, Model, Mpg) temp");
	parser.evaluateStatement("SHOW temp");
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

void ActionHandler::listAllCarLocations()
{
	parser.evaluateStatement("temp1 <- project (Location) MakeLocation");
	parser.evaluateStatement("temp2 <- (project (Name) Make) JOIN temp1");
	parser.evaluateStatement("SHOW temp2");
}