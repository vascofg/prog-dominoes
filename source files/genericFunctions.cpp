#include <cstdlib>
#include "genericFunctions.h"
#include "Game.h"

using namespace std;

void eraseLine(int y) //Erases a line of text
{
	gotoxy(0,y);
	cout << "                                                                                                                        ";
}

void displayDrawMsg() //Displays a message if the game ends with a drow
{
	eraseLine(57);
	eraseLine(58);
	gotoxy(1,57);
	cout << "The game ends with a draw!";
}

void displayWinner(Player* playerPtr) //Displays the winner of the match
{
	eraseLine(57);
	eraseLine(58);
	gotoxy(1,57);
	cout << playerPtr->getPlayerName() << " wins the game!";
}

int roundto5(int nr) //Rounds a number to be a multiple of five
{
	double x = (double)nr / 5;
	int y = nr / 5;
	double z = x - y;
	if (z < 0.5)
		return (int)(nr - z*5);
	else
		return (int)(nr + (5-z*5));
}


bool displayStart() //Displays the start menu
{
	srand((unsigned int)time(NULL));
	resizeConsole();
	bool showAgain;
	do
	{
		showAgain = false;
		setBackGroundColor(BLACK);
		clrscr();
		setcolor(GREEN); /**/

		gotoxy(0,10);
		cout << "                               ___           ___                       ___           ___           ___      \n" <<
			"                _____         /\\  \\         /\\  \\                     /\\  \\         /\\  \\         /\\__\\     \n" <<
			"               /::\\  \\       /::\\  \\       |::\\  \\       ___          \\:\\  \\       /::\\  \\       /:/ _/_    \n" <<
			"              /:/\\:\\  \\     /:/\\:\\  \\      |:|:\\  \\     /\\__\\          \\:\\  \\     /:/\\:\\  \\     /:/ /\\  \\   \n" <<
			"             /:/  \\:\\__\\   /:/  \\:\\  \\   __|:|\\:\\  \\   /:/__/      _____\\:\\  \\   /:/  \\:\\  \\   /:/ /::\\  \\  \n" <<
			"            /:/__/ \\:|__| /:/__/ \\:\\__\\ /::::|_\\:\\__\\ /::\\  \\     /::::::::\\__\\ /:/__/ \\:\\__\\ /:/_/:/\\:\\__\\ \n" <<
			"            \\:\\  \\ /:/  / \\:\\  \\ /:/  / \\:\\~~\\  \\/__/ \\/\\:\\  \\__  \\:\\~~\\~~\\/__/ \\:\\  \\ /:/  / \\:\\/:/ /:/  / \n" <<
			"             \\:\\  /:/  /   \\:\\  /:/  /   \\:\\  \\          \\:\\/\\__\\  \\:\\  \\        \\:\\  /:/  /   \\::/ /:/  /  \n" <<
			"              \\:\\/:/  /     \\:\\/:/  /     \\:\\  \\          \\::/  /   \\:\\  \\        \\:\\/:/  /     \\/_/:/  /   \n" <<
			"               \\::/  /       \\::/  /       \\:\\__\\         /:/  /     \\:\\__\\        \\::/  /        /:/  /    \n" <<
			"                \\/__/         \\/__/         \\/__/         \\/__/       \\/__/         \\/__/         \\/__/     \n";

		gotoxy(0,27);
		cout <<	"                                 ___   _      _         ______ _____ _   _ _____ _____  \n" <<
			"                                / _ \\ | |    | |        |  ___|_   _| | | |  ___/  ___| \n" << 
			"                               / /_\\ \\| |    | |  ______| |_    | | | | | | |__ \\ `--.  \n" <<
			"                               |  _  || |    | | |______|  _|   | | | | | |  __| `--. \\ \n" <<
			"                               | | | || |____| |____    | |    _| |_\\ \\_/ / |___/\\__/ / \n" <<
			"                               \\_| |_/\\_____/\\_____/    \\_|    \\___/ \\___/\\____/\\____/  \n";
		setcolor(WHITE);
		setBackGroundColor(GREEN); /**/
		gotoxy(0,0);
		for (int i = 0; i < 60; i++)
			cout << " *";
		cout << ' ';
		gotoxy(0,59);
		for (int i = 0; i < 59; i++)
			cout << " *";
		cout << " *";

		for (int i = 1; i < 59; i++)
		{
			gotoxy(0,i);
			cout << " *";
			gotoxy(119,i);
			cout << "* ";
		}
		setBackGroundColor(BLACK);
		gotoxy(52,47);
		setcolor(GREEN);/**/
		cout << "Joao Reis";
		gotoxy(52,48);
		cout << "Vasco Goncalves";
		gotoxy(43,45);
		cout << "=================================";
		for (int i = 46; i < 51; i++)
		{
			gotoxy(43,i);
			cout << "||";
			gotoxy(74,i);
			cout << "||";
		}
		gotoxy(43,50);
		cout << "=================================";
		setcolor(GREEN);
		gotoxy(47,54);
		cout << "Press 1 for Instructions";
		setcolor(WHITE);
		gotoxy(52,39);
		cout << "Press 0 to exit";
		gotoxy(50,37);
		cout << "Press Enter to Play";
		bool done = false;
		while (!done)
		{
			char temp = _getch();
			if (temp == 13 || temp == 10)
				done = true;
			else if (temp == '1')
			{
				showAgain = displayInstructions();
				done = true;
			}
			else if (temp == '0')
				return false;
		}
		setcolor(GREEN); /**/
	} while (showAgain);

	return true;
}

