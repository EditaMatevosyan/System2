#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    if(argc == 1){
        printf("Bilan : 0 succès, 0 échecs\n");
        return 0;
    }
    for(int i = 1; i < argc; i++){
        pid_t pid = fork();
        if (pid < 0){
            perror("fork failed");
            EXIT_FAILURE;
        }
        if (pid == 0){
            int n = atoi(argv[i]);
            if(n != 0){
                float inverse = 1.0/n;
                printf("Enfant %d : 1/%d ~= %.4f\n", i, n, inverse);
                exit(EXIT_SUCCESS);
            }
            else{
                printf("Enfant %d : erreur pour \"%s\"\n", i, argv[i]);
                exit(EXIT_FAILURE);
            }
        }
    }
    int success_count = 0;
    int failure_count = 0;
    for(int i = 1; i < argc; i++){
        int status;
        wait(&status);    
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == EXIT_SUCCESS)
                success_count++;
            else
                failure_count++;
        }
    }
    printf("Bilan : %d succès, %d échecs\n", success_count, failure_count);
    return 0;
}