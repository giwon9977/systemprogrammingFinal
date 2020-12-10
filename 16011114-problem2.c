#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int stop;

void handler(int signo) {
	// if signo equals to SIGINT
	if(signo == SIGINT)
		psignal(SIGINT, "Received signal:");
	// if signo equals to SIGTSTP
	if(signo == SIGTSTP)
		psignal(SIGTSTP, "Received signal:");
	// if signo equals to SIGQUIT
	if(signo == SIGQUIT) {
		psignal(SIGQUIT, "Received signal:");
		stop = 1;	// this means to stop while loop in main function
	}
}

int main() {
	int i = 0;
	struct sigaction act;

	act.sa_handler = handler;	// set sa_handler with handler
	act.sa_flags = 0;		// initialize sa_flags
	sigemptyset(&act.sa_mask);	// empty set sa_mask

	// Add handler for SIGINT.
	if(sigaction(SIGINT, &act, NULL) == -1) {
		perror("Error setting SIGINT handler");
		exit(EXIT_FAILURE);
	}
	// Add handler for SIGTSTP.
	if(sigaction(SIGTSTP, &act, NULL) == -1) {
		perror("Error setting SIGTSTP handler");
		exit(EXIT_FAILURE);
	}
	// Add handler for SIGQUIT.
	if(sigaction(SIGQUIT, &act, NULL) == -1) {
		perror("Error setting SIGQUIT handler");
		exit(EXIT_FAILURE);
	}


	// Loop
	while(!stop) {
		printf("Waiting for signal to be received! Count:%d\n", i);
		i++;
		sleep(1);
	}

	return 0;
}
