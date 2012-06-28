#include <string>
#include <iostream>
#include <sqlite3.h>

#include "sql_utils.h"
#include "GeneratePlayers.h"

using namespace std;

int main()
{
	GeneratePlayers();
	//szSQL = "select * from myTable";
	//rc = sqlite3_exec(database,szSQL,callback,0,&zErrMsg);
	return 0;
}