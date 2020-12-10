#include <signal.h>
#include <stdio.h>

int main(int argc, char **argv) {
        union sigval sval;
	
	// Show Usage
        if(argc != 3) {
              printf("Usage: %s <process id> <student_id>\n", argv[0]);
              return 1;
        }

	sval.sival_int = atoi(argv[2]);		// input student id with int type
	sigqueue(atoi(argv[1]), SIGTSTP, sval);	// send data with SIGTSTP in Real Time Signal

	return 0;
}
