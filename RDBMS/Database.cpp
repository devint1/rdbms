#include "Database.h"


Database::Database()
{
}

void Database::openTable(string filename){
	string line;
	ifstream myfile;
	int lineNumber = 0;
	myfile.open(filename.c_str());
	while (getline(myfile, line)){
		istringstream iss(line);
		vector<string> deliminated_input{ istream_iterator<string>(iss), istream_iterator<string>() };

	}
	myfile.close();
}

Database::~Database()
{
}
