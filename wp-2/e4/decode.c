//Include section
#include <stdio.h>
#include <stdlib.h>

//Main program section

/**
* This program accepts 1 hex number of maximum 8 bits
* that is then unpacked into instructions for a 
* car computer, explaining what positions,
* each system should be in.
* 
* Purpose: To practice bitwise operations in C
* DIT632
* 
**/

// Used to convert a set of bits to a hex char
char bitsToHex(int bits);

// Used to print a standard error message
void printErr();

// Used to describe the minimum and max values for
// a place in the packed bits.
typedef struct {
    int min; // Minimum value of the bit
    int max; // Maximum value of the bit
} MINMAX;

// Used to describe the different car systems
// that are inside of the car
typedef struct {
    char description[20]; // Car part description
    MINMAX size; // Min and max size interval
    int bitSize; // How much is occupied
    int padWith; // How much we should pad with for masking
} CAR_PART;

// Used to generate a mask to be able
// to isolate bits in a number.
int makeMask(int bitSize, int pad);

int main(int argc, char* argv[]){
    // Variable declarations
    char* endptr=NULL; // Used for input validation
    int packedBits=0; // The packed bits that we receive
    int i; // To keep track where we are in a loop.
    int isolatedBits;  // The isolated bits of each system
    CAR_PART parts[]={ // The different car parts that exist.
        {
            "engine_on",
            {0,1},
            1,7
        },
        {
            "gear_pos",
            {0,7},
            3,4
        },
        {
            "key_pos",
            {0,2},
            2,2
        },
        {
            "brake1",
            {0,1},
            1,1
        },
        {
            "brake2",
            {0,1},
            1,1
        },
    };


    // Program logic

    // If the number of arguments is not 2.
    if(argc != 2) {
        // Call printErr function.
        printErr();
        // Stop execution.
        return 0;
    }
    // Parse the input as a long and then cast it.
    packedBits=(int) strtol(argv[1],&endptr,16);

    // If the received data exceeds max size.
    if(packedBits>255){
        // Print an error
        printErr();
        // Stop execution
        return 0;
    }

    // If strtol failed to parse the entire string
    if(*endptr!='\0'){
        // Print an error
        printErr();
        // Stop execution
        return 0;
    }

    // Print to stdout.
    printf("Name             Value\n");
    printf("-----------------------------\n");

    // For each car part
    for(i=0;i<(sizeof(parts)/sizeof(CAR_PART));i++){
        // Print the car part description padded with 16 chars whitespace (max).
        printf("%-16s",parts[i].description);

        // Isolate the wanted bits by masking them using the bitwise AND
        // e.g. we have this value 10101011 and we want the gear pos:
        // so we create the mask 01110000 which will allow us to do:
        // 10101011 & 01110000 = 00100000
        isolatedBits=packedBits & makeMask(parts[i].bitSize,parts[i].padWith);

        // Print the value by first shifting it down
        // by how much of bits are to the left of the sub-bits LSB.
        printf("%d\n",(isolatedBits>>parts[i].padWith));
    }   
}

char bitsToHex(int bits){ 
    if(bits<10){
        // Since hex and dec are equal up to the number 10
        // we can just take the char 0 and increment the
        // number to the char to get the wanted char.
        char hex='0'+bits;
        return hex;
    } else {
        // If its bigger or equal to 10
        // we can subtract 15-the number to get the
        // number of chars that we need to subtract
        // from the maximum hex number which is F.
        char hex = ('F'-(15-bits));
        return hex;
    }
}

int makeMask(int bitSize, int padEnd){
    int i; // To keep track of where we are in loop.
    int mask=0; // The mask used to isolate bits.

    // From 0 to the size of the car parts bits
    for(i=0;i<bitSize;i++){
        // Make place for one more bit.
        mask=mask<<1;

        // Set mask LSB to 1.
        mask=mask|1;
    }

    // From 0 to how much we need to pad the mask by
    for(i=0;i<padEnd;i++){
        // Shift the mask by 1 to the left;
        mask=mask<<1;
    }

    // Return the mask
    return mask;
}

void printErr(){
    // Print string to stdout
    printf("Invalid input \n" \
    "Usage: ./a.out [hex number] \n" \
    "e.g. ./a.out AB\n");
}