#include "util.h"
unsigned long long getEpochMill(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned long long)(tv.tv_sec)*1000 + (unsigned long long)(tv.tv_usec)/1000;
}
char * getString(int x, int y, int length)
{
	char *stringHolder = (char *)malloc(sizeof(char) * length);
	char *startPointer = stringHolder;
	move(y, x);
	char currentCharacter;
	while (currentCharacter != EOF && currentCharacter != '\n')
	{
		timeout(-1);
		currentCharacter = getchar();
		*(stringHolder++) = currentCharacter;
		mvaddch(y, x++, currentCharacter);
	}
	return startPointer;
}