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
			string unionTableName = table1.getName() + "_" + table2.getName() + "_union";
			vector<string> attributeNames;
			vector<string> dataTypeNames;
			int keyAttributeIndex = table1.findAttributebyName(keyAttribute);

			for (TableAttribute attrib : table1.getAttributes()){
				attributeNames.push_back(attrib.getName());
				dataTypeNames.push_back(attrib.getType());
			}

			Table unionTable(unionTableName, attributeNames, dataTypeNames, table1.getPrimaryKeys());

			// insert contents of table 1 into unionTable
			for (size_t k = 0; k < table1.getTableData().size(); k++){
				unionTable.insert(table1.getTableData()[k]);
			}

			// insert contents of table 2 into unionTable excluding duplicates
			bool duplicate = false;
			for (size_t j = 0; j < table2.getTableData().size(); j++){
				for (size_t k = 0; k < table1.getTableData().size(); k++){
					if (table2.getTableData()[j][keyAttributeIndex] == table1.getTableData()[k][keyAttributeIndex])
						duplicate = true;
				}
				if (!duplicate)
					unionTable.insert(table2.getTableData()[j]);
				duplicate = false;
			}

			unionTable.writeTable();
			return unionTable;
		}
	}
	return table1; // not sure what to return if not unionable
}

// returns table of elements in table 2 that are not in table 1
Table TableOperations::setDifference(Table table1, Table table2, string keyAttribute){
	bool attributesEqual = true;
	int i = 0;

	for (TableAttribute attrib : table1.getAttributes()){
		if (attrib.getName() != table2.getAttributes()[i].getName() || attrib.getType() != table2.getAttributes()[i].getType())
			attributesEqual = false;
		i++;
	}

	if (table1.getAttributes().size() != table2.getAttributes().size() || !attributesEqual)
		cout << "\nError: Tables do not have same attributes! (cannot compute difference)";

	else{
		string differenceTableName = table1.getName() + "_" + table2.getName() + "_difference";
		vector<string> attributeNames;
		vector<string> dataTypeNames;
		int keyAttributeIndex = table1.findAttributebyName(keyAttribute);

		for (TableAttribute attrib : table1.getAttributes()){
			attributeNames.push_back(attrib.getName());
			dataTypeNames.push_back(attrib.getType());
		}

		Table differenceTable(differenceTableName, attributeNames, dataTypeNames, table1.getPrimaryKeys());

		// insert contents of table 2 into differenceTable excluding table1 elements
		bool inTable1 = false;
		for (size_t j = 0; j < table2.getTableData().size(); j++){
			for (size_t k = 0; k < table1.getTableData().size(); k++){
				if (table2.getTableData()[j][keyAttributeIndex] == table1.getTableData()[k][keyAttributeIndex])
					inTable1 = true;
			}
			if (!inTable1)
				differenceTable.insert(table2.getTableData()[j]);
			inTable1 = false;
		}

		differenceTable.writeTable();
		return differenceTable;
	}
	return table1; // not sure what to return if not difference-able
}

vector<TableAttribute> TableOperations::attributeIntersection(Table table1, Table table2){
	vector<TableAttribute> attributes;
	bool duplicate = false;

	for (size_t j = 0; j < table2.getAttributes().size(); j++){
		for (size_t k = 0; k < table1.getAttributes().size(); k++){
			if (table2.getAttributes()[j].getName() == table1.getAttributes()[k].getName())
				duplicate = true;
		}
		if (duplicate)
			attributes.push_back(table2.getAttributes()[j]);
		duplicate = false;
	}
	return attributes;
}

vector<TableAttribute> TableOperations::attributeUnion(Table table1, Table table2){
	vector<TableAttribute> attributes;
	bool duplicate = false;

	for (size_t k = 0; k < table1.getAttributes().size(); k++){
		attributes.push_back(table1.getAttributes()[k]);
	}

	for (size_t j = 0; j < table2.getAttributes().size(); j++){
		for (size_t k = 0; k < table1.getAttributes().size(); k++){
			if (table2.getAttributes()[j].getName() == table1.getAttributes()[k].getName())
				duplicate = true;
		}
		if (!duplicate)
			attributes.push_back(table2.getAttributes()[j]);
		duplicate = false;
	}

	return attributes;
}

vector<TableAttribute> TableOperations::attributeDifference(Table table1, Table table2){
	vector<TableAttribute> attributes;
	bool inTable1 = false;
	for (size_t j = 0; j < table2.getAttributes().size(); j++){
		for (size_t k = 0; k < table1.getAttributes().size(); k++){
			if (table2.getAttributes()[j].getName() == table1.getAttributes()[k].getName())
				inTable1 = true;
		}
		if (!inTable1)
			attributes.push_back(table2.getAttributes()[j]);
		inTable1 = false;
	}

	return attributes;
}

Table TableOperations::naturalJoin(Table table1, Table table2){

		// (1) find union of attributes (should require separate function)
		vector<TableAttribute> joinAttributes = attributeUnion(table1, table2);
		vector<TableAttribute> intersectAttributes = attributeIntersection(table1, table2);
		vector<TableAttribute> appendAttributes = attributeDifference(table1, table2);

		string keyAttribute = intersectAttributes[0].getName();

		int keyAttributeIndex1 = table1.findAttributebyName(keyAttribute);
		int keyAttributeIndex2 = table2.findAttributebyName(keyAttribute);

		if (keyAttributeIndex1 == -1 || keyAttributeIndex2 == -1)
			cout << "\nError: Tables do not have matching " << keyAttribute << " attribute! (cannot be joined)";
		else{
			// (2) create table with union of attributes
			string joinTableName = table1.getName() + "_" + table2.getName() + "_join";
			vector<string> attributeNames;
			vector<string> dataTypeNames;

			for (TableAttribute attrib : joinAttributes){
				attributeNames.push_back(attrib.getName());
				dataTypeNames.push_back(attrib.getType());
			}

			Table joinTable(joinTableName, attributeNames, dataTypeNames, table1.getPrimaryKeys());
			vector<string> newTableEntry;
			vector<int> table1AttributeInd;
			vector<int> table2AttributeInd;

			for (size_t j = 0; j < (joinAttributes.size() - appendAttributes.size()); j++){
				table1AttributeInd.push_back(table1.findAttributebyName(joinAttributes[j].getName()));
			}

			for (size_t k = 0; k < appendAttributes.size(); k++){
				table2AttributeInd.push_back(table2.findAttributebyName(appendAttributes[k].getName()));
			}

 			for (size_t i = 0; i < table1.getTableData().size(); i++){
				for (size_t x = 0; x < table2.getTableData().size(); x++){
					if (table1.getTableData()[i][keyAttributeIndex1] == table2.getTableData()[x][keyAttributeIndex2]){
						for (size_t n = 0; n < table1AttributeInd.size(); n++){
							newTableEntry.push_back(table1.getTableData()[i][table1AttributeInd[n]]);
						}
						for (size_t m = 0; m < table2AttributeInd.size(); m++){
							newTableEntry.push_back(table2.getTableData()[x][table2AttributeInd[m]]);
						}
						joinTable.insert(newTableEntry);
						newTableEntry.clear();
					}
				}
			}
			joinTable.writeTable();
		}

	return table1; // not sure what to return if not join-able
}