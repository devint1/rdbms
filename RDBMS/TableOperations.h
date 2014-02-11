#pragma once

#include <string>
#include "Table.h"
#include <tuple>

class TableOperations //All relational algebra logic is handled by this class
{
public:
	//These are close to what the assignment requires, but not exactly
	static Table select(string attributesToInclude, Table targetTable, string condition); //Sergio //User provided a WHERE clause
	static Table select(string attributesToInclude, Table targetTable); //Sergio //User did not provide a WHERE clause

	//Calculates set union of two tables, returns the the result as a new table
	static Table setUnion(Table table1, Table table2, string keyAttribute); // MIGUEL
	static Table setDifference(Table table1, Table table2, string keyAttribute); //Calculates set difference of two tables, returns the the result as a new table
	static Table crossProduct(Table table1, Table table2); //Calculates cartesian product of two tables, returns the result as a new table
	static vector<TableAttribute> attributeUnion(Table table1, Table table2);
	static Table naturalJoin(Table table1, Table table2, string keyAttribute); // MIGUEL
	static TableAttribute project(Table table, string name);	//Corey, takes a name, returns the entire TableAttribute
	static tuple<TableAttribute, TableAttribute> project(Table table, string name1, string name2);//Corey, takes two names, returns a tuple of the two Attributes

	static Table renamingAttributes(Table table, string attributeName, string rename);	//Corey, takes a table, the attribute name to be renamed, and the name to be changed to. returns the new table
};

