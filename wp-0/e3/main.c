#include <stdio.h>

void main(int argc, char *argv[]) {
    if(argv[1]=="-h") {
        printf("Use the -h argument to display this message.\n");
        return;
    }
    printf("Error: expected -h argument. Use the -h argument.");
    return;
}