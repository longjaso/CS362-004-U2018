/*
Random Test Adventurer
Testing function: Adventurer
*/

#include "dominion.h"
#include <stdio.h>
#include "dominion_helpers.h"
#include <stdlib.h>

int main() {

	
	printf("Card test 1: Adventurer\n");
	int count = 0;
	int errorFlag = 0;

	// Call adventurer multiple times
	do
	{
		//New Game
		struct gameState G;
		int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy };
		int numPlayers = 2 +(rand() % 3);
		int gameSeed = 1 + (rand() % 10);

		initializeGame(numPlayers, k, gameSeed, &G);

		int currentPlayer = 0;
		int cardDrawn;
		int check = 1;
		int drawntreasure = 0;
		int temphand[MAX_HAND];
		int z = 0;

		//Make Random
		drawntreasure = rand() % 3;
		
		// Execute empty deck branch to get to 100%
		if (count % 50 == 0)
		{
			G.deckCount[currentPlayer] = 0;
		}

		check = adventurerEffect(&drawntreasure, &G, &currentPlayer, &cardDrawn, temphand, &z);
		count++;


		//Num players are passed in correctly
		if (G.numPlayers <0 || G.numPlayers > 5) {
			errorFlag = 1;
		}

		//Check to make sure function finished normally
		if (check != 0) {
			printf("error.");
			errorFlag = 1;
		}

	}
	while (count < 300 && errorFlag == 0);

	if (errorFlag != 1)
	{
		printf("Random Test - Adventurer PASSED\n");
		printf("\n\n");
	}
		
	else
	{
		printf("Random Test - Adventurer FAILED\n");
		printf("\n\n");

	}
		
	return 0;
}
