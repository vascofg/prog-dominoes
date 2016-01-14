#ifndef BOARD_H
#define BOARD_H

#include "Bone.h"
#include <vector>

using namespace std;

class Board
{

public:
	Board(); //Constructor for the Board class
	vector<Bone>& getRow(char row); //Returns the vector of bones that correspondes to the letter given as an argument (N/S/E/W)
	void addSpinner(Bone b); //Adds a spinner to the board
	void addSpinnerByRow(Bone b, char row); //used if the first bone wasnt a double
	void addToBoard(Bone b, char row); //Adds a bone to the board
	unsigned int getLastValueByRow(char row); //Gets the value of the last bone on the row
	int getBoardSum(); //Gets the sum of all the rows' scores
	int getScoreOfRow(char row); //Gets the total score of a given row
	Bone* getSpinner(); //Returns a pointer to the spinner
	bool display(); //Displays the board
	bool hasSpinner(); //Returns true if the spinner is the board or false if it isn't

private:
	Bone spinner; //First double in play
	vector<Bone> bottomRow; //South row of bones
	vector<Bone> leftRow; //West row of bones
	vector<Bone> rightRow; //East row of bones
	vector<Bone> topRow; //North row of bones

};
#endif
