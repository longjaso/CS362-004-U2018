/***************************************
* Author: Jason Long
* Testing: whoseTurn
* Date: 7/16/2018
***************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "rngs.h"

int main() {
	struct gameState state;
	int allKingdomCards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	initializeGame(2, allKingdomCards, 4, &state);
	int pass = 1;

	//Test ordinary number
	state.whoseTurn = 1;
	if (whoseTurn(&state) != 1) { pass = 0;  printf("WHOSE TURN FAILED: Player 1 did not match\n"); }

	//Test lower than expected number
	state.whoseTurn = -1;
	if (whoseTurn(&state) != -1) { pass = 0;  printf("WHOSE TURN FAILED: Negative number not given back\n"); }

	//Test higher than expected number 
	state.whoseTurn = INT_MAX;
	if (whoseTurn(&state) != INT_MAX) { pass = 0; printf("WHOSE TURN FAILED: Max INT not given back\n"); }

	if (pass == 1) { printf("WHOSE TURN PASSED: No errors found\n"); }
	return 0;
}