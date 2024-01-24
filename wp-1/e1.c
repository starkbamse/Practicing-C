//Include section
#include <stdio.h>

//Define section


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
        printf("Please enter a number from 1 to 5.\n");

        // Read decimal input from stdin and store 
        // it at the memory address of selectedSentence
        scanf("%d",&selectedSentence);

        // Check if number is within interval before accessing array
        if(selectedSentence<=5 && selectedSentence>=1){
            // Print the selected sentence to stdout.
            printf("%s\n",sentences[selectedSentence-1]);
        }

        // We keep repeating this loop until the input
        // is outside of the interval.
    } while(selectedSentence<=5 && selectedSentence>=1);

    // Exit gracefully
    return 0;
}