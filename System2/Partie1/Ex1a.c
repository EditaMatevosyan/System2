#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int i = 1;
    int result = 1;
    if(argc == 1){
        printf("%d\n", result);
        return 0;
    }
    while (i < argc){
        result *= atoi(argv[i]);
        i++;
    }
    printf("%d\n", result);
}