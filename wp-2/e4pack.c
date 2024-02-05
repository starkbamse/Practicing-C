// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 2
// Exercise 4 (part A)
// Submission code: xxxxxxx (provided by your TA-s)

// Inlude section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Type definitions ---
// The arguments that will be packed are gathered in one struct called car
typedef struct {
    int engineOn;
    int gearPos;
    int keyPos;
    int breakOne;
    int breakTwo;
} CAR;
// --- Type definitions ---

// --- Function declarations ---
// This function interperets the numbers that are given (the max value is 256) and
// packs them into a byte
void packBits(CAR *packCar);
// Validate the arguments given
int validateArgs(int argc, char *argv[]);
// --- Function declarations ---

/**
 * This program packs 5 different values that are the members of the struct defined above,
 * into one byte and then prints out the hexadecimal value of the byte to the console
*/

// Main function, where the programe starts
int main(int argc, char *argv[]) {
    CAR toPack; // Variable that holds the values that are to be packed

    // If validation fails, return 1 to indicate programe failure
    if (!validateArgs(argc, argv)) {
        return 1;
    }

    // Validation passed, save arguments in the struct
    // Use atoi() to convert the string into integer
    toPack.engineOn = atoi(argv[1]);
    toPack.gearPos = atoi(argv[2]);
    toPack.keyPos = atoi(argv[3]);
    toPack.breakOne = atoi(argv[4]);
    toPack.breakTwo = atoi(argv[5]);
    // Pack the bits and print the hexadecimal val
    packBits(&toPack);

    // Return 0 upon programe finish
    return 0;
}

void packBits(CAR *packCar) {
    // Note that unsigned char is one byte as it obly has 256 different values
    unsigned char packed = 0b0; // Variable that holds the packed bits in one byte. Initialised with 0

    // Use the or bitwise operator to input the value of the bit that attributeVal holds
    packed = packed | packCar->engineOn;
    // Shift packed to the left by 3, as next is gearPos that takes 3 bits
    packed <<= 3;

    // Use | to combine both packed and gearPos
    packed = packed | packCar->gearPos;
    // Next is keyPOs, shift 2 bits to the left
    packed <<= 2;

    // Use | to add keyPos bits to the packed byte
    packed = packed | packCar->keyPos;
    // Shift 1 as the next one (breakOne) is only 1 bit
    packed <<= 1;

    // Use | to add breakOne bits to the packed byte
    packed = packed | packCar->breakOne;
    // Shift 1 as the next one (breakTwo) is only 1 bit
    packed <<= 1;

    // Use | to add breakTwo bits to the packed byte
    packed = packed | packCar->breakTwo;

    // The bits are pavked now, print the hexdecimal value
    printf("%X\n", packed);

}

int validateArgs(int argc, char *argv[]) {
    // If there are less or more than 5 args (6 with program name), return 0 to indicate failure in validation
    if (argc < 6 || argc > 6) {
        printf("You must provide 5 arguments only.\n");
        return 0;
    }

    // Check that all arguments have length 1. (One char)
    for (int i = 1; i <= 5; i++) {
        // If the length of the argument is bigger than 1, print error massage
        if (strlen(argv[i]) > 1) {
            printf("Your arguments must have length 1.\n");
            return 0;
        }

        // For gearPos which is the second provided arg, check if it is between and including 0 and 7
        // ASCII 0 = 48 and ASCII 7 = 55
        if (i == 2 && (argv[i][0] < 48 || argv[i][0] > 55)) {
            printf("Gear_pos can be between and including 0 and 7 only.\n");
            return 0;
        // For keyPos which is the thirs provided arg, check if it is between and including 0 and 3
        // ASCII 0 = 48 and ASCII 3 = 51
        } else if (i == 3 && (argv[i][0] < 48 || argv[i][0] > 51)) {
            printf("Key_pos can be between and including 0 and 3 only.\n");
            return 0;
        // Else, check that the values are either 1 or 0
        // ASCII 0 = 48 and ASCII 1 = 49
        } else if (i == 1 || i == 4 || i == 5){
            if (argv[i][0] != 48 && argv[i][0] != 49) {
            printf("Engine_on, Break1, and Break2 can only be 0 or 1.\n");
            return 0;
            }
        }

    }

    // All checks pass, return 1 to indicate arguments validation
    return 1;

}