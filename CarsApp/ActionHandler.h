#pragma once

#include "../RDBMS/Parser.h"

class ActionHandler
{
private:
	static Parser parser;
public:
	static void init();
	static void modifyCar();
	static void startInterpreter();
};
