#include "Database.h"

Database::Database()
{
}

void Database::openTable(string filename){
	tables.push_back(Table(filename));
}

void Database::exit()
{
	exit();
}

Database::~Database()
{
}
