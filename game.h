#pragma once

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// char aary for print bord --->
extern char space[3][3];


// place marker of player to her/his choice --->
bool placemarker(int choice, char mark);

// function to decleare the winner --->
bool winner(char mark);

// function to reset the game bord --->
void resetbord();

// mode for vs AI ---->
int modeai();

#endif // !GAME_H

