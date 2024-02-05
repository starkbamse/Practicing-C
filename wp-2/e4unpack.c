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
void unpack(char *packedByte);
// Validate the argument provided
void validateArg(int argc, char *argv[]);
// --- Function declarations ---

/**
 * This program receives one hexadecimal value and unpacks it into the bits that it contains.
 * The unpacked bits make up the values for each of the five attributes of the struct defined above
*/

// Main function, where the programe starts
int main(int argc, char *argv[]) {

    // Return 0 upon programe finish to indicate success
    return 0;
}

void unpack(char *packedByte) {
    
}