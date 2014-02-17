#pragma once

#include <string>
#include "Table.h"
#include <tuple>

class TableOperations //All relational algebra logic is handled by this class
{
public:
	//These are close to what the assignment requires, but not exactly
	static Table select(Table targetTable, string conditionAttribute, string conditionOp, string condition); //Sergio //User provided a WHERE clause
	static Table select(string attributesToInclude, Table targetTable); //Sergio //User did not provide a WHERE clause
	static bool isNumber(const string s);
	//Calculates set union of two tables, returns the the result as a new table
	static bool entriesAreEqual(vector<string> entry1, vector<string> entry2);
	static Table setUnion(Table table1, Table table2); // MIGUEL
	static Table setDifference(Table table1, Table table2); //Calculates set difference of two tables, returns the the result as a new table
	static Table crossProduct(Table table1, Table table2); //Calculates cartesian product of two tables, returns the result as a new table
	static vector<TableAttribute> attributeUnion(Table table1, Table table2);
	static vector<TableAttribute> attributeIntersection(Table table1, Table table2);
	static vector<TableAttribute> attributeDifference(Table table1, Table table2);
	static Table naturalJoin(Table table1, Table table2); // MIGUEL
	//Projection
	static Table naturalJoin(Table table1, Table table2, string keyAttribute); // MIGUEL
	static Table project(Table table, string name);	//Corey, takes a name, returns new table
	static Table combineTables(Table table1, Table table2);
	static Table renamingAttributes(Table table, string attributeName, string rename);	//Corey, takes a table, the attribute name to be renamed, and the name to be changed to. returns the new table
};

