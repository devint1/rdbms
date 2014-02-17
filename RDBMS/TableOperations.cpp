#include "TableOperations.h"

bool TableOperations::isNumber(const string s)
{
	for (size_t i = 0; i < s.size(); i++){
		if (!isdigit(s[i]))
			return false;
	}
	return true;
}

Table TableOperations::select(Table targetTable, string conditionAttribute, string conditionOp, string condition)

{
	
	enum conditionOperator { equal, notEqual, lessThan, lessThanEqual, greaterThan, greaterThanEqual };
	conditionOperator operation;
	if (conditionOp == "==")
		operation = equal;
	else if (conditionOp == "!=")
		operation = notEqual;
	else if (conditionOp == "<=")
		operation = lessThanEqual;
	else if (conditionOp == "<")
		operation = lessThan;
	else if (conditionOp == ">=")
		operation = greaterThanEqual;
	else if (conditionOp == ">")
		operation = greaterThan;

	int conditionAttributeIndex = targetTable.findAttributebyName(conditionAttribute);
	if (conditionAttributeIndex == -1){
		cout << "ERROR: " << conditionAttribute << " not found in " << targetTable.getName() << " table\n";
	}


	vector< vector<string> > targetData = targetTable.getTableData();
	vector<TableAttribute> targetAttributes = targetTable.getAttributes();

	string newTableName = "SELECT_" + condition + "_FROM_" + targetTable.getName();
	vector<string> newTableDataTypeNames;
	vector<string> newTableAttributeNames;
	vector<string> newTablePrimaryKeyNames;

	for (size_t i = 0; i < targetTable.getPrimaryKeys().size(); i++)
		newTablePrimaryKeyNames.push_back(targetTable.getPrimaryKeys()[i]);
	

	for (size_t i = 0; i < targetAttributes.size(); i++)   //Finds the attributes to include index within a table attributes to later relate it to TableData
	{
		newTableAttributeNames.push_back(targetAttributes[i].getName());
		newTableDataTypeNames.push_back(targetAttributes[i].getType());
	}

	Table selectTable(newTableName, newTableAttributeNames, newTableDataTypeNames, newTablePrimaryKeyNames);

	for (size_t i = 0; i < targetData.size(); i++)
	{
		string entry = targetData[i][conditionAttributeIndex];
		if (operation != equal && operation != notEqual && !isNumber(entry)){
			cout << "ERROR: cannot apply condition to non-numeric attribute.\n";
				break;
		}

		switch (operation){
		case equal:
			if (entry == condition)
				selectTable.insert(targetData[i]);
			break;
		case notEqual:
			if (entry != condition)
				selectTable.insert(targetData[i]);
			break;
		case lessThanEqual:
			if (entry <= condition && isNumber(entry))
				selectTable.insert(targetData[i]);
			break;
		case lessThan:
			if (entry == condition && isNumber(entry))
				selectTable.insert(targetData[i]);
			break;
		case greaterThanEqual:
			if (entry == condition && isNumber(entry))
				selectTable.insert(targetData[i]);
			break;
		case greaterThan:
			if (entry == condition && isNumber(entry))
				selectTable.insert(targetData[i]);
			break;
		default:
			break;
		}
		

	}

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
	return selectTable;
}

bool TableOperations::entriesAreEqual(vector<string> entry1, vector<string> entry2){
	bool areEqual = true;
	for (size_t i = 0; i < entry1.size(); i++){
		if (entry1[i] != entry2[i]){
			areEqual = false;
			break;
		}
	}
	return areEqual;
}

Table TableOperations::setUnion(Table table1, Table table2){
	bool attributesEqual = true;
	int i = 0;

	for (TableAttribute attrib : table1.getAttributes()){
		if (attrib.getName() != table2.getAttributes()[i].getName() || attrib.getType() != table2.getAttributes()[i].getType())
			attributesEqual = false;
		i++;
	}

	if (table1.getAttributes().size() != table2.getAttributes().size() || !attributesEqual)
		throw exception("Tables are not Difference compatible");

	else{
		string unionTableName = table1.getName() + "_" + table2.getName() + "_union";
		vector<string> attributeNames;
		vector<string> dataTypeNames;

		for (TableAttribute attrib : table1.getAttributes()){
			attributeNames.push_back(attrib.getName());
			dataTypeNames.push_back(attrib.getType());
		}

		Table unionTable(unionTableName, attributeNames, dataTypeNames, table1.getPrimaryKeys());
		bool duplicate = false;
		// insert contents of table 1 into unionTable
		for (size_t j = 0; j < table1.getTableData().size(); j++){
			duplicate = false;
			for (size_t k = 0; k < unionTable.getTableData().size(); k++){
				if (entriesAreEqual(table1.getTableData()[j], unionTable.getTableData()[k])){
					duplicate = true;
					break;
				}
			}
			if (!duplicate){
				unionTable.insert(table1.getTableData()[j]);
			}
		}


		for (size_t j = 0; j < table2.getTableData().size(); j++){
			duplicate = false;
			for (size_t k = 0; k < table1.getTableData().size(); k++){
				if (entriesAreEqual(table2.getTableData()[j], table1.getTableData()[k])){
					duplicate = true;
					break;
				}
			}
			if (!duplicate){
				unionTable.insert(table2.getTableData()[j]);
			}
		}
		return unionTable;
	}

	return table1; // not sure what to return if not unionable
}

// returns table of elements in table 2 that are not in table 1
Table TableOperations::setDifference(Table table1, Table table2){
	bool attributesEqual = true;
	int i = 0;

	for (TableAttribute attrib : table1.getAttributes()){
		if (attrib.getName() != table2.getAttributes()[i].getName() || attrib.getType() != table2.getAttributes()[i].getType())
			attributesEqual = false;
		i++;
	}

	if (table1.getAttributes().size() != table2.getAttributes().size() || !attributesEqual)
		throw exception("Tables are not Difference compatible");

	else{
		string differenceTableName = table1.getName() + "_" + table2.getName() + "_difference";
		vector<string> attributeNames;
		vector<string> dataTypeNames;
	

		for (TableAttribute attrib : table1.getAttributes()){
			attributeNames.push_back(attrib.getName());
			dataTypeNames.push_back(attrib.getType());
		}

		Table differenceTable(differenceTableName, attributeNames, dataTypeNames, table1.getPrimaryKeys());

		// insert contents of table 1 that are not in table 2
		bool duplicate = false;
		for (size_t j = 0; j < table1.getTableData().size(); j++){
			duplicate = false;
			for (size_t k = 0; k < table2.getTableData().size(); k++){
				if (entriesAreEqual(table1.getTableData()[j], table2.getTableData()[k])){
					duplicate = true;
					break;
				}
			}
			if (!duplicate)
				differenceTable.insert(table1.getTableData()[j]);
		}

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

	for(size_t i = 0; i < table.getTableData().size(); i++)
	{
		newrow.push_back(table.getTableData()[i][index]);
		newtable.insert(newrow);
		newrow.clear();
	}
	return newtable;
}

Table TableOperations::combineTables(Table table1, Table table2)
{
	Table newtable = table1;
	vector<TableAttribute> t2attr = table2.getAttributes();
	
	vector<vector<string>> t2data = table2.getTableData();
	for (size_t i = 0; i < t2attr.size(); i++)
		newtable.addAttribute(t2attr);
	

	for (size_t i = 0; i < t2data.size(); i++)
		for (size_t j = 0; j < table2.getAttributes().size(); j++)
			newtable.appendToRow(i, t2data[i]);
	
	return newtable;
}
