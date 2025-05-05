#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat fileStat;

    if (stat(argv[1], &fileStat) == -1) {
        perror("stat");
        return 1;
    }

    printf("Inode : %ld\n", fileStat.st_ino);

    printf("Type de fichier : ");
    if (S_ISREG(fileStat.st_mode)) printf("Fichier regulier\n");
    else if (S_ISDIR(fileStat.st_mode)) printf("Repertoire\n");
    else if (S_ISLNK(fileStat.st_mode)) printf("Lien symbolique\n");
    else printf("Autre\n");

    printf("Id proprietaire : %d\n", fileStat.st_uid);
    printf("Taille : %ld octets\n", fileStat.st_size);

    char timebuf[80];
    struct tm *timeinfo = localtime(&fileStat.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%c", timeinfo);
    printf("Derniere modification : %s\n", timebuf);

    return 0;
}