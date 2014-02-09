#include "Database.h"

Table Database::findTable(string name)
{
	for (Table t : tables) {
		if (t.getName() == name) {
			return t;
		}
	}
}

Database::Database()
{
}

void Database::openTable(string filename)
{
	tables.push_back(Table(filename));
}

void Database::exit()
{
	exit();
}

Database::~Database()
{
}

void Database::closeTable(string tablename)
{
	Table table = findTable(tablename);
	table.writeTable();
	for(int i=0;i<(int)tables.size();i++)
	{
		if(tables[i].getName()==tablename)
			tables.erase(tables.begin()+i);
	}
}

void Database::writeTable(string tablename)
{
	Table table = findTable(tablename);
	table.writeTable();

}

void Database::showTable(string tablename)
{
	Table table = findTable(tablename);
	table.showTable();
}

void Database::createTable(string name, string attributeNames[], string dataTypeNames[], string primaryKeyNames[])
{
	tables.push_back(Table(name, attributeNames, dataTypeNames, primaryKeyNames));
}