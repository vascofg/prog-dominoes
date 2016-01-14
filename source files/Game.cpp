#include "Game.h"
#include "genericFunctions.h"


using namespace std;

Game::Game() //Default constructor for the Game class
{
	vPlayers.reserve(4);
}

bool Game::drawBone(unsigned int playerID) //Draws a bone from the boneyard to the given player's hand
{
	if (boneyard.isEmpty())
		return false;
	Player* playerPtr = getPlayerByID(playerID);
	Bone drawedBone = boneyard.takeBone();
	playerPtr->addBone(drawedBone);
	return true;
}

Player* Game::getPlayerByID(unsigned int id) //Returns a pointer to the Player identified by the given ID
{
	Player* aPtr;
	vector<Player>::iterator it = (vPlayers.begin() + (id-1));
	aPtr = &(*it);
	return aPtr;
}

bool Game::addPlayer(Player p) //Adds a human player to the game
{
	if (vPlayers.size() == 4)
		return false;
	else
	{
		p.setPlayerID(vPlayers.size() + 1);
		vPlayers.push_back(p);
		return true;
	}
}

bool Game::addAI(Player p) //Adds a CPU player to the game
{
	if (vPlayers.size() == 4)
		return false;
	else
	{
		p.setPlayerID(vPlayers.size()+1);
		p.setAI();
		vPlayers.push_back(p);
		return true;
	}
}

void Game::start(vector<Player> &vecPlayers, vector<Player> &vecAI) //Initializes the variables and displays the menu
{
	
	for (unsigned int i = 0; i < vecPlayers.size(); i++)
		addPlayer(vecPlayers[i]);
	
	for (unsigned int i = 0; i < vecAI.size(); i++)
		addAI(vecAI[i]);

	int numBones;
	if (vPlayers.size() == 2)
		numBones = 7;
	else
		numBones = 5;

	for (size_t i = 0; i < vPlayers.size(); i++)
	{
		for (int k = 1; k <= numBones; k++)
			drawBone(i+1);
	}
	
	currentPlayer = findFirstPlayer();
	play();
}


void Game::play() //Starts the game
{
	setcolor(GREEN);
	bool endGame = false;
	bool blocked = false;
	bool firstRound = true;
	int blockedPlayers = 0;
	unsigned int playerID = 0;
	do
	{
		if (blockedPlayers == vPlayers.size())
		{
			endGame = true;
			blocked = true;
		}
		clrscr();
		displayScore();
		displayCompassRose();
		board.display();
		boneyard.displayNumBones();

		Player* currentPlayerPtr;
		currentPlayerPtr = getPlayerByID(currentPlayer);
			
		int counter = 0;
		while (!hasPlayableBone(currentPlayer))
			if (drawBone(currentPlayer))
				counter++;
			else
				break;

		if (counter != 0) //if there are no bones in hand, some are drawn
		{
			boneyard.displayNumBones();
			eraseLine(59);
			gotoxy(1,59);
			if (currentPlayerPtr->isAI())
				cout << currentPlayerPtr->getPlayerName();
			else
				cout << "You";
			cout << " had no playable bones, therefore " << counter;
			if (counter == 1)
				cout << " bone was drawn!";
			else
				cout << " bones were drawn!";
		}

		currentPlayerPtr->displayPlayerUI();

		if (hasPlayableBone(currentPlayer))
		{
			blockedPlayers = 0;
			bool done;
			do
			{
				done = false;
				int playOption;
				char row;
				if (currentPlayerPtr->isAI()) //if player is CPU controlled find out the best move for this round
					AIgetOption(currentPlayer, playOption, row);
				else //if player is human, ask him for the next move
					askForOption(currentPlayer, playOption, row);

				if (playOption != 0)
					if (playBone(currentPlayer, currentPlayerPtr->getPlayerBones()[playOption-1], row))
					{
						int score = board.getBoardSum();

						if (score % 5 == 0 && score != 0)
						{
							currentPlayerPtr->addScore(score);
							gotoxy(1,54);
							cout << "Player scored " << score << " points!";
						}
						done = true;
					}
				if (!done)
				{
					eraseLine(59);
					gotoxy(1,59);
					cout << "Invalid move!";
					eraseLine(58);
				}
			} while (!done);
		}
		else
		{
			eraseLine(59);
			gotoxy(1,59);
			cout << "No playable bones and empty boneyard!";
			blockedPlayers++;
		}

		clrscr();
		displayScore();
		displayCompassRose();
		board.display();
		boneyard.displayNumBones();
		currentPlayerPtr->displayPlayerUI();
		int score = board.getBoardSum();

		if (score % 5 == 0 && score != 0)
		{
			gotoxy(1,59);
			cout << "Player scored " << score << " points!";
		}

		if (currentPlayerPtr->getNumPlayerBones() == 0)
		{
			playerID = currentPlayerPtr->getID();
			endGame = true;
		}

		eraseLine(58);
		gotoxy(1,58);

		if (!blocked)
		{
			cout << "Press enter to continue...";
			char dummy;
			do
			{
				dummy = _getch();
			}
			while (dummy != 13 && dummy != 10);
			currentPlayer = currentPlayer % vPlayers.size() + 1;
		}
		eraseLine(59);
		eraseLine(54);

	} while (!endGame);
	
	end(playerID, blocked);
}

