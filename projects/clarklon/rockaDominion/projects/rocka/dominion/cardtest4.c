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
**	Card Testing: Feast
**	Card Effect: Trash This Card. Gain a Card Costing Up to 5.
** 
**	Implicit Requirements:
**	1. Cards received are exactly 1; IN THE DISCARD PILE!!!
**  2. Feast is actually removed from play.
**	2. No state change should occur for other players.
**	3. No change should occur to the victory card/kingdom card piles,
*      except card gained.
**************************************************************************/
int main()
{
	/*Game setup**********************************************************/ 
	// Variable declaration/initialization
	int bonus = 0;
	int choice1 = 13; //Needed for card to buy, Smithy here.
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
	// Force card to be feast
	preTest.hand[currentPlayer][handPos] = feast;
	memcpy(&postTest, &preTest, sizeof(struct gameState));

	/*Test run************************************************************/
	printf("\n----------------------------------------Test ""Feast"" Card---------------------------------------\n");
	if (cardEffect(feast, choice1, choice2, choice3, &postTest, handPos, &bonus) == 0)
	{
		// Card description
		printf("Card Effect: Trash This Card. Gain a Card Costing Up to 5.\n\n");

		// Check net effect of a -1 hand size (-1 from discarding Feast)
		if (postTest.handCount[currentPlayer] == (preTest.handCount[currentPlayer] - 1))
			printf("Test 1 Passed - Hand Size Decreased by 1 (-1 from Play)\n\n");
		else
			printf("Test 1 Failed - Hand Size Incorrect After Card Being Played\n\tHand Size Before Test = %d\n\tHand Size After Test = %d\n\tExpected Hand Size = %d\n\n", preTest.handCount[currentPlayer], postTest.handCount[currentPlayer], preTest.handCount[currentPlayer] - 1);

		// Check net effect of a +1 discard size (+1 from Card)
		if (postTest.discardCount[currentPlayer] == (preTest.discardCount[currentPlayer] + 1))
			printf("Test 2 Passed - Discard Size Grew by 1 (+1 from Card)\n\n");
		else
			printf("Test 2 Failed - Discard Size Incorrect After Card Being Played\n\tDiscard Size Before Test = %d\n\tDiscard Size After Test = %d\n\tExpected Discard Size = %d\n\n", preTest.discardCount[currentPlayer], postTest.discardCount[currentPlayer], preTest.discardCount[currentPlayer] + 1);

		// Make sure feast is trashed
		if (postTest.playedCardCount == (preTest.playedCardCount))
			printf("Test 3 Passed - Played Card Size Stayed the Same (Feast is Trashed)\n\n");
		else
			printf("Test 3 Failed - Played Card Size Incorrect After Card Being Played\n\tPlayed Card Size Before Test = %d\n\tPlayed Card Size After Test = %d\n\tExpected Played Card Size = %d\n\n", preTest.playedCardCount, postTest.playedCardCount, preTest.playedCardCount);

		// Make sure deck is unchanged
		if (postTest.deckCount[currentPlayer] == (preTest.deckCount[currentPlayer]))
			printf("Test 4 Passed - Deck Size Didn't Change\n\n");
		else
			printf("Test 4 Failed - Deck Size Incorrect After Card Being Played\n\tDeck Size Before Test = %d\n\tDeck Size After Test = %d\n\tExpected Deck Size = %d\n\n", preTest.deckCount[currentPlayer], postTest.deckCount[currentPlayer], preTest.deckCount[currentPlayer]);

		// Compare state of other players hand/deck/discard
		if(preTest.handCount[nextPlayer] == postTest.handCount[nextPlayer] && preTest.deckCount[nextPlayer] == postTest.deckCount[nextPlayer] && preTest.discardCount[nextPlayer] == postTest.discardCount[nextPlayer])
			printf("Test 5 Passed - Opponent's Hand, Deck, and Discard Unchanged\n\n");
		else
			printf("Test 5 Failed - Opponent's Hand, Deck, or Discard Changed\n\n");
		
		// Make sure supply card selected is reduced by 1
		if (postTest.supplyCount[choice1] == (preTest.supplyCount[choice1] - 1))
			printf("Test 6 Passed - Supply Count of Selected Card Decreased by 1 (-1 from Card)\n\n");
		else
			printf("Test 6 Failed - Supply Count of Selected Card Incorrect After Card Being Played\n\tSupply Count of Card Before Test = %d\n\tSupply Count of Card After Test = %d\n\tExpected Supply Count of Card After Test = %d", preTest.supplyCount[choice1], postTest.supplyCount[choice1], preTest.supplyCount[choice1] - 1);

		// Make sure supply cards are unchanged
		for (i = 0; i <= treasure_map; i++)
		{
			if (i != 13 && preTest.supplyCount[i] != postTest.supplyCount[i])
			{
				printf("Test 7 Failed - Supply Cards Have Changed After Card Play\n");
				break;
			}

			if (i == treasure_map)
				printf("Test 7 Passed - Supply Cards Have Not Changed After Card Play, Except for Card Gained\n");
		}
	}
	else
		printf("Test Failed - Feast Card Was Unable to Play\n");
	printf("------------------------------------------End of Test-----------------------------------------\n\n\n");

	return 0;
}
