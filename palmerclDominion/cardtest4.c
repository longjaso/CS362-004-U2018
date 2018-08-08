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
	state.hand[0][0] = cutpurse;
	state.hand[1][0] = copper;
	memcpy(&oldState, &state, sizeof(struct gameState));

	cardEffect(cutpurse, 0, 0, 0, &state, 0, 0);

	//Checking 16 cards in the supply (10 Kingdom cards, 3 Currency, 3 Victory)
	for (int i = 0; i < 16; i++) {
		if (oldState.supplyCount[i] != state.supplyCount[i]) {
			supplyStateFlag = 0;
		}
	}

	if (state.coins != (oldState.coins + 2)) { pass = 0; printf("CUTPURSE FAILED: Coins were not appropriately added to player. Was %i, is now %i\n", oldState.coins, state.coins); }
	if (state.hand[1][0] == copper) { pass = 0; printf("CUTPURSE FAILED: Copper was not removed from other player's hand\n"); }
	if (state.handCount[1] != (oldState.handCount[1] - 1)) { pass = 0; printf("CUTPURSE FAILED: Other player's handCount did not change\n"); }
	if (state.discardCount[1] != (oldState.discardCount[1] + 1)) { pass = 0; printf("CUTPURSE FAILED: Other player's discard pile did not increase properly\n"); }
	if (supplyStateFlag == 0) { pass = 0; printf("CUTPURSE FAILED: Supply was affected\n"); }
	if (pass == 1) { printf("CUTPURSE PASSED: No errors were found\n"); }

	return 0;
}