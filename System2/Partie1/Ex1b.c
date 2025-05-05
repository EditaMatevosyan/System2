#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){
    int i = 1;
    long result = 1;
    if (argc == 1)
    {
        printf("%ld\n", result);
        return EXIT_SUCCESS;
    }
    while(i < argc){   
        char *suite;
        errno = 0;
        long valeur = strtol(argv[i],&suite,10);
        if (errno!=0 || *suite!='\0') {
            printf("Erreur de conversion\n");
            return EXIT_FAILURE;
        }
        result *= valeur;
        i++;
    }
    printf("Produit: %ld\n", result);
    return EXIT_SUCCESS;
}