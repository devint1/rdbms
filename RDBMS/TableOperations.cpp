#include "TableOperations.h"

static Table setUnion(Table table1, Table table2, string attributeName){
	bool attributesEqual = true;
	int i = 0;

	for (TableAttribute attrib : table1.getAttributes()){
		if (attrib.getName() != table2.getAttributes()[i].getName() || attrib.getType() != table2.getAttributes()[i].getType())
			attributesEqual = false;
		i++;
	}

	if (table1.getAttributes.size() != table1.getAttributes.size() || !attributesEqual)
		cout << "\nError: Tables do not have same attributes! (cannot compute Union)";

	else{
		int attributeIndex1 = table1.findAttributebyName(attributeName);
		int attributeIndex2 = table2.findAttributebyName(attributeName);

		if (attributeIndex1 == -1)
			cout << "\nError: " << attributeName << " not found in " << table1.getName();
		
		else if (attributeIndex2 == -1)
			cout << "\nError: " << attributeName << " not found in " << table2.getName();

		else{
			string unionTableName = table1.getName() + "_" + table2.getName() + "_union.db";
			vector<string> attributeNames;
			vector<string> dataTypeNames;

			for (TableAttribute attrib : table1.getAttributes()){
				attributeNames.push_back(attrib.getName());
				dataTypeNames.push_back(attrib.getType());
			}

			Table unionTable(unionTableName, attributeNames, dataTypeNames, table1.getPrimaryKeys());

		}
	}
}