/***************************************
* Author: Jason Long
* Testing: buyCard
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

	//Test if buying a card adds the card to owner's discard pile, removes a card from the kingdom cards
	//Get initial set of information to compare against after purchasing
	state.whoseTurn = 0;
	state.coins = 10;

	int pass = 1;
	int buysRemaining = state.numBuys;
	int previousDiscardCount = state.discardCount[0];
	int previousHandCount = state.handCount[0];
	int previousSupplySmithyCount = state.supplyCount[smithy];
	int previousCoins = state.coins;
	int smithyCost = getCost(smithy);
	int previousSmithyCount = 0;
	int newSmithyCount = 0;
	//Check how many smithy cards are in the player's hand currently
	for (int i = 0; i < state.discardCount[0]; i++) {
		if (state.discard[0][i] == smithy) {
			previousSmithyCount++;
		}
	}
	
	buyCard(smithy, &state);

	//Get the new count of Smithy cards in the deck
	for (int i = 0; i < state.discardCount[0]; i++) {
		if (state.discard[0][i] == smithy) {
			newSmithyCount++;
		}
	}

	if (state.numBuys != (buysRemaining - 1)) { pass = 0;  printf("BUY TEST FAILED: Number of buys did not decrease by 1. Was %i, is now %i\n", buysRemaining, state.numBuys); }
	if (state.discardCount[0] != (previousDiscardCount + 1)) { pass = 0; printf("BUY TEST FAILED: Deck count did not increase by 1. Was %i, is now %i\n", previousDiscardCount, state.discardCount[0]); }
	if (state.handCount[0] != previousHandCount) { pass = 0; printf("BUY TEST FAILED: Hand count increased, hand size should remain same. Was %i, is now %i\n", previousHandCount, state.handCount[0]); }
	if (state.supplyCount[smithy] != (previousSupplySmithyCount - 1)) { pass = 0; printf("BUY TEST FAILED: Smithy supply count did not decrease by 1. Was %i, is now %i\n", previousSupplySmithyCount, state.supplyCount[smithy]); }
	if (state.coins != (previousCoins - smithyCost)) { pass = 0; printf("BUY TEST FAILED: Coins did not decrease properly. Was %i, is now %i\n", previousCoins, state.coins); }
	if (newSmithyCount != (previousSmithyCount + 1)) { pass = 0; printf("BUY TEST FAILED: Smithy was not added to player's discard pile. Was %i, is now %i\n", previousSmithyCount, newSmithyCount); }
	if (pass == 1) { printf("BUY TEST PASSED: No errors found\n"); }

	return 0;
}