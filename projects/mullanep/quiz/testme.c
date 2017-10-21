/*************************************************************
 * Author: Patrick Mullaney
 * Description: testme.c program for random quiz, CS362.
 * Program is a simple random tester to generate random 
 * chars and random strings to meet conditions.
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar(){
    //   TODO: rewrite this function
    int randomNum = 0;
    // Obtain random number within alphanumeric char ranges.
    // rand()%(max + 1 - min)+min
    randomNum = rand()%((126 + 1 - 33) + 33);
    // Convert int to char
    char randomChar = (char)randomNum;
    // Return char.
    return randomChar;
    
}
char *inputString(){
    //   TODO: rewrite this function
    char randomString[6];
    int randomChar;  
    char alphaBet [20] = {'a','x','d','r','f','p','j','w','l','n','o','i','e','s','k','u','t','d','y','z'};
    int i;
    for(i = 0; i < 5; i++){
        // Runtime was too long with full ascii range.
      // randomChar = (rand()%(122 + 1 - 97)+97);
        randomChar = (rand()%(19 + 1 - 0) + 0);
        randomString[i] = alphaBet [randomChar];
    }
    randomString[5] = '\0';
    
    char* returnString = randomString;
  return returnString;  
}
void testme(){
    int tcCount =  0;
    char *s;
    char c;
    int state =  0;
    while (1){
        tcCount++;
        c  =  inputChar();
        s  =  inputString();
        printf("Iteration %d: c =  %c, s  =  %s, state = %d\n", tcCount, c, s, state);
        if (c == '[' && state == 0) state = 1;
        if (c == '(' && state == 1) state = 2;
        if (c == '{' && state == 2) state = 3;
        if (c == ' ' && state == 3) state = 4;
        if (c == 'a' && state == 4) state = 5;
        if (c == 'x' && state == 5) state = 6;
        if (c == '}' && state == 6) state = 7;
        if (c == ')' && state == 7) state = 8;
        if (c == ']' && state == 8) state = 9;
        if (s[0] == 'r' && s[1] == 'e'&& s[2] == 's' && s[3] == 'e'&& s[4] == 't' && s[5] == '\0'&& state == 9){
            printf("error ");
            exit(200);
        }
    }
}

int main(int argc, char *argv[]){

    srand(time(NULL));
    testme();

    return 0;
}
