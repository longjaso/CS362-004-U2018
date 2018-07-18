/***************************************
* Author: Jason Long
* Testing: updateCoins
* Date: 7/16/2018
***************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

//This test function verifies that amounts are added correctly based on CARD and BONUS
void correctAmount(enum CARD card, char cardName[7], struct gameState* state, int shouldHave, int bonus) {
	//Set a Player 0's hand to all CARD and check that updateCoins appropriately counts coins
	for (int i = 0; i < state->handCount[0]; i++) {
		state->hand[0][i] = card;
	}

	//Set Player 1's hand to all CARD to make sure that the updateCoins function does not count other player's coins
	for (int i = 0; i < state->handCount[1]; i++) {
		state->hand[1][i] = card;
	}

	updateCoins(0, state, bonus);

	//Update coins should have only added a single player's set of cards
	if (state->coins == shouldHave) { printf("COUNT TEST PASSED: COIN COUNT (%s) MATCHED\n", cardName); }
	else {
		printf("COUNT TEST FAILED: COIN COUNT (%s) DID NOT MATCH\n", cardName);
		printf("\tCOUNT WAS %i, should have been %i\n", state->coins, shouldHave);
	}
}

//This test function verifies that updateCoins only counts Treasure cards while adding things together
//Treasure cards will handsize - 1
void onlyAddTreasures(enum CARD card, char cardName[7], struct gameState* state, int treasureNum,int shouldHave, int bonus) {
	int i;
	//Set the requested number of treasure cards in a player's hand
	for (i = 0; i < treasureNum; i++) {
		state->hand[0][i] = card;
	}
	//Set the rest of the hand to "smithy"
	for (i; i < state->handCount[0]; i++) {
		state->hand[0][i] = smithy;
	}
	
	updateCoins(0, state, bonus);

	//Update coins should have only added a single player's set of cards
	if (state->coins == shouldHave) { printf("TREASURE-ONLY TEST PASSED: COIN COUNT (%s) MATCHED\n", cardName); }
	else {
		printf("TREASURE-ONLY TEST FAILED: COIN COUNT (%s) DID NOT MATCH\n", cardName);
		printf("\tCOUNT WAS %i, should have been %i\n", state->coins, shouldHave);
	}
}

int main() {
	struct gameState state;
	int allKingdomCards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

	initializeGame(2, allKingdomCards, 4, &state);

	//Ensures that the amounts are properly added to the gameState's coins
	printf("\nThis set of tests should PASS\n");
	correctAmount(copper, "COPPER", &state, 5, 0);
	correctAmount(silver, "SILVER", &state, 10, 0);
	correctAmount(gold, "GOLD", &state, 15, 0);
	correctAmount(gold, "GOLD+B", &state, 18, 3);
	onlyAddTreasures(copper, "COPPER", &state, 3, 6, 3);

	printf("\nThis set of tests should FAIL\n");
	correctAmount(copper, "COPPER", &state, 6, 0);
	correctAmount(silver, "SILVER", &state, 9, 0);
	correctAmount(gold, "GOLD", &state, 16, 0);
	correctAmount(gold, "GOLD+B", &state, 17, 3);
	onlyAddTreasures(copper, "COPPER", &state, 3, 5, 3);

	return 0;
}