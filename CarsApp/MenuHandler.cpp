#include "ActionHandler.h"
#include "MenuHandler.h"
#include "../RDBMS/Parser.h"
using namespace std;

void MenuHandler::printMenu()
{
	//Car operations	
	cout << "1)  Add car" << endl;						 //Miguel
	cout << "2)  Add car location" << endl;				 //Sergio
	cout << "3)  Modify car" << endl;
	cout << "4)  Modify car location" << endl;			 //Corey
	cout << "5)  Delete car" << endl;					 //Miguel
	cout << "6)  Delete car location" << endl;			 //Sergio
	cout << "7)  List all cars" << endl;
	cout << "8)  List all car locations" << endl;
	cout << "9)  List all cars with locations" << endl;  //Miguel
	cout << "10) Find cars" << endl;

	//User operations
	cout << "11) Add user" << endl;
	cout << "12) Modify user" << endl;					 //Corey
	cout << "13) Delete user" << endl;                   //Miguel
	cout << "14) Show all users" << endl;                //Sergio
	cout << "15) Find users" << endl;

	//Utilities
	cout << "16) Remove duplicates" << endl;			 //Corey
	cout << "17) Display duplicates" << endl;            //Miguel
	cout << "18) Display all ownership combonations" << endl;	 //Sergio
	cout << "19) Exit program" << endl;
	cout << endl;
}

void MenuHandler::executeOption(int option)
{
	string statement;
	switch (option)
	{
	case 1:

		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		break;
	case 12:
		break;
	case 13:
		break;
	case 14:
		break;
	case 15:
		break;
	case 16:
		break;
	case 17:
		break;
	case 18:
		break;
	case 19:
		break;
	case 20:
		ActionHandler::startInterpreter();
		break;
	default:
		cerr << endl << "ERROR: Unknown option." << endl;
	}
}
