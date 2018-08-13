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
**	Card Testing: Adventurer
**	Card Effect: Reveal Cards from your deck until you reveal 2 treasure 
**               cards. Put those treasure cards into your hand and discard
**               the other revealed cards.
** 
**	Implicit Requirements:
**	1. Cards received are exactly 2.
**  2. The cards gained must be treasure cards.
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
	int discards = 0;
	int handPos = 1;
	int i;
	int kingdomCards[10] = { 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	int players = 2;
	int preTreasure = 0;
	int postTreasure = 0;
	int randSeed = 777;
	int treasure = 0;
	struct gameState preTest;
	struct gameState postTest;
	//Game initialization & test case copy
	initializeGame(players, kingdomCards, randSeed, &preTest);
	int currentPlayer = whoseTurn(&preTest);
	int nextPlayer = currentPlayer + 1;
	if (nextPlayer > (players - 1))
		nextPlayer = 0;
	// Force card to be adventurer
	preTest.hand[currentPlayer][handPos] = adventurer;
	// Set top card to something other than treasure
	preTest.deck[currentPlayer][preTest.deckCount[currentPlayer] - 1] = smithy;
	memcpy(&postTest, &preTest, sizeof(struct gameState));

	/*Test run************************************************************/
	printf("\n-------------------------------------Test ""Adventurer"" Card-------------------------------------\n");
	if (cardEffect(adventurer, choice1, choice2, choice3, &postTest, handPos, &bonus) == 0)
	{
		// Card description
		printf("Card Effect: Reveal Cards from your deck until you reveal 2 treasure cards.Put those treasure\ncards into your hand and discard the other revealed cards.\n\n");

		// Check net effect of a +1 hand size (+2 from deck, -1 from discarding Adventurer)
		if (postTest.handCount[currentPlayer] == (preTest.handCount[currentPlayer] + 1))
			printf("Test 1 Passed - Hand Size Grew by Net of 1 (+2 from Card, -1 from Play)\n\n");
		else
			printf("Test 1 Failed - Hand Size Incorrect After Card Being Played\n\tHand Size Before Test = %d\n\tHand Size After Test = %d\n\tExpected Hand Size = %d\n\n", preTest.handCount[currentPlayer], postTest.handCount[currentPlayer], preTest.handCount[currentPlayer] + 1);

		// Check net effect of discard size matches expectation
		// First find how many cards before finding 2 treasure cards
		for (i = (preTest.deckCount[currentPlayer] - 1); i >= 0; i--)
		{
			if (preTest.deck[currentPlayer][i] == copper || preTest.deck[currentPlayer][i] == silver || preTest.deck[currentPlayer][i] == gold)
				treasure++;
			else
				discards++;

			// Stop once 2 treasure are found
			if (treasure == 2)
				break;
		}
		
		// Check net effect of a +1 played cards size (+1 from Adventurer)
		if (postTest.playedCardCount == (preTest.playedCardCount + 1))
			printf("Test 2 Passed - Played Card Size Grew by 1 (+1 from Play)\n\n");
		else
			printf("Test 2 Failed - Played Card Size Incorrect After Card Being Played\n\tPlayed Card Size Before Test = %d\n\tPlayed Card Size After Test = %d\n\tExpected Played Card Size = %d\n\n", preTest.playedCardCount, postTest.playedCardCount, preTest.playedCardCount + 1);
		
		// Now check discard pile
		if (postTest.discardCount[currentPlayer] == (preTest.discardCount[currentPlayer] + discards))
			printf("Test 3 Passed - Discard Size Grew by %d (+%d from Card)\n\n", discards, discards);
		else
			printf("Test 3 Failed - Discard Size Changed by Unexpected Amount\n\tDiscard Size Before Test = %d\n\tDiscard Size After Test = %d\n\tExpected Discard Size = %d\n\n", preTest.discardCount[currentPlayer], postTest.discardCount[currentPlayer], preTest.discardCount[currentPlayer] + discards);

		// Make sure cards came from deck
		if (postTest.deckCount[currentPlayer] == (preTest.deckCount[currentPlayer] - (discards + 2)))
			printf("Test 4 Passed - Deck Size Decreased by %d (-%d from Card)\n\n",discards + 2, discards + 2);
		else
			printf("Test 4 Failed - Deck Size Incorrect After Card Being Played\n\tDeck Size Before Test = %d\n\tDeck Size After Test = %d\n\tExpected Deck Size = %d\n\n", preTest.deckCount[currentPlayer], postTest.deckCount[currentPlayer], preTest.deckCount[currentPlayer] - (discards + 2));

		// Check that increased hand size is from treasure only
		for (i = 0; i <= preTest.handCount[currentPlayer]; i++)
		{
			if (preTest.hand[currentPlayer][i] == copper || preTest.hand[currentPlayer][i] == silver || preTest.hand[currentPlayer][i] == gold)
				preTreasure++;
		}
		for (i = 0; i <= postTest.handCount[currentPlayer]; i++)
		{
			if (postTest.hand[currentPlayer][i] == copper || postTest.hand[currentPlayer][i] == silver || postTest.hand[currentPlayer][i] == gold)
				postTreasure++;
		}
		if (postTreasure == (preTreasure + 2))
			printf("Test 5 Passed - Treasure Cards in Hand Grew by 2 (+2 from Card)\n\n");
		else
			printf("Test 5 Failed - Treasure Cards in Hand Changed by Unexpected Amount\n\tTreasure Cards in Hand Before Test = %d\n\tTreasure Cards in Hand After Test = %d\n\tExpected Treasure Cards in Hand = %d\n\n", preTreasure, postTreasure, preTreasure + 2);

		// Compare state of other players hand/deck/discard
		if(preTest.handCount[nextPlayer] == postTest.handCount[nextPlayer] && preTest.deckCount[nextPlayer] == postTest.deckCount[nextPlayer] && preTest.discardCount[nextPlayer] == postTest.discardCount[nextPlayer])
			printf("Test 6 Passed - Opponent's Hand, Deck, and Discard Unchanged\n\n");
		else
			printf("Test 6 Failed - Opponent's Hand, Deck, or Discard Changed\n\n");
		
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
		printf("Test Failed - Adventurer Card Was Unable to Play\n");
	printf("------------------------------------------End of Test-----------------------------------------\n\n");

	return 0;
}