//Include section
#include <stdio.h>

//Define section
#define MIN_INTERVAL 1 // Minimum sentence id
#define MAX_INTERVAL 5 // Maximum sentence id

//Main program section

/**
* This program reads an integer between 1 and 5 and
* prints out one of 5 previously defined sentences.
* 
* Purpose: To showcase how conditionals are used in C.
* DIT632
* 
* Author: Kaisa Arumeel, Omid Khodaparast, Alexander Säfström
*
**/

int main(int argc, char* argv[]) {

    // Variable declarations

    // Array with pointers that point to the first char in the string.
    char* sentences[]={
        "1. Lorem ipsum dolor sit amet, adipiscing elit.",
        "2. Duis at luctus bob augue.",
        "3. Ut vehicula magna metus, nulla placerat eu.",
        "4. Etiam vulputate volutpat id maximus.",
        "5. In lorem lectus, vel, posuere et justo."}; 

    int selectedSentence; // Number to store the selected sentence
    
    // Program logic

    do {
        // Prompt the user to enter a number
        printf("Please enter a number from %d to %d.\n",MIN_INTERVAL,MAX_INTERVAL);

        // Read decimal input from stdin and store 
        // it at the memory address of selectedSentence
        scanf("%d",&selectedSentence);

        // Check if number is within interval before accessing array
        if(selectedSentence<=MAX_INTERVAL && selectedSentence>=MIN_INTERVAL){
            // Print the selected sentence to stdout.
            printf("%s\n",*(sentences+selectedSentence-1));
        }

        // We keep repeating this loop until the input
        // is outside of the interval.
    } while(selectedSentence<=MAX_INTERVAL && selectedSentence>=MIN_INTERVAL);

    // Exit gracefully
    return 0;
}