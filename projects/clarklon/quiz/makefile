CC = gcc
CFLAGS = -Wall -fpic -coverage -lm 

testme: 
	$(CC) -g testme.c -o testme $(CFLAGS) 
	./testme

clean:
	rm -f *.o *.gcov *.gcda *.gcno testme
