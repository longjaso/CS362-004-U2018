/*************************************
* Author: Jason Long
* Date: 8/5/2018
* Assignment 4 - Random Testing (Village)
*************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include <time.h>
#include <string.h>

int villageTest(struct gameState* state, int currentPlayer, int handPos) {
	//+1 Card
	drawCard(currentPlayer, state);

	//+2 Actions
	state->numActions = state->numActions + currentPlayer;

	//discard played card from hand
	discardCard(handPos, currentPlayer, state, 0);
	return 0;
}

int main() {
	srand(time(NULL));
	for (int testCount = 0; testCount < 100; testCount++) {
		printf("Village Random Test %i\n", testCount);
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
		kingdomCards[0] = village; //manually setting the adventurer so we know its selected
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
		state.whoseTurn = currentPlayer;
		state.hand[currentPlayer][0] = village; //Make the very first card a village card
		memcpy(&oldState, &state, sizeof(struct gameState));

		villageTest(&state, currentPlayer, 0);

		//Checking 16 cards in the supply (10 Kingdom cards, 3 Currency, 3 Victory)
		for (int i = 0; i < 16; i++) {
			if (oldState.supplyCount[i] != state.supplyCount[i]) {
				supplyStateFlag = 0;
			}
		}

		if (state.numActions != (oldState.numActions + 1)) { pass = 0; printf("VILLAGE FAILED: Incorrect number of actions granted to player. Was %i, is now %i\n", oldState.numActions, state.numActions); }
		if (state.handCount[currentPlayer] != oldState.handCount[currentPlayer]) { pass = 0; printf("VILLAGE FAILED: Incorrect number of cards in hand. Was %i, is now %i\n", oldState.handCount[currentPlayer], state.handCount[currentPlayer]); }
		if (state.deckCount[currentPlayer] != (oldState.deckCount[currentPlayer] - 1)) { pass = 0; printf("VILLAGE FAILED: Incorrect number of cards removed from deck. Was %i, is now %i\n", oldState.deckCount[currentPlayer], state.deckCount[currentPlayer]); }
		if (state.handCount[anotherPlayer] != oldState.handCount[anotherPlayer]) { pass = 0; printf("VILLAGE FAILED: Another player's hand was affected\n"); }
		if (state.discardCount[anotherPlayer] != oldState.discardCount[anotherPlayer]) { pass = 0; printf("VILLAGE FAILED: Another player's discard pile was affected\n"); }
		if (state.deckCount[anotherPlayer] != oldState.deckCount[anotherPlayer]) { pass = 0; printf("VILLAGE FAILED: Another player's deck was affected\n"); }
		if (supplyStateFlag == 0) { pass = 0; printf("VILLAGE FAILED: Supply was affected\n"); }
		if (pass == 1) { printf("VILLAGE PASSED: No errors found\n"); }
	}

	return 0;
}