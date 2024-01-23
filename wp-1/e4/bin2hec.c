// Exercise 4

// Include section
#include<stdio.h>    
#include<stdlib.h>  
#include <string.h>
#include <ctype.h>


// Main function in the program

/*
* Purpose: This program turns a bunary value to a hexadecimal value.
* 
* Authors: Kaisa Arumeel, Alexander Säfström, Omid Khodaparast
*/


// Main function of the program
int main(int argc, char *argv[]) {

//Variable declarations
long int hexadecimal[2] = {0};      // Hexadecimal value
int i = 1;                          // Index of the loop
long binaryNumber = atol(argv[1]);  // Inputted binary number
int remainder;                      // Remainder of dividing the binary value by 10.

// Check if there is an argument provided.
if(argc != 2){
    // If not, show an error message and return error code.
    printf("Please provide a binary value to turn into a hexadecimal value.\n");
    return 2;
}

// Check that the binary value is valid.
if (atol(argv[1]) < 0 ) {
    // Print error message and return error code.
    printf("Error: invalid binary value.");
    return 2;
} 
// Check if user has types -h for help
else if(strcmp(argv[1], "-h") == 0) {
    // Give instructions on how to use the program and return error code as the calculation was not successful.
    printf("To run the program, you need to compile the code with the following command: 'gcc bin2hec.c -o bin2hec',");
    printf("\nand then run it using \n\n./bin2hec <binary value>. \n");
    return 2;
} 

// Loop through the input to check that it only has 0's and 1's
for (int i=0; i<strlen(argv[1]); i++) {
    if ((argv[1][i] - '0') > 1) {
        //If we find a value that is not a 1 or 0, show error message and return error code
        printf("Please provide a valid binary number.\n");
        return 2;
    }

}

// If the input is correct, continue.

// While the binary number is not 0, do the following:
while (binaryNumber != 0)
{
    // Get the remainder of dividing the binary number by ten through the % modulus operation
    remainder = binaryNumber % 10;

    // Multiply the obtained remainder with index i add it to the already existing hexadecimal value.
    hexadecimal[1] += remainder*i;

    // Multiply i by 2.
    i *= 2;

    // Divide the binary number by 10 and do the same steps until binarynumber becomes 0.
    binaryNumber = binaryNumber / 10;

}
    // Print the hexadecimal value in uppercase letters.
    printf("%lX\n",hexadecimal[1]);
    // Return success code.
    return 0;

}