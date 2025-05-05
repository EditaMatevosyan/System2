#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Je suis exercice5_affiche_pids : PID = %d, PPID = %d\n", getpid(), getppid());
    return 0;
}
