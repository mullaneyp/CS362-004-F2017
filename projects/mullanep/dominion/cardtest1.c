/*************************************************************
 * Author: Patrick Mullaney
 * Description: card test1 program for assignment 3, CS362.
 * Program tests smithy card.
**************************************************************/
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// compile: gcc -o card1 cardtest1.c dominion.c rngs.c -coverage -lm

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

// This test tests smithy card.

int main () {
    
    int result = 0;
    int seedNum = 1;
    char* errorMessage;
    int newCards = 0;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    
    struct gameState game, testGame;
    SelectStream(2);
    PutSeed(3);
    printf ("************************* cardtest1.c: Testing smithy card ****************************\n\n");
    
    result = initializeGame(2, k, seedNum, &game);
    errorMessage = "Initialization returned 0.";
    assertTrue(result == 0, errorMessage);
    
    // Make copy of game for testing comparison.
    memcpy(&testGame, &game, sizeof(struct gameState));

    printf("TEST: After initialization, hand and deck card counts are 5.\n\n");
    // Obtain number of hand cards before smithy card is played.
    newCards = 3;
    errorMessage = "Hand and deck counts before smithy == 5.";
    assertTrue((testGame.handCount[0] == 5 && testGame.deckCount[0] == 5), errorMessage);
    
    // For debugging:
    // printf("Before: HandCount: Actual: %d, Expected: %d\n", testGame.handCount[0], (game.handCount[0]));
    // printf("Before: DeckCount: Actual: %d, Expected: %d\n", testGame.deckCount[0], (game.deckCount[0]));
    
    printf("TEST: smithy cardEffect returns 0.\n\n");
    // Card effect for smithy card should return 0.
    errorMessage = "Testing smithy card effect returned 0.";
    result = cardEffect(smithy, 0, 0, 0, &testGame, 0, 0);
    assertTrue(result == 0, errorMessage);

    printf("TEST: Player's hand count after smithy played should be +3.\n\n");
    errorMessage = "After smithy played, handCount is +3.";
    // Num of handcards before smithy played + 3 should equal number of handcards post smithy.
    assertTrue((game.handCount[0] + newCards) == testGame.handCount[0], errorMessage);
    // If number of hand cards is + 3, test passed.
    if((game.handCount[0] + newCards) == testGame.handCount[0]){
        printf("PASS: After smithy handCount is +3.\n");
    }
    else
        printf("Handcount Actual: %d, Expected: %d.\n", testGame.handCount[0], (game.handCount[0] +newCards));
    
    // Test whether cards came from players deck and not other.
    printf("TEST: Cards came from players deck and not other player.\n\n");
    // Obtain number of hand cards after smithy card played.
    errorMessage = "After smithy played, deckCount is -3.";
    // Deckcount should be -3 post smithy.
    assertTrue((game.deckCount[0] - newCards) == testGame.deckCount[0], errorMessage);
    
    // Results of assertion.
    if((game.deckCount[0] - newCards) == testGame.deckCount[0]){
        printf("PASS: After smithy deckCount is -3.\n");
    }
    else
        printf("Deckcount: Actual: %d, Expected: %d.\n", testGame.deckCount[0], (game.deckCount[0] - newCards));
    
    // Test opponent's hand & deck counts.
    printf("TEST: Opponent's hand & deck counts were not altered.\n\n");
    errorMessage = "No changes to other player's piles.";
    assertTrue(game.deckCount[1] == testGame.deckCount[1] && game.handCount[1] == testGame.handCount[1], errorMessage);
    
    if(failures == 0){
        printf ("ALL TESTS PASSED.\n\n");
    }
    else
        printf("TESTS FAILED: %d. TESTS PASSED: %d\n\n", failures, success);
    
    return 0;
}