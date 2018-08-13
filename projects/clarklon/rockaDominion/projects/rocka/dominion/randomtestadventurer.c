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
	// Seed random and loop random
	srand(time(NULL));
	int k;
	int test1Fails = 0;
	int test2Fails = 0;
	int test3Fails = 0;
	int test4Fails = 0;
	int test5Fails = 0;
	int test6Fails = 0;
	int test7Fails = 0;
	int testAllFails = 0;

	printf("\n-------------------------------------Test ""Adventurer"" Card-------------------------------------\n");
	// Card description
	printf("Card Effect: Reveal Cards from your deck until you reveal 2 treasure cards.Put those treasure\ncards into your hand and discard the other revealed cards.\n\n");
	for (k = 0; k < TEST_RUNS; k++)
	{
		// Variable declaration/initialization
		int bonus = 0;
		int choice1 = 0;
		int choice2 = 0;
		int choice3 = 0;
		int discards = 0;
		int handPos = 0;
		int i, j;
		int passFlag = 1;
		int players = (rand() % 3) + 2;
		int preTreasure = 0;
		int postTreasure = 0;
		int randKingdomCard;
		int randSeed = (rand() % 999) + 1;
		int totalDeck;
		int treasure = 0;
		struct gameState preTest;
		struct gameState postTest;

		// Valid kingdom cards are 7 to 26; council room is 8...randomize rest
		int kingdomCards[KINGDOMCARDSIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		kingdomCards[0] = 7;

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
			totalDeck = (rand() % (MAX_DECK - 211)) + 20;
			preTest.discardCount[i] = (rand() % totalDeck);
			preTest.handCount[i] = (rand() % (totalDeck - preTest.discardCount[i])) + 1;
			preTest.deckCount[i] = (totalDeck - (preTest.discardCount[i] + preTest.handCount[i])) + 1;
			//preTest.deckCount[i] = (totalDeck - (preTest.discardCount[i] + preTest.handCount[i])) + 180;

			// Randomize played cards for current player
			if (i == currentPlayer)
				preTest.playedCardCount = rand() % 11;
		}

		// Set cards for deck
		for (i = 0; i < preTest.deckCount[currentPlayer]; i++)
		{
			preTest.deck[currentPlayer][i] = (rand() % 7) + 4;
		}

		// Set cards for discard
		for (i = 0; i < preTest.discardCount[currentPlayer]; i++)
		{
			preTest.discard[currentPlayer][i] = (rand() % 7) + 4;
		}

		// Print test info
		printf("\nTest Run %d: ", k + 1);
		printf("Seed = %d, ", randSeed);
		printf("Players = %d, ", players);
		printf("Deck # = %d, ", preTest.deckCount[currentPlayer]);
		printf("Discard # = %d, ", preTest.discardCount[currentPlayer]);
		printf("Hand # = %d, ", preTest.handCount[currentPlayer]);
		printf("Played # = %d\n", preTest.playedCardCount);

		// Force card to be adventurer
		preTest.hand[currentPlayer][handPos] = adventurer;
		memcpy(&postTest, &preTest, sizeof(struct gameState));

		/*Test run************************************************************/
		if (cardEffect(adventurer, choice1, choice2, choice3, &postTest, handPos, &bonus) == 0)
		{
			// Check net effect of a +1 hand size (+2 from deck, -1 from discarding Adventurer)
			if (!(postTest.handCount[currentPlayer] == (preTest.handCount[currentPlayer] + 1)))
			{
				printf("\tTest 1 Failed - Hand Size Incorrect After Card Being Played\n");
				test1Fails++;
				passFlag = 0;
			}

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
			if (!(postTest.playedCardCount == (preTest.playedCardCount + 1)))
			{
				printf("\tTest 2 Failed - Played Card Size Incorrect After Card Being Played\n");
				test2Fails++;
				passFlag = 0;
			}

			// Now check discard pile
			if (!(postTest.discardCount[currentPlayer] == (preTest.discardCount[currentPlayer] + discards)))
			{
				printf("\tTest 3 Failed - Discard Size Changed by Unexpected Amount\n");
				test3Fails++;
				passFlag = 0;
			}

			// Make sure cards came from deck
			if (!(postTest.deckCount[currentPlayer] == (preTest.deckCount[currentPlayer] - (discards + 2))))
			{
				printf("\tTest 4 Failed - Deck Size Incorrect After Card Being Played\n");
				test4Fails++;
				passFlag = 0;
			}

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
			if (!(postTreasure == (preTreasure + 2)))
			{
				printf("\tTest 5 Failed - Treasure Cards in Hand Changed by Unexpected Amount\n");
				test5Fails++;
				passFlag = 0;
			}

			// Compare state of other players hand/deck/discard
			if (!(preTest.handCount[nextPlayer] == postTest.handCount[nextPlayer] && preTest.deckCount[nextPlayer] == postTest.deckCount[nextPlayer] && preTest.discardCount[nextPlayer] == postTest.discardCount[nextPlayer]))
			{
				printf("\tTest 6 Failed - Opponent's Hand, Deck, or Discard Changed\n");
				test6Fails++;
				passFlag = 0;
			}

			// Make sure supply cards are unchanged
			for (i = 0; i <= treasure_map; i++)
			{
				if (preTest.supplyCount[i] != postTest.supplyCount[i])
				{
					printf("\tTest 7 Failed - Supply Cards Have Changed After Card Play\n");
					test7Fails++;
					passFlag = 0;
					break;
				}
			}
		}
		else
		{
			printf("\tTest Failed - Adventurer Card Was Unable to Play\n");
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
	printf("Test 3 - Discard Size Updated Correctly, # of Fails: %d\n", test3Fails);
	printf("Test 4 - Deck Size Updated Correctly, # of Fails: %d\n", test4Fails);
	printf("Test 5 - Treasure in Hand Updated Correctly, # of Fails: %d\n", test5Fails);
	printf("Test 6 - Opponent Hand, Deck, and Discard Updated Correctly, # of Fails: %d\n", test6Fails);
	printf("Test 7 - Supply Cards Updated Correctly, # of Fails: %d\n", test7Fails);
	printf("Test 8 - Card is Returned Successfully, # of Fails: %d\n", testAllFails);

	printf("------------------------------------------End of Test-----------------------------------------\n\n");
	return 0;
}
