#include <cstdlib>
#include <sqlite3.h>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "GeneratePlayers.h"
#include "sql_utils.h"

using namespace std;
// function to create and populate a database of players

const int num_players = 500;

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

	// SQL wrapper requires C style char *
	// buffers
	char cpos[30];
	char cfname[30];
	char clname[30];

	string fname;
	string lname;
	vector<string> fnames;
	vector<string> lnames;

	int num_first_names;
	int num_last_names;

	//populate lists of firstnames and lastnames
	loadNames(fnames, lnames);

	num_first_names = fnames.size();
	num_last_names = lnames.size();

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

		strcpy(cfname,fnames[FirstNameIndex].c_str());
		strcpy(clname,lnames[LastNameIndex].c_str());

		strcpy(cpos,returnPosition((rand() % 10)).c_str());
		//Position = returnPosition((rand() % 10));
		//Position = "Forward";

		// skill level 1-10
		SkillLevel = rand() % 10 + 1;
		// Age range 15-40
		Age = rand() % 25 + 15;
		// Value(price) - (This needs to be smarter)
		Value = SkillLevel * 10000;
		//insert record into players table
		RunInsertParamSQL(playersdb,cfname,clname,cpos,Age, Value, SkillLevel);
		//cout << i << endl;
	}
	sqlite3_close(playersdb);
}

