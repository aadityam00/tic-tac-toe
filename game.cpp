#include "game.h"

// var for set aarry --->
int row;
int coloum;

// char aary for print bord --->
char space[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };


// place marker of player to her/his choice --->
bool placemarker(int choice, char mark)
{
	row = (choice - 1) / 3;
	coloum = (choice - 1) % 3;

	if (choice < 1 || choice > 9 || space[row][coloum] == 'O' || space[row][coloum] == 'X')
	{
		cout << "invelid choice ! try again." << endl;
		return false;
	}
	else
	{
		space[row][coloum] = mark;
		return true;
	}
	return false;
}

// function to decleare the winner --->
bool winner(char mark)
{
	for (int j = 0; j < 3; j++)
	{
		if (space[j][0] == mark && space[j][1] == mark && space[j][2] == mark ||
			space[0][j] == mark && space[1][j] == mark && space[2][j] == mark)
			return true;
	}

	if (space[0][0] == mark && space[1][1] == mark && space[2][2] == mark ||
		space[0][2] == mark && space[1][1] == mark && space[2][0] == mark)
		return true;

	return false;
}

// function to reset the game bord --->
void resetbord()
{
	char val = '1';
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			space[i][j] = val++;
		}
	}
}

// mode for vs AI ---->
int modeai()
{
	int choice;
	do
	{
		choice = rand() % 9 + 1; // Generates number between 1 and 9
		row = (choice - 1) / 3;
		coloum = (choice - 1) % 3;
	} while (space[row][coloum] == 'O' || space[row][coloum] == 'X');
	return choice;
}