void Game::end(unsigned int playerID, bool blocked) //Given the winner player, ends the game
{

	bool draw = false;
	Player *winnerPtr;

	if (blocked)
	{
		int minScore = 50000;
		for (size_t i = 0; i < vPlayers.size(); i++)
		{
			Player *pTemp = getPlayerByID(i+1);
			int sum = 0;
			for (int k = 0; k < pTemp->getNumPlayerBones(); k++)
				sum = sum + pTemp->getPlayerBones()[k].getValue1() + pTemp->getPlayerBones()[k].getValue2();
			if (minScore > sum)
			{
				minScore = sum;
				playerID = i+1;
			}
		}
	}

	Player *p = getPlayerByID(playerID);

	int sumScore = 0;
	for (size_t i = 0; i < vPlayers.size()-1; i++)
	{
		unsigned int id = i+1;
		if (id == playerID)
			id = id % vPlayers.size() + 1;
		Player *pTemp = getPlayerByID(id);
		int sum = 0;
		for (int k = 0; k < pTemp->getNumPlayerBones(); k++)
			sum = sum + pTemp->getPlayerBones()[k].getValue1() + pTemp->getPlayerBones()[k].getValue2();
		sumScore = sum + sumScore;
	}
	p->addScore(roundto5(sumScore));
	gotoxy(1,55);
	cout << "Player has played all bones and scores " << roundto5(sumScore) << " points!";


	int maxScore = 0;
	unsigned int winnerID;
	int firstPlayersScore = getPlayerByID(1)->getScore(); //given the first players score, we can detect if theres any score different than this one. if there isn't, all the scores are the same, therefore there's a tie
	bool tie = true;
	for (size_t i = 0; i < vPlayers.size(); i++)
	{
		if (getPlayerByID(i+1)->getScore() > maxScore)
		{
			maxScore = getPlayerByID(i+1)->getScore();
			winnerPtr = getPlayerByID(i+1);
			winnerID = i;
		}
		if (getPlayerByID(i+1)->getScore() != firstPlayersScore)
			tie = false;
	}

	if (maxScore == 0)
		draw = true;

	if (draw | tie)
	{
		displayScore();
		displayDrawMsg();
	}
	else
	{
		displayScore(winnerID);
		displayWinner(winnerPtr);
	}

	eraseLine(59);
	gotoxy(1,58);
	cout << "Press enter to go back to menu...";
	char dummy;
	do
	{
		dummy = _getch();
	}
	while (dummy != 13 && dummy != 10);
	setBackGroundColor(BLACK);
	clrscr();
	cout << endl;
}

void Game::displayCompassRose() //Displays the compass rose
{
	gotoxy(115,1);
	cout << 'N';
	gotoxy(115,2);
	cout << '|';
	gotoxy(111,3);
	cout << "W ----- E";
	gotoxy(115,4);
	cout << '|';
	gotoxy(115,5);
	cout << 'S';
}

