// functions for generating random players
#ifndef GENERATEPLAYERS_H
#define GENERATEPLAYERS_H

#include "sql_utils.h"

using namespace std;

const int num_first_names = 10;
const int num_last_names = 10;
const int num_players = 4000;

// Create random database of players
void GeneratePlayers();
char* returnPosition(int randomnumber);

#endif