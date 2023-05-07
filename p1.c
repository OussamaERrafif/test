#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int nb_SigInt_recus = 0;

void handler_SIGINT(int sig) {
    printf("Processus P2 a reçu un signal SIGINT.\n");
    nb_SigInt_recus++;
    if (nb_SigInt_recus >= 5) {
        printf("Processus P2 a reçu %d signaux SIGINT et s'arrête.\n", nb_SigInt_recus);
        exit(0);
    }
}

int main() {
    int nb_SigInt = 5;
    int pid_P2 = getpid();
    
    signal(SIGINT, handler_SIGINT);
    
    printf("Processus P2 est en cours d'exécution avec pid %d.\n", pid_P2);
    
    printf("Processus P1 envoie un signal SIGINT à P2.\n");
    kill(pid_P2, SIGINT);
    
    printf("Processus P1 envoie %d autres signaux SIGINT à P2.\n", nb_SigInt-1);
    for (int i = 0; i < nb_SigInt-1; i++) {
        sleep(1);
        kill(pid_P2, SIGINT);
    }
    
    printf("Processus P1 a terminé.\n");
    
    return 0;
}
