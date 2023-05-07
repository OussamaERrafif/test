#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handle_sigint(int sig) {
    static int count = 0;
    count++;
    
    if (count >= 5) {
        printf("J'ai reçu %d signaux SIGINT. Je m'arrête maintenant...\n", count);
        exit(0);
    }
    else {
        printf("J'ai reçu le signal SIGINT numéro %d. J'attends la prochaine...\n", count);
    }
}

int main() {
    int pid;
    
    // Créer un nouveau processus P2
    if ((pid = fork()) == 0) {
        signal(SIGINT, handle_sigint);
    }
    else {
        // Attendre 2 secondes pour s'assurer que P2 a commencé à s'exécuter
        sleep(2);
        printf("Je suis P1, mon PID est %d, j'envoie le signal SIGINT à P2 (PID = %d)...\n", getpid(), pid);
        
        // Envoyer le signal SIGINT à P2
        kill(pid, SIGINT);
    }
    
    return 0;
}
