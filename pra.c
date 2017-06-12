#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <fcntl.h>

#include "pra.h"



int main()
{
	pid_t proc_a;
	pid_t proc_b;
	pid_t proc_c;
	int   result;
	int   pipefile;
	
	proc_a = getpid();	// main program process is PROCESS A - parent
	
	printf("I'm process \"A\". My ID is %d\n", (int)proc_a);

	proc_b = fork();			// copy parent process A
	
	if (proc_b) {				// if we are in parent process (process A)
		proc_c = fork();		// copy parent process A
		if (proc_c == 0) {		// if we are in child process C
			execv("./prc", 0);	// create child process C
			perror("execv()");
			abort();
		}
	} else {
		execv("./prb", 0);	// create child process B
		perror("execv()");
		abort();
	}
	
	// Delete FIFO-file (for case if exists).
	remove(PIPEFILE_PATH);
	
	// Create pipe FIFO-file named PIPEFILE_PATH
	result = mkfifo(PIPEFILE_PATH, 0777);
	if (result) {
		perror("mkfifo()");
		abort();
	}
	
	pipefile = open(PIPEFILE_PATH, O_WRONLY);
	if (pipefile <= 0) {
		perror("open");
		abort();
	}
	printf("I'm process \"A\". Pipe \"%s\" is opened for WRITTING.\n", PIPEFILE_PATH);
	
	while(true) {
		int number, items, bytes;
		union integer_u integer;
		
		usleep(2000);	// sleep 2 milliseconds for Process B response.
		
		printf("Process \"A\" asks a number (enter not-a-number for exit): ");
		items = scanf("%d", &number);
		if (items) {
			integer.num = number;
			bytes = write(pipefile, integer.buf, sizeof(integer.buf));
			if (bytes == 0)
				break;
		} else
			break;
	}
	
	close(pipefile);
	remove(PIPEFILE_PATH);
	
	
	return 0;
}