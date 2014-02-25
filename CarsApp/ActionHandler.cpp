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
	parser.evaluateStatement("OPEN Cart");
	parser.evaluateStatement("OPEN MakeLocation");
}

void ActionHandler::ownerCombination()
{
	/*Database db = parser.getDb();
	Table user = db.findTable("User");
	Table cars = db.findTable("Model");	   */

	//Table crossProd = user.getTableData * cars;	
	parser.evaluateStatement("temp <- user * cars");
	//parser.evaluateStatement("temp <- Model JOIN  temp");
	//parser.evaluateStatement("temp <- project (Make, Location) temp");
	parser.evaluateStatement("SHOW temp");


	/*parser.evaluateStatement("temp1 <- JOIN (Username) Users");
	parser.evaluateStatement("temp2 <- (project (Name) Model) JOIN temp1");
	parser.evaluateStatement("SHOW temp2");			*/

}

void ActionHandler::modifyCar()
{
	string carId;
	string choiceStr;
	string modifiedValue;

	listAllCars();

	cout << endl << "Car ID to modify: ";
	cin >> carId;

	cout << endl << "Select a value to modify:" << endl;
	cout << "1) Make" << endl;
	cout << "2) Model" << endl;
	cout << "3) Mpg" << endl << endl;
	cout << "Enter choice: ";
	cin >> choiceStr;

	switch (stoi(choiceStr))
	{
	case 1:
		cout << endl;
		parser.evaluateStatement("SHOW Make");
		cout << "Enter new ID: ";
		cin >> modifiedValue;
		parser.evaluateStatement("UPDATE cars SET (MakeID = " + modifiedValue + ") WHERE (CarID = " + carId + ")");
		break;
	case 2:
		cout << endl;
		parser.evaluateStatement("SHOW Model");
		cout << "Enter new ID: ";
		cin >> modifiedValue;
		parser.evaluateStatement("UPDATE cars SET (ModelID = " + modifiedValue + ") WHERE (CarID = " + carId + ")");
		break;
	case 3:
		cout << endl;
		cout << "Enter new value: ";
		cin >> modifiedValue;
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
		parser.evaluateStatement("UPDATE User SET (Username = " + newinput + ") WHERE (UserId = " + userID + ")");
		break;
	case 2:
		cout << "Enter new Firstname: ";
		cin >> newinput;
		parser.evaluateStatement("UPDATE User SET (Firstname = " + newinput + ") WHERE (UserId = " + userID + ")");
		break;
	case 3:
		cout << "Enter new Lastname: ";
		cin >> newinput;
		parser.evaluateStatement("UPDATE User SET (Lastname = " + newinput + ") WHERE (UserId = " + userID + ")");
		break;
	case 4:
		cout << "Enter new Email: ";
		cin >> newinput;
		parser.evaluateStatement("UPDATE User SET (email = " + newinput + ") WHERE (UserId = " + userID + ")");
		break;
	default:
		cerr << "ERROR: Invalid option." << endl;
		break;
	}


}

void ActionHandler::deleteCar()
{
	listAllCars();
	string carId;

	cout << endl << "Enter car ID to delete: ";
	cin >> carId;
	parser.evaluateStatement("DELETE FROM cars WHERE CarID = " + carId);
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
	string location;
	string MakeID;
	bool makeIDFound = false;
	vector< vector<string> >makeData;

	cout << "Please input the Make of the car you want to add a location for: " << endl;
	cin >> make;
	cout << endl;

	makeData = db.findTable("Make").getTableData();

	Table makes = db.findTable("Make");
	for (size_t i = 0; i < makes.getTableData().size(); i++)
	{
		if (toLower(makes.getTableData()[i][1]) == toLower(make))
	{
			MakeID = makes.getTableData()[i][0];
			makeIDFound = true;
			break;
		}
	}
		if (makeIDFound == false)
		{
			cout << "Make not found!" << endl;
		}

		else
		{

			Table makeLoc = db.findTable("MakeLocation");
			for (size_t i = 0; i < makeLoc.getTableData().size(); i++)
	{
				if (toLower(makes.getTableData()[i][0]) == toLower(MakeID))
				{
					cout << "Please input the new Location desired: " << endl;
					cin >> location;
					parser.evaluateStatement("UPDATE MakeLocation SET (Location = " + location + ") WHERE (MakeID = " + MakeID + ")");
	}
	else
	{
		cout << "Please input the new Location desired: " << endl;
		cin >> location;
		cout << endl;

					int locationID1 = stoi(makeData[makeData.size() - 1][0]) + 1;
					string locationID2 = to_string(locationID1);
					parser.evaluateStatement("INSERT INTO MakeLocation VALUES FROM (" + locationID2 + ", " + MakeID + ", " + location + ")");
					break;
			}
		}
	}
}

