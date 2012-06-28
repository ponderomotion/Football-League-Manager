#ifndef SQL_UTILS_H
#define SQL_UTILS_H

#include <sqlite3.h>

using namespace std;

//void RunUpdateParamSQL(sqlite3 *db, int age, char *fn);
void RunInsertParamSQL(sqlite3 *db, char* fn,char* ln,char* pos, int age, int value, int skill);
int callback(void *NotUsed, int argc, char **argv, char **azColName);


#endif