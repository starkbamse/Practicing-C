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
    int tempNumber;

    // Program logic 

    // If result is NULL it means that we could not allocate memory.
    if(result==NULL) {
        // Print the error
        printf("Memory allocation failed.");
        // Exit with exit code 1 signalling that there was a problem.
        return 2;
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
    // of 4 or the length of a byte/2.
    for(int i=0;i<inputLength;i+=(BYTE_LENGTH/2)){
        tempNumber=0;
        // We also need to look at each character 
        // within the group
        for(int x=0;x<(BYTE_LENGTH/2);x++){
            // If x+i (entire pos.) is still smaller than the length of the input.
            if( (x+i) < inputLength){
                // Since we have entered this part of the loop,
                // we must shift the bits to make space for the new bit.
                tempNumber = tempNumber << 1;
                // If the current char in the group is a 1
                // We do i+x because i is the group and
                // x is the position within the group.
                if(userInput[i+x]=='1'){
                    // Perform OR operation on the number.
                    // This will set LSB to 1 if it is not already
                    // Similar to false | true which will evaluate to true
                    tempNumber = tempNumber | 1;
                }
    
            } else {
                // If we cannot access any more data, we can exit loop.
                break;
            }

        }
        // If increasing the length of result will overrun the allocated memory.
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
        // If the resulting integer is less than 10
        if(tempNumber<10){
            // Since hex and dec are equal up to the number 10
            // we can just take the char 0 and increment the
            // number to the char to get the wanted char.
            result[position]='0'+tempNumber;
        } else {
            // If its bigger or equal to 10
            // we can subtract 15-the number to get the
            // number of chars that we need to subtract
            // from the maximum hex number which is F.
            result[position]=('F'-(15-tempNumber));
        }
        // Increment the position in the resulting string literal.
        position++;
    }
    // Print the result.
    printf("%s\n",result);
    free(result);

    return 0;
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

    // Return local status code.
    return 0;
}

