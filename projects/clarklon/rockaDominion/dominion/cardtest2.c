/**************************************************************************
** Name: Lonnie Clark
** Class: CS362 Section 400
** Prof.: Ali Aburas
** Assignment: Assignment 3
** Date: 7/20/2018
**************************************************************************/

// Bring in appropriate header files
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**************************************************************************
**	Card Testing: Council Room
**	Card Effect: +4 Cards, +1 Buy; Each Other Player Draws a Card
** 
**	Implicit Requirements:
**	1. Cards received are exactly 4.
**  2. Buy actions are increased by 1.
**	3. The only state change that should occur to other players is gaining
**     a single card.
**	4. No change should occur to the victory card/kingdom card piles.
**************************************************************************/
int main()
{
	/*Game setup**********************************************************/ 
	// Variable declaration/initialization
	int bonus = 0;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handPos = 1;
	int i;
	int kingdomCards[10] = { 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	int players = 2;
	int randSeed = 777;
	struct gameState preTest;
	struct gameState postTest;
	//Game initialization & test case copy
	initializeGame(players, kingdomCards, randSeed, &preTest);
	int currentPlayer = whoseTurn(&preTest);
	int nextPlayer = currentPlayer + 1;
	if (nextPlayer > (players - 1))
		nextPlayer = 0;
	// Force card to be council room
	preTest.hand[currentPlayer][handPos] = council_room;
	memcpy(&postTest, &preTest, sizeof(struct gameState));

	/*Test run************************************************************/
	printf("\n------------------------------------Test ""Council Room"" Card------------------------------------\n");
	if (cardEffect(council_room, choice1, choice2, choice3, &postTest, handPos, &bonus) == 0)
	{
		// Card effect
		printf("Card Effect: +4 Cards, +1 Buy; Each Other Player Draws a Card\n\n");

		// Check net effect of a +3 hand size (+4 from deck, -1 from discarding Council Room)
		if (postTest.handCount[currentPlayer] == (preTest.handCount[currentPlayer] + 3))
			printf("Test 1 Passed - Hand Size Grew by 3 (+4 from Card, -1 from Play)\n\n");
		else
			printf("Test 1 Failed - Hand Size Incorrect After Card Being Played\n\tHand Size Before Test = %d\n\tHand Size After Test = %d\n\tExpected Hand Size = %d\n\n", preTest.handCount[currentPlayer], postTest.handCount[currentPlayer], preTest.handCount[currentPlayer] + 3);

		// Check net effect of a +1 played card size (+1 from Council Room)
		if (postTest.playedCardCount == (preTest.playedCardCount + 1))
			printf("Test 2 Passed - Played Card Size Grew by 1 (+1 from Play)\n\n");
		else
			printf("Test 2 Failed - Played Card Size Incorrect After Card Being Played\n\tPlayed Card Size Before Test = %d\n\tPlayed Card Size After Test = %d\n\tExpected Played Card Size = %d\n\n", preTest.playedCardCount, postTest.playedCardCount, preTest.playedCardCount + 1);

		// Make sure cards came from deck
		if (postTest.deckCount[currentPlayer] == (preTest.deckCount[currentPlayer] - 4))
			printf("Test 3 Passed - Deck Size Decreased by 4 (-4 from Card)\n\n");
		else
			printf("Test 3 Failed - Deck Size Incorrect After Card Being Played\n\tDeck Size Before Test = %d\n\tDeck Size After Test = %d\n\tExpected Deck Size = %d\n\n", preTest.deckCount[currentPlayer], postTest.deckCount[currentPlayer], preTest.deckCount[currentPlayer] - 4);

		// Check that buy actions increased by +1
		if (postTest.numBuys == (preTest.numBuys + 1))
			printf("Test 4 Passed - Number of Buys for Player Grew by 1 (+1 from Card)\n\n");
		else
			printf("Test 4 Failed - Number of Buys Incorrect After Card Being Played\n\tBuys Before Test = %d\n\tBuys After Test = %d\n\tExpected Number of Buys = %d\n\n",preTest.numBuys, postTest.numBuys, preTest.numBuys + 1);

		// Ensure oppponent was able to draw a card
		if ((preTest.handCount[nextPlayer] + 1) == postTest.handCount[nextPlayer] && (preTest.deckCount[nextPlayer] - 1) == postTest.deckCount[nextPlayer])
			printf("Test 5 Passed - Opponent Was Able to Draw a Card; Hand Increased by 1, Deck Decreased by 1\n\n");
		else
			printf("Test 5 Failed - Opponent Wasn't Able to Draw a Card Properly\n\n");

		// Compare state of other players, such that hand +1, deck -1, and discard remains the same
		if(preTest.discardCount[nextPlayer] == postTest.discardCount[nextPlayer])
			printf("Test 6 Passed - Opponent's Discard is Unchanged\n\n");
		else
			printf("Test 6 Failed - Opponent's Discard Changed in Unexpected Manner\n\n");
		
		// Make sure supply cards are unchanged
		for (i = 0; i <= treasure_map; i++)
		{
			if (preTest.supplyCount[i] != postTest.supplyCount[i])
			{
				printf("Test 7 Failed - Supply Cards Have Changed After Card Play\n");
				break;
			}

			if (i == treasure_map)
				printf("Test 7 Passed - Supply Cards Have Not Changed After Card Play\n");
		}
	}
	else
		printf("Test Failed - Council Room Card Was Unable to Play\n");
	printf("------------------------------------------End of Test-----------------------------------------\n\n");

	return 0;
}