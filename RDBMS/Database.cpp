#include "Database.h"

Table& Database::findTable(string name)
{
	for (Table& t : tables) {
		if (t.getName() == name) {
			return t;
		}
	}
	string error = "Table not found: " + name;
	throw exception(error.c_str());
}

bool Database::tableExists(string name)
{
	bool exists = false;
	for (Table& t : tables) {
		if (t.getName() == name) {
			return true;
		}
	}

	return false;
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
	bool found = false;
	for (int i = 0; i<(int)tables.size(); i++)
	{
		if (tables[i].getName() == name){
			tables[i].deleteFromTable(attributeName, dataName);
			found = true;
		}
	}

	if (!found)
		cout << "Error: " + dataName + " not found in table." << endl;

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

void Database::insertIntoTable(string tablename, Table relation)
{
	Table& t = findTable(tablename);
	if (relation.getAttributes().size() != t.getAttributes().size())
		throw exception("Tables have different number of columns.");

	for (vector<string> str : relation.getTableData())
	{
		t.insert(str);
	}
}

void Database::updateTable(string relationName, string attributeNameToChange, string valueToChange, string conditionAttributeName, string conditionValue)
{
	int changeAttributePos;
	int conditionAttributePos;

	Table& relation = findTable(relationName);

	//Gets the attribute that will be modified index's
	changeAttributePos = relation.findAttributebyName(attributeNameToChange);
	//Gets the attribute that will be used as conditions index's
	conditionAttributePos = relation.findAttributebyName(conditionAttributeName);
	
	relation.update(changeAttributePos, conditionAttributePos, conditionValue, valueToChange);
}

void Database::addTable(Table table)
{
	tables.push_back(table);
}