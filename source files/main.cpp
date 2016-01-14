#include "Game.h"
#include "genericFunctions.h"

int main()
{
	bool exit;
	do
	{
		exit = !displayStart();

		if (exit)
			return 0;
		
		vector<Player> vecAI;
		vector<Player> vecPlayers;
		askForPlayers(vecPlayers, vecAI);

		Game game;               //Creates a game
		game.start(vecPlayers, vecAI);           //Starts the game
	}
	while (!exit);

	return 0; //Exit
}
