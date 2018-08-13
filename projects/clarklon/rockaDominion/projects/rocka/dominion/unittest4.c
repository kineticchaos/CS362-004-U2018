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
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**************************************************************************
** Function Tested: Whose Turn
** Test Cases:
** 1. Function correctly returns turn of player from game state.
**************************************************************************/
int main()
{
	// Variable declaration
	int i;
	int size = 4;
	struct gameState testCases[size];
	int turns[4] = { 1, 2, 3, 4 };

	// Variable initialization
	for (i = 0; i < size; i++)
	{
		testCases[i].whoseTurn = turns[i];
	}

	printf("\n\n-------------------------------------Test ""Whose Turn"" Unit-------------------------------------");
	printf("\nTest Case 1: Function correctly returns turn of player from game state.\n");

	for (i = 0; i < size; i++)
	{
		if (whoseTurn(&testCases[i]) == turns[i])
			printf("Test %d Passed - Correct Player Returned\n", i + 1);
		else
			printf("Test %d Failed - Incorrect Player Returned\n", i + 1);
	}
	printf("------------------------------------------End of Test-----------------------------------------\n");

	return 0;
}
