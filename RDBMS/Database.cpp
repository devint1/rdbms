#include "Database.h"

Table& Database::findTable(string name)
{
	for (Table& t : tables) {
		if (t.getName() == name) {
			return t;
		}
	}

	throw exception("Table not found.");
}

Database::Database()
{
}

void Database::openTable(string filename)
{
	tables.push_back(Table(filename));
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

void Database::showTable(Table table)
{
	table.showTable();
}

void Database::createTable(string name, vector<string> attributeNames, vector<string> dataTypeNames, vector<string> primaryKeyNames)
{
	tables.push_back(Table(name, attributeNames, dataTypeNames, primaryKeyNames));
}

void Database::insertIntoTable(string tablename, vector<string> values)
{
	Table& t = findTable(tablename);
	t.insert(values);
}

void Database::updateTable(string relationName, string attributeNameToChange, string valueToChange, string conditionAttributeName, string conditionValue)
{
	int changeAttributePos;
	int conditionAttributePos;

	Table& relation = findTable(relationName);

	changeAttributePos = relation.findAttributebyName(attributeNameToChange);	  //Gets the attribute that will be modified index's
	conditionAttributePos = relation.findAttributebyName(conditionAttributeName);	  //Gets the attribute that will be used as conditions index's
	
	relation.update(changeAttributePos, conditionAttributePos, conditionValue, valueToChange);
}
