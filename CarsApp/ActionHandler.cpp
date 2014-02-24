#include "ActionHandler.h"
#include <iostream>
#include <algorithm>

using namespace std;

Parser ActionHandler::parser;


// ----------------------Helper Functions-----------------------
bool isNumber(const string s)
{
	for (size_t i = 0; i < s.size(); i++){
		if (!isdigit(s[i]))
			return false;
	}
	return true;
}

string toLower(const string s){
	string data = s;
	transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}


// ------------------Action Handler Functions------------------
void ActionHandler::init()
{
	parser.evaluateStatement("OPEN cars");
	parser.evaluateStatement("OPEN Make");
	parser.evaluateStatement("OPEN Model");
	parser.evaluateStatement("OPEN User");
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

void ActionHandler::addCar(){
	Database db = parser.getDb();
	vector< vector<string> > carData = db.findTable("cars").getTableData();
	vector< vector<string> > modelData = db.findTable("Model").getTableData();
	vector< vector<string> > makeData = db.findTable("Make").getTableData();

	int carID1 = stoi(carData[carData.size() - 1][0]) + 1;
	string carID = to_string(carID1);
	string MakeID, MakeName, ModelID, ModelName, Mpg;
	MakeID = "-1";
	ModelID = "-1";

	cout << "Enter car Make: ";
	cin >> MakeName;
	
	Table makes = db.findTable("Make");
	for (size_t i = 0; i < makes.getTableData().size(); i++){
		if (toLower(makes.getTableData()[i][1]) == toLower(MakeName)){
			MakeID = makes.getTableData()[i][0];
			break;
		}
	}
	if (MakeID == "-1"){
		int makeID1 = stoi(makeData[makeData.size() - 1][0]) + 1;
		MakeID = to_string(makeID1);
		parser.evaluateStatement("INSERT INTO Make VALUES FROM (" + MakeID + ", " + MakeName + ")");
	}

	cout << "Enter car Model: ";
	cin >> ModelName;

	Table models = db.findTable("Model");
	for (size_t i = 0; i < models.getTableData().size(); i++){
		if (toLower(models.getTableData()[i][1]) == toLower(ModelName)){
			ModelID = models.getTableData()[i][0];
			break;
		}
	}

	if (ModelID == "-1"){
		int modelID1 = stoi(modelData[modelData.size() - 1][0]) + 1;
		ModelID = to_string(modelID1);
		parser.evaluateStatement("INSERT INTO Model VALUES FROM (" + ModelID + ", " + ModelName + ")");
	}

	cout << "Enter car Mpg: ";
	cin >> Mpg;
	
	if (!isNumber(Mpg)){
		throw exception("Invalid Mpg (non-numeric)");
		return;
	}
	
	parser.evaluateStatement("INSERT INTO cars VALUES FROM (" + carID + ", " + MakeID + ", " + ModelID + ", " + Mpg + ")");
	cout << "Make: " + MakeName + "   Model: " + ModelName + " Added to database." << endl;
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

void ActionHandler::listLocations()
{
	parser.evaluateStatement("temp <- MakeLocation JOIN (rename (MakeID, Make) Make)");
	parser.evaluateStatement("temp <- project (Make, Location) temp");
	parser.evaluateStatement("SHOW temp");
}

void ActionHandler::addLocation()
{
	Database db = parser.getDb();
	string make;
	int	makeTableNamePos;
	int makeTableMakeIDPos;
	string makeID;
	vector< vector<string> >makeData;

	cout << "Please input the Make of the car you want to change a location for: " << endl;
	cin >> make;

	makeTableNamePos = db.findTable("Make").findAttributebyName("Name");
	makeTableMakeIDPos = db.findTable("Make").findAttributebyName("MakeID");

	makeData = db.findTable("Make").getTableData();

	for (size_t i = 0; i < makeData.size(); i++)
	{
		if (makeData[makeTableNamePos][i] == make)
		{
			makeID = makeData[makeTableMakeIDPos][i];
		}
		else
		{
			makeID = "NoMakeFound";
		}
	}

	if (makeID == "NoMakeFound")
	{
		cout << "No such make was found!" << endl;
	}
	else
	{
		//Check if make Id is in MakeLocation.db, if so, just modify the location, if not, add it completely.
		//parser.evaluateStatement("INSERT ");
	}


}

void ActionHandler::showUsers(){
	parser.evaluateStatement("SHOW User");
}

void ActionHandler::deleteUser(){
	Database db = parser.getDb();
	string username = "-1";
	cout << "Enter Username to be deleted: ";
	cin >> username;

	parser.evaluateStatement("DELETE FROM User WHERE Username == " + username);
}

void ActionHandler::listAllCarLocations(){
	parser.evaluateStatement("temp <- (cars JOIN (rename (MakeID, Make) Make)) JOIN (rename (ModelID, Model) Model)");
	parser.evaluateStatement("temp <- project (CarID, Make, Model, Mpg, Location) (temp JOIN MakeLocation)");
	parser.evaluateStatement("SHOW temp");
}