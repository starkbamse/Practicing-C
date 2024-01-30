// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 1
// Exercise 2
// Submission code: 2024297 (provided by your TA-s)

//Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define section
#define INITIAL_MEMORY_ALLOCATION 1 // Initial memory allocation set to 1 byte
#define UPPER_START 65 // Start of the uppercase alphabet ASCII code
#define UPPER_END 90 // End of the uppercase alphabet ASCII code
#define LOWER_START 97 // Start of the lowercase alphabet ASCII code
#define LOWER_END 122 // End of the lowercase alphabet ASCII code
#define ALPHABET_LENGTH 26 // Length of the alphabet

// ------ Function declarations ----------

// Has the responsibility to shift and print the shifted characters
void shiftAndPrint(char* userInput,int shiftBy, int newChar);

// ------ Function declarations ----------

//Main program section

/**
* This program reads input from the user character by character
* until it reaches a newline or receives an EOF signal. Upon
* execution of the program the user shall provide a number
* which will shift entered text by that number. Finally,
* the fully shifted input is outputted to the user.
* 
* Purpose: To cipher data input by a custom length defined by the
* passed argument upon program execution.
* DIT632
* 
* 
**/

int main(int argc,char* argv[]){
    
    // Variable declarations
    size_t allocation = INITIAL_MEMORY_ALLOCATION; // Init alloc size of user input
    char* userInput = malloc(allocation); // Pointer to first char in string in heap
    int position; // Position of the next char in user's input
    int nextChar; // ASCII char code of the received input.
    int shiftBy; // N characters to shift letters with.
    int newChar; // Temp variable for new character

    // Program logic

    // If memory allocation failed we exit with error.
    if(userInput==NULL){
        exit(1);
    }

    // Run the loop until we get a \n.
    // Executed on every char received.
    while (nextChar != EOF) {
        // Reset position to 0
        position=0;
        //As long as the next character is not a newline and not EOF we enter.
        while((nextChar=fgetc(stdin)) != '\n' && nextChar != EOF) {
            // If the next addition overruns the allocated
            // memory, we must reallocate the memory.
            if (strlen(userInput)+1>allocation) {
                // Multibly allocation by itself by 2.
                allocation *= 2;
                // Reallocate the memory by twice of its previous size.
                userInput = realloc(userInput,allocation);
                
                // If memory allocation failed we exit with error.
                if(userInput==NULL){
                    exit(1);
                }
            } 

            // Using the address set the char
            *(userInput+position) = (char) nextChar;
            // Increment the position of the index that 
            // is used for accessing the user input.
            position++;
        }

        // Shift the characters and print them
        // Convert the received char* arg to an int
        // so that we can use it to access elements in an array.
        shiftAndPrint(userInput,atoi(*(argv+1)),newChar);

        // Clear the stored userInput
        memset(userInput,0,strlen(userInput));
    }
    
    // Free the occupied memory from heap
    free(userInput);

    // Exit gracefully
    return 0;
}

void shiftAndPrint(char* userInput,int shiftBy, int newChar){
    int alphabetStart; // Start of the alphabet
    int alphabetEnd; // End of the alphabet
    for(int i=0;i<strlen(userInput);i++){
        // Init new character by casting to int.
        newChar = (int)*(userInput+i);

        // If the current char is within the interval of
        // the uppercase alphabet
        if(newChar<=UPPER_END && newChar>=UPPER_START) {
            alphabetStart=UPPER_START;
            alphabetEnd=UPPER_END;
        // If the current char is within the interval of the
        // lowercase alphabet
        } else if(newChar>=LOWER_START && newChar<=LOWER_END) {
            alphabetStart=LOWER_START;
            alphabetEnd=LOWER_END;
        } else {
            // If no matching alphabet is found.
            break;
        }

        // Perform the shift
        newChar+=shiftBy;

        // If we are out of the boundary of the alphabet
        if(newChar>alphabetEnd){
            // Decrement the length of the alphabet
            // to "loop" back.
            newChar-=(ALPHABET_LENGTH);
        }

        // Print out the character by casting to char
        printf("%c",((char)newChar));
    }
    // Separate the line by adding a newline.
    printf("\n");
}