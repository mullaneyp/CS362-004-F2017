/*************************************************************
 * Author: Patrick Mullaney
 * Description: unit test 3 program for assignment 3, CS362.
 * Program tests scoreFor function. 
**************************************************************/
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// compile: gcc -o unit3 unittest3.c dominion.c rngs.c -coverage -lm

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

// Functions to calculate victory points in players hand, discard, and deck piles.
int getHandScore(int player, struct gameState *state);
int getDiscardScore(int player, struct gameState *state);
int getDeckScore(int player, struct gameState *state);

// This tests scorefor is this random testing?.
int main () {
    
    int result = 0;
    int seedNum = 1;
    char* message;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    
    struct gameState game, testGame;
    
    printf ("*********************** unittest3.c: Testing scorefor **********************\n\n");
    
    printf("TEST: Initialization returns 0.\n");
    result = initializeGame(2, k, seedNum, &game);
    message = "Initialization returned 0.";
    assertTrue(result == 0, message);
    
    // Make copy of game for testing comparison.
    memcpy(&testGame, &game, sizeof(struct gameState));
    
    // Test invalid input.
    printf("TEST: Invalid input (3) returns -9999.\n");
    message = "Invalid input returns -9999.";
    //assertTrue(getHandScore(3,&testGame) == -9999, message);
    assertTrue(scoreFor(3, &testGame) == -9999, message);
    printf("invalid: %d\n", getHandScore(3, &testGame));
    
    // Test invalid input 2.
    printf("TEST: Invalid input (-1) returns -9999.\n");
    message = "Invalid input returns -9999.";
    //assertTrue(getHandScore(3,&testGame) == -9999, message);
    assertTrue(scoreFor(-1, &testGame) == -9999, message);
    printf("invalid: %d\n", getHandScore(3, &testGame));
    
    // Player 1 hand
    testGame.hand[0][0] = curse;        // -1
    testGame.hand[0][1] = estate;       // +1
    testGame.hand[0][2] = great_hall;   // +1
    testGame.hand[0][3] = duchy;        // +3
    testGame.hand[0][4] = province;     // +6
    testGame.handCount[0] = 5;
    // Player 1 deck
    testGame.deck[0][0] = copper;       // 0
    testGame.deck[0][1] = duchy;        // +3
    testGame.deck[0][2] = great_hall;   // +1
    testGame.deck[0][3] = mine;         // 0
    testGame.deck[0][4] = province;     // +6
    testGame.deckCount[0] = 5;
    // Player 1 discard
    testGame.discard[0][0] = estate;        // +1
    testGame.discard[0][1] = estate;        // +1
    testGame.discard[0][2] = great_hall;    // +1
    testGame.discard[0][3] = curse;         // -1
    testGame.discard[0][4] = province;      // +6
    testGame.discardCount[0] = 5;
    // Expect hand score = 10, deck = 10, discard = 8
    
    // Player 2 hand
    testGame.hand[1][0] = duchy;        // +3
    testGame.hand[1][1] = estate;       // +1
    testGame.hand[1][2] = curse;        // -1
    testGame.hand[1][3] = duchy;        // +3
    testGame.hand[1][4] = province;     // +6
    testGame.handCount[1] = 5;
    // Player 2 deck
    testGame.deck[1][0] = baron;        // 0
    testGame.deck[1][1] = duchy;        // +3
    testGame.deck[1][2] = silver;       // 0
    testGame.deck[1][3] = mine;         // 0
    testGame.deck[1][4] = province;     // +6
    testGame.deckCount[1] = 5;
    // Player 2 discard
    testGame.discard[1][0] = estate;    // +1
    testGame.discard[1][1] = curse;     // -1
    testGame.discard[1][2] = duchy;     // +3
   // testGame.discard[1][3] = curse;     // -1
//    testGame.discard[1][4] = province;  // +6
    testGame.discardCount[1] = 3;
    // Expect hand score = 12, deck = 9, discard = 8
    
    // Test p1 score.
    printf("TEST: Player 1 score is correct.\n");
    message = "Player 1 score correct.";
    // P1 score should equal hand score + discard score + deck score;
    int p1HandScore = getHandScore(0, &testGame);
    int p1DiscardScore = getDiscardScore(0, &testGame);
    int p1DeckScore = getDeckScore(0, &testGame);
    // printf("Hand score :%d discard: %d deck: %d\n", p1HandScore, p1DiscardScore, p1DeckScore);
    // P1 score should equal score calculated above.
    int p1score = p1HandScore + p1DiscardScore + p1DeckScore;
    int p1ScoreFor = scoreFor(0, &testGame);
    assertTrue(p1score == p1ScoreFor, message);
    printf("Player 1 Expected score: %d scoreFor: %d\n\n", p1score, p1ScoreFor);
    
    /* For debugging, prints out values of card piles.
    printf("P1 deck: \n");
    int i;
    for(i = 0; i < testGame.deckCount[0]; i++){
        printf("%d: %d\n", i, testGame.deck[0][i]);
    }

    printf("P1 discard: \n");
    //int i;
    for(i = 0; i < testGame.discardCount[0]; i++){
        printf("%d: %d\n", i, testGame.discard[0][i]);
    }
    
    printf("P2 deck: \n");
    //int i;
    for(i = 0; i < testGame.deckCount[1]; i++){
        printf("%d: %d\n", i, testGame.deck[1][i]);
    }

    printf("P2 discard: \n");
    //int i;
    for(i = 0; i < testGame.discardCount[1]; i++){
        printf("%d: %d\n", i, testGame.discard[1][i]);
    }
    end debugging */
    
    // Test p2 score.
    printf("TEST: Player 2 score is correct.\n\n");
    message = "Player 2 score correct.";
    // P2 score should equal hand score + discard score + deck score;
    int p2HandScore = getHandScore(1, &testGame);
    int p2DiscardScore = getDiscardScore(1, &testGame);
    int p2DeckScore = getDeckScore(1,&testGame);
    int p2score = p2HandScore + p2DiscardScore + p2DeckScore;
    // P2 score should equal score calculated above.
    int p2ScoreFor = scoreFor(1, &testGame);
    assertTrue(p2score == p2ScoreFor, message);
    printf("Player 2 Expected score: %d.  scoreFor: %d.\n", p2score, p2ScoreFor);
    
    if(failures == 0){
        printf ("ALL TESTS PASSED.\n\n");
    }
    else
        printf("TESTS FAILED: %d.  TESTS PASSED: %d\n\n", failures, success);
    
    return 0;
}
// Calculate score for victory points in hand.
int getHandScore(int player, struct gameState *state){
    int score, i;
    score = 0;
    for (i = 0; i < state->handCount[player]; i++)
    {
        if (state->hand[player][i] == curse) { 
            score = score - 1; 
        }
        if (state->hand[player][i] == estate) { 
            score = score + 1;
        }
        if (state->hand[player][i] == duchy) { 
            score = score + 3; 
        }
        if (state->hand[player][i] == province) { 
            score = score + 6; 
        }
        if (state->hand[player][i] == great_hall) { 
            score = score + 1; 
        }
        if (state->hand[player][i] == gardens) { 
            score = score + ( fullDeckCount(player, 0, state) / 10 );
        }
    }
    return score;
}
// Calculate score for victory points in discard.
int getDiscardScore(int player, struct gameState *state){
    int i;
    int score = 0;
    for (i = 0; i < state->discardCount[player]; i++)
    {
        if (state->discard[player][i] == curse) { 
            score = score - 1; 
        }
        if (state->discard[player][i] == estate) { 
            score = score + 1; 
        }
        if (state->discard[player][i] == duchy) { 
            score = score + 3; 
        }
        if (state->discard[player][i] == province) { 
            score = score + 6; 
        }
        if (state->discard[player][i] == great_hall) { 
            score = score + 1; 
        }
        if (state->discard[player][i] == gardens) { 
            score = score + ( fullDeckCount(player, 0, state) / 10 );
        }
    }
    return score;
}
// Calculate score for victory points in deck.
int getDeckScore(int player, struct gameState *state){
    int i;
    int score = 0;
     for (i = 0; i < state->deckCount[player]; i++)
    {
        if (state->deck[player][i] == curse) { 
            score = score - 1; 
        }
        if (state->deck[player][i] == estate) { 
            score = score + 1;
        }
        if (state->deck[player][i] == duchy) { 
            score = score + 3; 
        }
        if (state->deck[player][i] == province) { 
            score = score + 6; 
        }
        if (state->deck[player][i] == great_hall) { 
            score = score + 1; 
        }
        if (state->deck[player][i] == gardens) { 
            score = score + ( fullDeckCount(player, 0, state) / 10 ); 
        }
    }
    return score;
}