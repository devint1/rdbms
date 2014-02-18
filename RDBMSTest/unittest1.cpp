#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\RDBMS\Table.h"
#include "..\RDBMS\Database.h"
#include "..\RDBMS\TableOperations.h"
#include "..\RDBMS\Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RDBMSTest
{		
	TEST_CLASS(UnitTest1)
	{
	private:
		Database db;
		Parser parser;

		void initDB() 
		{
			db.openTable("cars");
			db.openTable("cars2");
			db.openTable("students");
			db.openTable("schoolLocations");
			parser.evaluateStatement("OPEN cars");
			parser.evaluateStatement("OPEN cars2");
			parser.evaluateStatement("OPEN students");
			parser.evaluateStatement("OPEN schoolLocations");

			Database parserDb = parser.getDb();

			//Assert::AreEqual(parserDb.findTable("cars"), db.findTable("cars"));
		}
	public:
		TEST_METHOD(CreateTable)
		{
			//db.UpdateTable("cars", "")
			vector<string> attNames = { "firstName", "lastName", "email", "cars" };
			vector<string> attTypes = { "varchar(255)", "varchar(255)", "varchar(255)", "varchar(255)" };
			vector<string> primKeys = { "email" };
			db.createTable("users", attNames, attTypes, primKeys);
		}
		TEST_METHOD(CloseTable)
		{
			initDB();
			db.closeTable("cars");
			auto func = [this] { db.findTable("cars"); };
			Assert::ExpectException<exception>(func); //Should not find the table
		}
		TEST_METHOD(Insert)
		{
			initDB();
			vector<string> vals = { "646", "Lamborghini", "Gallardo", "11" };
			int before = db.findTable("cars").getTableData().size();
			db.insertIntoTable("cars", vals);
			int after = db.findTable("cars").getTableData().size();
			Assert::AreEqual(before + 1, after); //Size should increase by one
		}
		TEST_METHOD(Update)
		{
			initDB();
			db.updateTable("cars", "Model", "Celica", "Model", "corolla");
		}
		TEST_METHOD(Delete)
		{
			initDB();
			int before = db.findTable("cars").getTableData().size();
			db.deleteFromTable("cars", "Make", "ford");
			int after = db.findTable("cars").getTableData().size();
			Assert::AreEqual(before, after + 2); //Our database has two rows that match the test, so we should expect a size decrease of two
		}
		TEST_METHOD(CrossProduct)
		{
			initDB();
			Table testTable = TableOperations::crossProduct(db.findTable("cars2"), db.findTable("cars"));
			Assert::AreEqual(testTable.getTableData().size(), db.findTable("cars2").getTableData().size() * db.findTable("cars").getTableData().size()); //Size of result should equal the product of the sizes of the input tables
		}
		TEST_METHOD(Union)
		{
			initDB();
			Table testTable = TableOperations::setUnion(db.findTable("cars2"), db.findTable("cars"));
			vector<TableAttribute> testAttributes = TableOperations::attributeUnion(db.findTable("cars"), db.findTable("cars2"));
			Assert::AreEqual(testTable.getAttributes().size(), testAttributes.size());
		}
		TEST_METHOD(Difference)
		{
			initDB();
			Table testTable = TableOperations::setDifference(db.findTable("cars"), db.findTable("cars"));
			int testCols = testTable.getTableData().size();
			Assert::AreEqual(testCols, 0); //Difference of a table with itself should be zero
		}
		TEST_METHOD(Project)
		{
			initDB();
			string name1 = "Model";
			string name2 = "my_model";
			Table rename = TableOperations::project(db.findTable("cars"), name1);
		}
		//Need to complete
		TEST_METHOD(Select)
		{
			/*initDB();
			Table testTable1 = TableOperations::select("Model", db.findTable("cars"));
			Table testTable2 = TableOperations::select("Make", db.findTable("cars"), "Make", "hyundai");
			Assert::AreEqual((int)testTable1.getAttributes().size(), 1);
			Assert::AreEqual((int)testTable2.getAttributes().size(), 1);*/
		}
		TEST_METHOD(Rename)
		{
			initDB();
			Table table = db.findTable("schoolLocations");
			table.changeAttributeName("School", "my_school");
			string testString = "my_school";
			Assert::AreEqual(table.getAttributes()[0].getName(), testString);

			vector<string> newNames = {"super_school", "super_location"};

			Table renamedTable = TableOperations::renamingAttributes(table, newNames);
		}
		TEST_METHOD(NaturalJoin)
		{
			initDB();
			Table testTable = TableOperations::naturalJoin(db.findTable("students"), db.findTable("schoolLocations"));
			vector<TableAttribute> testAttributes = TableOperations::attributeUnion(db.findTable("students"), db.findTable("schoolLocations"));
			Assert::AreEqual(testTable.getAttributes().size(), testAttributes.size());
		}
		TEST_METHOD(Parser)
		{
			parser.evaluateStatement("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind)");
			parser.evaluateStatement("INSERT INTO animals VALUES FROM (Joe, cat, 4)");
			parser.evaluateStatement("INSERT INTO animals VALUES FROM (Spot, dog, 10)");
			parser.evaluateStatement("INSERT INTO animals VALUES FROM (Snoopy, dog, 3)");
			parser.evaluateStatement("INSERT INTO animals VALUES FROM (Tweety, bird, 1)");
			parser.evaluateStatement("INSERT INTO animals VALUES FROM (Joe, bird, 2)");
			parser.evaluateStatement("SHOW animals");
			//parser.evaluateStatement("dogs <- select (kind == dog) animals");
			//parser.evaluateStatement("old_dogs <- select (age > 10) dogs");
			//parser.evaluateStatement("cats_or_dogs <- dogs + (select (kind == cat) animals)");
			parser.evaluateStatement("CREATE TABLE species (kind VARCHAR(10)) PRIMARY KEY (kind)");
			parser.evaluateStatement("INSERT INTO species VALUES FROM RELATION project (kind) animals");
			parser.evaluateStatement("a <- rename (aname, akind) (project (name, kind) animals)");
			//parser.evaluateStatement("common_names <- project (name) (select (aname == name && akind != kind) (a * animals))");
			//parser.evaluateStatement("answer <- common_names");
			//parser.evaluateStatement("SHOW answer");
			parser.evaluateStatement("WRITE animals");
			parser.evaluateStatement("CLOSE animals");
		}
	};
}