//Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define section
#define INITIAL_MEMORY_ALLOCATION 20 // Initial memory to allocate
#define BUFFER_READ 10 // How many chars to read from the buffer
#define MIN_CHAR 48 // The number 0 in the ASCII table
#define MAX_CHAR 57 // The number 9 in the ASCII table
#define BYTE_LENGTH 8 // The number of bits in a byte
#define BASE 10 // The defined input base 

int validateInput(int* argc,char*argv[],char* charInput,int* tempChar,size_t allocation,int *position); // Used to validate user input

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
    char* charInput = malloc(INITIAL_MEMORY_ALLOCATION); // Users char input
    long userInput; // Users input converted to long
    int position=0; // Cursor or position in the conversion result.
    int readStdinPosition=0; // Cursor or position for the standard input reading
    int inputOk; // Is input valid or not
    int bitsLeft; // Number of bits left in the byte.
    int conversionLength; // The resulting length of the conversion
    int tempChar; // ASCII code of the received input from stdin.

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
    userInput=validateInput(&argc,argv,charInput,&tempChar,allocation,&readStdinPosition);

    // If the input is valid we will not get a -1. 
    // If the input is invalid we return a 2
    if ( userInput==-1 ) { return 2; }

    // While the users input is not 0
    while (userInput!=0){
        // We check if one addition to the string literal
        // will overrun the allocated memory.
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

        // Perform bitwise operation AND on 
        // userInput and 1. Since 1's LSB is 1,
        // it will require userInput's LSB be to also
        // be 1.
        if(userInput & 1) {
            // Set the current position of result to 1
            result[position]='1';
        } else {
            // Set the current position of result to 0
            result[position]='0';
        }
        // Shift userInput one bit to the right.
        userInput=userInput>>1;
        // Increment position.
        position++;
    }

    // The length of the resulting binary string.
    conversionLength=strlen(result);

    // To ensure we add padding where needed,
    // we check how many slots in a slot of 8 are overflowing
    // by performing the modulus operation, and then subtracting
    // the result from 8, which tells us how many zeros we need
    // to prepend the result by.
    bitsLeft=8-(conversionLength%8);

    // Prepend the result for how many bits we need.
    for(int i=0;i<bitsLeft;i++){
        // Prepend with 0.
        printf("0");
    }
    // Since we worked with LSBs we start at the end of the string literal
    // to get the correct order of the bits.
    for(int i=(conversionLength-1);i>=0;i--){
        // Print the character.
        printf("%c",result[i]);
    }
    // Finalize the string by adding a newline.
    printf("\n");
    free(charInput);
    free(result);
}

int validateInput(int* argc,char*argv[],char* charInput,int* tempChar,size_t allocation,int*position){
    // If the number of arguments is less than 2
    if(*argc<2){
        // Since the user has not passed argument we attempt
        // to read from std input to conform to pipeline
        // requirements.
        while((*tempChar=fgetc(stdin))!='\n' && *tempChar!=EOF) {
            // If the addition of one char to the charInput overruns allocation
            // attempt to increase the allocation
            if(strlen(charInput)+1>allocation){
                // Increment the allocation by 2
                allocation*=2;
                // Update the charInputs allocation of memory.
                charInput=realloc(charInput,allocation);
                // If the allocation failed
                if(charInput==NULL) {
                    // Return error code to the main function.
                    return -1;
                }
            }
            // Set the char value of the charInput at current position.
            charInput[*position]=(char) *tempChar;
            // Increment position by 1.
            *position+=1;
        }
        // If we did not receive any input from stdin
        if(strlen(charInput)==0){
            // Print the error message.
        printf("Provide an argument, or use this program in combination with another program that outputs to stdout.\n");
            // Return error code since we do not have any input.
            return -1;
        }
    } else {
        // There is data on argv[1] so lets set the variable
        charInput=argv[1];
    }

    // Loop through the entire first argument,
    // char by char.
    for(int i=0;i<strlen(charInput);i++){
        // Cast the current char to its char code.
        int c=(int) charInput[i];
        // If the current char code is outside
        // of the valid bounds.
        if(c>MAX_CHAR||c<MIN_CHAR){
            // Print an error message.
            printf("Invalid input provided.\n");
            // Return a local status code.
            return -1;
        }
    }

    // Convert the argument to a long and return it
    // We have already performed validation so
    // We pass NULL to the end_ptr and set base 10.
    return strtol(charInput,NULL,BASE);

}

