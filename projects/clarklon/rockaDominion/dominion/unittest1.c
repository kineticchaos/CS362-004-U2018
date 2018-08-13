/**************************************************************************
** Name - Lonnie Clark
** Class - CS362 Section 400
** Prof. - Ali Aburas
** Assignment - Assignment 3
** Date - 7/20/2018
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
** Function Tested - Buy Card
** Test Cases:
** 1. Enough actions, money, and card if available.
**		a. Make sure supply is reduced by 1.
**		b. Make sure card is added to discard pile.
**		c. Players coins are reduced by cost.
** 2. Enough money, and card is available. Insufficient actions.
** 3. Enough actions and card is available. Insufficient money.
** 4. Enough money and actions. Card is unavailable.
** 5. Enough money. Insufficient actions and card is unavailable.
** 6. Enough actions. Insufficient money and card is unavailable.
** 7. Card is available. Insufficient money and actions.
** 8. Insufficient money, actions, and card is unavailable.
**************************************************************************/
int main()
{
	// Variable declaration
	int i;
	int buys[8] = { 1, 0, 1, 1, 0, 1, 0, 0 };
	int kingdomCards[10] = { 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	int money[8] = { 5, 5, 0, 5, 5, 0, 0, 0 };
	int players = 2;
	int randSeed = 777;
	int size = 8;
	int supplyCard = 5; // Silver
	struct gameState testCases[size];

	// Game initialization
	initializeGame(players, kingdomCards, randSeed, &testCases[0]);

	// Variable initialization
	for (i = 0; i < size; i++)
	{
		testCases[i].numBuys = buys[i];
		testCases[i].coins = money[i];
	}
	int tempHandSize = testCases[0].handCount[testCases[0].whoseTurn];
	int tempSupply = testCases[0].supplyCount[supplyCard];
	int tempDiscard = testCases[0].discardCount[testCases[0].whoseTurn];
	int tempMoney = testCases[0].coins;

	printf("\n--------------------------------------Test ""Buy Card"" Unit--------------------------------------");

	/************************************************************************/
	printf("\nTest Case 1 - Enough actions, money, and card if available.\n");
	if (buyCard(supplyCard, &testCases[0]) == 0)
	{
		// Check to make sure supply is reduced
		if (testCases[0].supplyCount[supplyCard] == (tempSupply - 1))
			printf("Test Passed - Supply Count Reduced Successfully\n");
		else
			printf("Test Failed - Supply Count NOT Reduced Properly\n");

		// Make sure card is added to discard pile
		if (testCases[0].discardCount[testCases[0].whoseTurn] == (tempDiscard + 1))
			printf("Test Passed - Card Successfully Added to Discard\n");
		else
			printf("Test Failed - Card Not Added to Discard\n");

		// Player coins are reduced by cost
		if (testCases[0].coins == (tempMoney - getCost(supplyCard)))
			printf("Test Passed - Coins Successfully Reduced from Player\n");
		else
			printf("Test Failed - Coins Not Reduced from Player\n");

		// Check hand size not growing
		if (testCases[0].handCount[testCases[0].whoseTurn] == tempHandSize)
			printf("Test Passed - Hand Size Remained Unchanged\n");
		else
			printf("Test Failed - Hand Size Changed Unexpectedly\n");
	}
	else
		printf("Test Failed - Couldn't Process Buy Action\n");

	/************************************************************************/
	printf("\nTest Case 2 - Enough money, and card is available. Insufficient actions.\n");
	if (buyCard(supplyCard, &testCases[1]) == -1)
		printf("Test Passed - Error Due to Insufficient Actions\n");
	else
		printf("Test Failed - No Error Received as Expected\n");

	/************************************************************************/
	printf("\nTest Case 3 - Enough actions and card is available. Insufficient money.\n");
	if (buyCard(supplyCard, &testCases[2]) == -1)
		printf("Test Passed - Error Due to Insufficient Money\n");
	else
		printf("Test Failed - No Error Received as Expected\n");

	/************************************************************************/
	printf("\nTest Case 4 - Enough money and actions. Card is unavailable.\n");
	testCases[3].supplyCount[supplyCard] = 0;
	if (buyCard(supplyCard, &testCases[3]) == -1)
		printf("Test Passed - Error Due to Card Unavailability\n");
	else
		printf("Test Failed - No Error Received as Expected\n");

	/************************************************************************/
	printf("\nTest Case 5 - Enough money. Insufficient actions and card is unavailable.\n");
	testCases[4].supplyCount[supplyCard] = 0;
	if (buyCard(supplyCard, &testCases[4]) == -1)
		printf("Test Passed - Error Due to Insufficient Actions and Card Unavailability\n");
	else
		printf("Test Failed - No Error Received as Expected\n");

	/************************************************************************/
	printf("\nTest Case 6 - Enough actions. Insufficient money and card is unavailable.\n");
	testCases[5].supplyCount[supplyCard] = 0;
	if (buyCard(supplyCard, &testCases[5]) == -1)
		printf("Test Passed - Error Due to Insufficient Money and Card Unavailability\n");
	else
		printf("Test Failed - No Error Received as Expected\n");

	/************************************************************************/
	printf("\nTest Case 7 - Card is available. Insufficient money and actions.\n");
	if (buyCard(supplyCard, &testCases[6]) == -1)
		printf("Test Passed - Error Due to Insufficient Money and Actions\n");
	else
		printf("Test Failed - No Error Received as Expected\n");

	/************************************************************************/
	printf("\nTest Case 8 - Insufficient money, actions, and card is unavailable.\n");
	testCases[7].supplyCount[supplyCard] = 0;
	if (buyCard(supplyCard, &testCases[7]) == -1)
		printf("Test Passed - Error Due to Insufficient Money, Actions, and Card Unavailability\n");
	else
		printf("Test Failed - No Error Received as Expected\n");
	printf("------------------------------------------End of Test-----------------------------------------\n\n");

	return 0;
}