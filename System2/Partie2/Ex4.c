#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int estPremier(long n) {
    if (n <= 1) return 0;
    
    for (long d = 2; d*d<=n; d++) {
        if (n%d==0) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]){
    if (argc == 1){
        printf("Bilan :\nNombres premiers : 0\nNombres non premiers : 0\nErreurs de conversion: 0\n");
        return 0;
    }
    for(int i = 1; i < argc; i++){
        pid_t pid = fork();
        char *suite;
        errno = 0;
        if (pid < 0){
            perror("fork failed!");
            exit(EXIT_FAILURE);
        }
        if (pid == 0){
            long valeur = strtol(argv[i], &suite, 10);
            if (errno!=0 || *suite!='\0') {
                printf("Enfant %d: Erreur de conversion\n", i);
                exit(2);
            }

            if (estPremier(valeur)){
                printf("Enfant %d: %lu est premier.\n", i, valeur);
                exit(0);
            }
            else{
                printf("Enfant %d: %lu n'est pas premier.\n", i, valeur);
                exit(1);
            }
        }
    }

    int num_of_prem = 0;
    int num_of_non_prem = 0;
    int num_of_err = 0;

    for(int i = 1; i < argc; i++){
        int status;
        wait(&status);
        if(WIFEXITED(status)){
            int res = WEXITSTATUS(status);
            if(res == 0)
                num_of_prem++;
            else if (res == 1)
                num_of_non_prem++;
            else if (res == 2)
                num_of_err++;
        }
    }

    printf("\nBillan : \n");
    printf("\tNombres premiers      : %d\n", num_of_prem);
    printf("\tNombres non premiers  : %d\n", num_of_non_prem);
    printf("\tErreurs de conversion : %d\n", num_of_err);
    return 0;
}