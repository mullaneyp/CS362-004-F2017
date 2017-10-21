CFLAGS = -Wall -fpic -coverage -lm
	
buildTest: testme.c
	gcc -o testMe testme.c -g  $(CFLAGS)
	
runTest:  buildTest
	-./testMe
	#gcov -b -f testme.c >> testme.out
	gcov -b -f testme.c
	#cat testme.c.gcov >> testme.out
	
all: 
	make buildTest
	make runTest
	
clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out testMe
