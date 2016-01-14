#ifndef GENERICFUNCTIONS_H
#define GENERICFUNCTIONS_H 

#include <vector>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
#include <algorithm>
#include "checkos.h"

class Game;
class Player;
class Bone;

using namespace std;

template <typename T>
void removeFromVector(vector<T> &vec, int vecPos) //Template for a function that removes a value from a vector and rearranges it
{
	for (unsigned int i = vecPos; i < vec.size(); i++)
	{
		if (i + 1 == vec.size())
		{
			vec.pop_back();
		}
		else
		{
			T temp = vec[vecPos];
			vec[vecPos] = vec[vecPos+1];
			vec[vecPos+1] = temp;
			vecPos++;
		}
	}
}

template <typename X>
void insertAtFront(vector<X> &vec, X tempX) //Template for a function that inserts a value at the front of a vector
{
	vec.push_back(vec[vec.size()-1]);
	for (int i = vec.size()-1; i >= 0; i--)
	{
		if (i == 0)
			vec[i] = tempX;
		else
			vec[i] = vec[i-1];
	}
}

int roundto5(int nr); //Rounds a number to be a multiple of five

void eraseLine(int y); //Erases a line of text

//Some functions for display and extraction purposes (using std::cout and std::cin)

void askForNames(vector<string> &vec, int numNames); //Asks for the players' names at the beginning of the game

void displayDrawMsg(); //Displays a message if the game ends with a drow

void displayWinner(Player* playerPtr); //Displays the winner of the match

bool displayInstructions(); //Displays the instructions

bool displayStart(); //Displays the start menu

void askForPlayers(vector<Player> &humanPlayers, vector<Player> &AIPlayers); //Displays the menu for player configuration

#endif