void Game::displayScore() //Displays the score table
{
	for (size_t i = 0; i < vPlayers.size(); i++)
	{
		Player* playerPtr = getPlayerByID(i+1);
		int namesize;
		if (playerPtr->getPlayerName().size() == 0)
			namesize = 7;
		else
			namesize = playerPtr->getPlayerName().size();
		gotoxy(11-namesize,i+1);
		if (playerPtr->getPlayerName() == "")
			cout << " Player" << playerPtr->getID() << ": " << playerPtr->getScore();
		else
			cout << " " << playerPtr->getPlayerName() << ": " << playerPtr->getScore();
	}
}

void Game::displayScore(unsigned int winner) //Overloaded function that displays the score table and the winner of the game (used at the end of the match)
{
	for (size_t i = 0; i < vPlayers.size(); i++)
	{
		Player* playerPtr = getPlayerByID(i+1);
		int namesize;
		if (playerPtr->getPlayerName().size() == 0)
			namesize = 7;
		else
			namesize = playerPtr->getPlayerName().size();
		gotoxy(11-namesize,i+1);
		if (playerPtr->getPlayerName() == "")
			cout << " Player" << playerPtr->getID() << ": " << playerPtr->getScore();
		else
			cout << " " << playerPtr->getPlayerName() << ": " << playerPtr->getScore();
		if (i==winner)
			cout << " -> WINNER!";
	}
}

bool Game::hasPlayableBone(unsigned int playerID) //Returns true if a given player has any bones fit for play in that round and false if he hasn't
{
	Player* playerPtr = getPlayerByID(playerID);
	vector<Bone> playerBones = playerPtr->getPlayerBones();
	for (unsigned int i = 0; i < playerBones.size(); i++)
	{
		if (isBonePlayable(playerBones[i]))
			return true;
	}
	return false;
}

unsigned int Game::findFirstPlayer() //Finds the player that shall play first
{
	if (vPlayers.size() == 0)
		return 0;
	else if (vPlayers.size() == 1)
		return 1;
	else
	{
		unsigned int playerID;
		Bone topDouble;
		Bone topBone;
		bool topDoubleExists = false;
		bool topBoneExists = false;

		for (size_t i = 0; i < vPlayers.size(); i++)
		{
			Player* temp = getPlayerByID(i+1);
			vector<Bone> playerBones = temp->getPlayerBones();
			for (unsigned int k = 0; k < playerBones.size(); k++)
			{
				if (playerBones[k].isDouble())
				{
					if (topDoubleExists)
					{
						if (playerBones[k].getValue1() > topDouble.getValue1())
						{
							topDouble = playerBones[k];
							playerID = i+1;
						}
					}
					else
					{
						topDouble = playerBones[k];
						topDoubleExists = true;
						playerID = i+1;
					}
				}
				else
				{
					if (topBoneExists)
					{
						if (playerBones[k].getValue2() > topBone.getValue2())
						{
							topBone = playerBones[k];
							playerID = i+1;
						}
					}
					else
					{
						topBone = playerBones[k];
						topBoneExists = true;
						playerID = i+1;
					}
				}
			}
		}
		return playerID;
	}
}


bool Game::playBone(unsigned int playerID, Bone bone, char row) //Given a player ID, a bone and a direction puts a bone into play. Returns true if successful (valid move) and false otherwise
{
	Player* playerPtr = getPlayerByID(playerID);
	if (!playerPtr->hasBone(bone))
		return false;
	if (toupper(row) == 'N' || toupper(row) == 'S')
		if (board.getRow('e').size() == 0 || board.getRow('w').size() == 0)
			return false;
	vector<Bone> vecRow = board.getRow(row);

	Bone lastBone;
	if (vecRow.size() == 0)
		if (toupper(row) == 'W' && !board.hasSpinner())
			lastBone = board.getRow('E')[0];
		else
			lastBone = *board.getSpinner();
	else
		lastBone = vecRow[vecRow.size()-1];
	unsigned int conValue;
	if (toupper(row) == 'E' && !board.hasSpinner() && vecRow.size() == 1)
		if (lastBone.getValue1() == bone.getValue1())
			conValue = bone.getValue1();
		else if (lastBone.getValue1() == bone.getValue2())
			conValue = bone.getValue2();
		else
			conValue = 7;
	else 
		conValue = whereBonesConnect(lastBone, bone);
	if (conValue != 7)
	{
		if (!board.hasSpinner() && bone.isDouble())
		{
			if (board.getRow('E').size() == 0)
				board.addSpinner(bone);
			else
				board.addSpinnerByRow(bone, row);
		}
		else
			board.addToBoard(bone,row);

		playerPtr->removeBone(bone);

		return true;
		
	}
	else
		return false;
}

