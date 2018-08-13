/**************************************************************************
** Name: Lonnie Clark
** Class: CS362 Section 400
** Prof.: Ali Aburas
** Assignment: Assignment 4
** Date: 8/4/2018
**************************************************************************/

// Bring in appropriate header files
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constants
#define KINGDOMCARDSIZE 10
#define TEST_RUNS 1000

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
	// Seed random and loop random
	srand(time(NULL));
	int k;
	int test1Fails = 0;
	int test2Fails = 0;
	int test3Fails = 0;
	int test4Fails = 0;
	int test5Fails = 0;
	int testAllFails = 0;

	printf("\n---------------------------------------Test ""Smithy"" Card---------------------------------------\n");
	// Card description
	printf("Card Effect: +3 Cards\n");
	for (k = 0; k < TEST_RUNS; k++)
	{
		// Variable declaration/initialization
		int bonus = 0;
		int choice1 = 0;
		int choice2 = 0;
		int choice3 = 0;
		int handPos = 0;
		int i, j;
		int passFlag = 1;
		int players = (rand() % 3) + 2;
		int randKingdomCard;
		int randSeed = (rand() % 999) + 1;
		int totalDeck;
		struct gameState preTest;
		struct gameState postTest;

		// Valid kingdom cards are 7 to 26; council room is 8...randomize rest
		int kingdomCards[KINGDOMCARDSIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		kingdomCards[0] = 13;

		// Set of loops to fill card array with random unique integers in range
		for (i = 1; i < KINGDOMCARDSIZE; i++)
		{
			while (kingdomCards[i] != 0)
			{
				// Select random card, check if used
				randKingdomCard = (rand() % 20) + 7;
					for (j = 0; j < i; j++)
					{
						if (kingdomCards[j] == randKingdomCard)
						{
							break;
						}
						else if (j == (i - 1))
						{
							kingdomCards[i] = randKingdomCard;
						}
					}
			}
		}

		// Game initialization & test case copy
		initializeGame(players, kingdomCards, randSeed, &preTest);
		int currentPlayer = whoseTurn(&preTest);
		int nextPlayer = currentPlayer + 1;
		if (nextPlayer > (players - 1))
			nextPlayer = 0;

		// Randomize discard, deck, and hand count
		for (i = 0; i < 4; i++)
		{
			totalDeck = (rand() % (MAX_DECK - 31)) + 20;
			preTest.discardCount[i] = (rand() % totalDeck);
			preTest.deckCount[i] = (rand() % (totalDeck - preTest.discardCount[i]));
			preTest.handCount[i] = (totalDeck - (preTest.discardCount[i] + preTest.deckCount[i])) + 1;

			// Randomize played cards for current player
			if (i == currentPlayer)
				preTest.playedCardCount = rand() % 11;
		}

		// Print test info
		printf("\nTest Run %d: ", k + 1);
		printf("Seed = %d, ", randSeed);
		printf("Players = %d, ", players);
		printf("Deck # = %d, ", preTest.deckCount[currentPlayer]);
		printf("Discard # = %d, ", preTest.discardCount[currentPlayer]);
		printf("Hand # = %d, ", preTest.handCount[currentPlayer]);
		printf("Played # = %d\n", preTest.playedCardCount);

		// Force card to be smithy
		preTest.hand[currentPlayer][handPos] = smithy;
		memcpy(&postTest, &preTest, sizeof(struct gameState));

		/*Test run************************************************************/
		if (cardEffect(smithy, choice1, choice2, choice3, &postTest, handPos, &bonus) == 0)
		{
			// Check net effect of a +2 hand size (+3 from deck, -1 from discarding Smithy)
			if (!(postTest.handCount[currentPlayer] == (preTest.handCount[currentPlayer] + 2)))
			{
				printf("\tTest 1 Failed - Hand Size Incorrect After Card Being Played\n");
				test1Fails++;
				passFlag = 0;
				printf("Current Player = %d, Next Player = %d\n", currentPlayer, nextPlayer);
			}

			// Check net effect of a +1 played cards size (+1 from Smithy)
			if (!(postTest.playedCardCount == (preTest.playedCardCount + 1)))
			{
				printf("\tTest 2 Failed - Played Card Size Incorrect After Card Being Played\n");
				test2Fails++;
				passFlag = 0;
			}

			// Make sure cards came from deck
			if (!(postTest.deckCount[currentPlayer] == (preTest.deckCount[currentPlayer] - 3)))
			{
				printf("\tTest 3 Failed - Deck Size Incorrect After Card Being Played\n");
				test3Fails++;
				passFlag = 0;
			}

			// Compare state of other players hand/deck/discard
			if (!(preTest.handCount[nextPlayer] == postTest.handCount[nextPlayer] && preTest.deckCount[nextPlayer] == postTest.deckCount[nextPlayer] && preTest.discardCount[nextPlayer] == postTest.discardCount[nextPlayer]))
			{
				printf("\tTest 4 Failed - Opponent's Hand, Deck, or Discard Changed\n");
				test4Fails++;
				passFlag = 0;
			}

			// Make sure supply cards are unchanged
			for (i = 0; i <= treasure_map; i++)
			{
				if (preTest.supplyCount[i] != postTest.supplyCount[i])
				{
					printf("\tTest 5 Failed - Supply Cards Have Changed After Card Play\n");
					test5Fails++;
					passFlag = 0;
					break;
				}
			}
		}
		else
		{
			printf("\tTest Failed - Smithy Card Was Unable to Play\n");
			passFlag = 0;
			testAllFails++;
		}
		if (passFlag == 1)
		{
			printf("\tAll Tests PASS\n");
		}
	}
	// Summary of test results
	printf("\nSummary of test results:\n");
	printf("Total Runs: %d\n", TEST_RUNS);
	printf("Test 1 - Handsize Updated Correctly, # of Fails: %d\n", test1Fails);
	printf("Test 2 - Played Cards Updated Correctly, # of Fails: %d\n", test2Fails);
	printf("Test 3 - Deck Size Updated Correctly, # of Fails: %d\n", test3Fails);
	printf("Test 4 - Opponent's Hand, Deck, or Discard Didn't Changed, # of Fails: %d\n", test4Fails);
	printf("Test 5 - Supply Cards Updated Correctly, # of Fails: %d\n", test5Fails);
	printf("Test 6 - Card is Returned Successfully, # of Fails: %d\n", testAllFails);

	printf("------------------------------------------End of Test-----------------------------------------\n\n");
	return 0;
}
