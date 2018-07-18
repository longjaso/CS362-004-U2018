/***************************************
* Author: Jason Long
* Testing: fullDeckCount
* Date: 7/16/2018
***************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

int main() {
	struct gameState state;
	int allKingdomCards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	initializeGame(2, allKingdomCards, 4, &state);
	int pass = 1;
	int totalDeckSize = state.handCount[0] + state.discardCount[0] + state.deckCount[0];

	//Set everything in the player 0's deck and hand to smithy so you can reliably count all positions
	for (int i = 0; i < state.handCount[0]; i++) {
		state.hand[0][i] = smithy;
	}

	for (int i = 0; i < state.discardCount[0]; i++) {
		state.discard[0][i] = smithy;
	}

	for (int i = 0; i < state.deckCount[0]; i++) {
		state.deck[0][i] = smithy;
	}

	int checkSmithy = fullDeckCount(0, smithy, &state); //Ensure that fullDeckCount returns a match for every possible card
	int checkAdventurer = fullDeckCount(0, adventurer, &state); //Ensure that fullDeckCount doesn't return anything for cards that aren't there

	if (checkSmithy != totalDeckSize) { pass = 0;  printf("DECK COUNT TEST FAILED: Smithy should have been everything but wasn't\n"); }
	if (checkAdventurer != 0) { pass = 0;  printf("DECK COUNT TEST FAILED: Returned more than 0 adventurer counts, should have been 0\n"); }
	if (pass == 1) { printf("DECK COUNT TEST PASSED: No errors found\n"); }

	return 0;
}