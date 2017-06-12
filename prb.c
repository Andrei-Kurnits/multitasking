#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	printf("Process \"B\" ID is %d\n", (int)getpid());
	return 0;
}