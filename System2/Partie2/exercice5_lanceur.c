#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Je suis exercice5_lanceur : PID = %d, PPID = %d\n", getpid(), getppid());

    char *args[] = {"./exercice5_affiche_pids", NULL};
    execve("./exercice5_affiche_pids", args, NULL);

    perror("execve a échoué");
    return 1;
}
