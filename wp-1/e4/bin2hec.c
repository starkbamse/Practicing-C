// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 1
// Exercise 4.2
// Submission code: 2024297 (provided by your TA-s)

//Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define section
#define INITIAL_MEMORY_ALLOCATION 5 // Initial memory allocation for the strings
#define MIN_CHAR 48 // The number 0 in the ASCII table
#define MAX_CHAR 49 // The number 1 in the ASCII table
#define BYTE_LENGTH 8 // The number of bits in a byte
#define BASE 10 // The defined input base 

// ------ Function declarations ----------

// To validate user input
int validateInput(int* argc,char*argv[],char** userInput,size_t allocation,int position,int*c); 
 // To ensure memory has been allocated.
int assertMemoryAllocated(char* ptr);
// To check if we are running out of memory and need to reallocate.
int checkAndReallocateMemory(char* ptr, size_t*allocation); 

// ------ Function declarations ----------

//Main program section

/**
* This program takes in a binary number and outputs its
* hexadecimal representation.
* 
* Purpose: To be able to convert binary numbers to hexadecimal numbers
* very fast.
* DIT632
* 
* 
**/

int main(int argc, char* argv[]) {

    // Variable declarations
    size_t allocation=INITIAL_MEMORY_ALLOCATION; //Init alloc for conv. result
    char* result = malloc(INITIAL_MEMORY_ALLOCATION); // Alloc mem for conv. result
    char* userInput = malloc(INITIAL_MEMORY_ALLOCATION); // Users input converted to long
    int position=0; // Cursor or position in the conversion result.
    int bitsLeft; // Number of bits left in the byte.
    int inputLength; // The user input length
    int tempNumber; // Used to hold an int representation of 4-bit binary group.
    int c; // Used to store the current char from stdin.


    // Program logic 

    // If result is NULL it means that we could not allocate memory.
    if(assertMemoryAllocated(result)==0){
        // Exit with exit code 2.
        return 2;
    }

    // Call validate input function with arguments and length
    // of arguments.
    if(validateInput(&argc,argv,&userInput,allocation,position,&c)==0){
        // Exit with exit code 2.
        return 2;
    }
    // Clear the result string
    memset(result,0,strlen(result));

    // Setting input length to be the length of user input
    inputLength=strlen(userInput);

    // Loop through the entire input, increment by groups
    // of 4 or the length of a byte/2.
    // Note: A hex number represents 4 bits.
    for(int i=0;i<inputLength;i+=(BYTE_LENGTH/2)){
        tempNumber=0; // Set number to 0.
        // We also need to look at each character 
        // within the group
        for(int x=0;x<(BYTE_LENGTH/2);x++){
            // Since we have entered this part of the loop,
            // we must shift the bits to make space for the new bit.
            tempNumber = tempNumber << 1;
            // If the current char in the group is a 1
            // We do i+x because i is the group and
            // x is the position within the group.
            if(*(userInput+i+x)=='1'){
                // Perform OR operation on the number.
                // This will set LSB to 1 if it is not already
                // Similar to false | true which will evaluate to true
                tempNumber = tempNumber | 1;
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
        if(assertMemoryAllocated(result)==0) {
            // Exit with exit code 2.
            return 2;
        }
        // If the resulting integer is less than 10
        if(tempNumber<10){
            // Since hex and dec are equal up to the number 10
            // we can just take the char 0 and increment the
            // number to the char to get the wanted char.
            *(result+position)='0'+tempNumber;
        } else {
            // If its bigger or equal to 10
            // we can subtract 15-the number to get the
            // number of chars that we need to subtract
            // from the maximum hex number which is F.
            *(result+position)=('F'-(15-tempNumber));
        }
        // Increment the position in the resulting string.
        position++;
    }
    // Print the result.
    printf("%s\n",result);
    free(result); // Free occupied heap memory.
    // If the user did not provide an argument
    if(argc<2){
        free(userInput); // Free occupied heap memory.
    }
    return 0; // Exit gracefully
}

int validateInput(int* argc,char*argv[],char** userInput, size_t allocation,int position,int*c){
    // If the number of arguments is less than 2
    if(*argc<2){
        // Since the user has not passed argument we attempt
        // to read from std input to conform to pipeline
        // requirements.
        while((*c=fgetc(stdin))!='\n' && *c!=EOF) {
            // Check and reallocate memory if needed.
            if(checkAndReallocateMemory(*userInput,&allocation)==0){
                // Return error code since allocation failed.
                return 0;
            }
            // Set the char value of the charInput at current position.
            *((*userInput)+position)=(char) *c;
            // Increment position by 1.
            position+=1;
        }
        // If we did not receive any input from stdin
        if(strlen(*userInput)==0){
            // Print the error message.
            printf("Provide an argument, or use this "\
            "program in combination with another program that outputs to stdout.\n");
            // Return error code since we do not have any input.
            return 0;
        }
    } else {
        // If -h argument is provided
        if(strcmp("-h",*(argv+1))==0){
            // Print help message
            printf("This program converts binary numbers to hexadecimal numbers."\
            "\nUsage: ./a.out <binary_number>\nYou can also use this program in"\
            "combination with dec2bin: ./dec2bin 12 | ./bin2hec\n");
            // Return error code to break execution.
            return 0;
        } else {
            // Since userInput previously had memory allocated, we
            // need to free this to prevent a memory leak.
            free(*userInput);
            // There is data on argv[1] so lets set the variable
            *userInput=*(argv+1);
        }
    }

    // Loop through the entire first argument,
    // char by char.
    for(int i=0;i<strlen(*userInput);i++){
        // Cast the current char to its char code, 
        // but make sure to dereference first.
        *c=(int) *((*userInput)+i);
        // If the current char code is outside
        // of the valid bounds.
        if(*c>MAX_CHAR||*c<MIN_CHAR){
            // Print an error message.
            printf("Invalid input provided.\n");
            // Return a local status code.
            return 0;
        }
    }
    // Return success status code.
    return 1;
}

int assertMemoryAllocated(char* ptr){
    // If result is null it means reallocation failed.
    if(ptr==NULL){
        // Output error message.
        printf("Memory reallocation failed.");
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
        // If the allocation failed it will return an error.
        return assertMemoryAllocated(ptr);
    }
    // Return success status code.
    return 1;
}
