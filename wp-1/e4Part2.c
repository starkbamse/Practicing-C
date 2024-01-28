// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 1
// Exercise 4 (part 2)
// Submission code: xxxxxx (provided by your TA-s)

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Function declarations
char *convertBinaryToHex (char *binaryRep);
int isUserArgValid (int argc, char *argv[]);
int turnIntToChar (int integer);
void printHelpInfo (void);

// main function (where the programe starts)
int main (int argc, char *argv[]) {
    char *binaryRep; // variable to hold the binary arg entered by the user
    char *hexRep; // variable to hold the hex string

    // if user argument is valid convert it to hex, else return 2 to indicate error
    if (isUserArgValid(argc, argv)) {
        // set the binart representation
        binaryRep = argv[1];
        // get the hex rep
        hexRep = convertBinaryToHex(binaryRep);
        // print the hex form
        printf("%s\n", hexRep);
        // free the memory allocated by the hexRep pointer
        free(hexRep);
    } else {
        return 2;
    }

    // return 0 upon programe finish
    return 0;
}

char *convertBinaryToHex (char *binaryRep) {
    int length; // variable to hold the length of the binary number (how many 0s and 1s)
    char *hexRep; // pointer to array of chars that hold the hex representation
    int fourBitValue = 0; // variable used to determine the eqaul char in hex for each 4 bits
    int powerInt; // variable used to determine to what power should 3 be raised to
    int hexRepSize; // variable that holds the hexRep size
    int hexRepCounter = 0; // counter to go through the hexRep

    // get the legth of the binary representation to know how much memeory to allocate to the hex representation
    length = strlen(binaryRep);
    // allocate memory to the array of chars that represents the hex representation (each 4 bit eqaul one char in hex) + 1 for the null char
    hexRepSize = (length / 4) + 1;
    hexRep = (char*)calloc(hexRepSize, sizeof(char));

    printf("Binary rep: %s\n", binaryRep);

    // check that memory is correctly allocated
    if (hexRep == NULL) {
        printf("Memory allocation failed.\n");
        exit(2);
    }

    // each iteration add 4 to i, as we want to check each group of 4 bits together
    for (int i = 0; i < length; i += 4) {
        // strting from the right most bit of the 4 bits, it has a max value of 2^3
        powerInt = 3;

        // go over the 4 bits from bit 4 to bit 1
        for (int j = i; j < i + 4; j++) {

            // getting th equal integer value of each bit and adding to the value that was there before
            // the max will be 16. Note that we subtract '0' from the char at j, simply to turn the char to an integer
            fourBitValue = fourBitValue + (pow(2, powerInt) * (binaryRep[j] - '0'));
            // decrement powerInt as the next bit has 2^(powerint - 1) as its max
            printf("power int: %d    bit number: %d   number at bit: %c  four bit value: %d\n", powerInt, j, binaryRep[j], fourBitValue);
            powerInt--;

        }

        // if value of a four bit is greater than 15, smth has gone wrong
        if (fourBitValue > 15) {
            printf("Conversion was unsuccessful. Exiting...\n");
            exit(2);
        }

        // Using a switch case we determine which char in Hex is represented by the value of the four bits added
        // the defualt uses normal integers, meaing that the four bit value was less than 10.
        // The char is then saved at the right index using hexRepCounter
        switch (fourBitValue) {
            case 10:
                hexRep[hexRepCounter] = 'A';
                break;
            case 11:
                hexRep[hexRepCounter] = 'B';
                break;
            case 12:
                hexRep[hexRepCounter] = 'C';
                break;
            case 13:
                hexRep[hexRepCounter] = 'D';
                break;
            case 14:
                hexRep[hexRepCounter] = 'E';
                break;
            case 15:
                hexRep[hexRepCounter] = 'F';
                break;
            default:
                // turn the integer into its corresponding ASCII value
                hexRep[hexRepCounter] = (char) turnIntToChar(fourBitValue);
                break;
        }
        
        // increment counter for next interation
        hexRepCounter++;
        // set four bit value to 0
        fourBitValue = 0;
    }

    // set the null char as the last char in the array
    hexRep[hexRepCounter] = '\0';
    // return the char pointer
    return hexRep;
}

int turnIntToChar(int integer) {
    const int ASCIIZeroVal = 48; // value for zero in ASCII

    // add the integer to the ASCIIzero value. THe char is the integer but in char form
    return ASCIIZeroVal + integer;
}

int isUserArgValid(int argc, char *argv[]) {
    int argLength;  // The length of the argument string
    char *providedArg; // variable to hold user argument
    int is_h; // variable to see if providedArg is -h

    // make sure the user only provides one argument, not more, not less
    if (argc < 2 || argc > 2) {
        return 0;
    }

    // after making sure the user has provided an argument, set the variable
    providedArg = argv[1];
    // see if the arg is -h
    is_h = strcmp("-h", providedArg) == 0 ? 1 : 0;

    // if it is -h, provide help and then exit
    if (is_h) {
        printHelpInfo();
        exit(0);
    }

    // get the input length
    argLength = strlen(providedArg);

    // make sure the argument does not have length 0
    if (argLength == 0) {
        printf("You must provide an argument.\n");
        return 0;
    }

    // if the number of binary digits is not divisible by 4, tell the user
    if ((argLength % 4) != 0) {
        printf("You must provide a number of binary digits that is divisible by 4.\n");
        return 0;
    }

    for (int i = 0; i < argLength; i++) {
        if (providedArg[i] != '1' && providedArg[i] != '0') {
            printf("You must provide a number in binary format.\n");
            return 0;
        }
    }

    // argument is valid
    return 1;
}

void printHelpInfo(void) {
    printf("Please provide a number in terms of binary format. The argument can only contain 1s and 0s.\n");
}