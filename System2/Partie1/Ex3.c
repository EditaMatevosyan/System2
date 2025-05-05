#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return 1;    
    }
    int n = atoi(argv[1]);
    if (n < 0) {
        fprintf(stderr, "Enter a non-negative number: \n");
        return 1;
    }

    for (int i = n; i >= 0; i--) {
        printf("%d\n", i);
        sleep(1);
    }

}