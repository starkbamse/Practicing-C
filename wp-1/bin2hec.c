//Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define section
#define INITIAL_MEMORY_ALLOCATION 5
#define MIN_CHAR 48 // The number 0 in the ASCII table
#define MAX_CHAR 49 // The number 1 in the ASCII table
#define BYTE_LENGTH 8 // The number of bits in a byte
#define BASE 10 // The defined input base 


int validateInput(int* argc,char*argv[]); // Used to validate user input

//Main program section

/**
* This program takes in a decimal number and outputs its
* binary representation, padded to always ensure that the
* output is made up of groups of 8 bits.
* 
* Purpose: To be able to convert decimal numbers to binary numbers
* very fast.
* DIT632
* 
* Author: Kaisa Arumeel, Omid Khodaparast, Alexander Säfström
* 
**/

int main(int argc, char* argv[]) {

    // Variable declarations
    size_t allocation=INITIAL_MEMORY_ALLOCATION; //Init alloc for conv. result
    char* result = malloc(INITIAL_MEMORY_ALLOCATION); // Alloc mem for conv. result
    char* userInput; // Users input converted to long
    int position=0; // Cursor or position in the conversion result.
    int inputOk; // Is input valid or not
    int bitsLeft; // Number of bits left in the byte.
    int inputLength; // The user input length
    
    // Program logic 

    // If result is NULL it means that we could not allocate memory.
    if(result==NULL) {
        // Print the error
        printf("Memory allocation failed.");
        // Exit with exit code 1 signalling that there was a problem.
        return 1;
    }

    // Call validate input function with arguments and length
    // of arguments.
    inputOk=validateInput(&argc,argv);

    // If the input is valid we will get a 1. 
    // If the input is invalid we return a 2
    if ( inputOk==1 ) { return 2; }

    // Convert the argument to a long
    // We have already performed validation so
    // We pass NULL to the end_ptr and set base 10.
    userInput=argv[1];

    // Setting input length to be the length of user input
    inputLength=strlen(userInput);

    // Loop through the entire input, increment by groups
    // of 4 or the length of a byte/.
    for(int i=0;i<inputLength;i+=BYTE_LENGTH/2){
        int number;
        for(int x=i;x<BYTE_LENGTH/2;x++){
            if(x<inputLength){
                if(userInput[x]=='1'){
                    number = number | 1;
                }
                if((x+1)<inputLength){
                    number=number << 1;
                }
            }
        }
        if((strlen(result)+1)>allocation){
            // Increase the allocation by 2.
            allocation*=2;
            // Attempt to reallocate memory.
            result=realloc(result,allocation);
        }
        // If result is null it means reallocation failed.
        if(result==NULL) {
            // Output error message.
            printf("Memory reallocation failed.");
            // Exit with exit code 2.
            return 2;
        }
        if(number<10){
            result[position]='0'+number;
        } else {
            result[position]=('F'-(15-number));
        }
        position++;
    }

    printf("%s",result);
    // Finalize the string by adding a newline.
    printf("\n");
}

int validateInput(int* argc,char*argv[]){
    // If the number of arguments is less than 2
    if(*argc<2){
        // Print the error message.
        printf("Provide an argument.\n");
        // Return a local status code.
        return 1;
    }

    // Loop through the entire first argument,
    // char by char.
    for(int i=0;i<strlen(argv[1]);i++){
        // Cast the current char to its char code.
        int c=(int) argv[1][i];
        // If the current char code is outside
        // of the valid bounds.
        if(c>MAX_CHAR||c<MIN_CHAR){
            // Print an error message.
            printf("Invalid input provided.\n");
            // Return a local status code.
            return 1;
        }
    }

    // Exit gracefully.
    return 0;
}

