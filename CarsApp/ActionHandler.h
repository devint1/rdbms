#pragma once

#include "../RDBMS/Parser.h"

class ActionHandler
{
private:
	static Parser parser;
public:
	static void init();
	static void modifyCar();
	static void deleteCar();
	static void listAllCars();
	static void startInterpreter();
	static void addCar();
	static void modifyCarLocation();
};


