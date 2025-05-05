#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

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

    struct stat st;
    fstat(fd, &st);
    off_t filesize = st.st_size;

    int len = strlen(argv[2]);
    for (int i = 0; i < len; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Enfant
            char buf[1024];
            int count = 0;
            off_t offset = 0;

            while (offset < filesize) {
                ssize_t n = pread(fd, buf, sizeof(buf), offset);
                if (n <= 0) break;
                for (ssize_t j = 0; j < n; j++) {
                    if (buf[j] == argv[2][i]) 
                        count++;
                }
                offset += n;
            }

            printf("Enfant %d (caractère '%c') : %d occurrence(s)\n", i+1, argv[2][i], count);
            exit(0);
        }
    }

    for (int i = 0; i < len; i++) {
        wait(NULL);
    }

    close(fd);
    return 0;
}