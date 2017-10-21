/*************************************************************
 * Author: Patrick Mullaney
 * Description: unit test 2 program for assignment 3, CS362.
 * Program tests council_room card. 
**************************************************************/
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <assert.h>
#include "rngs.h"

// compile: gcc -o card2 cardtest2.c dominion.c rngs.c -coverage -lm

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

// This test should test council card.  In refactored code, changed ‘+1 buy’ 
// to ‘+2 buy’ on line 1412, giving a player more buys when the council card is played.

int main () {
    
    int result = 0;
    int seedNum = 1;
    // Message to be sent into assertion for testing messeages.
    char* errorMessage;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    
    struct gameState game, testGame;
    printf ("******************** cardtest2.c: Testing council card *****************\n\n");
    
    // Initialize game.
    result = initializeGame(2, k, seedNum, &game);
    errorMessage = "Initialize game did returns 0.";
    assertTrue(result == 0, errorMessage);
    
    // Make copy of game for testing comparison.
    memcpy(&testGame, &game, sizeof(struct gameState));
    
    printf("TEST: Before playing council card, numBuys == 1.\n");
    // Obtain number of buys before council card effect.
    errorMessage = "Before testing council card, numBuys == 1.";
    assertTrue(testGame.numBuys == 1, errorMessage);
    
    printf("TEST: Playing council_room card returns 0.\n");
    // Card effect for council card should return 0.
    errorMessage = "Council card effect returns 0.";
    result = cardEffect(8, -1,-1,-1,&testGame, 0, 0);
    assertTrue(result == 0, errorMessage);
    
    printf ("TEST: After council card, numBuys == 2 (+1).\n");
    // Obtain number of actions after council card effect, which should be +1.
    errorMessage = "After testing council card, numBuys == 2.";
    assertTrue(testGame.numBuys == (game.numBuys + 1), errorMessage);
    
    if((game.numBuys + 1) == testGame.numBuys){
        printf("PASSED: After council numBuys == %d\n", testGame.numBuys);
    }
    else
        printf("numBuys = %d\n", testGame.numBuys);
        
    printf("TEST: After playing card, player1 is + 3 cards, player2 is +1 cards.\n");
    // Obtain number of cards after council card effect, which should be +3 (+4 -1 discard) for player 1, +1 for player2.
    errorMessage = "After playing council_room card, player1 is +3 cards.";
    assertTrue(((game.handCount[0] + 3) == testGame.handCount[0]), errorMessage);
    errorMessage = "After playing council_room card, player2 is +1 cards.";
    assertTrue(((game.handCount[1] + 1) == testGame.handCount[1]), errorMessage);
    
    printf("TEST: After playing card, played card count is +1.\n");
    errorMessage = "After playing council_room card, played card count is +1.";
    assertTrue((game.playedCardCount + 1) == testGame.playedCardCount, errorMessage);
    
    if(failures == 0){
        printf ("ALL TESTS PASSED.\n\n");
    }
    else
        printf("TESTS FAILED: %d. TESTS PASSED: %d\n\n", failures, success);
    
    return 0;
}