// return position so players are distributed in ratio:
// 1GK : 4DEF : 4MID : 2ATT
// random number needs to be a uniform integer in
// the range [0-10]
string returnPosition(int randomnumber){

	string Position;

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

// Load first and last names
void loadNames(vector<string>& firstnames, vector<string>& lastnames)
{
	//add firstnames
	firstnames.push_back("Daniel");;	firstnames.push_back("Steven");
	firstnames.push_back("Alan");
	firstnames.push_back("Peter");
	firstnames.push_back("Joe");
	firstnames.push_back("Oliver");
	firstnames.push_back("Jack");
	firstnames.push_back("Thomas");
	firstnames.push_back("Charlie");
	firstnames.push_back("James");
	firstnames.push_back("Sean");
	firstnames.push_back("Richard");
	firstnames.push_back("Aiden");
	firstnames.push_back("Keith");
	firstnames.push_back("Kevin");
	firstnames.push_back("Robbie");
	firstnames.push_back("Damien");
	firstnames.push_back("Keiren");
	firstnames.push_back("Shane");
	firstnames.push_back("David");
	firstnames.push_back("Ronald");
	firstnames.push_back("Jermaine");
	firstnames.push_back("Brett");
	firstnames.push_back("Edgar");
	firstnames.push_back("Humphrey");
	firstnames.push_back("Larry");
	firstnames.push_back("George");
	firstnames.push_back("Isaac");
	firstnames.push_back("Alfred");
	firstnames.push_back("Rupert");
	firstnames.push_back("Theodore");
	firstnames.push_back("Howard");
	firstnames.push_back("Sebastian");
	firstnames.push_back("Montgomery");
	firstnames.push_back("Hugh");
	firstnames.push_back("Charles");
	firstnames.push_back("Bertram");
	firstnames.push_back("Clarence");
	firstnames.push_back("Gerald");
	firstnames.push_back("Horace");
	firstnames.push_back("Miles");
	firstnames.push_back("Bartholomew");
	firstnames.push_back("Wilfred");
	firstnames.push_back("Jeremy");
	firstnames.push_back("Mike");
	firstnames.push_back("Billy");
	firstnames.push_back("Patrick");
	firstnames.push_back("David");
	firstnames.push_back("Robert");
	firstnames.push_back("Martin");
	firstnames.push_back("Ryan");
	firstnames.push_back("Andrew");
	firstnames.push_back("Adam");
	firstnames.push_back("Matt");
	firstnames.push_back("Alistair");
	firstnames.push_back("Ben");
	firstnames.push_back("Paul");
	firstnames.push_back("Greg");
	firstnames.push_back("Simon");
	firstnames.push_back("Sophie");
	firstnames.push_back("Luke");
	firstnames.push_back("Lawrence");
	firstnames.push_back("Brinsley");
	firstnames.push_back("Pierre");
	firstnames.push_back("Aaron");
	firstnames.push_back("Alex");
	firstnames.push_back("Tom");
	firstnames.push_back("Neil");
	firstnames.push_back("Kerry");
	firstnames.push_back("Ross");
	firstnames.push_back("Gary");
	firstnames.push_back("Tony");
	firstnames.push_back("Jake");
	firstnames.push_back("Trey");
	firstnames.push_back("Nigel");
	firstnames.push_back("Barry");
	firstnames.push_back("Ieuan");
	firstnames.push_back("Iolo");
	firstnames.push_back("Adam");
	firstnames.push_back("Joe");


	//add lastnames
	lastnames.push_back("Smith");
	lastnames.push_back("Jones");
	lastnames.push_back("Taylor");
	lastnames.push_back("Williams");
	lastnames.push_back("Brown");
	lastnames.push_back("Davies");
	lastnames.push_back("Evans");
	lastnames.push_back("Wilson");
	lastnames.push_back("Thomas");
	lastnames.push_back("Roberts");
	lastnames.push_back("Fletcher");
	lastnames.push_back("Kelly");
	lastnames.push_back("Cole");
	lastnames.push_back("Dyer");
	lastnames.push_back("Keane");
	lastnames.push_back("McClean");
	lastnames.push_back("McDonald");
	lastnames.push_back("Ward");
	lastnames.push_back("Whitehouse");
	lastnames.push_back("Babbage");
	lastnames.push_back("Crick");
	lastnames.push_back("Hargreaves");
	lastnames.push_back("Hawking");
	lastnames.push_back("Heaviside");
	lastnames.push_back("Newton");
	lastnames.push_back("Young");
	lastnames.push_back("Higgs");
	lastnames.push_back("Cox");
	lastnames.push_back("Turing");
	lastnames.push_back("Rees");
	lastnames.push_back("Bacon");
	lastnames.push_back("McCartney");
	lastnames.push_back("Lennon");
	lastnames.push_back("Starkey");
	lastnames.push_back("Plant");
	lastnames.push_back("Morissey");
	lastnames.push_back("Lowe");
	lastnames.push_back("Ireland");
	lastnames.push_back("Irving");
	lastnames.push_back("Mellor");
	lastnames.push_back("McKenzie");
	lastnames.push_back("Clement");
	lastnames.push_back("Roberto");
	lastnames.push_back("Hunt");
	lastnames.push_back("Allerton");
	lastnames.push_back("Bradford");
	lastnames.push_back("Brewster");
	lastnames.push_back("Carver");
	lastnames.push_back("Chilton");
	lastnames.push_back("Cooke");
	lastnames.push_back("Cooper");
	lastnames.push_back("Crackstone");
	lastnames.push_back("Crutcher");
	lastnames.push_back("Cushman");
	lastnames.push_back("Fuller");
	lastnames.push_back("Goodman");
	lastnames.push_back("Minter");
	lastnames.push_back("Priest");
	lastnames.push_back("Samson");
	lastnames.push_back("Tilley");
	lastnames.push_back("Tinker");
	lastnames.push_back("Turner");
	lastnames.push_back("Winslow");
	lastnames.push_back("Billington");
	lastnames.push_back("Eaton");
	lastnames.push_back("Goffrey");
	lastnames.push_back("Hopkins");
	lastnames.push_back("Margesson");
	lastnames.push_back("Mullins");
	lastnames.push_back("Prower");
	lastnames.push_back("Rigsdale");
	lastnames.push_back("Warren");
	lastnames.push_back("Standish");
	lastnames.push_back("Alden");
	lastnames.push_back("English");
	lastnames.push_back("Button");
	lastnames.push_back("Carter");
	lastnames.push_back("Hooke");
	lastnames.push_back("Wilkinson");
	lastnames.push_back("Storey");
	lastnames.push_back("Travis");
	lastnames.push_back("Phillips");
	lastnames.push_back("Collyer");
	lastnames.push_back("McDermott");
	lastnames.push_back("Staniforth");
	lastnames.push_back("Hempshall");
	lastnames.push_back("Barraclough");
	lastnames.push_back("Marshall");
	lastnames.push_back("Bowling");
	lastnames.push_back("Jennings");
	lastnames.push_back("Boyd");
	lastnames.push_back("Lee");
	lastnames.push_back("Finnegan");
	lastnames.push_back("Cuthbertson");
	lastnames.push_back("Lake");
	lastnames.push_back("Gray");
	lastnames.push_back("Norrel");
	lastnames.push_back("Kissane");
	lastnames.push_back("Bown");
	lastnames.push_back("Denny");
	lastnames.push_back("Vann");
	lastnames.push_back("Whittam");
	lastnames.push_back("Porter");
	lastnames.push_back("Hayward");
	lastnames.push_back("Reynolds");
	lastnames.push_back("Baxter");
	lastnames.push_back("Sugden");
	lastnames.push_back("Coggin");
	lastnames.push_back("Smeaton");
	lastnames.push_back("Thurling");
	lastnames.push_back("Wilde");
	lastnames.push_back("Sambrook");
	lastnames.push_back("Pilarz");
	lastnames.push_back("Merrick");
	lastnames.push_back("Brearly");
	lastnames.push_back("Butterworth");
	lastnames.push_back("Barron");
	lastnames.push_back("Brito");
	lastnames.push_back("Hardiment");
	lastnames.push_back("Wells");
	lastnames.push_back("Ross");
	lastnames.push_back("Raw");
	lastnames.push_back("Webster");
	lastnames.push_back("Nichols");
	lastnames.push_back("Alexander");
	lastnames.push_back("Newbold");
	lastnames.push_back("Holloway");
	lastnames.push_back("Tesh");
	lastnames.push_back("Wolstencroft");
	lastnames.push_back("Appleyard");
	lastnames.push_back("Hollands");
	lastnames.push_back("Coffey");
	lastnames.push_back("Hardy");
	lastnames.push_back("Quinn");
	lastnames.push_back("McAllister");
	lastnames.push_back("Doyle");
	lastnames.push_back("Howard");
	lastnames.push_back("Maguire");
	lastnames.push_back("Cork");
	lastnames.push_back("Warnock");
	lastnames.push_back("Agana");
	lastnames.push_back("Morris");
	lastnames.push_back("Edwards");
	lastnames.push_back("Hatton");
	lastnames.push_back("Beagrie");
	lastnames.push_back("Kendall");
	lastnames.push_back("Tonge");
	lastnames.push_back("Gillespie");
	lastnames.push_back("Webber");
	lastnames.push_back("Stead");
	lastnames.push_back("Speed");
	lastnames.push_back("Shearer");
	lastnames.push_back("Dunne");
	lastnames.push_back("Clegg");
	lastnames.push_back("Partridge");
	lastnames.push_back("Pegg");
	lastnames.push_back("Frost");
	lastnames.push_back("Barron");
	lastnames.push_back("Leek");
	lastnames.push_back("Stone");
	lastnames.push_back("Parker");
	lastnames.push_back("Buxton");
	lastnames.push_back("Cornish");

}


