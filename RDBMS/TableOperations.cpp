#include "TableOperations.h"

static Table setUnion(Table table1, Table table2, string attributeName){
	if (table1.getAttributes().size() != table1.getAttributes().size())
		cout << "\nError: Tables do not have same number of attributes! (cannot compute Union)";
	else{
		int attributeIndex1 = table1.findAttributebyName(attributeName);
		int attributeIndex2 = table2.findAttributebyName(attributeName);

		if (attributeIndex1 == -1)
			cout << "\nError: " << attributeName << " not found in " << table1.getName();
		
		else if (attributeIndex2 == -1)
			cout << "\nError: " << attributeName << " not found in " << table2.getName();

		else{
			Table unionTable();
		}
	}
}