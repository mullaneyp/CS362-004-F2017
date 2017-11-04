CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)
	
runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: unittest1.c dominion.o rngs.o
	gcc  -o unittest1 -g  unittest1.c dominion.o rngs.c $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc  -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc  -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc  -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	
cardtest1: cardtest1.c dominion.o rngs.o
	gcc  -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc  -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc  -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc  -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

randomcardtest1: randomcardtest1.c dominion.o rngs.o
	gcc  -o randomcardtest1 -g  randomcardtest1.c dominion.o rngs.o $(CFLAGS)

randomcardtest2: randomcardtest2.c dominion.o rngs.o
	gcc  -o randomcardtest2 -g  randomcardtest2.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc  -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

buildTests:
	make unittest1 
	make unittest2 
	make unittest3 
	make unittest4 
	make cardtest1 
	make cardtest2 
	make cardtest3 
	make cardtest4

buildRandom:
	make randomcardtest1
	make randomcardtest2
	make randomtestadventurer

unittestresults.out: buildTests
	./unittest1 > unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

runRandom: buildRandom
	./randomcardtest1 > randomcardtest1.out
	gcov -b -f dominion.c >> randomcardtest1.out
	./randomcardtest2 > randomcardtest2.out
	gcov -b -f dominion.c >> randomcardtest2.out
	./randomtestadventurer > randomtestadventurer.out
	gcov -b -f dominion.c >> randomtestadventurer.out

all: playdom player testDrawCard testBuyCard badTestDrawCard unittestresults.out

cleanBuild:
	rm unittest1
	rm unittest2
	rm unittest3
	rm unittest4
	rm cardtest1
	rm cardtest2
	rm cardtest3
	rm cardtest4

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe