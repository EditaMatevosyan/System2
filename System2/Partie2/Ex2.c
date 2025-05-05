#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Invalid number of arguments!\n");
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    printf("Parent [PID=%d]\n", getpid());
    pid_t pid = fork();
    if(pid < 0){
        perror("fork failed\n");
        return EXIT_FAILURE;
    }
    if(pid == 0){
        for (int i = n; i >= 0; i--){
            printf("Childe [PPID=%d] : %d\n", getppid(), i);
            sleep(1);  
        }
    }
    else
        wait(NULL);

    return EXIT_SUCCESS;

}