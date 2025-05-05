#include <stdio.h>
#include <stdlib.h>

#define MAX_CADRES 100
#define MAX_PAGES 100

// Déclarations
void afficherMemoire(int nbCadres, const int memoire[], const int horodatage[]) {
    printf("Mémoire : ");
    for (int i = 0; i < nbCadres; i++) {
        printf("%d(%d) ", memoire[i], horodatage[i]);
    }
    printf("\n");
}

int rechercherPage(int nbCadres, const int memoire[], int page) {
    for (int i = 0; i < nbCadres; i++) {
        if (memoire[i] == page)
            return i;
    }
    return -1;
}

int indexRemplacement(int nbCadres, const int memoire[], const int horodatage[]) {
    int indexMin = -1;
    int minDate = __INT_MAX__; // ou 9999999, un très grand nombre
    for (int i = 0; i < nbCadres; i++) {
        if (horodatage[i] < minDate) {
            minDate = horodatage[i];
            indexMin = i;
        }
    }
    return indexMin;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s nbCadres page1 page2 ...\n", argv[0]);
        return 1;
    }

    int nbCadres = atoi(argv[1]);
    int nbPages = argc - 2;

    int pages[MAX_PAGES];
    int memoire[MAX_CADRES];
    int horodatage[MAX_CADRES];

    for (int i = 0; i < nbPages; i++) {
        pages[i] = atoi(argv[i + 2]);
    }

    for (int i = 0; i < nbCadres; i++) {
        memoire[i] = -1;
        horodatage[i] = -1;
    }

    printf("------------------------------\n");
    for (int t = 0; t < nbPages; t++) {
        int page = pages[t];
        printf("Page demandée : %d\n", page);

        int index = rechercherPage(nbCadres, memoire, page);
        if (index != -1) {
            printf("Page présente\n");
            horodatage[index] = t;
        } else {
            printf("Défaut de page\n");
            int remplacement = -1;
            for (int i = 0; i < nbCadres; i++) {
                if (memoire[i] == -1) {
                    remplacement = i;
                    break;
                }
            }
            if (remplacement == -1) {
                remplacement = indexRemplacement(nbCadres, memoire, horodatage);
            }

            memoire[remplacement] = page;
            horodatage[remplacement] = t;
        }

        afficherMemoire(nbCadres, memoire, horodatage);
        printf("------------------------------\n");
    }

    return 0;
}
