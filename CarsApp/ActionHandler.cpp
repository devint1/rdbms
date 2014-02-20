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