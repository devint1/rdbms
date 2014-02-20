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

	for (int i = 0; i < makeData.size(); i++)
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

	}


}