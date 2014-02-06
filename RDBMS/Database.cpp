#include "Database.h"

Table Database::findTable(string name)
{
	for (Table t : tables) {
		if (t.getName == name) {
			return t;
		}
	}
}

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

int Database::findTableIndex(string name){
	for(int i=0;i<(int)tables.size();i++)
	{
		if(tables[i].getName==name)
			return i;
	}
}

void Database::writeTable(string tablename){
	Table table;

}
