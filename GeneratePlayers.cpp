#include <cstdlib>
#include <sqlite3.h>
#include <ctime>
#include <iostream>

#include "GeneratePlayers.h"
#include "sql_utils.h"

using namespace std;
// function to create and populate a database of players

// List of first names
char *first_names[num_first_names] = {	"Daniel",
										"Steven",
										"Alan",
										"Peter",
										"Joe",
										"Oliver",
										"Jack",
										"Thomas",
										"Charlie",
										"James"};

// List of last names
char *last_names[num_last_names] = {	"Smith",
										"Jones",
										"Taylor",
										"Williams",
										"Brown",
										"Davies",
										"Evans",
										"Wilson",
										"Thomas",
										"Roberts"};


void GeneratePlayers()
{
	sqlite3 *playersdb;
	char *szErrMsg = 0;
	char *szSQL;
	int rc;

	int SkillLevel;
	int Value;
	int FirstNameIndex;
	int LastNameIndex;
	int Age;

	char *Position;
	char *Fname;
	char *Lname;

	//srand(time(NULL));
	srand(10); //deterministic database

	// create database
	rc = sqlite3_open("players.sqlite", &playersdb);
	if(rc)
	{
		// database failed to open
		cerr << "Cant Open Database" << endl;
	}

	// SQL Command
	szSQL = "create table allPlayers (FirstName varchar(30),LastName varchar(30),Position varchar(10), Age smallint not null, Value bigint, SkillLevel smallint)";
	rc = sqlite3_exec(playersdb,szSQL,callback,0,&szErrMsg);

	if(rc != SQLITE_OK)
    {
      std::cout << "SQL Error: " << szErrMsg << std::endl;
      sqlite3_free(szErrMsg);
    }  

	cout << "Generating Players..." << endl;
	// Populate database with random players
	for(int i=0;i<num_players;i++){
		/* Generate Random Attributes */

		FirstNameIndex = rand() % num_first_names;
		LastNameIndex = rand() % num_last_names;
		Fname = first_names[FirstNameIndex];
		Lname = last_names[LastNameIndex];
		//Fname = "Daniel";
		//Lname = "Fletcher";

		Position = returnPosition((rand() % 10));
		//Position = "Forward";

		// skill level 1-10
		SkillLevel = rand() % 10 + 1;
		// Age range 15-40
		Age = rand() % 25 + 15;
		// Value(price) - (This needs to be smarter)
		Value = SkillLevel * 10000;
		//insert record into players table
		RunInsertParamSQL(playersdb,Fname,Lname,Position,Age, Value, SkillLevel);
		//cout << i << endl;
	}
	sqlite3_close(playersdb);
}

// return position so players are distributed in ratio:
// 1GK : 4DEF : 4MID : 2ATT
// random number needs to be a uniform integer in
// the range [0-10]
char *returnPosition(int randomnumber){

	char *Position;


	if(randomnumber>0 && randomnumber<5){
		Position = "Defender";
	}
	else if(randomnumber>4 && randomnumber<9){
		Position = "Midfield";
	}
	else if(randomnumber>8){
		Position = "Attack";
	}
	else{
		Position = "Goalkeeper";
	}
	return Position;

}


