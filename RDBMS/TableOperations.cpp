#include "TableOperations.h"

Table TableOperations::setUnion(Table table1, Table table2, string keyAttribute){
	bool attributesEqual = true;
	int i = 0;

	for (TableAttribute attrib : table1.getAttributes()){
		if (attrib.getName() != table2.getAttributes()[i].getName() || attrib.getType() != table2.getAttributes()[i].getType())
			attributesEqual = false;
		i++;
	}

	if (table1.getAttributes().size() != table2.getAttributes().size() || !attributesEqual)
		cout << "\nError: Tables do not have same attributes! (cannot compute Union)";

	else{
		int attributeIndex1 = table1.findAttributebyName(keyAttribute);
		int attributeIndex2 = table2.findAttributebyName(keyAttribute);

		if (attributeIndex1 == -1)
			cout << "\nError: " << keyAttribute << " not found in " << table1.getName();
		
		else if (attributeIndex2 == -1)
			cout << "\nError: " << keyAttribute << " not found in " << table2.getName();

		else{
			string unionTableName = table1.getName() + "_" + table2.getName() + "_union.db";
			vector<string> attributeNames;
			vector<string> dataTypeNames;
			int keyAttributeIndex = table1.findAttributebyName(keyAttribute);

			for (TableAttribute attrib : table1.getAttributes()){
				attributeNames.push_back(attrib.getName());
				dataTypeNames.push_back(attrib.getType());
			}

			Table unionTable(unionTableName, attributeNames, dataTypeNames, table1.getPrimaryKeys());

			for (size_t k = 0; k < table1.getTableData().size(); k++){
				unionTable.insert(table1.getTableData()[k]);
			}

			for (size_t j = 0; j < table2.getTableData().size(); j++){
				unionTable.insert(table2.getTableData()[j]);
			}

			unionTable.writeTable();
			return unionTable;
		}
	}
}