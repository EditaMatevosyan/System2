#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int longueurPremiereLigne(int fd){
    int len = 0;
    char c;
    while(read(fd, &c, 1) == 1 && c != '\n')
        len++;
    lseek(fd, 0, SEEK_SET);
    return len;
}

int estFichierValide(int fd){
    int first_len = longueurPremiereLigne(fd);
    lseek(fd, 0, SEEK_SET);
    int len = 0;
    char c;
    while (read(fd, &c, 1) == 1) {
        if (c != 'v' && c != '>' && c != '\n') return 0;
        if (c == '\n') {
            if (len != first_len) return 0;
            len = 0;
        } else {
            len++;
        }
    }
    lseek(fd, 0, SEEK_SET);
    return 1;
}

int main(int argc, char *argv[]){
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (!estFichierValide(fd)) {
        fprintf(stderr, "Fichier invalide\n");
        close(fd);
        return 1;
    }

    int row = 0, col = 0;
    int width = longueurPremiereLigne(fd);
    int line_size = width + 1; // +1 for '\n'
    char c;

    while (1) {
        off_t offset = row * line_size + col;
        if (lseek(fd, offset, SEEK_SET) == -1) break;
        if (read(fd, &c, 1) != 1) break;

        printf("Position (%d,%d) : %c\n", row, col, c);

        if (c == 'v') {
            row++;
        } else if (c == '>') {
            col++;
        }

        // Exit conditions
        if (col >= width) {
            printf("Sortie à droite\n");
            break;
        }
        if (lseek(fd, row * line_size + col, SEEK_SET) == -1 ||
            read(fd, &c, 1) != 1) {
            printf("Sortie en bas\n");
            break;
        }
    }

    close(fd);
    return 0;
}