bool Game::isBonePlayable(Bone bone) //Returns true if a bone is playable and false if it isn't
{
	vector<Bone> vecRow;
	if (!board.hasSpinner())
	{
		vecRow = board.getRow('e');
		if (vecRow.size() == 0)
			return true;
		else
		{
			Bone lastBone = vecRow[vecRow.size() - 1];
			if (vecRow.size() == 1)
				return (bone.getValue1() == lastBone.getValue1() || bone.getValue1() == lastBone.getValue2() || bone.getValue2() == lastBone.getValue1() || bone.getValue2() == lastBone.getValue2());
			else
				return (whereBonesConnect(vecRow[0],bone) != 7 || whereBonesConnect(vecRow[vecRow.size()-1],bone) != 7);
		}
	}
	else if (board.getRow('e').size() == 0 && board.getRow('w').size() == 0)
		return (whereBonesConnect(*board.getSpinner(), bone) != 7);
	else if (board.getRow('e').size() == 0)
	{
		vecRow = board.getRow('w');
		return (whereBonesConnect(*board.getSpinner(), bone) != 7 || whereBonesConnect(vecRow[vecRow.size()-1], bone) != 7);
	}
	else if (board.getRow('w').size() == 0)
	{
		vecRow = board.getRow('e');
		return (whereBonesConnect(*board.getSpinner(), bone) != 7 || whereBonesConnect(vecRow[vecRow.size()-1], bone) != 7);
	}
	else
	{
		bool isPlayable = true;
		vector<Bone> vecRow = board.getRow('n');
		if (vecRow.size() != 0)
			isPlayable = whereBonesConnect(vecRow[vecRow.size()-1],bone) != 7;
		else
			isPlayable = whereBonesConnect(*board.getSpinner(), bone) != 7;
		if (isPlayable)
			return true;
		else
		{
			isPlayable = true;
			vecRow = board.getRow('s');
			if (vecRow.size() != 0)
				isPlayable = whereBonesConnect(vecRow[vecRow.size()-1],bone) != 7;
			else
				isPlayable = whereBonesConnect(*board.getSpinner(), bone) != 7;
			if (isPlayable)
				return true;
			else
			{
				isPlayable = true;
				vecRow = board.getRow('w');
				if (vecRow.size() != 0)
					isPlayable = whereBonesConnect(vecRow[vecRow.size()-1],bone) != 7;
				else
					isPlayable = whereBonesConnect(*board.getSpinner(), bone) != 7;
				if (isPlayable)
					return true;
				else
				{				
					isPlayable = true;
					vecRow = board.getRow('e');
					if (vecRow.size() != 0)
						isPlayable = whereBonesConnect(vecRow[vecRow.size()-1],bone) != 7;
					else
						isPlayable = whereBonesConnect(*board.getSpinner(), bone) != 7;
					if (isPlayable)
						return true;
				}
			}
		}
	}
	return false;
}

