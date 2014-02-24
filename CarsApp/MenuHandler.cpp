#include "ActionHandler.h"
#include "MenuHandler.h"
#include "../RDBMS/Parser.h"
using namespace std;

void MenuHandler::printMenu()
{
	//Car operations	
	cout << "1)  Add car" << endl;						 //Miguel
	cout << "2)  Add car location" << endl;				 //Sergio
	cout << "3)  Modify car" << endl;					 //Devin
	cout << "4)  Modify car location" << endl;			 //Corey
	cout << "5)  Delete car" << endl;					 //Devin
	cout << "6)  Delete car location" << endl;			 //Sergio
	cout << "7)  List all cars" << endl;				 //Devin
	cout << "8)  List all car locations" << endl;		 //Corey
	cout << "9)  List all cars with locations" << endl;  //Miguel
	cout << "10) Find cars" << endl;					 //Sergio

	//User operations
	cout << "11) Add user" << endl;						 //Devin
	cout << "12) Modify user" << endl;					 //Corey
	cout << "13) Delete user" << endl;                   //Miguel
	cout << "14) Show all users" << endl;                //Sergio
	cout << "15) Find users" << endl;					 //Devin

	//Utilities
	cout << "16) Remove duplicates" << endl;			 //Corey
	cout << "17) Display duplicates" << endl;            //Miguel
	cout << "18) Display all ownership combinations" << endl;	 //Sergio
	cout << "19) Exit program" << endl;					 //Devin
	cout << endl;
}

void MenuHandler::executeOption(int option)
{
	string statement;
	switch (option)
	{
	case 1:
		ActionHandler::addCar();
		break;
	case 2:
		ActionHandler::addLocation();
		break;
	case 3:
		ActionHandler::modifyCar();
		break;
	case 4:
		ActionHandler::modifyCarLocation();
		break;
	case 5:
		ActionHandler::deleteCar();
		break;
	case 6:
		ActionHandler::deleteLocation();
		break;
	case 7:
		ActionHandler::listAllCars();
		break;
	case 8:
		ActionHandler::listLocations();
		break;
	case 9:
		ActionHandler::listAllCarLocations();
		break;
	case 10:
		ActionHandler::findCars();
		break;
	case 11:
		ActionHandler::addCar();
		break;
	case 12:
		ActionHandler::modifyUser();
		break;
	case 13:
		ActionHandler::deleteUser();
		break;
	case 14:
		ActionHandler::showUsers();
		break;
	case 15:
		ActionHandler::findUsers();
		break;
	case 16:
		ActionHandler::removeDuplicates();
		break;
	case 17:
		break;
	case 18:
		//ActionHandler::ownerCombination();
		break;
	case 19:
		exit(0);
		break;
	case 20:
		ActionHandler::startInterpreter();
		break;
	default:
		cerr << endl << "ERROR: Unknown option." << endl;
	}
}
