// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 2
// Exercise 4 (part B)
// Submission code: xxxxxxx (provided by your TA-s)

// Inlude section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Type definitions ---
// The arguments that will be unpacked are gathered in one struct called car
typedef struct {
    int engineOn;
    int gearPos;
    int keyPos;
    int breakOne;
    int breakTwo;
} CAR;
// --- Type definitions ---

// --- Function declarations ---
// Unpack the hexadecimal value provided as an argument
// Then the function prints the unpacked values
void unpack(unsigned char *packedByte);
// Validate the argument provided
int validateArg(int argc, char *argv[]);
// --- Function declarations ---

/**
 * This program receives one hexadecimal value and unpacks it into the bits that it contains.
 * The unpacked bits make up the values for each of the five attributes of the struct defined above
*/

// Main function, where the programe starts
int main(int argc, char *argv[]) {
    unsigned char *hexrep; // Variable to hold the hex representation

    // If validation fails, return 1 to indicate error
    if (!validateArg(argc, argv)) {
        return 1;
    }
    // Set the hex arg to the hex rep
    hexrep = argv[1];
    // Unpack the hex rep
    unpack(hexrep);
    
    // Return 0 upon programe finish to indicate success
    return 0;
}

void unpack(unsigned char *packedByte) {
    unsigned char packed; // Variable to hold the packed hexadecimal
    CAR unpacked; // Variable to hold the unpacked values
    int decimal; // Variable to hold the decimal value of the hex chars
    
    // Convert the hex into decimal
    decimal = strtoul(packedByte, NULL, 16);
    // Set the packed unsigned char
    packed = packed | decimal;

    // Get the value for break two, LSB. Use bitwise &
    unpacked.breakTwo = 1 & packed;
    // Shift 1 to the right to get rid of the current bit and go to the second bit
    packed >>= 1;
    // Get the value for break 1
    unpacked.breakOne = 1 & packed;
    // Shift one to the right to get rid of the current bit
    packed >>= 1;
    // Get keyPos value. 3 is used as keyPos could have a max of 0b11
    unpacked.keyPos = 3 & packed;
    // Shift packed to right by 2 bits as keyPos took 2 bits
    packed >>= 2;
    // Get gearPos value by comparing to 7 as the max value of gearPos is 111
    unpacked.gearPos = 7 & packed;
    // Shift to the right 3 bits as gearPos took 3 bits
    packed >>= 3;
    // Get engineOn value
    unpacked.engineOn = 1 & packed;

    // Print the unpacked values
    printf("Name           Value\n");
    printf("-----------------------------\n");
    printf("engine_on      %d\n", unpacked.engineOn);
    printf("gear_pos       %d\n", unpacked.gearPos);
    printf("key_pos        %d\n", unpacked.keyPos);
    printf("brake1         %d\n", unpacked.breakOne);
    printf("brake2         %d\n", unpacked.breakTwo);
}

int validateArg(int argc, char *argv[]) {
    
    // If the arguments provided is less than or greater than 2, print error message and return 0 to indicate failure in validation
    if (argc < 2 || argc > 2) {
        printf("You must provide one argument.\n");
        return 0;
    }

    // If the length of the provided arg is greater than 2, whihc means that the value is greater than 256 (8 bytes), 
    // print error message and return 0 to indicate failure in validation
    if (strlen(argv[1]) > 2) {
        printf("The value provided is too big, enter a value between 0 and 255 in hex notation please.\n");
        return 0;
    }

    // Check that the chars conform to hex notation
    for (int i = 0; i < strlen(argv[1]); i++) {
        // ASCII 0 = 48
        // ASCII 9 = 57
        // ASCII A = 65
        // ASCII F = 70
        // if the char ASCII val is less than 48 or greater than 57 (given that it is not between 65 and 70), print error message and return 0
        if (argv[1][i] < 48 || (argv[1][i] > 57 && (argv[1][i] < 65 || argv[1][i] > 70))) {
            printf("The value provided does not conform to hex notation\n");
            return 0;
        }
    }

    return 1;
}