bool displayInstructions() //Displays the instructions
{
	clrscr();
	setcolor(GREEN); /**/
	gotoxy(0,10);
	cout << "     Dominos 'All Fives' is a game played with rectangular pieces each divided in 2 square parts.\n\n" <<
		"     Each part contains a number from 0 to 6. Therefore, there are 28 pieces.\n\n\n" <<
		"  Start\n\n" <<
		"     Every player gets a certain amount of pieces at start. (2 players: 7 pieces each; 3-4 players: 5 pieces each)\n\n\n" <<
		"  GamePlay\n\n" <<
		"     The first player is picked based on who has the 'double' (special piece who has 2 equal values) with the highest\n\n" <<
		"     value. However, that player may choose if he/she wants to start the game with a 'double' or not.\n\n" <<
		"     Every time the sum of the last values of each 'line' or 'row' is a multiple of 5, the current player scores that\n\n" <<
		"     sum. 'Double' pieces are worth twice its number. If a player does not have a playable bone, he draws a bone from\n\n" <<
		"     the 'pile' or 'boneyard' until he/she has a playable one. If the 'boneyard' is empty, the player passes his/her\n\n" <<
		"     turn.\n\n\n" <<
		"  Ending\n\n" <<
		"     The first player who plays all his/her bones scores the sum of every bone's points in each player's hand rounded\n\n" <<
		"     to the nearest multiple number of 5.\n\n";
	gotoxy(50,45);		
	cout << "Press Enter to Play";
	gotoxy(50,47);
	cout << "Press 1 to go back to Menu";
	bool done = false;
	char temp;
	while (!done)
	{
		temp = _getch();
		if (temp == 13 || temp == 10 || temp == '1')
			done = true;
	}
	return (temp == '1');
}

