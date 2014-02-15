#include "TableOperations.h"


Table TableOperations::select(string attributesToInclude, Table targetTable, string conditionAttribute, string condition)
{

	int conditionAttributeIndex;
	int attributesToIncludeIndex;
	vector< vector<string> > targetData;
	vector<TableAttribute> targetAttributes;

	string newTableName;
	vector<string> newTableData;
	vector<string> newTableDataTypeNames;
	vector<string> newTableAttributeNames;
	vector<string> newTablePrimaryKeyNames;

	for (size_t i = 0; i < targetTable.getPrimaryKeys().size(); i++)
	{
		if (attributesToInclude == targetTable.getPrimaryKeys()[i])
			newTablePrimaryKeyNames.push_back(targetTable.getPrimaryKeys()[i]);
	}

	targetData = targetTable.getTableData();
	targetAttributes = targetTable.getAttributes();
	newTableName = ("Cars_select_") + attributesToInclude; //Check if literals and non-literals can be concatenated


	for (size_t i = 0; i < targetAttributes.size(); i++)   //Finds the attributes to include index within a table attributes to later relate it to TableData
	{
		if (targetAttributes[i].getName() == attributesToInclude)	 //had == condition (I think  == condition is wrong)
		{
			attributesToIncludeIndex = i;
			newTableAttributeNames.push_back(targetAttributes[i].getName());
			newTableDataTypeNames.push_back(targetAttributes[i].getType());
		}
	}

	for (size_t i = 0; i < targetAttributes.size(); i++)   //Finds the condition attribute index within a table attributes to later relate it to TableData
	{
		if (targetAttributes[i].getName() == conditionAttribute)	 //had == condition (I think  == condition is wrong)
		{
			conditionAttributeIndex = i;
		}
	}
	for (size_t i = 0; i < targetData.size(); i++)
	{
		if (targetData[i][conditionAttributeIndex] == condition)
			newTableData.push_back(targetData[i][attributesToIncludeIndex]); //Inputs attribute desired that met condition from old, original table, into the new table Data
	

	}

	Table selectTable(newTableName, newTableAttributeNames, newTableDataTypeNames, newTablePrimaryKeyNames);

	for (size_t i = 0; i < newTableData.size(); i++)	 //Inserts Attribute Data into Table
	{
		vector<string>data;
		data.push_back(newTableData[i]);
		selectTable.insert(data);
	}

	selectTable.writeTable();
	return selectTable;
}

