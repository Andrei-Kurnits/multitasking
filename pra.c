#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>



int main()
{
	pid_t proc_a;
	pid_t proc_b;
	pid_t proc_c;
	
	proc_a = getpid();	// main program process is PROCESS A - parent
	
	printf("Process \"A\" ID is %d\n", (int)proc_a);

	proc_b = fork();			// copy parent process A
	
	if (proc_b) {				// if we are in parent process (process A)
		proc_c = fork();		// copy parent process A
		if (proc_c == 0) {		// if we are in child process C
			execv("./prc", 0);	// create child process C
			fprintf(stderr, "Error #%d occurred in execv()\n", errno);
			abort();
		}
	} else {
		execv("./prb", 0);	// create child process B
		fprintf(stderr, "Error #%d occurred in execv()\n", errno);
		abort();
	}
	
	
	return 0;
}