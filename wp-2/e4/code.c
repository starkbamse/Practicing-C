//Include section
#include <stdio.h>
#include <stdlib.h>

//Main program section

/**
* This program accepts 5 arguments that each have a different
* minimum and maximum value. It then packs them together in a single
* integer that it then converts to a hexadecimal number.
* 
* Purpose: To practice bitwise operations in C.
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
    int min;
    int max;
} MINMAX;

int main(int argc, char* argv[]){
    // Variable declarations

    int bitSize[]={1,3,2,1,1}; // The expected size of each passed bit.
    char* endptr=NULL; // Used for input validation
    MINMAX maxVal[]={ // The min and max values for each bit (decimal)
        {0,1},{0,7},{0,2},{0,1},{0,1}
    };
    int number; // The current number that we are working on. 
    int packedBits=0; // The packed bits containing all numbers.
    int byteOne; // First byte, later converted to hex.
    int byteTwo; // Second byte, later converted to hex.
    int i; // Used for keeping track of where we are in the loop.

    // Program logic

    // If the number of arguments is not 5.
    if(argc != 6) {
        // Call printErr function.
        printErr();
        // Stop execution.
        return 0;
    }

    // From 1 (program name) through all arguments
    for(i=1;i<argc;i++){
        // Convert the string to a long and then downcast to int.
        int number=strtol(argv[i],&endptr,10);

        // If the end char pointer is not a end string char
        if(*endptr!='\0'){
            // Call printErr function
            printErr();
            // Stop execution
            return 0;
        }

        // Make space for our new bits
        packedBits=packedBits << bitSize[i-1];

        // Perform bitwise OR to "concatenate" two binary numbers.
        packedBits=packedBits | number;
    }

    // Split the packedBits into two by
    // first making the first byte, by shifting it four
    // bits to the right, essentially deleting the last four bits.
    byteOne=packedBits>>4;

    // Perform bitwise AND with 00001111
    // to isolate the second part of the packed
    // bits but remove the first byte.
    byteTwo=packedBits & 0x0F;

    // Print the hex chars
    printf("%c%c",bitsToHex(byteOne),bitsToHex(byteTwo));

    // Exit gracefully
    return 0;
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

void printErr(){
    // Print string to stdout
    printf("Invalid input \n" \
    "Usage: ./a.out [5 numbers separated by space] \n" \
    "e.g. ./a.out 1 2 2 1 1\n");
}