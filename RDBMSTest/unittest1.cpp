#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\RDBMS\Table.h"
#include "..\RDBMS\Database.h"
#include "..\RDBMS\TableOperations.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RDBMSTest
{		
	TEST_CLASS(UnitTest1)
	{
	private:
		Database db;

		void initDB() 
		{
			db.openTable("cars");
			db.openTable("cars2");
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
		TEST_METHOD(DropTable)
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
		TEST_METHOD(Union) //Add assertions
		{
			initDB();
			TableOperations::setUnion(db.findTable("cars2"), db.findTable("cars"), "car_id");
		}
		TEST_METHOD(Difference) //Add assertions
		{
			initDB();
			TableOperations::setDifference(db.findTable("cars"), db.findTable("cars2"), "car_id");
			TableOperations::setDifference(db.findTable("cars2"), db.findTable("cars2"), "car_id");
			TableOperations::setDifference(db.findTable("cars2"), db.findTable("cars"), "car_id");
		}
		//Need to complete
		TEST_METHOD(Project)
		{

		}
		TEST_METHOD(Select)
		{

		}
		TEST_METHOD(Rename)
		{

		}
		TEST_METHOD(NaturalJoin)
		{

		}
	};
}