#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // Declare variables, for ASCII ignore non-input but include extended
	int firstASCIIChar = 32;
	int lastASCIIChar = 255;

	// Intialize random character in range and return
    return (rand() % (lastASCIIChar - (firstASCIIChar - 1))) + firstASCIIChar;
}

char *inputString()
{
	// Declare variables, for ASCII consider only lower case letters
	int firstASCIIChar = 97;
	int lastASCIIChar = 122;
	static char myString[5];
	int i;

	// Run loop to populate string
	for (i = 0; i < 5; i++)
	{
		myString[i] = ((rand() % (lastASCIIChar - (firstASCIIChar - 1))) + firstASCIIChar);
	}
		
	// Return pointer to char array
	return myString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
