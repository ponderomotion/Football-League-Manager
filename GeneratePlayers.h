// functions for generating random players
#ifndef GENERATEPLAYERS_H
#define GENERATEPLAYERS_H

#include <vector>
#include <string>

#include "sql_utils.h"

using namespace std;

// Create random database of players
void GeneratePlayers();
string returnPosition(int randomnumber);
void loadNames(vector<string>& firstnames, vector<string>& lastnames);

#endif