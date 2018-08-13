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
** Function Tested: Shuffle
** Test Cases:
** 1. Deck is successfully shuffled multiple times.
** 2. Deck size hasn't changed through shuffle.
** 3. Shuffle is attempted with empty deck.
** 
** Note: Header files assumption of empty discard pile is preserved, so 
** not testing that case here.
**************************************************************************/
int main()
{
	// Variable declaration
	int deckSize;
	int i;
	int likeCount;
	int player = 1;
	int run;
	int runLimit = 2;
	struct gameState testCase1;
	struct gameState testCase3;
	struct gameState control;

	// Variable initialization
	testCase1.deckCount[player] = 20;
	testCase1.discardCount[player] = 0;
	control.deckCount[player] = 20;
	control.discardCount[player] = 0;
	testCase3.deckCount[player] = 0;
	deckSize = testCase1.deckCount[player];

	// Populate deck with sequence of numbers
	for (i = 0; i < testCase1.deckCount[player]; i++)
	{
		testCase1.deck[player][i] = i;
		control.deck[player][i] = i;
	}

	printf("\n\n--------------------------------------Test ""Shuffle"" Unit---------------------------------------\n");
	
	printf("Test Case 1: Deck is successfully shuffled multiple times.\n");
	// Run shuffle
	for (run = 0; run < runLimit; run++)
	{
		likeCount = 0;
		if (shuffle(player, &testCase1) == 0)
		{
			// Check to see if deck is exactly the same
			for (i = 0; i < testCase1.deckCount[player]; i++)
			{
				if (testCase1.deck[player][i] == control.deck[player][i])
					likeCount++;
			}
			if (likeCount == testCase1.deckCount[player])
				printf("Test %d Failed - Shuffle Didn't Change Order of Deck\n", run + 1);
			else
				printf("Test %d Passed - Deck is Shuffled Successfully\n", run + 1);
		}
		else
			printf("\nTest Run %d Failed - Shuffle Didn't Return Successfully\n", run);

		// Reset control
		for (i = 0; i < testCase1.deckCount[player]; i++)
			control.deck[player][i] = testCase1.deck[player][i];
	}

	/************************************************************************/
	printf("\nTest Case 2: Deck size hasn't changed through shuffle.\n");
	// Check Deck Size 
	if (testCase1.deckCount[player] == deckSize)
		printf("Test Passed - Deck Size Remain Unchanged After Shuffles\n");
	else
		printf("Test Failed - Deck Size Changed After Shuffle\n");

	/************************************************************************/
	printf("\nTest Case 3: Shuffle is attempted with empty deck.\n");
	// Try Shuffle on Empty Deck
	if (shuffle(player, &testCase3) == -1)
		printf("Test Passed - Shuffle on Empty Deck Returned Error");
	else
		printf("Test Failed - Shuffle on Empty Deck Didn't Return Error");

	printf("\n------------------------------------------End of Test-----------------------------------------\n");

	return 0;
}
