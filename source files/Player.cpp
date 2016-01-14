#include "Player.h"
#include "genericFunctions.h"

using namespace std;


Player::Player() //Default constructor for the Player class
{
	id = 0;
	playerName = "";
	score = 0;
	boolAI = false;
	playerBones.reserve(21);
}


Player::Player(string name) //Constructor for the Player class
{
	id = 0;
	playerName = name;
	score = 0;
	boolAI = false;
	playerBones.reserve(21);
}

int Player::highestDouble() //Returns the highest double in a players hand (used in the first move of the CPU)
{
	unsigned int highest = 0;
	int returnInt = -1;
	for (unsigned int i = 0; i < playerBones.size(); i++)
	{
		if (playerBones[i].isDouble())
			if (playerBones[i].getValue1()>=highest)
			{
				highest = playerBones[i].getValue1();
				returnInt = i;
				if (playerBones[i].getValue1() == 5) //5-5 is the best possible first move
					break;
			}		
	}
	return returnInt;
}

void Player::setAI() //Set's a player as CPU controlled
{
	stringstream ss;
	playerName = "Computer";
	ss << playerName << id;
	ss >> playerName;
	boolAI = true;
}

unsigned int Player::getID() //Gets the ID of the player
{
	return id;
}


int Player::getNumPlayerBones() //Gets the number of bones in the player's hand
{
	return playerBones.size();
}


vector<Bone>& Player::getPlayerBones() //Returns the address of the first element of the player's bone vector
{
	return playerBones;
}


string Player::getPlayerName() //Returns the player's name
{
	return playerName;
}


int Player::getScore() //Returns the player's score
{
	return score;
}

bool Player::hasBone(Bone b) //Returns true if the player has any bones in his hand and false if he hasn't
{
	for (unsigned int i = 0; i < playerBones.size(); i++)
		if (b == playerBones[i])
			return true;
	return false;
}

void Player::setPlayerName(string name) //Sets the name of the player
{
	playerName = name;
}


void Player::addBone(Bone b) //Adds a bone to the player's hand
{
	playerBones.push_back(b);
}


void Player::addScore(int s) //Adds a given number of points to the player's score
{
	score = score + s;
}

void Player::displayPlayerUI() //Displays the player interface
{
	gotoxy(0,51);
	setBackGroundColor(GREEN);
	for (int i = 0; i < 121; i++)
		cout << ' ';
	setBackGroundColor(BLACK);
	setcolor(GREEN);
	int numChars = playerBones.size();
	numChars = 60 - (playerBones.size()*6 - 1)/2;
	gotoxy(1,53);
	cout << "Current Player: ";        //The current player name
	if (playerName == "")
		cout << "Player " << id;
	else
		cout << playerName;
	
	if (isAI())
		return;
	else							   //if it's not a CPU controlled player, display the pieces on the player hand
		for (unsigned int i = 0; i < playerBones.size(); i++)
		{
			gotoxy(numChars+2,55);
			cout << i+1;
			playerBones[i].display(numChars,56);
			cout << ' ';
			numChars = numChars + 6;
		}
	setcolor(GREEN);
}

void Player::setPlayerID(unsigned int playerID) //Sets the player ID
{
	id = playerID;
}

bool Player::removeBone(Bone b) //Removes a bone from the player's hand
{
	if (playerBones.size() == 0)
		return false;
	else
	{
		unsigned int i;
		for (i = 0; i < playerBones.size(); i++)
			if (playerBones[i] == b)
				break;
		removeFromVector(playerBones, (int)i);
		return true;
	}
}

bool Player::isAI() //Returns true if the player is CPU controlled and false if it isn't
{
	return boolAI;
}