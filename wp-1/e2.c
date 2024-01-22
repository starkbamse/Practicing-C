// Exercise 2

// Include section
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 

// Main function in the program

/*
* Purpose: This is an encryption program that “shifts characters” in the ASCII-code table of a given
* input string. The user inputs the number of characters to shift as well as the input text.
* The program outputs the encrypted text.
*
* Authors: Kaisa Arumeel, Alexander Säfström, Omid Khodaparast
*/

// The main function
int main(int argc, char *argv[]) {

    // Variable declarations
    int shift,  // Number of characters to shift
    i,          // Index of the loop
    ascii,      // Ascii value of the current character
    result;     // Ascii value of the encrypted character
    char insertedText[50];  // User inputted text

    // Check for the provided argument to shift characters.
    if (argc != 2){
       printf("Please enter the number of characters you wish to shift. \n");
       return 0;
    }

    // Convert the provided argument into an integer.
    shift = atoi(argv[1]);

    do {
    
    // Ask the user to type a text and save the input.
    printf("\nType a text to encrypt: ");
    scanf("%s", insertedText);

    // Loop through each character in the inputted text.
    for (i = 0; i < strlen(insertedText); i++) {
    // Save the ascii value of the current character as an integer.
    ascii = (int)insertedText[i];
    // Get the encrypted character ascii value by adding the shift number.
    result = ascii + shift;
    // Check if the current character is lower-case letter.
    if(islower(insertedText[i])){ 
        // Check if the encrypted character is more than 122, so the lower-case z in ASCII table
        if(result > 122) {
            // Then substract 26, so the encrypted character would stay lower-case and go back a round in the alphabet.
            result = result - 26; 
        } 
    } 
    // Check if the current character is upper-case letter.
    if (isupper(insertedText[i])) {
    // Check if the encrypted character is more than 90, so the upper-case Z in ASCII table
        if(result > 90) { 
            // Then substract 26, so the encrypted character would stay upper-case and go back a round in the alphabet.
            result = result - 26; 
        } 
    } 
    // Show the encrypted letter to the user
    printf("%c", result);
    }
    
    // Do this as long as the EOF character is detected.
    // feof() method finds EOF characters and stdin means in the standard input.
    }  while (!feof(stdin));
    
}