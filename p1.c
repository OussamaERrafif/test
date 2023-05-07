#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig) {
    static int count = 0;
    printf("Received signal SIGINT (%d)\n", ++count);
    if (count >= 5) {
        exit(0);
    }
}

int main() {
    pid_t pid;
    if ((pid = fork()) == 0) {
        // Child process (P2)
        signal(SIGINT, handle_sigint);
        printf("P2 is running with PID %d\n", getpid());
        while (1) {
            pause();
        }
    } else {
        // Parent process (PI)
        sleep(1);  // Give P2 time to initialize
        printf("P1 is running with PID %d\n", getpid());
        printf("Sending SIGINT to P2 (PID %d)\n", pid);
        kill(pid, SIGINT);
    }
    return 0;
}
