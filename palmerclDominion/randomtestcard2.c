/*************************************
* Author: Jason Long
* Date: 8/5/2018
* Assignment 4 - Random Testing (Smithy)
*************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include <time.h>
#include <string.h>

int smithyTest(struct gameState* state, int currentPlayer, int handPos) {
	//+3 Cards
	for (int i = 0; i < 3; i++) {
		drawCard(currentPlayer, state);
	}

	//discard card from hand
	discardCard(handPos, currentPlayer, state, 1);
	return 0;
}

int main() {
	srand(time(NULL));
	for (int testCount = 0; testCount < 100; testCount++) {
		printf("Smithy Random Test %i\n", testCount);
		struct gameState state;
		struct gameState oldState;
		int randomPlayers = (rand() % MAX_PLAYERS) + 1; //Pick randomly up to max number of possible players
		while (randomPlayers == 1) { randomPlayers = (rand() % MAX_PLAYERS) + 1; }
		int pass = 1;
		int currentPlayer = rand() % randomPlayers;
		int anotherPlayer = rand() % randomPlayers;
		
		//If anotherPlayer is the same as currentPlayer, choose a new one
		while (anotherPlayer == currentPlayer) { anotherPlayer = rand() % randomPlayers; }

		//This block randomly selects new kingdom cards for the game
		int kingdomCards[10];
		kingdomCards[0] = smithy; //manually setting the adventurer so we know its selected
		for (int i = 1; i < 10; i++) {
			int selectedNum = rand() % 26;
			int isNew = 1;

			//Verify that the new selection doesn't match any existing selection
			for (int k = 0; k < i; k++) {
				//printf("K: %i ... I: %i ... SEL: %i\n", k, i, selectedNum);
				if (kingdomCards[k] == selectedNum) {
					isNew = 0;
				}
			}

			if (isNew == 1) {
				kingdomCards[i] = selectedNum; //If the card hasn't already been selected, insert it
			}
			else {
				i--; //Try again
			}
		}
		
		initializeGame(randomPlayers, kingdomCards, rand(), &state);

		//Previous state variables for later comparison
		int supplyStateFlag = 1;
		state.hand[currentPlayer][0] = smithy; //Make the very first card a smithy card
		memcpy(&oldState, &state, sizeof(struct gameState));

		smithyTest(&state, currentPlayer, 0);
		
		//Checking 16 cards in the supply (10 Kingdom cards, 3 Currency, 3 Victory)
		for (int i = 0; i < 16; i++) {
			if (oldState.supplyCount[i] != state.supplyCount[i]) {
				supplyStateFlag = 0;
			}
		}

		//Conditional checks to make sure nothing adverse occurred during cardEffect
		if (state.handCount[currentPlayer] != (oldState.handCount[currentPlayer] + 2)) { pass = 0; printf("SMITHY FAILED: Hand did not have net gain of 2. Was %i, is now %i\n", oldState.handCount[currentPlayer], state.handCount[currentPlayer]); }
		if (state.handCount[anotherPlayer] != oldState.handCount[anotherPlayer]) { pass = 0; printf("SMITHY FAILED: Another player's hand has been affected\n"); }
		if (state.deckCount[currentPlayer] != (oldState.deckCount[currentPlayer] - 3)) { pass = 0; printf("SMITHY FAILED: Incorrect number of cards removed from deck. Was %i, is now %i\n", oldState.deckCount[currentPlayer], state.deckCount[currentPlayer]); }
		if (state.deckCount[anotherPlayer] != oldState.deckCount[anotherPlayer]) { pass = 0; printf("SMITHY FAILED: Another player's deck was affected\n"); }
		if (state.discardCount[currentPlayer] != oldState.discardCount[currentPlayer] + 1) { pass = 0; printf("SMITHY  FAILED: Card was not discarded. Possibly trashed or remains in hand\n"); }
		if (supplyStateFlag == 0) { pass = 0;  printf("SMITHY FAILED: Supply was affected\n"); }
		if (pass == 1) { printf("SMITHY PASSED: No errors found\n"); }
	}

	return 0;
}