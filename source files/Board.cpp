#include "Board.h"
#include "genericFunctions.h"
#include <cctype>
#include <iostream>


Board::Board() //Constructor for the Board class
{
	spinner = Bone();
	rightRow.reserve(28);
	leftRow.reserve(27);
	topRow.reserve(25);
	bottomRow.reserve(25);
}


void Board::addSpinner(Bone b) //Adds a spinner to the board
{
	spinner = b;
}

void Board::addSpinnerByRow(Bone b, char row) //used if the first bone wasnt a double
{
	if (toupper(row) == 'E')
	{
		leftRow = rightRow;
		vector<Bone> tempRow;
		rightRow = tempRow;
		for (unsigned int i = 1; i < leftRow.size(); i++)	//first bone needs no change
		{
			Bone tempBone = leftRow[i];
			tempBone.swap();
			leftRow[i] = tempBone;
		}
		for (unsigned int i = 0; i < leftRow.size(); i++)
		{
			Bone tempBone = leftRow[i];
			leftRow[i] = leftRow[leftRow.size()-1-i];
			leftRow[leftRow.size()-1-i] = tempBone;
		}
	}
	else
	{
		Bone tempBone = rightRow[0];
		tempBone.swap();
		rightRow[0] = tempBone;
	}
	addSpinner(b);
}

void Board::addToBoard(Bone b, char row) //Adds a bone to the board
{
	unsigned int lastValue = getLastValueByRow(row);
	if (!b.isDouble())
	{
		if (b.getValue2() == lastValue)
			b.swap();
	}

	if (toupper(row) == 'W' && !hasSpinner())
	{
		Bone tempBone = rightRow[0];
		tempBone.swap();
		rightRow[0] = tempBone;
		if (b.getValue2() == tempBone.getValue1())
			b.swap();
		insertAtFront(rightRow, b);
	}
	else
		getRow(row).push_back(b);
}

vector<Bone>& Board::getRow(char row) //Returns the vector of bones that correspondes to the letter given as an argument (N/S/E/W)
{
	switch (toupper(row))
	{
	case 'N':
		return topRow;
		break;
	case 'S':
		return bottomRow;
		break;
	case 'E':
		return rightRow;
		break;
	case 'W':
		return leftRow;
	}
	return leftRow;
}

bool Board::hasSpinner() //Returns true if the spinner is the board or false if it isn't
{
	if (spinner.getValue1() == 7)
		return false;
	else
		return true;
}

unsigned int Board::getLastValueByRow(char row) //Gets the value of the last bone on the row
{
	vector<Bone> vecRow = getRow(row);
	Bone lastBone;
	if (vecRow.size() == 0)
		if (toupper(row) == 'W' && !hasSpinner())
		{
			lastBone = rightRow[0];
			if (rightRow.size() == 1)
				lastBone.swap();
		}
		else if (!hasSpinner())
			lastBone = Bone();
		else
			lastBone = *getSpinner();
	else
		lastBone = vecRow[vecRow.size() - 1];
	if (toupper(row) == 'E' && !hasSpinner() && vecRow.size() == 1)
		return lastBone.getValue1();
	else
		return lastBone.getValue2();
}

Bone* Board::getSpinner() //Returns a pointer to the spinner
{
	Bone* bonePtr;
	bonePtr = &spinner;
	return bonePtr;
}

int Board::getScoreOfRow(char row) //Gets the total score of a given row
{
	vector<Bone> vecRow = getRow(row);
	if (vecRow.size() != 0)
	{
		Bone tempBone = vecRow[vecRow.size()-1];
		if (tempBone.isDouble())
			return 2 * tempBone.getValue2();
		else if (!hasSpinner() && vecRow.size() == 1)
			return tempBone.getValue1();
		else
			return tempBone.getValue2();
	}
	else if (hasSpinner() && (toupper(row) == 'E' || toupper(row) == 'W'))
		return 0;
	else if (hasSpinner())
		return spinner.getValue1();
	else if (toupper(row) == 'W' && rightRow.size() > 0)
		return rightRow[0].getValue2();
	else
		return 0;
}

int Board::getBoardSum() //Gets the sum of all the rows' scores
{
	int sum;
	sum = getScoreOfRow('N') + getScoreOfRow('S') + getScoreOfRow('E') + getScoreOfRow('W');
	return sum;
}

