#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "Invalid number of arguments.\n");
        return 1;
    }
    
    int fd = open(argv[1], O_RDWR);
    if(fd == -1){
        perror("open");
        return 1;
    }
    char buf[1024];
    off_t offset;
    ssize_t bytes_read;
    int replaced;
    while((bytes_read = read(fd, buf, 1024)) > 0){
        for(ssize_t i = 0; i < bytes_read; i++){
            if(buf[i] == argv[2][0])
                buf[i] == argv[3][0];
                replaced++;
        }
        lseek(fd, offset, SEEK_SET);
        wrtie(fd, buf, bytes_read);
        offset += bytes_read;
    }
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    close(fd);
    printf("%d remplacement(s) '%c' -> '%c'\n", replaced, argv[2][0], argv[3][0]);
    return 0;
}