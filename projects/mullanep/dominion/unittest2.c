/*************************************************************
 * Author: Patrick Mullaney
 * Description: unit test 2 program for assignment 3, CS362.
 * Program tests getCost function 
**************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// This test tests the getCost function.  

// compile: gcc -o unit2 unittest2.c dominion.c rngs.c -coverage -lm

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

int main () {
    
    int result = 0;
    //int seedNum = 0;
    char* message;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    
    struct gameState testGame;
    
    printf ("************************** unittest2.c: Testing getCost ****************************\n\n");
    
    printf ("TEST: Initialization returns 0.\n");
    result = initializeGame(2, k, 1, &testGame);
    message = "Initialization returns 0.";
    assertTrue(result == 0, message);
    
    // Test invalid input.  Should return -1.
    printf ("TEST: Invalid input returns -1.\n");
    message = "Invalid input -1 returns -1.";
    result = getCost(-1);
    assertTrue(result == -1, message);
    
    // Test valid input, should return 0?
    printf ("TEST: Valid input returns 0.\n");
    message = "Valid input 4 returns 0.";
    result = getCost(4);
    assertTrue(result == 0, message);
    
    printf ("TEST: Curse returns 0.\n");
    message = "Curse returns 0.";
    result = getCost(curse); // 0
    assertTrue(result == 0, message);
    
    printf ("TEST: Estate returns 2.\n");
    message = "Estate returns 2.";
    assertTrue(getCost(estate) == 2, message); //1
    
    printf ("TEST: Duchy returns 5.\n");
    message = "Duchy returns 5.";
    assertTrue(getCost(duchy) == 5, message); //2
    
    printf ("TEST: Province returns 5.\n");
    message = "Province returns 8.";
    assertTrue(getCost(province) == 8, message); //3
    
    printf ("TEST: Copper returns 0.\n");
    message = "Copper returns 0.";
    assertTrue(getCost(copper) == 0, message); //4
    
    printf ("TEST: Silver returns 3.\n");
    message = "Silver returns 3.";
    assertTrue(getCost(silver) == 3, message); //5
    
    printf ("TEST: Gold returns 6.\n");
    message = "Gold returns 6.";
    assertTrue(getCost(gold) == 6, message); //6
    
    printf ("TEST: Adventurer returns 6.\n");
    message = "Adventurer returns 6.";
    assertTrue(getCost(adventurer) == 6, message); //7
    
    printf ("TEST: council_room returns 5.\n");
    message = "council_room returns 5.";
    assertTrue(getCost(council_room) == 5, message); //8
    
    printf ("TEST: feast returns 4.\n");
    message = "feast returns 4.";
    assertTrue(getCost(feast) == 4, message); //9
    
    printf ("TEST: gardens returns 4.\n");
    message = "gardens returns 4.";
    assertTrue(getCost(gardens) == 4, message); //10
    
    printf ("TEST: mine returns 5.\n");
    message = "mine returns 5.";
    assertTrue(getCost(mine) == 5, message); //11
    
    printf ("TEST: remodel returns 4.\n");
    message = "remodel returns 4.";
    assertTrue(getCost(remodel) == 4, message); //12
    
    printf ("TEST: smithy returns 4.\n");
    message = "smithy returns 4.";
    assertTrue(getCost(smithy) == 4, message); //13
    
    printf ("TEST: village returns 3.\n");
    message = "village returns 3.";
    assertTrue(getCost(village) == 3, message); //14
    
    printf ("TEST: baron returns 4.\n");
    message = "baron returns 4.";
    assertTrue(getCost(baron) == 4, message); //15
    
    printf ("TEST: great_hall returns 3.\n");
    message = "great_hall returns 3.";
    assertTrue(getCost(great_hall) == 3, message); //16
    
    printf ("TEST: minion returns 5.\n");
    message = "minion returns 5.";
    assertTrue(getCost(minion) == 5, message); //17
    
    printf ("TEST: steward returns 3.\n");
    message = "steward returns 3.";
    assertTrue(getCost(steward) == 3, message); //18
    
    printf ("TEST: tribute returns 5.\n");
    message = "tribute returns 5.";
    assertTrue(getCost(tribute) == 5, message); //19
    
    printf ("TEST: ambassador returns 3.\n");
    message = "ambassador returns 3.";
    assertTrue(getCost(ambassador) == 3, message); //20
    
    printf ("TEST: cutpurse returns 4.\n");
    message = "cutpurse returns 4.";
    assertTrue(getCost(cutpurse) == 4, message); //21
    
    printf ("TEST: embargo returns 2.\n");
    message = "embargo returns 2.";
    assertTrue(getCost(embargo) == 2, message); //22
    
    printf ("TEST: outpost returns 5.\n");
    message = "outpost returns 5.";
    assertTrue(getCost(outpost) == 5, message); //23
    
    printf ("TEST: salvager returns 4.\n");
    message = "salvager returns 4.";
    assertTrue(getCost(salvager) == 4, message); //24
    
    printf ("TEST: sea hag returns 4.\n");
    message = "sea hag returns 4.";
    assertTrue(getCost(sea_hag) == 4, message); //25
    
    printf ("TEST: treasure_map returns 4.\n");
    message = "treasure_map returns 4.";
    assertTrue(getCost(treasure_map) == 4, message); //26
    
    if(failures == 0){
        printf ("ALL TESTS PASSED.\n\n");
    }
    else
        printf("TESTS FAILED: %d.  TESTS PASSED: %d\n\n", failures, success);
    
    return 0;
}