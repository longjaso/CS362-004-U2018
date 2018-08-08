/***************************************
* Author: Jason Long
* Testing: adventurer
* Date: 7/16/2018
***************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

int main() {
	//Game state setup
	struct gameState state;
	int allKingdomCards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	initializeGame(2, allKingdomCards, 4, &state);
	state.whoseTurn = 0;
	int pass = 1;
	int drawntreasure = 0;
	int currentPlayer = 0;
	int cardDrawn = 0;
	int temphand[MAX_HAND];
	int z;

	//Previous states setup (for later comparison)
	int previousHandSize = state.handCount[0];
	int previousDeckSize = state.deckCount[0];
	int previousCoins = state.coins;
	int totalNewCoins = 0;
	int previousLastCardSpot = state.handCount[0];
	int wrongCardFlag = 0;
	int previousPlayer2HandSize = state.handCount[1];

	state.hand[0][0] = adventurer; //Make the player's first card an adventurer card
	state.deck[0][0] = gold; //Set the first card to be drawn to gold
	state.deck[0][1] = gold; //Set the first card to be drawn to gold
	state.deck[0][2] = gold; //Set the first card to be drawn to gold
	state.deck[0][3] = gold; //Set the first card to be drawn to gold
	state.deck[0][4] = gold; //Set the first card to be drawn to gold
	adventurerEffect(&drawntreasure, &state, &currentPlayer, &cardDrawn, temphand, &z);

	//Count the number of coins added by the new treasure cards
	for (int i = previousLastCardSpot; i < state.handCount[0]; i++) {
		if (state.hand[0][i] == copper) { totalNewCoins++;  }
		else if (state.hand[0][i] == silver) { totalNewCoins += 2; }
		else if (state.hand[0][i] == gold) { totalNewCoins += 3; }
		else { wrongCardFlag = 1; } //If somehow a non-treasure card was added by Adventurer
	}

	//Conditional checks to see if anything went wrong during the card effect
	if (state.handCount[0] != (previousHandSize + 2)) { pass = 0;  printf("ADVENTURER FAILED: Incorrect number of cards drawn. Was %i, is now %i\n", previousHandSize, state.handCount[0]); }
	if (state.deckCount[0] > previousDeckSize - 2) { pass = 0; printf("ADVENTURER FAILED: Deck did not decrease by at least 2 cards\n"); }
	if (wrongCardFlag == 1) { pass = 0; printf("ADVENTURER FAILED: A non-treasure card was added to the player's hand\n"); }
	if (state.handCount[1] != previousPlayer2HandSize) { pass = 0; printf("ADVENTURER FAILED: Other player's hand was affected\n"); }
	if (pass == 1) { printf("ADVENTURER PASSED: No errors found\n"); }

	printf("GameState:\n\tOLD COINS: %i\n\tNEW COINS: %i\n\tOLD HANDCOUNT: %i\n\tNEW HANDCOUNT: %i\n", previousCoins, totalNewCoins, previousHandSize, state.handCount[0]);

	return 0;
}