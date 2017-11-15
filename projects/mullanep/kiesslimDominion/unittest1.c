/*************************************************************
 * Author: Patrick Mullaney
 * Description: unit test 1 program for assignment 3, CS362.
 * Program tests buyCard function. 
**************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// compile: gcc -o unit1 unittest1.c dominion.c rngs.c -lm
// gcc -o unit1 unittest1.c dominion.c rngs.c -coverage -lm

// Assert statement which will also display error message and increment test failure count.
int failures = 0;
int success = 0;
void assertTrue(int assertion, char* message){
    
    if(!assertion){
        printf("FAILED: %s\n\n", message);
        failures++;
    }
    else{
        printf("PASSED: %s\n\n", message);
        success++;
    }
}

// This tests buy card
int main () {
    
    int result = 0;
    int seedNum = 1;
    char* errorMessage;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    
    struct gameState testGame;
    
    printf ("*********************** unittest1.c: Testing buyCard *******************************\n\n");
    
    printf("TEST: Initialization returns 0.\n");
    result = initializeGame(2, k, seedNum, &testGame);
    errorMessage = "Initialization returned 0.";
    assertTrue(result == 0, errorMessage);
    
    // Set coins to 10 and buys to 2.  Will attempt to make 3 buys.
    testGame.coins = 10;
    testGame.numBuys = 2;
  
    // Test invalid input.
    printf("TEST: Invalid input returns -1.\n");
    errorMessage = "Invalid input -1 returns -1.";
    result = buyCard(-1, &testGame);
    assertTrue(result == -1, errorMessage);
    
    // Test valid input.
    printf("TEST: Valid input returns 0.\n");
    errorMessage = "Valid input 0 returns 0.";
    result = buyCard(0, &testGame);
    assertTrue(result == 0, errorMessage);
    
    // Test not enough buys.
    testGame.numBuys = 0;
    printf("TEST: Not enough buys, returns -1.\n");
    errorMessage = "Not enough buys, returns -1.";
    result = buyCard(1, &testGame);
    assertTrue(result == -1, errorMessage);
    
    // Test not enough supply.
    testGame.supplyCount[4] = 0;
    printf("TEST: Not enough card supply, returns -1.\n");
    errorMessage = "Not enough card supply, returns -1.";
    result = buyCard(4, &testGame);
    assertTrue(result == -1, errorMessage);
    
    // Test not enough coins.
    testGame.coins = 1;
    printf("TEST: Not enough coins, returns -1.\n");
    errorMessage = "Not enough coins, returns -1.";
    result = buyCard(6, &testGame);
    assertTrue(result == -1, errorMessage);
    
    if(failures == 0){
        printf ("ALL TESTS PASSED.\n\n");
    }
    else
        printf("TESTS FAILED: %d.  TEST PASSED: %d.\n\n", failures, success);
    
    return 0;
}