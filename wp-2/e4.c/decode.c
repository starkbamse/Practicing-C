// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 2
// Exercise 4.2
// Submission code: 


/**
* This program unpacks a hexadecimal value into bits.
*
* Purpose: Bit unpacking.
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
#define NINE 57 // 9 in the Ascii table
#define A 65 // A in the Ascii table
#define F 70 // F in the Ascii table

// Main function of the program
int main(int argc,char* argv[]){
    
    unsigned char byte = 0; // Declare a byte and set it to 0.

    // Check that there is exactly 1 argument provided
    if (argc != 2)
    {
    // If not, print error message and return.
       printf("Please input a hexadecimal value as an argument.");
       return 1;
    }

    // Check that the argument provided has 2 characters.
    if (strlen(argv[1]) != 2) {
    // If not, print error message and return.
        printf("Error: Please enter a 2-digit hexadecimal value.\n");
        return 1;
    }

    
    // Check that both of the characters are either between 0-9 or A-F. 
    if ((!((argv[1])[0] >= ZERO && (argv[1])[0] <= NINE) && !((argv[1])[0] >= A && (argv[1])[0] <= F)) 
    || (!((argv[1])[1] >= ZERO && (argv[1])[1] <= NINE) && !((argv[1])[1] >= A && (argv[1])[1] <= F))) {
        // If not, print error message and return.
        printf("Error: Not a valid hexadecimal value. Both characters need to be either 0-9 or A-F. \n");
        return 1;
    } 
    // If both of the characters are either between 0-9 or A-F. 
    else {
        // Then loop through the Ascii values from 0 to 9.
        for (int i=ZERO; i<=NINE; i++) {
            // Check if the first character is any of those numbers.
            if (argv[1][0] == i) {
                // Add the value to the byte and move it 4 places to the left because the first character of the hexadecimal represents the left 4 bits. 
                byte += i << 4;
            }
           // Check if the second character is any of those values.
            if (argv[1][1] == i) {
                // Add the value to the byte, no shifting is required because the second character of the hexadecimal represents the right 4 bits. 
                byte += i;
            }
        }
        // Loop through the Ascii values from A to F.
        for (int i=A; i<=F; i++) {
            // Check if the first character is any of those values.
            if (argv[1][0] == i) {
            /*
            * The values A-F are converted to values 12-15 by substracting the number 55.
            * 55 stands for the difference between 12 and A , 13 and B etc in the Ascii table.
            */
            // Then we add the value to the byte and shift it left by 4 bits because the the first character of the hexadecimal represents the left 4 bits. 
                byte += (i-55) << 4;
            }
             // Check if the second character is any of those values.
            if (argv[1][1] == i) {
            /*
            * The values A-F are converted to values 12-15 by substracting the number 55.
            * 55 stands for the difference between 12 and A , 13 and B etc in the Ascii table.
            */
            // Then we add the value to the byte and no shifting is required because the the second character of the hexadecimal represents the right 4 bits. 
               byte += (i-55);
            }
        }
    }

    // Print the table
    printf("Name\t\tValue\n");
    printf("-----------------------------\n");
    // Engine_on is the left most bit
    printf("engine_on\t%d\n", (byte >> 7));
    // Gear_pos is bits 2-4, and operation is done to remove the previous positions
    printf("gear_pos\t%d\n", (byte >> 4) & 7);
    // Key_pos is bits 5-6, and operation is done to remove the previous positions
    printf("key_pos\t\t%d\n", (byte >> 2) & 3);
    // Brake1 is bit 7, and operation is done to remove the previous positions
    printf("brake1\t\t%d\n", (byte >> 1) & 1);
    // Brake2 is bit 8
    printf("brake2\t\t%d\n", (byte) & 1);

// Return success code.
return 0;
}