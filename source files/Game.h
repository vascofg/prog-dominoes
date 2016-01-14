#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Boneyard.h"
#include "Player.h"

class Bone;

class Game
{

public:
	Game(); //Default constructor for the Game class
	Player* getPlayerByID(unsigned int id); //Returns a pointer to the Player identified by the given ID
	bool addPlayer(Player p); //Adds a human player to the game
	bool addAI(Player p); //Adds a CPU player to the game
	void start(vector<Player> &vecPlayers, vector<Player> &vecAI); //Initializes the variables and displays the menu
	void play(); //Starts the game
	void end(unsigned int playerWithoutBonesID, bool blocked); //Given the player with less bones and a bool that represents the state of the game when finished (blocked or not), ends the game
	void displayScore(); //Displays the score table
	void displayScore(unsigned int winner); //Overloaded function that displays the score table and the winner of the game (used at the end of the match)
	void displayCompassRose(); //Displays the compass rose
	unsigned int findFirstPlayer(); //Finds the player that shall play first
	bool AIgetOption(unsigned int playerID, int &option, char &row); //Returns true if a good play option was found for the CPU player and false if one wasn't
	void askForOption(unsigned int playerID, int &option, char &row);
	bool playBone(unsigned int playerID, Bone bone, char row); //Given a player ID, a bone and a direction puts a bone into play. Returns true if successful (valid move) and false otherwise
	bool isBonePlayable(Bone bone); //Returns true if a bone is playable and false if it isn't
	bool hasPlayableBone(unsigned int playerID); //Returns true if a given player has any bones fit for play in that round and false if he hasn't
	bool drawBone(unsigned int playerID); //Draws a bone from the boneyard to the given player's hand

private:
	Board board; //The game board
	Boneyard boneyard; //The boneyard (stack of bones that are not in any players' hands)
	vector<Player> vPlayers; //The vector of all the players (CPU and not)
	unsigned int currentPlayer; //The number of the player that's currently playing

};
#endif