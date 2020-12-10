#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sighandler(int signo, siginfo_t *si) {
    // if the si_code equals to SI_QUEUE
    if(si->si_code == SI_QUEUE) {
        printf("si_pid: %d\n", si->si_pid);		// 16011114-send's pid
        printf("signo: %d\n",     si->si_signo);	// 16011114-send's signo
        printf("si_value.sival_int: %d\n",    si->si_value.sival_int);	// 16011114-send's data
    }
    // else if si_code not equals to SI_QUEUE
    else {
        printf("Not RTS %d\n", signo); 
    }

    sleep(2);
}

int main() {
    struct sigaction act;

    printf("16011114-receive's pid %d\n", getpid());

    sigemptyset(&act.sa_mask);		// empty signal set
    act.sa_flags     = SA_SIGINFO;	// set flags
    act.sa_restorer  = NULL; 		// set restorer to NULL
    act.sa_sigaction = sighandler; 	// set sigaction with sighandler

    // if SIGTSTP is received
    if (sigaction(SIGTSTP, &act, 0) == 1) {
        printf("signal error\n");
        exit(0);
    }

    // Loop
    while(1) {
        sleep(1);
    }

    return 0;
}
