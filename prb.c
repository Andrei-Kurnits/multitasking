#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "pra.h"

int main()
{
	int   pipefile;
	int   bytes;
	int   result = 0;
	
	printf("I'm process \"B\". My ID is %d\n", (int)getpid());
	
	pipefile = open(PIPEFILE_PATH, O_RDONLY);
	if (pipefile <= 0) {
		perror("open");
		abort();
	}
	printf("I'm process \"B\". Pipe \"%s\" is opened for READING\n", PIPEFILE_PATH);
	
	while (true) {
		union integer_u integer;
		bytes = read(pipefile, integer.buf, sizeof(integer.buf));
		if (bytes <= 0 ) {
			perror("I'm process \"B\". Error in function read().");
			result = -1;
			break;
		} else
			printf("Process \"B\" receives a number: %d\n", integer.num);
        }
	
	close(pipefile);

	return result;
}