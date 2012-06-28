#include <sqlite3.h>
#include <cstdio>
#include <cstring>
#include <iostream>

#include "sql_utils.h"

using namespace std;
/*void RunUpdateParamSQL(sqlite3 *db, int age, char *fn)
{
	if (!db)
		return;

	char *zErrMsg = 0;
	sqlite3_stmt *stmt;
	const char *pzTest;
	char *szSQL;

	// insert data item into myTable
	szSQL = "update myTable set Age = ? where FirstName = ?";

	int rc = sqlite3_prepare(db,szSQL,strlen(szSQL),&stmt, &pzTest);

	if (rc == SQLITE_OK){
		//bind the value
		sqlite3_bind_int(stmt, 1, age);
		sqlite3_bind_text(stmt,2,fn,strlen(fn),0);

		//commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
}*/

// Insert record
void RunInsertParamSQL(sqlite3 *db, char* fn, char* ln, char* pos, int age, int value, int skill)
{
  if (!db)
    return;

  char *zErrMsg = 0;
  sqlite3_stmt *stmt;
  const char *pzTest;
  char *szSQL;

  // Insert data item into myTable
  szSQL = "insert into allPlayers (FirstName, LastName, Position, Age, Value, SkillLevel) values (?,?,?,?,?,?)";

  int rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);

  if( rc == SQLITE_OK ) {
    // bind the value 
    sqlite3_bind_text(stmt, 1, fn, strlen(fn), 0);
    sqlite3_bind_text(stmt, 2, ln, strlen(ln), 0);
    sqlite3_bind_text(stmt, 3, pos, strlen(pos), 0);
    sqlite3_bind_int(stmt, 4, age);
    sqlite3_bind_int(stmt, 5, value);
    sqlite3_bind_int(stmt, 6, skill);

    // commit 
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }
  else
  {
    cout << "ERRORORORSSSS!!!" << endl;
    cout << strlen(szSQL) << endl;
  }
}

int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
  }