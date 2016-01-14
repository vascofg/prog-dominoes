#ifndef PLAYER_H
#define PLAYER_H 

#include <vector>
#include <string>
#include "Bone.h"

using namespace std;

class Player {

public:
	Player(); //Default constructor for the Player class
	Player(string name); //Constructor for the Player class
	unsigned int getID(); //Gets the ID of the player
	int getNumPlayerBones(); //Gets the number of bones in the player's hand
	vector<Bone>& getPlayerBones(); //Returns the address of the first element of the player's bone vector
	string getPlayerName(); //Returns the player's name
	int getScore(); //Returns the player's score
	void setPlayerName(string name); //Sets the name of the player
	void setPlayerID(unsigned int playerID); //Sets the player ID
	void addBone(Bone b); //Adds a bone to the player's hand
	void addScore(int s); //Adds a given number of points to the player's score
	bool isAI(); //Returns true if the player is CPU controlled and false if it isn't
	bool hasBone(Bone b); //Returns true if the player has any bones in his hand and false if he hasn't
	void displayPlayerUI(); //Displays the player interface
	bool removeBone(Bone b); //Removes a bone from the player's hand
	void setAI(); //Set's a player as CPU controlled
	int highestDouble(); //Returns the highest double in the player's hand (used in the first move of an AI Player)

private:
	unsigned int id; //The ID of the player
	vector<Bone> playerBones; //The player's hand
	string playerName; //The player's name
	int score; //The player's score
	bool boolAI; //True if the player is CPU controlled and false if he isn't
};
#endif
