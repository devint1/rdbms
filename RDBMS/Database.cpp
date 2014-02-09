#include "Database.h"

Table& Database::findTable(string name)
{
	for (Table& t : tables) {
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

void Database::deleteFromTable(string name, string attributeName, string dataName)
{
	for (int i = 0; i<(int)tables.size(); i++)
	{
		if (tables[i].getName() == name)
			tables[i].deleteFromTable(attributeName, dataName);
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

void Database::insertIntoTable(string tablename, string values[])
{
	Table& t = findTable(tablename);
	t.insert(values);
}

void Database::UpdateTable(string relationName, string changeAtrributeName, string conditionAttributeData, string conditionAttributeName, string changeAttributeData)
{
	Table relation;
	int changeAttributePos;
	int conditionAttributePos;
	

	relation = findTable(relationName);

	changeAttributePos = relation.findAttributebyName(changeAtrributeName);	  //Gets the attribute that will be modified index's
	conditionAttributePos = relation.findAttributebyName(conditionAttributeName);	  //Gets the attribute that will be used as conditions index's
	
	relation.update(changeAttributePos, conditionAttributePos, conditionAttributeData, changeAttributeData);
	
}




