/*************************************************************
 * Author: Patrick Mullaney
 * Description: unit test 4 program for assignment 3, CS362.
 * Program tests initializeGame function as well as post 
 * initilization conditions.
**************************************************************/
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// compile: gcc -o unit4 unittest4.c dominion.c rngs.c -coverage -lm

int failures = 0;
int success = 0;
// Assert statement which will also display error message and increment test failure count.
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
/* This tests initializeGame function.  Max players are 2-4.
** Will test invalid boundaries outside input, 1 and 5 players, 
** as well as valid input of 2 players. */
int main () {
    
    int result = 0;
    int seedNum = 1;
    char* message;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    
    // Uninitialized, empty array of kingdom cards.
    int j[10];
    
    struct gameState testGame;
    
    printf("************************* unittest4.c: Testing initializeGame ****************************\n\n");
    
    // Testing initialize with 1 player.  Result should return -1.
    printf("TEST: Initialize game with invalid input, 1 player, should return -1.\n");
    result = initializeGame(1, k, seedNum, &testGame);
    message = "Initialize game with 1 player returns -1.";
    assertTrue(result == -1, message);
    
    // Testing initializing with 5 players. Result should return -1.
    printf("TEST: Initialize game with invalid input, 5 players, should return -1.\n");
    result = initializeGame(5, k, seedNum, &testGame);
    message = "Initialize game with 5 players returns -1.";
    assertTrue(result == -1, message);
    
    // Testing initializing with 2 players, but empty kingdom cards array. Result should return -1.
    printf("TEST: Initialize game with valid input, but empty kingdom cards array, should return -1.\n");
    result = initializeGame(2, j, seedNum, &testGame);
    message = "Initialize game with 2 players, but empty kingdom cards array returns -1.";
    assertTrue(result == -1, message);
    
    // Testing initializing with 2 players. Result should return 0.
    result = initializeGame(2, k, seedNum, &testGame);
    message = "Initialize game with 2 players and initialized kingdom cards array returns 0.";
    assertTrue(result == 0, message);
    
    /************ Game conditions to test **************/
    
    // Test number of players should be 2.
    printf("TEST: numPlayers == 2.\n");
    message = "numPlayers == 2.";
    assertTrue(testGame.numPlayers == 2, message);

    // Check curse card count.
    printf("TEST: Curse cards == 10.\n");
    message = "Curse cards == 10.";
    assertTrue(testGame.supplyCount[curse] == 10, message);
    // Check estate card count.
    printf("TEST: Estate cards == 8.\n");
    message = "Estate cards = 8.";
    assertTrue(testGame.supplyCount[estate] == 8, message);
    // Check duchy card count.
    printf("TEST: Duchy cards == 8.\n");
    message = "Duchy cards = 8";
    assertTrue(testGame.supplyCount[duchy] == 8, message);
    // Check province card count.
    printf("TEST: Province cards == 8.\n");
    message = "Province cards = 8";
    assertTrue(testGame.supplyCount[province] == 8, message);
  
    // Check copper card count.
    printf("TEST: Copper cards == 46.\n");
    message = "Copper cards = 46";
    assertTrue(testGame.supplyCount[copper] == 46,  message);
    // Check silver card count.
    printf("TEST: Silver cards == 40.\n");
    message = "Silver cards = 40";
    assertTrue(testGame.supplyCount[silver] == 40,  message);
    // Check gold card count.
    printf("TEST: Gold cards == 30.\n");
    message = "Gold cards = 30";
    assertTrue(testGame.supplyCount[gold] == 30,  message);
    
    // Check player hand  and disard counts.
    printf("TEST: Player hand counts == 5 & 0 respectively.\n");
    message = "Player hand counts = 5 & 0 respectively.";
    assertTrue((testGame.handCount[0] == 5) && (testGame.handCount[1] == 0),  message);
    printf("TEST: Player deck count: player 1 = 5, player 2 = 10.\n");
    message = "Player deck count: player 1 = 5, player 2 = 10.";
    assertTrue((testGame.deckCount[0] == 5) && (testGame.deckCount[1] == 10),  message);
    
    // Test embargo tokens set to 0.
    printf("TEST: Embargo tokens set to 0.\n");
    int i;
    int embargo = 1;
    message = "Embargo Tokens all == 0";
    for ( i = 0; i <= treasure_map; i++){
        
       if(testGame.embargoTokens[i] != 0){
           embargo = 0;
       }
    }
    assertTrue(embargo == 1, message);
    
    // Test initialized to first player's correctly.
    printf("TEST: Outpost played 0.\n");
    message = "Outpost played = 0.";
    assertTrue(testGame.outpostPlayed == 0, message);
    printf("TEST: Phase set to 0.\n");
    message = "Phase = 0.";
    assertTrue(testGame.phase == 0, message);
    printf("TEST: numActions set to 1.\n");
    message = "numActions = 1.";
    assertTrue(testGame.numActions == 1, message);
    printf("TEST: numBuys set to 1.\n");
    message = "numBuys = 1.";
    assertTrue(testGame.numBuys == 1, message);
    printf("TEST: playedCardCount set to 0.\n");
    message = "playedCardCount = 0.";
    assertTrue(testGame.playedCardCount == 0, message);
    printf("TEST: whoseTurn set to 0.\n");
    message = "whoseTurn = 0.";
    assertTrue(testGame.whoseTurn == 0, message);
    printf("TEST: handCount player 1 set to 5.\n");
    message = "handCount[0] == 5.";
    assertTrue(testGame.handCount[testGame.whoseTurn] == 5, message);
    
    /**************************** End game conditions to test. ****************************/
    
    if(failures == 0){
        printf ("ALL TESTS PASSED.\n\n");
    }
    else
        printf("TESTS FAILED: %d.  PASSED: %d\n\n", failures, success);
    
    return 0;
}