Table TableOperations::select(string attributesToInclude, Table targetTable)
{
	int attributesToIncludeIndex;
	vector< vector<string> > targetData;
	vector<TableAttribute> targetAttributes;

	string newTableName;
	vector<string> newTableData;
	vector<string> newTableDataTypeNames;
	vector<string> newTableAttributeNames;
	vector<string> newTablePrimaryKeyNames;

	for (size_t i = 0; i < targetTable.getPrimaryKeys().size(); i++)
	{
		if (attributesToInclude == targetTable.getPrimaryKeys()[i])
			newTablePrimaryKeyNames.push_back(targetTable.getPrimaryKeys()[i]);
	}

	targetData = targetTable.getTableData();
	targetAttributes = targetTable.getAttributes();
	newTableName = (targetTable.getName()+"_select_") + attributesToInclude; //Check if literals and non-literals can be concatenated


	for (size_t i = 0; i < targetAttributes.size(); i++)   //Finds the attributes to include index within a table attributes to later relate it to TableData
	{
		if (targetAttributes[i].getName() == attributesToInclude)	 //had == condition (I think  == condition is wrong)
		{
			attributesToIncludeIndex = i;
			newTableAttributeNames.push_back(targetAttributes[i].getName());
			newTableDataTypeNames.push_back(targetAttributes[i].getType());
		}
	}

	for (size_t i = 0; i < targetData.size(); i++)
	{
		//if (targetData[i][attributesToIncludeIndex] == attributesToInclude)
		//{
		newTableData.push_back(targetData[i][attributesToIncludeIndex]); //Inputs attribute desired that met condition from old, original table, into the new table Data
		//}

	}

	Table selectTable(newTableName, newTableAttributeNames, newTableDataTypeNames, newTablePrimaryKeyNames);

	for (size_t i = 0; i < newTableData.size(); i++)	 //Inserts Attribute Data into Table
	{
		vector<string>data;
		data.push_back(newTableData[i]);
		selectTable.insert(data);
	}

	selectTable.writeTable();
	return selectTable;
}

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
		if (intersectAttributes.size() == 0){
			cout << "\nError: no intersecting attributes. (no join possible)";
			return table1;
		}
		string keyAttribute = intersectAttributes[0].getName();
	
		int keyAttributeIndex1 = table1.findAttributebyName(keyAttribute);
		int keyAttributeIndex2 = table2.findAttributebyName(keyAttribute);

		
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
		for (size_t j = 0; j < (joinAttributes.size() - appendAttributes.size()); j++)
			table1AttributeInd.push_back(table1.findAttributebyName(joinAttributes[j].getName()));
		
		for (size_t k = 0; k < appendAttributes.size(); k++)
			table2AttributeInd.push_back(table2.findAttributebyName(appendAttributes[k].getName()));

		bool matchFound = false;
 		for (size_t i = 0; i < table1.getTableData().size(); i++){
			matchFound = false;
			for (size_t x = 0; x < table2.getTableData().size(); x++){
				if (table1.getTableData()[i][keyAttributeIndex1] == table2.getTableData()[x][keyAttributeIndex2]){
					matchFound = true;
					for (size_t n = 0; n < table1AttributeInd.size(); n++)
						newTableEntry.push_back(table1.getTableData()[i][table1AttributeInd[n]]);
					
					for (size_t m = 0; m < table2AttributeInd.size(); m++)
						newTableEntry.push_back(table2.getTableData()[x][table2AttributeInd[m]]);
					
					joinTable.insert(newTableEntry);
					newTableEntry.clear();
					break;
				}
				// In case no corresponding data, set to "N/A"
				else if (!matchFound && x == table2.getTableData().size()-1){
					for (size_t n = 0; n < table1.getAttributes().size(); n++)
						newTableEntry.push_back(table1.getTableData()[i][table1AttributeInd[n]]);

					for (size_t m = 0; m < table2AttributeInd.size(); m++)
						newTableEntry.push_back("(N/A)");

					joinTable.insert(newTableEntry);
					newTableEntry.clear();
				}
			}
		}
		joinTable.writeTable();
		return joinTable;
		
		// not sure what to return if not join-able
		return table1; 
}

Table TableOperations::crossProduct(Table table1, Table table2)
{
	string resultTableName = table1.getName() + "_" + table2.getName() + "_crossProduct";

	//Concatenate the primary keys from both tables
	vector<TableAttribute> resultAttributes = table1.getAttributes();
	for (TableAttribute attribute : table2.getAttributes()) {
		resultAttributes.push_back(attribute);
	}

	//Concatenate the primary keys from both tables
	vector<string> resultPrimaryKeys = table1.getPrimaryKeys();
	for (string key : table2.getPrimaryKeys()) {
		resultPrimaryKeys.push_back(key);
	}

	Table result(resultTableName, resultAttributes, resultPrimaryKeys);

	//Compute all row combinations
	for (vector<string> row1 : table1.getTableData()) {
		for (vector<string> row2 : table2.getTableData()) {
			//Create a new row for the result table
			vector<string> rowToInsert = row1;
			for (string value : row2) {
				rowToInsert.push_back(value);
			}

			result.insert(rowToInsert); //Add the row to the result table
		}
	}

	result.writeTable();

	return result;
}

Table TableOperations::renamingAttributes(Table table, string attributeName, string rename)
{
	Table newtable = table;
	newtable.changeAttributeName(attributeName, rename);
	return newtable;
}

Table TableOperations::project(Table table, string name)
{
	int index = table.findAttributebyName(name);
	string tablename = table.getName() + "_project_" + name;
	vector<string> attrnames;
	attrnames.push_back(name);
	vector<string> attrtypes;
	attrtypes.push_back(table.getAttributes()[index].getType());
	Table newtable(tablename, attrnames, attrtypes, attrnames);
	vector<string> newrow;
	vector<vector<string>> newdata = newtable.getTableData();
	vector<vector<string>> olddata = table.getTableData();
	for(size_t i = 0; i < olddata.size(); i++)
	{
		newrow.push_back(olddata[i][index]);
		newtable.insert(newrow);
	}
	return newtable;
}
