#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid > 0) {
        // Parent process
        printf("Parent: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(1);
        wait(NULL); // Now parent waits for child
    } else {
        // Child process
        printf("Child: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(2);
        printf("Child after sleep: PID = %d, PPID = %d\n", getpid(), getppid());
    }

    return 0;
}
