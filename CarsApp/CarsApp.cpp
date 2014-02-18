#pragma once
#include "../RDBMS/Parser.h"
#include "../RDBMS/Database.h"

#include "MenuHandler.h"
#include "ActionHandler.h"

int main()
{
	cout << "Welcome to our Cars App!" << endl;
	Parser parser;
	string option;

	ActionHandler::init();

	while (true) {
		MenuHandler::printMenu();
		cout << "Choose option: ";
		getline(cin, option);
		try
		{
			MenuHandler::executeOption(stoi(option));
		}
		catch (invalid_argument e)
		{
			cerr << endl << "ERROR: Value is non-numeric." << endl;
		}
		catch (out_of_range e)
		{
			cerr << endl << "ERROR: The value is out of range." << endl;
		}
		cout << endl;
	}
	return 0;
}

