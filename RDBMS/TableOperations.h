#pragma once

#include <string>
#include "Table.h"

class TableOperations //All relational algebra logic is handled by this class
{
public:
	//These are close to what the assignment requires, but not exactly
	//static Table select(string attributesToInclude, Table targetTable, string condition); //User provided a WHERE clause
	//static Table select(string attributesToInclude, Table targetTable); //User did not provide a WHERE clause

	//Calculates set union of two tables, returns the the result as a new table
	static Table setUnion(Table table1, Table table2, string keyAttribute); // MIGUEL
	static Table setDifference(Table table1, Table table2, string keyAttribute); //Calculates set difference of two tables, returns the the result as a new table
	static Table crossProduct(Table table1, Table table2); //Calculates cartesian product of two tables, returns the result as a new table
	static vector<TableAttribute> attributeUnion(Table table1, Table table2);
	static Table naturalJoin(Table table1, Table table2, string keyAttribute); // MIGUEL
	//Projection
};

