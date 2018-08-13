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
** Function Tested: Get Cost
** Test Cases:
** 1. Test that cost returned matches game rules.
** 2. Non-existent card returns error.
**************************************************************************/
int main()
{
	// Variable declaration
	int i;
	int size = 27;
	char *cardNames[] = { "Curse", "Estate", "Duchy", "Province", "Copper", "Silver", "Gold", "Adventurer", "Council Room", "Feast", "Gardens", "Mine", "Remodel", "Smithy", "Village", "Baron", "Great Hall", "Minion", "Steward", "Tribute", "Ambassador", "Cutpurse", "Embargo", "Outpost", "Salvager", "Sea Hag", "Treasure Map" };
	int expectedCosts[27] = { 0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4 };

	printf("\n--------------------------------------Test ""Get Cost"" Unit--------------------------------------\n");

	printf("Test Case 1: Test that cost returned matches game rules.\n");
	// Cycle through each card and vaidate cost is returned appropriately
	for (i = 0; i < size; i++)
	{
		if (getCost(i) == expectedCosts[i])
		{
			printf("Test %d, Card %s - Test Passed, Cost Returned is Expected\n", i + 1, cardNames[i]);
		}
		else
			printf("Test %d, Card %s - Test Failed, Cost Returned is Not Expected\n", i, cardNames[i]);
	}

	/************************************************************************/
	printf("\nTest Case 2: Non-existent card returns error.\n");
	if (getCost(size + 1) == -1)
		printf("Test Passed - Error Value Returned\n");
	else
		printf("Test Failed - Non-Error Value Returned\n");
	printf("------------------------------------------End of Test-----------------------------------------\n");

	return 0;
}
