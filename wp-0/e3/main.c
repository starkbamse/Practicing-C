/*If the user provides no argument – the program should write an error message and information about
the parameter “-h”
• If the user provides more than one argument – the same as above
• If the user provides the first argument “-h” – the program should write the information how to use it*/

#include <stdio.h>
#include <string.h>
// Main function in the program, no program arguments supported
int main (int argc,  char *argv[]) {

if(argc != 2) {
    printf("Not a valid name, write .a/.out -h for help.\n");
    return 0;
}
if(strcmp(argv[1], "-h") == 0){
    printf("In order to use this program, write ./a.out <YourName>\n");
    return 0;
}
// Print a string to the console
printf("Hello World! – I’m %s!\n", argv[1]); 
return 0;
}