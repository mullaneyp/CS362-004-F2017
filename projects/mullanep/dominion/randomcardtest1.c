/******************************************************************
 * Author: Patrick Mullaney
 * Description: random card test1 program for assignment 4, CS362.
 * Program tests council_room card. 
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

// compile: gcc -o randomcardtest1 randomcardtest1.c dominion.c rngs.c -coverage -lm
//gcc -o rando randomcardtest1.c dominion.c rngs.c -coverage -lm

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
    printf ("******************** randomcardtest1.c: Testing council card *****************\n\n");
    
    int init = 0;
    int beforeNumBuys = 0;
    int councilReturn = 0;
    int afterNumBuys = 0;
    int p1cards = 0;
    int p2cards = 0;
    int played = 0;
    int testRun = 1000;
    int numPlayers;
    int player;
    int i;
    // Array to track indices of seed numbers that had failed tests.
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
        errorMessage = "Initialize game did returns 0.";
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
       // printf("Player: %d\n", player);
        
        // Make copy of game for testing comparison.
        memcpy(&testGame, &game, sizeof(struct gameState));
        
        // Obtain number of buys before council card effect.
        //errorMessage = "Before testing council card, numBuys == 1.";
        if(assertTrue(testGame.numBuys == 1, errorMessage) == 1){
            beforeNumBuys++;
        } else {
            errorSeeds[seedNum] = true;
            errorPlayerNums[numPlayers] = true;
        }
        // Card effect for council card should return 0.
        //errorMessage = "Council card effect returns 0.";
       // result = cardEffect(village, -1,-1,-1,&testGame, 0, 0);
        result = cardEffect(8, -1, -1, -1, &testGame, 0, 0);
        if(assertTrue(result == 0, errorMessage) == 1){
            councilReturn++;
        } else {
            errorSeeds[seedNum] = true;
            errorPlayerNums[numPlayers] = true;
        }
        // Obtain number of actions after council card effect, which should be +1.
        //errorMessage = "After testing council card, numBuys == 2.";
        if(assertTrue(testGame.numBuys == (game.numBuys + 1), errorMessage) == 1){
            afterNumBuys++;
        } else {
            errorSeeds[seedNum] = true;
            errorPlayerNums[numPlayers] = true;
        }
        // Obtain number of cards after council card effect, which should be +3 (+4 -1 discard) for player 1, +1 for player2.
        //errorMessage = "After playing council_room card, player1 is +3 cards.";
        if(assertTrue(((game.handCount[player] + 3) == testGame.handCount[player]), errorMessage) == 1){
            p1cards++;
        } else {
            errorSeeds[seedNum] = true;
            errorPlayerNums[numPlayers] = true;
        }
        //errorMessage = "After playing council_room card, player2 is +1 cards.";
        if(assertTrue(((game.handCount[1] + 1) == testGame.handCount[1]), errorMessage) == 1){
            p2cards++;
        } else {
            errorSeeds[seedNum] = true;
            errorPlayerNums[numPlayers] = true;
        }  
        // Obtain number of played cards after playing council_room card, which should be +1.
        // errorMessage = "After playing council_room card, played card count is +1.";
        if(assertTrue((game.playedCardCount + 1) == testGame.playedCardCount, errorMessage) == 1){
            played++;
        } else {
            errorSeeds[seedNum] = true;
            errorPlayerNums[numPlayers] = true;
        }
    }
    
    printf("TEST: Initialize game returns 0.\n");
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((init/testRun)*100), ((testRun-init)/testRun*100));
    printf("TEST: Before playing council card, numBuys == 1.\n");
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((beforeNumBuys/testRun)*100),((testRun-beforeNumBuys)/testRun*100));
    printf("TEST: Playing council_room card returns 0.\n");
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((councilReturn/testRun)*100), ((testRun-councilReturn)/testRun*100));
    printf ("TEST: After council card, numBuys == 2 (+1).\n");
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((afterNumBuys/testRun)*100), ((testRun-afterNumBuys)/testRun*100));
    printf("TEST: After playing card, player1 is + 3 cards.\n");
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((p1cards/testRun)*100), ((testRun-p1cards)/testRun*100));
    printf("TEST: After player card player2 is +1 cards.\n");;
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((p2cards/testRun)*100), ((testRun-p2cards)/testRun*100));
    printf("TEST: After playing card, played card count is +1.\n");
    printf("PASSED: %d%%.  FAILED: %d%%.\n\n", ((played/testRun)*100), ((testRun-played)/testRun*100));
    
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