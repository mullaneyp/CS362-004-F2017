/******************************************************************
 * Author: Patrick Mullaney
 * Description: random card test2 program for assignment 4, CS362.
 * Program tests village card. 
******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <assert.h>
#include "rngs.h"
#include <stdbool.h>
#include <math.h>
#include <time.h>

// compile: gcc -o randomcardtest2 randomcardtest2.c dominion.c rngs.c -coverage -lm
//gcc -o rando2 randomcardtest2.c dominion.c rngs.c -coverage -lm

// Assert statement which will also display error message and increment test failure count.
int assertTrue(int assertion, char* message){
    
    if(!assertion){
       // printf("FAILED: %s\n\n", message);
        return 0;
    }
    else{
      //  printf("PASSED: %s\n\n", message);
        return 1;
    }
}

// This test should test council card.  In refactored code, changed ‘+1 buy’ 
// to ‘+2 buy’ on line 1412, giving a player more buys when the council card is played.

int main () {
    srand(time(NULL));
    int result = 0;
    int seedNum = 1;
    // Message to be sent into assertion for testing messeages.
    char* errorMessage;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    
    struct gameState game, testGame;
    printf ("******************** randomcardtest2.c: Testing village card *****************\n\n");
    
    int init = 0;
    int beforeNumActions = 0;
    int villageReturn = 0;
    int afterNumActions = 0;
    int playerHandCount = 0;
    int deck = 0;
    int played = 0;
    int numPlayers;
    int player;
    int testRun = 1000;
    int i;
    // Array to track indices of seed numbers and number of players that had failed tests.
    bool errorSeeds[10];
    for(i = 0; i < 10; i++){
        errorSeeds[i] = false;
    }
    bool errorPlayerNums[5];
    for(i = 0; i < 5; i++){
        errorPlayerNums[i] = false;
    }
    
    for(i = 0; i < testRun; i ++){
        numPlayers = rand()%(4 + 1 - 2) + 2;
        seedNum = rand()%(10 - 1) + 1;
        // Initialize game.
        result = initializeGame(numPlayers, k, seedNum, &game);
        //errorMessage = "Initialize game did returns 0.";
        if (assertTrue(result == 0, errorMessage) == 1){
            init++;
        }
        
        // Randomize values
        player = rand()%numPlayers;
        game.deckCount[player] = floor(Random() * MAX_DECK);
        game.discardCount[player] = floor(Random() * MAX_DECK);
        game.handCount[player] = floor(Random() * MAX_HAND);
        // Randomize player's hand.
        int j;
        for(j = 0; j < game.handCount[player]; j++){
            game.hand[player][j] = k[rand()%10];
        }
        game.whoseTurn = player;
        
        
        // Make copy of game for testing comparison.
        memcpy(&testGame, &game, sizeof(struct gameState));
        
        // Number of actions before village card effect, which should be 1.
        // errorMessage = "Before testing village card, numActions = 1.";
        if(assertTrue(testGame.numActions == 1, errorMessage) == 1){
            beforeNumActions++;
        } else {
            errorSeeds[seedNum] = true;
            errorPlayerNums[numPlayers] = true;
        }
        
        // After playing village card effect should return 0.
        // errorMessage = "Testing village card effect returns 0.";
        result = cardEffect(14, -1,-1,-1,&testGame, 0, 0);
        if(assertTrue(result == 0, errorMessage) == 1){
            villageReturn++;
        } else {
            errorSeeds[seedNum] = true;
            errorPlayerNums[numPlayers] = true;
        }
            
        // Obtain number of actions after village card effect, which should be +2.
        // errorMessage = "After testing village card, numActions is + 2.";
        if(assertTrue(testGame.numActions == (game.numActions + 2), errorMessage) == 1){
            afterNumActions++;
        } else {
            errorSeeds[seedNum] = true;
            errorPlayerNums[numPlayers] = true;
        }
            
        // After playing, number of player's hand count should be unchanged (+1 draw, -1 discard).
        // errorMessage = "After testing village card, player's hand count is unchanged.";
        if(assertTrue(testGame.handCount[player] == game.handCount[player], errorMessage) == 1){
            playerHandCount++;
        } else {
            errorSeeds[seedNum] = true;
            errorPlayerNums[numPlayers] = true;
        }
            
        // After playing, number of played cards should be +1.
        // errorMessage = "After playing council_room card, played card count is +1.";
        if(assertTrue((game.playedCardCount + 1) == testGame.playedCardCount, errorMessage) == 1){
            played++;
        } else {
            errorSeeds[seedNum] = true;
            errorPlayerNums[numPlayers] = true;
        }
            
        // After playing, player deck count should be -1.
        //  errorMessage = "After testing village card, player deck count is -1.";
        if(assertTrue(testGame.deckCount[player] == (game.deckCount[player] - 1), errorMessage) == 1){
            deck++;
        } else {
            errorSeeds[seedNum] = true;
            errorPlayerNums[numPlayers] = true;
        }
    }
    // Print test results.
    printf("TEST: Initialize game returns 0.\n");
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((init/testRun)*100), ((testRun-init)/testRun*100));
    
    printf("TEST: Before village card effect, numActions = 1.\n");
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((beforeNumActions/testRun)*100),((testRun-beforeNumActions)/testRun*100));
    
    printf("TEST: Village card effect returns 0.\n");
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((villageReturn/testRun)*100), ((testRun-villageReturn)/testRun*100));
    
    printf("TEST: After playing village card, numActions is + 2.\n");
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((afterNumActions/testRun)*100), ((testRun-afterNumActions)/testRun*100));
    
    printf("TEST: After playing card, player's hand count is unchanged.\n");
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((playerHandCount/testRun)*100), ((testRun-playerHandCount)/testRun*100));
  
    printf("TEST: After playing card, played card count is +1.\n");
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((played/testRun)*100), ((testRun-played)/testRun*100));
    
    printf("TEST: After playing card, player's deck count is -1.\n");
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((deck/testRun)*100), ((testRun-deck)/testRun*100));
    
    printf("Random seeds that generated failing test cases: ");
    for(i = 0; i < 10; i++){
        if(errorSeeds[i] == true){
            printf("%d ", i);
        }
    }
    printf("\n");
    
    printf("Number of players for games that generated failed test cases: ");
    for(i = 0; i < 5; i++){
        if(errorPlayerNums[i] == true){
            printf("%d ", i);
        }
    }
    printf("\n");
    
    return 0;
}