#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(){
    pid_t pid = fork();
    if(pid < 0){
        perror("fork failed");
        return 1;
    }

    if (pid > 0) {
        // Parent process
        printf("Parent: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(1);
        // exits without waiting for child
        exit(0);
    } else {
        // Child process
        printf("Child: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(2);
        printf("Child after sleep: PID = %d, PPID = %d\n", getpid(), getppid());
    }

    return 0;
}