void ActionHandler::showUsers(){
	parser.evaluateStatement("SHOW User");
}

void ActionHandler::deleteUser(){
	Database db = parser.getDb();
	string username = "-1";
	
	cout << endl;
	cout << "Enter Username to be deleted: ";
	cin >> username;

	parser.evaluateStatement("DELETE FROM User WHERE Username == " + username);
}

void ActionHandler::listAllCarLocations(){
	parser.evaluateStatement("temp <- (cars JOIN (rename (MakeID, Make) Make)) JOIN (rename (ModelID, Model) Model)");
	parser.evaluateStatement("temp <- project (CarID, Make, Model, Mpg, Location) (temp JOIN MakeLocation)");
	parser.evaluateStatement("SHOW temp");
}

void ActionHandler::deleteLocation()
{
	Database db = parser.getDb();
	string make;

	int	makeTableNamePos;
	int makeTableMakeIDPos;
	int makeLocationTableLocPos;
	int makeLocationTableMakeIDPos;
	string makeID = "NoMakeFound";
	vector< vector<string> >makeData;
	vector< vector<string> >makeLocationData;

	listLocations();

	cout << "Please input the Make of the car you want to delete the location for: ";
	cin >> make;
	cout << endl;

	makeTableNamePos = db.findTable("Make").findAttributebyName("Name");
	makeTableMakeIDPos = db.findTable("Make").findAttributebyName("MakeID");
	makeLocationTableLocPos = db.findTable("MakeLocation").findAttributebyName("Location");
	makeLocationTableMakeIDPos = db.findTable("MakeLocation").findAttributebyName("MakeID");

	makeData = db.findTable("Make").getTableData();
	makeLocationData = db.findTable("MakeLocation").getTableData();

	for (size_t i = 0; i < makeData.size(); i++){
		if (toLower(makeData[i][1]) == toLower(make)){
			makeID = makeData[i][0];
			break;
		}
	}

	if (makeID == "NoMakeFound")
		cout << "No such make was found!" << endl;
	else
		parser.evaluateStatement("DELETE FROM MakeLocation WHERE MakeID == " + makeID);	

	cout << make + " Removed from MakeLocation table" << endl;
}

void ActionHandler::findCars()
{
	int makeOrModel = 0;
	string model;
	string make;

	cout << "Do you want to find a car by model or make?" << endl << endl;
	cout << "Please input 1 to find a car by model and 2 to find a cars of a given make" << endl << endl;

	cin >> makeOrModel;
	cout << endl;

	if (makeOrModel == 1 || makeOrModel == 2)
	{
		if (makeOrModel == 1)
		{
			cout << "Please input the model of the car you want to be shown: ";
			cin >> model;
			cout << endl << endl;

			parser.evaluateStatement("temp <- (cars JOIN (rename (MakeID, Make) Make)) JOIN (rename (ModelID, Model) Model)");
			parser.evaluateStatement("temp <- select (Model == " + model + ") temp");
			parser.evaluateStatement("temp <- project (CarID, Make, Model, Mpg) temp");
			parser.evaluateStatement("SHOW temp");

		}
		if (makeOrModel == 2)
		{
			cout << "Please input the make of the cars you want to be shown: ";
			cin >> make;
			cout << endl << endl;

			parser.evaluateStatement("temp <- (cars JOIN (rename (MakeID, Make) Make)) JOIN (rename (ModelID, Model) Model)");
			parser.evaluateStatement("temp <- select (Make == " + make + ") temp");
			parser.evaluateStatement("temp <- project (CarID, Make, Model, Mpg) temp");
			parser.evaluateStatement("SHOW temp");
			cout << endl;
		}
	}
	else
	{
		cout << "Incorrect Input";
	}

}