bool Game::AIgetOption(unsigned int playerID, int &option, char &row) //Returns true if a good play option was found for the CPU player and false if one wasn't
{
	Player* AItemp = getPlayerByID(playerID);
	int maxScore = 0;
	option = 0;

	for (int i = 0; i < AItemp->getNumPlayerBones(); i++)
	{
		Bone playBone = AItemp->getPlayerBones()[i];
		if (isBonePlayable(playBone))
		{
			if (!board.hasSpinner() && board.getRow('e').size() == 0)
			{
				if (AItemp->highestDouble() != -1)
					option = AItemp->highestDouble()+1;  //in the first CPU move the highest double it has is played
				else
					option = 0;
				row = 'e';
				break;
			}

			int tempScore = 0;
			int value;
			Bone vecBone;

			vector<Bone> vecRow = board.getRow('e');
			if (vecRow.size() == 0)
				vecBone = *board.getSpinner();
			else
				vecBone = vecRow[vecRow.size() - 1];
			value = whereBonesConnect(vecBone, playBone);
			if (!(value == vecBone.getValue2() && vecRow.size() == 1 && !board.hasSpinner()))
				if (value != 7)
				{
					tempScore = board.getScoreOfRow('w') + board.getScoreOfRow('n') + board.getScoreOfRow('s');
					if (playBone.isDouble())
						tempScore = tempScore + 2 * value;
					else
						tempScore = tempScore + value;

					if (tempScore >= maxScore)
					{
						option = i+1;
						row = 'e';
						maxScore = tempScore;
					}
					tempScore = 0;
				}

			vecRow = board.getRow('w');
			if (vecRow.size() == 0 && !board.hasSpinner())
			{
				vecRow = board.getRow('e');
				vecBone = vecRow[0];
			}
			else if (vecRow.size() == 0)
				vecBone = *board.getSpinner();
			else
				vecBone = vecRow[vecRow.size() - 1];
			value = whereBonesConnect(vecBone, playBone);		
			if (value != 7)
			{
				tempScore = board.getScoreOfRow('e') + board.getScoreOfRow('n') + board.getScoreOfRow('s');
				if (playBone.isDouble())
					tempScore = tempScore + 2 * value;
				else
					tempScore = tempScore + value;

				if (tempScore >= maxScore)
				{
					option = i+1;
					row = 'w';
					maxScore = tempScore;
				}

				tempScore = 0;
			}

			if (board.getRow('e').size() != 0 && board.getRow('w').size() != 0)
			{
				vecRow = board.getRow('n');		
				if (vecRow.size() == 0)
					vecBone = *board.getSpinner();
				else
					vecBone = vecRow[vecRow.size() - 1];
				value = whereBonesConnect(vecBone, playBone);
				if (value != 7)
				{
					tempScore = board.getScoreOfRow('e') + board.getScoreOfRow('w') + board.getScoreOfRow('s');
					if (playBone.isDouble())
						tempScore = tempScore + 2 * value;
					else
						tempScore = tempScore + value;

					if (tempScore >= maxScore)
					{
						option = i+1;
						row = 'n';
						maxScore = tempScore;
					}

					tempScore = 0;
				}

				vecRow = board.getRow('s');
				if (vecRow.size() == 0)
					vecBone = *board.getSpinner();
				else
					vecBone = vecRow[vecRow.size() - 1];
				value = whereBonesConnect(vecBone, playBone);
				if (value != 7)
				{
					tempScore = board.getScoreOfRow('e') + board.getScoreOfRow('n') + board.getScoreOfRow('w');
					if (playBone.isDouble())
						tempScore = tempScore + 2 * value;
					else
						tempScore = tempScore + value;

					if (tempScore >= maxScore)
					{
						option = i+1;
						row = 's';
						maxScore = tempScore;
					}

					tempScore = 0;
				}
			}
		}
	}
	return (option != 0);
}

void Game::askForOption(unsigned int playerID, int &option, char &row) //Asks the player for the bone to be played next
{
	Player* playerPtr = getPlayerByID(playerID);
	bool done;
	do
	{
		done = false;
		gotoxy(1,58);
		cout << "Which bone do you want to play? ";
		string temp;
		getline(cin,temp);
		istringstream iss(temp);
		int tempOption;
		if (iss >> tempOption)
			if (tempOption >= 1 && tempOption <= playerPtr->getNumPlayerBones())
				done = true;

		if (!done)
		{
			eraseLine(58);
			eraseLine(59);
			gotoxy(1,59);
			cout << "Invalid option!";
		}
		else
		{
			eraseLine(59);
			option = tempOption;
		}
	} while (!done);

	if (isBonePlayable(playerPtr->getPlayerBones()[option-1]))
		if (board.getRow('e').size() == 0 && !board.hasSpinner())
			row = 'E';
		else
			do
			{
				done = false;
				eraseLine(58);
				gotoxy(1,58);
				cout << "In which direction?(N/S/E/W) ";
				string temp;
				getline(cin,temp);
				istringstream iss(temp);
				char tempRow;
				if (iss >> tempRow && temp.size() == 1)
					if (toupper(tempRow) == 'N' || toupper(tempRow) == 'S' || toupper(tempRow) == 'E' || toupper(tempRow) == 'W')
						done = true;
				if (!done)
				{
					eraseLine(58);
					eraseLine(59);
					gotoxy(1,59);
					cout << "Invalid direction!";
				}
				else
					row = tempRow;
			} while (!done);
}
