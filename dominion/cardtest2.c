/***************************************
* Author: Jason Long
* Testing: smithy
* Date: 7/16/2018
***************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"

int main() {
	//Game state setup
	struct gameState state, oldState;
	int allKingdomCards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	initializeGame(2, allKingdomCards, 4, &state);
	state.whoseTurn = 0;
	int pass = 1;

	//Previous state variables for later comparison
	int supplyStateFlag = 1;
	state.hand[0][0] = smithy; //Make the very first card a smithy card
	memcpy(&oldState, &state, sizeof(struct gameState));

	cardEffect(smithy, 0, 0, 0, &state, 0, 0);

	//Checking 16 cards in the supply (10 Kingdom cards, 3 Currency, 3 Victory)
	for (int i = 0; i < 16; i++) {
		if (oldState.supplyCount[i] != state.supplyCount[i]) {
			supplyStateFlag = 0;
		}
	}

	//Conditional checks to make sure nothing adverse occurred during cardEffect
	if (state.handCount[0] != (oldState.handCount[0] + 2)) { pass = 0; printf("SMITHY FAILED: Hand did not have net gain of 2. Was %i, is now %i\n", oldState.handCount[0], state.handCount[0]); }
	if (state.handCount[1] != oldState.handCount[1]) { pass = 0; printf("SMITHY FAILED: Another player's hand has been affected\n"); }
	if (state.deckCount[0] != (oldState.deckCount[0] - 3)) { pass = 0; printf("SMITHY FAILED: Incorrect number of cards removed from deck. Was %i, is now %i\n", oldState.deckCount[0], state.deckCount[0]); }
	if (state.deckCount[1] != oldState.deckCount[1]) { pass = 0; printf("SMITHY FAILED: Another player's deck was affected\n"); }
	if (state.discardCount[0] != oldState.discardCount[0] + 1) { pass = 0; printf("SMITHY  FAILED: Card was not discarded. Possibly trashed or remains in hand\n"); }
	if (supplyStateFlag == 0) { pass = 0;  printf("SMITHY FAILED: Supply was affected\n"); }
	if (pass == 1) { printf("SMITHY PASSED: No errors found\n"); }

	return 0;
}
