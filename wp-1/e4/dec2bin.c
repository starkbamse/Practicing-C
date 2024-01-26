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

// ------ Function declarations ----------

// Used to validate user input
int validateInput(int* argc,char*argv[],char* input,size_t allocation,int position); 
// To ensure memory has been allocated.
int assertMemoryAllocated(char* ptr); 
 // To check if we are running out of memory and need to reallocate.
int checkAndReallocateMemory(char* ptr, size_t*allocation);

// ------ Function declarations ----------


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
    char* result = malloc(INITIAL_MEMORY_ALLOCATION); // Alloc mem for conv. result and char input
    long userInput; // Users input converted to long
    int position=0; // Cursor or position used for traversing a string.
    int bitsLeft; // Number of bits left in the byte.
    int conversionLength; // The resulting length of the converted binary value

    // Program logic 

    // If the memory allocation failed, exit with code 2.
    if(assertMemoryAllocated(result)==0){
        return 2;
    }

    // Call validate input function with arguments and length
    // of arguments.
    userInput=validateInput(&argc,argv,result,allocation,position);
    
    // Clear the result string
    memset(result,0,strlen(result));

    // If the input is valid we will not get a -1. 
    // If the input is invalid we return a 2
    if ( userInput==-1 ) { return 2; }

    // While the users input is not 0
    while (userInput!=0){
        
        // Check and reallocate memory if needed.
        if(checkAndReallocateMemory(result,&allocation)==0){
            return 2;
        }

        // Perform bitwise operation AND on 
        // userInput and 1. Since 1's LSB is 1,
        // it will require userInput's LSB be to also
        // be 1.
        if(userInput & 1) {
            // Set the current position of result to 1
            *(result+position)='1';
        } else {
            // Set the current position of result to 0
            *(result+position)='0';
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
        printf("%c",*(result+i));
    }
    // Finalize the string by adding a newline.
    printf("\n");
    free(result);
}

int validateInput(int* argc,char*argv[],char* input,size_t allocation,int position){
    int c; // Used to store the current char from stdin.
    
    // If the number of arguments is less than 2
    if(*argc<2){
        // Since the user has not passed argument we attempt
        // to read from std input to conform to pipeline
        // requirements.
        while((c=fgetc(stdin))!='\n' && c!=EOF) {

            // Check and reallocate memory if needed.
            if(checkAndReallocateMemory(input,&allocation)==0){
                return -1;
            }

            // Set the char value of the charInput at current position.
            *(input+position)=(char) c;
            // Increment position by 1.
            position+=1;
        }
        // If we did not receive any input from stdin
        if(strlen(input)==0){
            // Print the error message.
            printf("Provide an argument, or use this "\
            "program in combination with another program that outputs to stdout.\n");
            // Return error code since we do not have any input.
            return -1;
        }
    } else {
        if(strcmp("-h",*(argv+1))==0){
            printf("This program converts decimal numbers to binary numbers.\n"\
            "Usage: ./a.out <decimal number>\nYou can also use this program in"\
            "combination with bin2hec: ./dec2bin 12 | ./bin2hec\n");
            return -1;
        } else {
            // There is data on argv[1] so lets set the variable
            input=*(argv+1);
        }

    }

    // Loop through the entire first argument,
    // char by char.
    for(int i=0;i<strlen(input);i++){
        // Cast the current char to its char code.
        int c=(int) *(input+i);
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
    return strtol(input,NULL,BASE);

}

int assertMemoryAllocated(char* ptr){
    // If result is null it means reallocation failed.
    if(ptr==NULL){
        // Return status code 0 (false)
        return 0;
    }
    // Return status code 1 (true)
    return 1;
}

int checkAndReallocateMemory(char* ptr, size_t *allocation){
    // If the increase by 1 in the string size overruns allocation
    if(strlen(ptr)+1>*allocation){
        // Increment the allocation by 2
        *allocation*=2;
        // Update the charInputs allocation of memory.
        ptr=realloc(ptr,*allocation);
        // If the allocation failed
        return assertMemoryAllocated(ptr);
    }
    return 1;
}