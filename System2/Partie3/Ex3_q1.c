#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <string>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    int len = strlen(argv[2]);
    for (int i = 0; i < len; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Enfant
            char buf[1024];
            int count = 0;
            ssize_t n;
            while ((n = read(fd, buf, sizeof(buf))) > 0) {
                for (ssize_t j = 0; j < n; j++) {
                    if (buf[j] == argv[2][i]) count++;
                }
            }
            printf("Enfant %d (caractère '%c') : %d occurrence(s)\n", i+1, argv[2][i], count);
            exit(0);
        }
    }

    // Parent
    for (int i = 0; i < len; i++) {
        wait(NULL);
    }
    close(fd);
    return 0;
}