bool Board::display() //Displays the board
{
	if (!hasSpinner() && rightRow.size() == 0)
		return false;

	if (!hasSpinner())  //if no spinner is in the board
	{
		vector<Bone> vecRow = getRow('e');
		int numChars = vecRow.size()*4;
		numChars = 60 - numChars/2;
		int x = numChars;
		int y = 27;
		for (unsigned int i = 0; i < vecRow.size(); i++)
		{
			Bone tempBone = vecRow[i];
			if (i == 0)
				tempBone.swap();
			tempBone.display(x,y,'e');
		}
	}
	else               //if there is a spinner on the board
	{
		int tempX = 60;
		int tempY = 27;
		spinner.display(tempX,tempY,'e');

		if (rightRow.size() != 0)
		{
			int x = 62;
			int y = 27;
			bool up = false;
			bool left = false;
			bool lastDouble = false;
			for (unsigned int i = 0; i < rightRow.size(); i++) //the following code accounts for the possibility of the bones coming out of the board's limits
			{
				if (x >= 114 && !up)
				{
					up = true;
					if (lastDouble)
					{
						y = y - 3;
						x = x - 2;
					}
					else
					{
						x = x - 2;
						y = y - 2;
					}
				}
				if (y <= 8 && !left)
				{
					left = true;
					if (lastDouble)
					{
						y = y + 2;
						x = x - 3;
					}
					else
					{
						y = y + 2;
						x = x - 2;
					}
				}

				if (up)
					if (left)
						rightRow[i].display(x,y,'w');
					else
						rightRow[i].display(x,y,'n');
				else
					rightRow[i].display(x,y,'e');

				if (rightRow[i].isDouble())
					lastDouble = true;
				else
					lastDouble = false;
			}
		}

		if (leftRow.size() != 0)
		{
			int x = 58;
			int y = 27;
			bool down = false;
			bool right = false;
			bool lastDouble = false;
			for (unsigned int i = 0; i < leftRow.size(); i++)
			{
				if (x <= 4 && !down)
				{
					down = true;
					if (lastDouble)
					{
						x = x + 2;
						y = y + 3;
					}
					else
					{
						x = x + 2;
						y = y + 2;
					}
				}
				if (y >= 45 && !right)
				{
					right = true;
					if (lastDouble)
					{
						y = y - 2;
						x = x + 3;
					}
					else
					{
						y = y - 2;
						x = x + 2;
					}
				}

				if (down)
					if (right)
						leftRow[i].display(x,y,'e');
					else
						leftRow[i].display(x,y,'s');
				else
					leftRow[i].display(x,y,'w');

				if (leftRow[i].isDouble())
					lastDouble = true;
				else
					lastDouble = false;
			}
		}

		if (topRow.size() != 0)
		{
			int x = 60;
			int y = 24;
			bool left = false;
			bool down = false;
			bool lastDouble = false;
 			for (unsigned int i = 0; i < topRow.size(); i++)
			{				
				if (x <= 20 && !down)
				{
					down = true;
					if (lastDouble)
					{
						x = x + 2;
						y = y + 3;
					}
					else
					{
						x = x + 2;
						y = y + 2;
					}
				}
				if (y <= 5 && !left)
				{
					left = true;
					if (lastDouble)
					{
						y = y + 2;
						x = x - 3;
					}
					else
					{
						y = y + 2;
						x = x - 2;
					}
				}

				if (left)
					if (down)
						topRow[i].display(x,y,'s');
					else
						topRow[i].display(x,y,'w');
				else
					topRow[i].display(x,y,'n');

				if (topRow[i].isDouble())
					lastDouble = true;
				else
					lastDouble = false;
			}
		}

		if (bottomRow.size() != 0)
		{
			int x = 60;
			int y = 30;
			bool right = false;
			bool up = false;
			bool lastDouble = false;
			for (unsigned int i = 0; i < bottomRow.size(); i++)
			{
				if (x >= 114 && !up)
				{
					up = true;
					if (lastDouble)
					{
						x = x - 2;
						y = y - 3;
					}
					else
					{
						x = x - 2;
						y = y - 2;
					}
				}
				if (y >= 45 && !right)
				{
					right = true;
					if (lastDouble)
					{
						y = y - 2;
						x = x + 3;
					}
					else
					{
						y = y - 2;
						x = x + 2;
					}
				}

				if (right)
					if (up)
						bottomRow[i].display(x,y,'n');
					else
						bottomRow[i].display(x,y,'e');
				else
					bottomRow[i].display(x,y,'s');

				if (bottomRow[i].isDouble())
					lastDouble = true;
				else
					lastDouble = false;
			}
		}

	}


	return true;
}
