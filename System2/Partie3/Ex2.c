#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "Invalid number of arguments.\n");
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1){
        perror("open");
        return 1;
    }
    char buf[1024];
    ssize_t bytes_read;
    int count = 0;
    while ((bytes_read = read(fd, buf, sizeof(buf))) > 0)
    {
        for (ssize_t i = 0; i < bytes_read; i++) {
            if(buf[i] == argv[2][0]) {
                count++;
            }
        }
    }
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return 1;
    }
    close(fd);
    printf("Caractère '%s' : %d occurrence(s)\n", argv[2], count);
    return 0;
}