void ActionHandler::findUsers()
{
	string choiceStr;
	string conditionValue;

	cout << endl << "Select a value to search by:" << endl;
	cout << "1) Username" << endl;
	cout << "2) First Name" << endl;
	cout << "3) Last Name" << endl;
	cout << "4) Email" << endl;
	cout << "Enter choice: ";
	getline(cin, choiceStr);
	getline(cin, choiceStr);

	switch (stoi(choiceStr))
	{
		case 1:
			cout << "Enter username to find: ";
			getline(cin, conditionValue);
			parser.evaluateStatement("temp <- select (Username == " + conditionValue + ") User");
			break;
		case 2:
			cout << "Enter first name to find: ";
			getline(cin, conditionValue);
			parser.evaluateStatement("temp <- select (Firstname == " + conditionValue + ") User");
			break;
		case 3:
			cout << "Enter last name to find: ";
			getline(cin, conditionValue);
			parser.evaluateStatement("temp <- select (Lastname == " + conditionValue + ") User");
			break;
		case 4:
			cout << "Enter email to find: ";
			getline(cin, conditionValue);
			parser.evaluateStatement("temp <- select (email == " + conditionValue + ") User");
			break;
		default:
			throw exception("Unknown option");
	}
	parser.evaluateStatement("SHOW temp");
}

void ActionHandler::removeDuplicates()
{
	string tablename;
	cout << "Enter table name: ";
	cin >> tablename;
	parser.evaluateStatement("temp <- " + tablename + " + " + tablename);
	parser.evaluateStatement("SHOW temp");
}

void ActionHandler::addToCart(){
	string carID;
	parser.evaluateStatement("SHOW cars");
	cout << "Enter car ID of desired car: ";
	cin >> carID;
	parser.evaluateStatement("addedCar <- select (CarID == "+ carID +") cars");
	parser.evaluateStatement("Cart <- Cart + addedCar");
	parser.evaluateStatement("Cart <- Cart + Cart");
	cout << "Car has been added to cart." << endl;
}

void ActionHandler::displayCart(){
	parser.evaluateStatement("temp <- (Cart JOIN (rename (MakeID, Make) Make)) JOIN (rename (ModelID, Model) Model)");
	parser.evaluateStatement("temp <- project (CarID, Make, Model, Mpg) temp");
	parser.evaluateStatement("SHOW temp");
}

void ActionHandler::displayNotInCart(){
	parser.evaluateStatement("temp <- ((cars - Cart) JOIN (rename (MakeID, Make) Make)) JOIN (rename (ModelID, Model) Model)");
	parser.evaluateStatement("temp <- project (CarID, Make, Model, Mpg) temp");
	parser.evaluateStatement("SHOW temp");
}

void ActionHandler::exit()
{
	string yesNo;
	cout << "Would you like to save your changes? (Y/N): ";
	getline(cin, yesNo);
	getline(cin, yesNo);

	if (yesNo == "y" || yesNo == "Y")
	{
		parser.evaluateStatement("WRITE cars");
		parser.evaluateStatement("WRITE Make");
		parser.evaluateStatement("WRITE Model");
		parser.evaluateStatement("WRITE User");
		parser.evaluateStatement("WRITE Cart");
		parser.evaluateStatement("WRITE MakeLocation");
	}
	_exit(0);
}