#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	printf("I'm process \"C\". My ID is %d\n", (int)getpid());
	return 0;
}