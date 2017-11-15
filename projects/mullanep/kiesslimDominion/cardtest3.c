/*************************************************************
 * Author: Patrick Mullaney
 * Description: card test 3 program for assignment 3, CS362.
 * Program tests village card.
**************************************************************/
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <assert.h>
#include "rngs.h"

// compile: gcc -o card3 cardtest3.c dominion.c rngs.c -coverage -lm

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

// This test should test village card.  In refactored code, changed 
// ‘+2 Actions’ to ‘+3 Actions’ on line 1394, giving a player more actions 
// when the village card is played.

int main () {
    
    int result = 0;
    int seedNum = 1;
    // Message to be sent into assertion for testing messeages.
    char* errorMessage;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    
    struct gameState game, testGame;
    
    printf ("************************ cardtest3.c: Testing village card.********************\n\n");
    
    // Initialize game.
    printf("TEST: Initialize game retuns 0.\n");
    result = initializeGame(2, k, seedNum, &game);
    errorMessage = "Initialize game.";
    assertTrue(result == 0, errorMessage);
    
    // Make copy of game for testing comparison.
    memcpy(&testGame, &game, sizeof(struct gameState));
    
    // Number of actions before village card effect, which should be 1.
    printf("TEST: Before village card effect, numActions = 1.\n");
    errorMessage = "Before testing village card, numActions = 1.";
    assertTrue(testGame.numActions == 1, errorMessage);
    
    // After playing village card effect should return 0..
    printf("TEST: Village card effect returns 0.\n");
    errorMessage = "Testing village card effect returns 0.";
    result = cardEffect(14, -1,-1,-1,&testGame, 0, 0);
    assertTrue(result == 0, errorMessage);
    
    // After playing village card, numActions should be +2.
    printf("TEST: After playing village card, numActions is + 2.\n");
    // Obtain number of actions after village card effect, which should be +2.
    errorMessage = "After testing village card, numActions is + 2.";
    assertTrue(testGame.numActions == (game.numActions + 2), errorMessage);
    if((game.numActions + 2) == testGame.numActions){
        printf("TEST PASSED: After village numActions = %d\n", testGame.numActions);
    }
    else
        printf("numActions = %d\n", testGame.numActions);
    
    // After playing, number of player's hand count should be unchanged (+1 draw, -1 discard).
    printf("TEST: After playing card, player's hand count is unchanged.\n");
    errorMessage = "After testing village card, player's hand count is unchanged.";
    //int afterVillage = testGame.numActions;
    assertTrue(testGame.handCount[0] == game.handCount[0], errorMessage);
    
    // After playing, number of played cards should be +1.
    printf("TEST: After playing card, played card count is +1.\n");
    errorMessage = "After playing council_room card, played card count is +1.";
    assertTrue((game.playedCardCount + 1) == testGame.playedCardCount, errorMessage);
    
    // After playing, player deck count should be -1.
    printf("TEST: After playing card, player's deck count is -1.\n");
    errorMessage = "After testing village card, player deck count is -1.";
    assertTrue(testGame.deckCount[0] == (game.deckCount[0] - 1), errorMessage);
    
    if(failures == 0){
        printf ("ALL TESTS PASSED.\n\n");
    }
    else
        printf("%d tests failed. %d tests passed.\n\n", failures, success);
    
    return 0;
}