/***************************************
* Author: Jason Long
* Testing: village
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
	
	//Previous state for later comparison
	int supplyStateFlag = 1;
	state.hand[0][0] = village;
	memcpy(&oldState, &state, sizeof(struct gameState));

	cardEffect(village, 0, 0, 0, &state, 0, 0);

	//Checking 16 cards in the supply (10 Kingdom cards, 3 Currency, 3 Victory)
	for (int i = 0; i < 16; i++) {
		if (oldState.supplyCount[i] != state.supplyCount[i]) {
			supplyStateFlag = 0;
		}
	}

	if (state.numActions != (oldState.numActions + 1)) { pass = 0; printf("VILLAGE FAILED: Incorrect number of actions granted to player. Was %i, is now %i\n", oldState.numActions, state.numActions); }
	if (state.discardCount[0] != (oldState.discardCount[0] + 1)) { pass = 0; printf("VILLAGE FAILED: Incorrect number of discards. Discard deck was %i, is now %i\n", oldState.discardCount[0], state.discardCount[0]); }
	if (state.handCount[0] != oldState.handCount[0]) { pass = 0; printf("VILLAGE FAILED: Incorrect number of cards in hand. Was %i, is now %i\n", oldState.handCount[0], state.handCount[0]); }
	if (state.deckCount[0] != (oldState.deckCount[0] - 1)) { pass = 0; printf("VILLAGE FAILED: Incorrect number of cards removed from deck. Was %i, is now %i\n", oldState.deckCount[0], state.deckCount[0]); }
	if (state.handCount[1] != oldState.handCount[1]) { pass = 0; printf("VILLAGE FAILED: Another player's hand was affected\n"); }
	if (state.discardCount[1] != oldState.discardCount[1]) { pass = 0; printf("VILLAGE FAILED: Another player's discard pile was affected\n"); }
	if (state.deckCount[1] != oldState.deckCount[1]) { pass = 0; printf("VILLAGE FAILED: Another player's deck was affected\n"); }
	if (supplyStateFlag == 0) { pass = 0; printf("VILLAGE FAILED: Supply was affected\n"); }
	if (pass == 1) { printf("VILLAGE PASSED: No errors found\n"); }

	return 0;
}