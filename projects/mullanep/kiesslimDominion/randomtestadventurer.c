/******************************************************************
 * Author: Patrick Mullaney
 * Description: random adventurer card program for assignment 4, CS362.
 * Program tests adventurer card. 
******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"
#include <math.h>
#include <time.h>

// compile: gcc -o randomtestadventurer randomtestadventurer.c dominion.c rngs.c -coverage -lm
//gcc -o rando3 randomtestadventurer.c dominion.c rngs.c -coverage -lm

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

// This test should test adventurer card.  In refactored code....

int main () {
    srand(time(NULL));
    int result = 0;
    int seedNum = 1;
    // Message to be sent into assertion for testing messeages.
    char* errorMessage;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    
    struct gameState game, testGame;
    printf ("******************** randomcardtestadventure.c: Testing adventurer card *****************\n\n");
    
    int init = 0;
    int adventurerReturn = 0;
    int beginHandCount = 0;
    int afterHandCount = 0;
    int numPlayers;
    int player;
    int testRun = 1000;
    int i;
    // Array to track indices of seed numbers and number of players for games that had failed tests.
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
        errorMessage = "Initialize game did return 0.";
        if (assertTrue(result == 0, errorMessage) == 1){
            init++;
        } else {
            errorSeeds[seedNum] = true;
            errorPlayerNums[numPlayers] = true;
        }
            
        // Randomize values
        player = rand()%numPlayers;
      //  game.deckCount[player] =  MAX_DECK;
    //    game.discardCount[player] = 0;
     //   game.handCount[player] = MAX_HAND;
     /*
        // Randomize player's hand.
        int j;
        for(j = 0; j < game.handCount[MAX_HAND]; j++){
            game.hand[player][j] = k[rand()%10];
        }
        game.whoseTurn = player;
        // Randomize deck.
        for(j = 0; j < game.deckCount[MAX_DECK]; j++){
            game.deck[player][j] = k[rand()%10];
        }
       */
            
        // Make copy of game for testing comparison.
        memcpy(&testGame, &game, sizeof(struct gameState));
        
        // Obtain number of cards before adventurer card effect.
        //errorMessage = "Before adventurer, handcount == 5.";
        if(assertTrue(testGame.handCount[player] == 5, errorMessage) == 1){
            beginHandCount++;
        } else {
            errorSeeds[seedNum] = true;
            errorPlayerNums[numPlayers] = true;
        }
            
        // Card effect for adventurer card should return 0.
        //errorMessage = "Adventurer card effect returns 0.";
        // Original
        //result = cardEffect(7, -1,-1,-1,&testGame, 0, 0);
        result = cardEffect(adventurer, 0, 0, 0, &testGame, 0, 0);
       //int handpos = 0;
      // int bonus = 0;
      // result = adventurerCardEffect(&testGame);
        if(assertTrue(result == 0, errorMessage) == 1){
            adventurerReturn++;
        } else {
            errorSeeds[seedNum] = true;
            errorPlayerNums[numPlayers] = true;
        }
            
        // Test handCount after adventurer card effect, which should be +1.
        // errorMessage = "After testing adventurer card handCount is +1";
        if(assertTrue(testGame.handCount[player] + (game.handCount[player] + 1) == 2, errorMessage) == 1){
            afterHandCount++;
        } else {
            errorSeeds[seedNum] = true;
            errorPlayerNums[numPlayers] = true;
        }
            
    }
    // Print test results.
    printf("TEST: Initialize game returns 0.\n");
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((init/testRun)*100), ((testRun-init)/testRun*100));
   
    // begin adventurer
    printf("TEST: Before adventurer card, handCount = 5.\n");
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((beginHandCount/testRun)*100), ((testRun-beginHandCount)/testRun*100));
    
    printf("TEST: Adventurer card effect returns 0.\n");
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((adventurerReturn/testRun)*100), ((testRun-adventurerReturn)/testRun*100));
   
    printf("TEST: After adventurer card effect player's handCount is + 1.\n");
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((afterHandCount/testRun)*100), ((testRun-afterHandCount)/testRun*100));
    
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