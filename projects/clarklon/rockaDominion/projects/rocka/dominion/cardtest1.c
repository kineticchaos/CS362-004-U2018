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
**	Card Testing: Smithy
**	Card Effect: +3 Cards
** 
**	Implicit Requirements:
**	1. Cards received are exactly 3.
**	2. No state change should occur for other players.
**	3. No change should occur to the victory card/kingdom card piles.
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
	// Game initialization & test case copy
	initializeGame(players, kingdomCards, randSeed, &preTest);
	int currentPlayer = whoseTurn(&preTest);
	int nextPlayer = currentPlayer + 1;
	if (nextPlayer > (players - 1))
		nextPlayer = 0;	
	// Force card to be smithy
	preTest.hand[currentPlayer][handPos] = smithy;
	memcpy(&postTest, &preTest, sizeof(struct gameState));

	/*Test run************************************************************/
	printf("\n\n---------------------------------------Test ""Smithy"" Card---------------------------------------\n");
	if (cardEffect(smithy, choice1, choice2, choice3, &postTest, handPos, &bonus) == 0)
	{
		// Card description
		printf("Card Effect: +3 Cards\n\n");

		// Check net effect of a +2 hand size (+3 from deck, -1 from discarding Smithy)
		if (postTest.handCount[currentPlayer] == (preTest.handCount[currentPlayer] + 2))
			printf("Test 1 Passed - Hand Size Grew by 2 (+3 from Card, -1 from Play)\n\n");
		else
			printf("Test 1 Failed - Hand Size Incorrect After Card Being Played\n\tHand Size Before Test = %d\n\tHand Size After Test = %d\n\tExpected Hand Size = %d\n\n", preTest.handCount[currentPlayer], postTest.handCount[currentPlayer], preTest.handCount[currentPlayer] + 2);

		// Check net effect of a +1 played cards size (+1 from Smithy)
		if (postTest.playedCardCount == (preTest.playedCardCount + 1))
			printf("Test 2 Passed - Played Card Size Grew by 1 (+1 from Play)\n\n");
		else
			printf("Test 2 Failed - Played Card Size Incorrect After Card Being Played\n\tPlayed Card Size Before Test = %d\n\tPlayed Card Size After Test = %d\n\tExpected Played Card Size = %d\n\n", preTest.playedCardCount, postTest.playedCardCount, preTest.playedCardCount + 1);

		// Make sure cards came from deck
		if (postTest.deckCount[currentPlayer] == (preTest.deckCount[currentPlayer] - 3))
			printf("Test 3 Passed - Deck Size Decreased by 3 (-3 from Card)\n\n");
		else
			printf("Test 3 Failed - Deck Size Incorrect After Card Being Played\n\tDeck Size Before Test = %d\n\tDeck Size After Test = %d\n\tExpected Deck Size = %d\n\n", preTest.deckCount[currentPlayer], postTest.deckCount[currentPlayer], preTest.deckCount[currentPlayer] - 3);

		// Compare state of other players hand/deck/discard
		if (preTest.handCount[nextPlayer] == postTest.handCount[nextPlayer] && preTest.deckCount[nextPlayer] == postTest.deckCount[nextPlayer] && preTest.discardCount[nextPlayer] == postTest.discardCount[nextPlayer])
			printf("Test 4 Passed - Opponent's Hand, Deck, and Discard Unchanged\n\n");
		else
			printf("Test 4 Failed - Opponent's Hand, Deck, or Discard Changed\n\n");
		
		// Make sure supply cards are unchanged
		for (i = 0; i <= treasure_map; i++)
		{
			if (preTest.supplyCount[i] != postTest.supplyCount[i])
			{
				printf("Test 5 Failed - Supply Cards Have Changed After Card Play\n");
				break;
			}

			if (i == treasure_map)
				printf("Test 5 Passed - Supply Cards Have Not Changed After Card Play\n");
		}
	}
	else
		printf("Test Failed - Smithy Card Was Unable to Play\n");
	printf("------------------------------------------End of Test-----------------------------------------\n\n");
	
	return 0;
}
