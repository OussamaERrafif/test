#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sigint(int sig) {
    static int count = 0;
    if (sig == SIGINT) {
        printf("Received SIGINT signal %d\n", ++count);
        if (count == 5) {
            exit(0);
        }
    }
}

int main() {
    int pid;
    signal(SIGINT, handle_sigint);
    if ((pid = fork()) == 0) {
        printf("Child process P2 with pid %d is running\n", getpid());
        while (1) {
            // do nothing
        }
    } else {
        printf("Parent process P1 with pid %d is running\n", getpid());
        sleep(1);
        printf("Sending SIGINT signal to P2\n");
        kill(pid, SIGINT);
        while (1) {
            // do nothing
        }
    }
    return 0;
}