void askForPlayers(vector<Player> &humanPlayers, vector<Player> &AIPlayers) //Displays the menu for player insertion
{
	clrscr();
	string temp;
	istringstream iss;
	int humanPlyrs = 0, AIPlyrs = 0;
	bool done = false;
	bool retry = false;
	do
	{
		retry = false;
		do
		{
			done = false;
			eraseLine(1);
			setcolor(WHITE);
			gotoxy(1,1);
			cout << "How many human players?: ";
			string temp;
			istringstream iss;
			getline (cin,temp);
			iss.str(temp);
			int tempQnt;
			if (iss >> tempQnt)
				if (tempQnt >= 0 && tempQnt <= 4)
					done = true;
			if (!done)
			{
				gotoxy(1,2);
				cout << "Invalid number of players!";
			}
			else
			{
				eraseLine(2);
				humanPlyrs = tempQnt;
			}
		} while (!done);

		if (humanPlyrs != 4)
		{
			do
			{
				retry = false;
				done = false;
				eraseLine(1);
				gotoxy(1,1);
				cout << "How many players controlled by the computer?: ";
				getline(cin,temp);
				iss.clear();
				iss.str(temp);
				int tempQnt;
				if (iss >> tempQnt)
					if (tempQnt >= 0 && tempQnt+humanPlyrs < 2)
						retry = true;
					else if (tempQnt >= 0 && tempQnt <= (4-humanPlyrs))
						done = true;
				if (retry)
				{
					gotoxy(1,2);
					cout << "Minimum number of players is 2!";
				}
				else if (!done)
				{
					gotoxy(1,2);
					cout << "Invalid number of players!";
				}
				else
				{
					eraseLine(2);
					AIPlyrs = tempQnt;
				}
			} while (!done && !retry);
		}
	} while (retry);

	vector<string> vecPlayersNames;

	eraseLine(1);
	eraseLine(2);
	askForNames(vecPlayersNames, humanPlyrs);
	for (int i = 0; i < humanPlyrs; i++)
	{
		Player pTemp(vecPlayersNames[i]);
		humanPlayers.push_back(pTemp);
	}

	for (int i = 0; i < AIPlyrs; i++)
	{
		AIPlayers.push_back(Player());
	}
	
	gotoxy(1,1);
	cout << "Press Enter to Start the Game...";
	while(true)
	{
		char tempCh = _getch();
		if (tempCh == 13 || tempCh == 10)
			break;
	}
}

void askForNames(vector<string> &vec, int numNames) //Asks for the players' names at the beggining of the game
{
	string temp, name;
	istringstream iss;
	bool done;
	for (int i = 0; i < numNames; i++)
	{
		do
		{
			done = false;
			eraseLine(1);
			gotoxy(1,1);
			setcolor(WHITE);
			cout << "Name for Player " << i+1 << "?: ";
			getline(cin, temp);
			istringstream iss;
			iss.str(temp);
			if (!(iss >> temp))
			{
				bool retry;
				do
				{
					retry = false;
					eraseLine(2);
					gotoxy(1,2);
					setcolor(WHITE);
					cout << "Are you sure you do NOT want to set a name for this Player?(Y/N): ";
					char tempCh;
					getline(cin, temp);
					iss.clear();
					iss.str(temp);
					if (iss >> tempCh && temp.size() == 1)
					{
						if (toupper(tempCh) == 'Y')
						{
							done = true;
							vec.push_back("");
						}
						else if (toupper(tempCh) == 'N')
							retry = true;
					}
				} while (!done && !retry);
				eraseLine(2);
			}
			else
			{
				name = temp;
				while (iss >> temp)
				{
					name = name + ' ' + temp;
				}

				done = false;

				if (name.size() > 10)
				{
					eraseLine(2);
					gotoxy(1,2);
					cout << "Name can contain up to " << 10 << " characters!";
				}
				else
				{
					bool uniqueName = true;
					for (unsigned int i = 0; i < vec.size() && uniqueName ; i++)
					{
						if (temp == vec[i])
							uniqueName = false;
					}

					if (name.find("Computer") != string::npos || name.find("Player") != string::npos)
						uniqueName = false;

					if (uniqueName)
					{
						vec.push_back(name);
						eraseLine(2);
						done = true;
					}
					else
					{
						eraseLine(2);
						gotoxy(1,2);
						cout << "That name is unavailable.";
					}
				}
			}
		} while (!done);
	}
}
