//Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define section
#define INITIAL_MEMORY_ALLOCATION 5 // Initial memory allocation for the binary representation.
#define MIN_CHAR_INTERVAL 48 // The number 0 in the ASCII table
#define MAX_CHAR_INTERVAL 57 // The number 9 in the ASCII table
//Main program section

/**
* This program expects a decimal number, from which it will 
* calculate its binary representation through the usage
* of the AND operator and inspecting the LSB (least significant
* bit). In the meantime it also counts the number of zeros and ones.  
*
* Purpose: To see the binary representation of any number, as 
* well as the numbers of zeros and ones.
* DIT632
* 
* Author: Alexander Säfström, 2024
* 
**/

int main(int argc,char* argv[]){

    // Variable declarations
    int number; // The number that user wants to inspect
    int zero=0; // stores the count of 0s
    int one=0; // stores the count of 1s
    size_t allocation = INITIAL_MEMORY_ALLOCATION; // Init alloc of bin. rep.
    char* bRep=malloc(INITIAL_MEMORY_ALLOCATION); // Alloc mem for bin. rep.
    int position=0; // Current position in bin. rep.
    
    // Program logic

    // If memory allocation failed we exit with an exit code.
    if(bRep==NULL){
        // Print the error
        printf("Memory allocation failed!\n");
        // Return exit code 1 (fault)
        return 1;
    }
    
    // If the user did not provide an argument, we output error.
    if(argc<2){
        // Print the error
        printf("Error: No number provided. Please provide a number as a command line argument.\n");
        // Return exit code 0
        return 0;
    }

    // Validate the input by going over every char
    for(int i=0;i<strlen(argv[1]);i++){
        // Cast the current char to a int to get the 
        // char code.
        int c=(int) argv[1][i];
        
        // If the char is outside of allowed interval
        if(c>MAX_CHAR_INTERVAL || c<MIN_CHAR_INTERVAL){
            // Print the error message.
            printf("Error: Invalid number.\n");
            // Exit the program with exit code 0.
            return 0;
        }
    }

    // Convert the string literal argument to an integer.
    number=atoi(argv[1]);

    // Print the decimal representation
    printf("Number: %d\n",number);
    // Print the binary prefix
    printf("Binary: 0b");

    // This for loop will run until we have reached 0
    // at this point we will have checked all the LSBs
    while(number!=0){
        // If addition of 1 character will overrun current alloc.
        if((strlen(bRep)+1)>allocation){
            // Increment allocation size by 2.
            allocation*=2;
            // Try to request more memory.
            bRep=realloc(bRep,allocation);
            // If memory allocation failed we exit with an exit code.
            if(bRep==NULL){
                // Print the error message.
                printf("Memory allocation failed!");
                // Exit the program with exit code 1.
                return 1;
            }
        }
        // Perform AND operator between 
        // number and 1 which in binary will be 1
        // therefore the number's LSB has to be 1
        if(number & 1) {
            // If the LSB is 1 we increment n ones
            one++;
            // Set a 1 in the binary representation
            bRep[position]='1';
        } else {
            // If the LSB is not 1 we increment n zeros
            zero++;
            // Set a 0 in the binary representation
            bRep[position]='0';
        }
        // Shift the number to the right to update the LSB.
        number=number>>1;
        // Increase the position (cursor) in the binary rep. string literal.
        position++;
    }

    // Print the binary representation starting from the
    // end of the string literal since we have been
    // working with LSBs.
    for(int i=(strlen(bRep)-1);i>=0;i--){
        // Print the character.
        printf("%c",bRep[i]);
    }

    // Print the number of zeros
    printf("\nNumber of 0s: %d\n",zero);

    // Print the number of ones
    printf("Number of 1s: %d\n",one);

    // Free the occupied memory.
    free(bRep);

    // Exit the program gracefully
    return 0;
}