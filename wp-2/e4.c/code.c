// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 2
// Exercise 4.1
// Submission code: 


/**
* This program packs bits into a byte. It takes in 5 arguments and outputs a hexadecimal value.
*
* Purpose: Bit packing.
* DIT632
* 
* 
**/


// Include section
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definitions
#define ZERO 48 // 0 in the Ascii table
#define ONE 49 // 1 in the Ascii table
#define TWO 50 // 2 in the Ascii table
#define FOUR 52 // 4 in the Ascii table

// Main function of the program
int main(int argc,char* argv[]){
    
    unsigned char byte = 0; // Declare a byte and set it to 0.

    // Check that there are exactly 5 arguments procided.
    if (argc != 6)
    {
    // If not, print error message and return.
       printf("You have to input five arguments.");
       return 1;
    }
    
    // Check that the first argument is either 0 or 1.
    if (((argv[1])[0] != ZERO && (argv[1])[0] != ONE)) {
        // If not, print error message and exit the program.
        printf("Invalid first input. The first argument has to be either 0 or 1.\n");
        return 1;
    } 
    // If the first argument is valid, then shift the bit to the left by 7 positions
    // Because the first argument will only take 1 bit in the byte (the left most).
    else { 
        // Add it to the byte.
        byte += atoi(argv[1]) << 7;
    }

    // Check that the second argument is between 0 and 4.
    if (((argv[2])[0] < ZERO || (argv[2])[0] > FOUR)) {
        // If not, print error message and exit the program.
        printf("Invalid second input. The second argument has to be between 0 and 4 (included).\n");
        return 1;
    } 
    // If the argument is valid, then shift the bit to the left by 4 positions
    // Because the second argument will take 3 bits in the byte. The leftmost bit is
    // taken by the first argument, so the second argument is bits 2-4.
    else { 
        // Add it to the current byte.
        byte += atoi(argv[2]) << 4;
    }

    // Check that the third argument is between 0 and 2.
    if (((argv[3])[0] < ZERO || (argv[3])[0] > TWO)) {
        // If not, print error message and exit the program.
        printf("Invalid third input. The third argument has to be between 0 and 2 (included).\n");
        return 1;
    } 
    // If the argument is valid, then shift the bit to the left by 2 positions
    // Because the third argument will take 2 bits in the byte. The leftmost bit is
    // taken by the first argument, bits 2-4 taken by the second argument.
    // The third argument will take bits 5-6 in the byte.
    else { 
        // Add it to the current byte.
        byte += atoi(argv[3]) << 2;
    }
    // Check that the fourth argument is either 0 or 1.
    if (((argv[4])[0] != ZERO && (argv[4])[0] != ONE)) {
        // If not, print error message and exit the program.
        printf("Invalid fourth input. The fourth argument has to be between 0 and 1 (included).\n");
        return 1;
    } 
    // If the argument is valid, then shift the bit to the left by 1 position
    // Because the third argument will take 1 bit in the byte. The leftmost bit is
    // taken by the first argument, bits 2-4 taken by the second argument, 5-6 by the third argument.
    // The fourth argument will take bit number 7.
    else { 
        // Add it to the current byte.
         byte += atoi(argv[4]) << 1;
    }

     // Check that the fifth argument is either 0 or 1.
    if (((argv[5])[0] != ZERO && (argv[5])[0] != ONE)) {
        // If not, print error message and exit the program.
        printf("Invalid fifth input. The fifth argument has to be between 0 and 1 (included).\n");
        return 1;
    } 
    // If the argument is valid, then add it to the byte since it will occupy one bit in the byte
    // and there is no need to shift because the only empty bit is the last one.
    else { 
        byte += atoi(argv[5]);
        // Print the byte as a hexadecimal.
        printf("%02X\n", byte);

    }

// Return success code.
return 0;
}