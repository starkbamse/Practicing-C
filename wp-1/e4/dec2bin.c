// Exercise 4

// Include section
#include<stdio.h>    
#include<stdlib.h>  
#include <string.h>
#include <ctype.h>
#include <limits.h>


// Main function in the program

/*
* Purpose: This program turns a decimal number into binary number.
* 
* Authors: Kaisa Arumeel, Alexander Säfström, Omid Khodaparast
*/

// This method checks if the argument provided is a decimal number.
int isDecimalNumber(const char *input) {
    int i; // Index of the loop
    // Loop through each charachter in the input
    for (i = 0; input[i] != '\0'; i++) {
        // Check if the character is a digit
        if (!isdigit(input[i])) {
            // If not, return 0
            return 0;
        }
    }
    // If each character is a digit, then the argument is a decimal number.
    return 1;
}


// Main function of the program
int main(int argc, char *argv[]) {

// Variable declarations
long decimalNumber,     // Inputted number by the user
i,                      // Index of the loop
binaryArray[64] = {0};  // Array to store the binary number
long max = LONG_MAX;    // Maximum long in c

// Convert the inserted decimal number into a long.
decimalNumber = atol(argv[1]);

// Check if there is an argument provided.
if(argc != 2){
    // If not, show an error message and return error code.
    printf("Please provide a decimal to turn into binary.\n");
    return 2;
}

// Check that the inputted number is not negative nor bigger than the maximum long.
if (decimalNumber < 0 || decimalNumber >= max ) {
    // Print error message and return error code.
    printf("Please provide a number between 0 and %ld\n", max);
    return 2;
} 
// Check if user has types -h for help
else if(strcmp(argv[1], "-h") == 0) {
    // Give instructions on how to use the program and return error code as the calculation was not successful.
    printf("To run the program, you need to compile the code with the following command: 'gcc dec2bin.c -o dec2bin',");
    printf("\nand then run it using \n\n./dec2bin <decimal you want to convert to binary>. \n");
    return 2;
} 
// Check that the input is a number.
else if (isDecimalNumber(argv[1]) == 0) {
    // If not, print an error message and return error code.
    printf("Please provide a valid decimal number. \n");
    return 2;
} 

// If the input is correct, continue.

// For loop to get the binary representation of the decimal number
    for (i = 0; decimalNumber > 0; i++)    {    
        // Store the remainder of decimal number divided by 2 (through a % modulus operation) in the binary array.
        binaryArray[i] = decimalNumber % 2;    
        // Divide the decimal number by two.
        decimalNumber = decimalNumber/2;    
    } 

    // Check if the inputted number is 256 or greater (that is when the 16 bit numbers start).
    if (atoi(argv[1]) >= 256) { 
        // Then print all 16 bits of the binary number.     
        for(int i = 15; i >= 0; i--)    {    
            printf("%ld", binaryArray[i]); 
        } 
    } 
        // Check if the inputted number is 65535 or greater (that is when the 32 bit numbers start).
    if (atoi(argv[1]) >= 65536) { 
        // Then print all 32 bits of the binary number.     
        for(int i = 31; i >= 0; i--)    {    
            printf("%ld", binaryArray[i]); 
        } 
    } 
     // Check if the inputted number is 65535 or greater (that is when the 64 bit numbers start).
    if (atol(argv[1]) >= 4294967296) { 
        // Then print all 64 bits of the binary number.     
        for(int i = 63; i >= 0; i--)    {    
            printf("%ld", binaryArray[i]); 
        } 
    } 

    // If the inputted number is less that 256, then it is 8 bit.
    else { 
        // Print only the last 8 bits of the array.
        for(i = 7; i >= 0; i--) { 
            printf("%ld", binaryArray[i]); 
        }
    }
    // New line and return success code.
    printf("\n");
    return 0;

}