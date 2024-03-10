/******************************************************************************

Advanced binary bit setter using the really smallest dataset

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// To print an error to the screen and free the occupied heap
int printErr(char* ptrToFree);

int main(int argc, char*argv[])
{
    
    char* hex; // To store the input hex number
    char* command; // To store the command that user wants to make
    char* bitToSetStr; // The bit that we need to operate on
    char* binNumber; // The binary rep. of number using the smallest datatype
    int bitToSet; // Bit rep of the bit that we need to set
    int i; // To keep track of where we are in loop
    int x; // To keep track of where we are in loop
    int hexNumberLength; // The length of the hex number
    int position; // Position in binary number for setting bin value
    size_t allocation; // How much memory was allocated on heap for the number
    int mask; // The mask used to isolate bits

    // If less than 3 args provided it means invalid input
    if(argc<4) return printErr(NULL);
    
    // Set the hex to be the first argument
    hex=argv[1];
    
    // Set the command to be the second argument
    command=argv[2];
    
    // Set the bit to set string to be the third argument.
    bitToSetStr=argv[3];
    
    // Calculate the length of the hex number, removing the prefix
    hexNumberLength=strlen(hex)-2;
    
    // Create a new var that is rep. the allocation
    allocation=hexNumberLength;
    
    // Allocate memory for the binary number
    binNumber=malloc(allocation);
    
    // We start counting at the MSB on the binary number which will be n bytes * bits in a nibble
    position=allocation*4;
    
    // Loop through all the chars in the bit that we want to set
    for(i=0;i<strlen(bitToSetStr);i++){
        // If any of the chars. is outside of valid range, print an error
        if(bitToSetStr[i]>'9' || bitToSetStr[i]<'0') return printErr(binNumber);
    }
    
    // Since verification passed convert the string into a number
    bitToSet=atoi(bitToSetStr);
    
    // Loop through the binary number's nibbles
    for(i=0;i<allocation;i++){
        // If the current hex letter is within interval A-F
        if(hex[i+2]>='A' && hex[i+2]<='F'){
            // Use bitwise OR to set the value of A-F in hex
            binNumber[i] = binNumber[i] | ((hex[i+2]-'A')+10);
        } else if(hex[i+2]<='9' && hex[i+2]>='0'){
            // if the current hex letter is within interval 0-9
            // Use bitwise OR to set the current value of 0-9 in hex
            binNumber[i] = binNumber[i] | (hex[i+2]-'0');
        } else {
            // If none of the cases match, the hex has invalid chars, and
            // we call the error method.
            return printErr(binNumber);
        }
    }
    
    
    
    
    
    // Loop through all nibbles
    for(i=0;i<allocation;i++){
        // Loop through all bits in nibble
        for(x=3;x>=0;x--){
            // If we have found the position that we should operate on
            if(bitToSet==position){
                // If the command was to set
                if(strcmp(command,"set")==0){
                    // Create the mask to isolate bit X
                    mask=1<<x;
                    
                    // Set the bit on bit position X to 1 using bitwise OR
                    binNumber[i]=binNumber[i] | mask;
                } else if(strcmp(command,"unset")==0){
                    // If the command was to unset
                    
                    // Create the mask to isolate bit X
                    mask=1<<x;
                    
                    // Check if the isolated bit in the number is a 1
                    if(binNumber[i] & mask){
                        // If it is, we can do bitwise XOR to unset it.
                        binNumber[i]=binNumber[i] ^ mask;
                    }
                    
                } else {
                    // If none of the command matched, print an error
                    return printErr(binNumber);
                }
                
            }
            // Decrement the position that we are at since we go from MSB to LSB
            position--;
        }
    }
    
    // Print hex number prefix
    printf("0x");

    // Loop through the binary number nibbles
    for(i=0;i<allocation;i++){
        // If the current nibble is less than 10
        if(binNumber[i]<10){
            // Invert the operation that we used to convert hex to number
            printf("%c",(binNumber[i]+'0'));
        } else {
            // Invert the operation that we used to convert hex to number
            printf("%c",((binNumber[i]+'A')-10));
        }
    }
    
    // Print binary number prefix
    printf(" === 0b");

    // Loop through the binary number nibbles
    for(i=0;i<allocation;i++){
        // Loop through all the bits within the nibble starting from its MSB
        for(x=3;x>=0;x--){
            // Create the mask to isolate that bit
            mask=1<<x;
            
            // If the bit is set at that position
            if(binNumber[i] & mask){
                // Print 1
                printf("1");
            } else {
                // If the bit is unset, print a zero
                printf("0");
            }
        }
    }
 
    // Free the occupied heap memory
    free(binNumber);
    
    // Exit gracefully
    return 0;
}


int printErr(char* ptrToFree ){
    // Print error message
    printf("Usage: ./a.out <hexnumber> <set or unset> <bit to set or unset>");
    
    // If the pointer passed is not NULL
    if(ptrToFree!=NULL){
        // Free the occupied memory
        free(ptrToFree);
    }

    // Exit gracefully
    return 0;
}
