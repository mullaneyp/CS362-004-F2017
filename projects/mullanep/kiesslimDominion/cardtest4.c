/*************************************************************
 * Author: Patrick Mullaney
 * Description: card test 4 program for assignment 3, CS362.
 * Program tests council_room card. 
**************************************************************/
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <assert.h>
#include "rngs.h"

// compile:  gcc -o card4 cardtest4.c dominion.c rngs.c -coverage -lm

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

// This test should test council card.  In refactored code, changed ‘+1 buy’ to ‘+2 buy’ on line 1412, 
// giving a player more buys when the council card is played.

int main () {
    
    int result = 0;
    int seedNum = 1;
    
    // Message to be sent into assertion for testing messeages.
    char* errorMessage;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    
    struct gameState game, testGame;
    
    printf ("******************* cardtest4.c: Testing adventurer card **********************\n\n");
    
    // Initialize game.
    printf("TEST: Initialize game retuns 0.\n");
    result = initializeGame(2, k, seedNum, &game);
    errorMessage = "Initialize game returns 0.";
    assertTrue(result == 0, errorMessage);
    
    // Make copy of game for testing comparison.
    memcpy(&testGame, &game, sizeof(struct gameState));
    
    // Obtain number of cards before adventurer card effect.
    printf("TEST: Before adventurer card, handCount = 5.\n");
    errorMessage = "Before adventuer, handcount == 5.";
    assertTrue(testGame.handCount[0] == 5, errorMessage);
    
    // Card effect for adventurer card should return 0.
    printf("TEST: Adventurer card effect returns 0.\n");
    errorMessage = "Adventurer card effect returns 0.";
    result = cardEffect(7, -1,-1,-1,&testGame, 0, 0);
    assertTrue(result == 0, errorMessage);
    
    // Test handCount after adventurer card effect, which should be +1.
    printf("TEST: After adventurer card effect player's handCount is + 1.\n");
    errorMessage = "After testing adventurer card handCount is +1";
    assertTrue(testGame.handCount[0] + (game.handCount[0] + 1) == 2, errorMessage);
    if((game.handCount[0] + 1) == testGame.handCount[0]){
        printf("Test passed: After adventurer, handCount = %d\n", testGame.handCount[0]);
    }
    else
        printf("handCount = %d(+%d).\n", testGame.handCount[0], (testGame.handCount[0]-game.handCount[0]));
    
    if(failures == 0){
        printf ("ALL TESTS PASSED.\n\n");
    }
    else
        printf("TESTS FAILED: %d. TESTS PASSED: %d.\n\n", failures, success);
    
    return 0;
}