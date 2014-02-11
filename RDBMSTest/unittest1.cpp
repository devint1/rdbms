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
			//db.UpdateTable("cars", "")
			vector<string> vals = { "646", "Lamborghini", "Gallardo", "11" };
			db.insertIntoTable("cars", vals);
			db.deleteFromTable("cars", "Make", "ford");
			db.updateTable("cars", "Model", "Celica", "Model", "corolla");
			vector<string> attNames = { "firstName", "lastName", "email", "cars" };
			vector<string> attTypes = { "varchar(255)", "varchar(255)", "varchar(255)", "varchar(255)" };
			vector<string> primKeys = { "email" };
			db.createTable("users", attNames, attTypes, primKeys);
			db.showTable("cars");
			db.showTable("users");
			db.writeTable("users");
			db.closeTable("users");
			db.openTable("cars2");
		}
	public:
		TEST_METHOD(CrossProduct)
		{
			initDB();
			Table testTable = TableOperations::crossProduct(db.findTable("cars2"), db.findTable("cars"));
			int x = db.findTable("cars2").getTableData().size();
			Assert::AreEqual(testTable.getTableData().size(), db.findTable("cars2").getTableData().size() * db.findTable("cars").getTableData().size());
		}
	};
}