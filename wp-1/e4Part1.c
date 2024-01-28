// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 1
// Exercise 4 (part 1)
// Submission code: xxxxxx (provided by your TA-s)

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function declarations
int getNumOfBits(unsigned long int deciNum);
char *convertDecimalToBinary(unsigned long int deciNum);
int isUserArgValid(int argc, char *argv[]);
void printHelpInfo(void);

// main function (where the programme starts)
int main(int argc, char *argv[]) {
    unsigned long int deciNum; // variable that holds the decimal number
    char *binaryRep; // variable that holds the binary representation of the number inputed by the user
    char *argument; // variable to hold the string inputed by the user

    // validate the argument provided by the user
    // if it is valid, exec main programme logic
    // else keep telling the user that they need to enter the right arg
    if (isUserArgValid(argc, argv)) {
        // set the argument variable
        argument = argv[1];
        // if the argument is 0, print 0 and end program
        if (strcmp("0", argument) == 0) {
            printf("0\n");
            return 0;
        }
        // use atoi to parse the string to int
        deciNum = atoi(argument);
        // convert the decimal number to binry representation
        binaryRep = convertDecimalToBinary(deciNum);
        // print the binary representation
        printf("%s\n", binaryRep);
        // free the memory consumed by the pointer
        free(binaryRep);
    } else {
        // return 2 as argument was not valid
        return 2;
    }

    // return 0 upon programme finish
    return 0;
}

int getNumOfBits(unsigned long int deciNum) {
    int numOfBits;  // this variable will hold the number of bits that a decimal occupies
    unsigned long int mask = 1; // smallest positive number that takes the least amount of bits (1)

    // initialise the numOfBits with 0 as 0 does not have any bits in a sense.
    numOfBits = 0;

    // use left shift (1 shift only) to increase the size of mask until mask is bigger than deciNum
    // each time the while loop exectes, increment the numOfBits variable
    while ((mask - 1) < deciNum) {
        // since deci num is bigger, increase num of bits by one
        numOfBits++;
        // left shift mask to make it bigger
        mask <<= 1;
    }

    // if number of bit is 0, the number printed was too big. 
    if (numOfBits == 0) {
        printf("Number was too big.\n");
        exit(2);
    }

    while ((numOfBits % 4) != 0) {
        numOfBits++;
    }

    // return the numOfBits to the caller
    return numOfBits;
}

char *convertDecimalToBinary(unsigned long int deciNum) {
    char *binaryRep;  // array of chars which is as big as the number of bits
    int mask = 0b1;  // set mask to the smallest number having a 1 bit. 0b1
    int bitwiseCheck; // this variable holds the bitwise check of mask with deciNum
    int numOfBIts; //variable to hold the number of bits

    // add one for the \0 char
    numOfBIts = getNumOfBits(deciNum) + 1;
    // allocate memory to the string
    binaryRep = (char*)calloc(numOfBIts, sizeof(char));

    // check that memory is correctly allocated
    if (binaryRep == NULL) {
        printf("Memory allocation failed.\n");
        exit(2);
    }
    // use bitwise operators to turn the decinum based on the number of bits it has to its binary represnetation
    for (int i = numOfBIts - 2; i >= 0; i--) {
        // use the mask with & bitwise operator get the check of the binary digits
        bitwiseCheck = deciNum & mask;
  
        // if the digits are equal (both are 1), the check is the same as mask, else, it is 0
        binaryRep[i] = bitwiseCheck == mask ? '1' : '0';

        // shift mask to the left by 1
        mask <<= 1;
    }

    // set the null in the last index
    binaryRep[numOfBIts - 1] = '\0';

    return binaryRep;
}

int isUserArgValid(int argc, char *argv[]) {
    const int ASCIIZeroVal = 48; // value for zero in ASCII
    const int ASCIINineVal = 57; // value for nine in ASCII
    int argLength;  // The length of the argument string
    int charASCIIVal; // variable to hold a char's ASCII value
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

    // for loop to go over the chars of the string provided by the user
    for (int i = 0; i < argLength; i++) {

        // get the ith char and get its ASCII val
        charASCIIVal = (int) providedArg[i];

        // if the ASCII val does not indicate a number return 0 to indicate invalid input
        if (charASCIIVal < ASCIIZeroVal || charASCIIVal > ASCIINineVal) {
            printf("You must provide numbers only.\n");
            return 0;
        }

    }

    // return 1 to indicate valid input number
    return 1;
}

void printHelpInfo(void) {
    printf("Please provide a positive integer. The integer must be smaller or equal to 4294967295.\n");
}
