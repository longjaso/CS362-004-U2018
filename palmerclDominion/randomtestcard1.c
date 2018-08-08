/*************************************
* Author: Jason Long
* Date: 8/5/2018
* Assignment 4 - Random Testing (Adventurer)
*************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include <time.h>
#include <string.h>

int adventurerTest(struct gameState* state, int drawntreasure, int currentPlayer, int temphand[], int z) {
	int cardDrawn;
	while (drawntreasure <= 2) {
		if (state->deckCount[currentPlayer] <1) {//if the deck is empty we need to shuffle discard and add to deck
			shuffle(currentPlayer, state);
		}
		drawCard(currentPlayer, state);
		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1];//top card of hand is most recently drawn card.
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
			drawntreasure++;
		else {
			temphand[z] = cardDrawn;
			state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
			z++;
		}
	}
	while (z - 1 >= 0) {
		state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z - 1]; // discard all cards in play that have been drawn
		z = z - 1;
	}
	return 0;
}

int main() {
	srand(time(NULL));
	for (int testCount = 0; testCount < 100; testCount++) {
		printf("Adventurere Random Test %i\n", testCount);
		struct gameState state;
		int randomPlayers = (rand() % MAX_PLAYERS) + 1; //Pick randomly up to max number of possible players
		while (randomPlayers == 1) { randomPlayers = (rand() % MAX_PLAYERS) + 1; }
		int tempHand[MAX_HAND];
		int pass = 1;
		int currentPlayer = rand() % randomPlayers;
		//printf("randomPlayers: %i ... currentPlayer: %i\n", randomPlayers, currentPlayer);
		//This block randomly selects new kingdom cards for the game
		int kingdomCards[10];
		kingdomCards[0] = adventurer; //manually setting the adventurer so we know its selected
		for (int i = 1; i < 10; i++) {
			int selectedNum = rand() % 26;
			int isNew = 1;
			//printf("SELECTED: %i\n", selectedNum);
			//Verify that the new selection doesn't match any existing selection
			for (int k = 0; k < i; k++) {
				//printf("K: %i ... I: %i ... SEL: %i\n", k, i, selectedNum);
				if (kingdomCards[k] == selectedNum) {
					isNew = 0;
				}
			}
			//printf("SEL: %i, isNew: %i\n", selectedNum, isNew);
			if (isNew == 1) {
				kingdomCards[i] = selectedNum; //If the card hasn't already been selected, insert it
			}
			else {
				i--; //Try again
			}
		}
		//printf("Initializing\n");
		initializeGame(randomPlayers, kingdomCards, rand(), &state);
		//printf("Finished initializing - starting the game stuff\n");
		//Previous states setup (for later comparison)
		int previousHandSize = state.handCount[currentPlayer];
		int previousDeckSize = state.deckCount[currentPlayer];
		int totalNewCoins = 0;
		int previousLastCardSpot = state.handCount[currentPlayer];
		int wrongCardFlag = 0;

		state.hand[currentPlayer][0] = adventurer; //Make the player's first card an adventurer card

		//printf("Calling test\n");
		adventurerTest(&state, 0, currentPlayer, tempHand, 0);
		//printf("Finished card test\n");
		//Count the number of coins added by the new treasure cards
		for (int i = previousLastCardSpot; i < state.handCount[currentPlayer]; i++) {
			if (state.hand[currentPlayer][i] == copper) { totalNewCoins++; }
			else if (state.hand[currentPlayer][i] == silver) { totalNewCoins += 2; }
			else if (state.hand[currentPlayer][i] == gold) { totalNewCoins += 3; }
			else { wrongCardFlag = 1; } //If somehow a non-treasure card was added by Adventurer
		}

		//Conditional checks to see if anything went wrong during the card effect
		if (state.handCount[currentPlayer] != (previousHandSize + 1)) { pass = 0;  printf("ADVENTURER FAILED: Incorrect number of cards drawn or adventurer was not discarded. Was %i, is now %i\n", previousHandSize, state.handCount[currentPlayer]); }
		if (state.deckCount[currentPlayer] > previousDeckSize - 2) { pass = 0; printf("ADVENTURER FAILED: Deck did not decrease by at least 2 cards\n"); }
		if (wrongCardFlag == 1) { pass = 0; printf("ADVENTURER FAILED: A non-treasure card was added to the player's hand\n"); }
		if (pass == 1) { printf("ADVENTURER PASSED: No errors found\n"); }
	}

	return 0;
}