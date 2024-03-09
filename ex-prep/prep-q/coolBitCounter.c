/******************************************************************************

Bits and bytes
Write a program that counts the number of 0s and 1s in the binary representation of a decimal
number.

Your program should ask the user to provide a decimal number. Then it should print the decimal
number, it's binary representation and then count the number of 0s and 1s.
The interaction with the program should look like this:

Please provide a number: <user inputs a number here>
Number: 3
Binary: 0b11
Number of 0s: 0
Number of 1s: 2

In this task, you must use bit operations. You are not allowed to convert the number to strings or
arrays of any sort. Leading 0s should not be counted (e.g., 0b0011 should return "Number of 0s:
0; Number of 1s: 2").

In this question you can use the online compiler.
Points:
- conversion to binary: 1p
- counting 1s and 0s: 2 p
- comments: 2p
- check for correct input: 1p

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

// Initial n bytes that we use to allocate memory
#define INITIAL_MEMORY_ALLOCATION 10

// To get the number of bits a number occupies.
int getBitSize(int number);

int main()
{
    // Variable declarations
    size_t allocation=INITIAL_MEMORY_ALLOCATION; // Initial allocation for input
    char* userInput=malloc(allocation); // Allocate heap memory for input
    int number; // The number that we are checking
    int length; // The number of bits that number occupies
    int i; // To keep track of where we are in loop
    int c; // The current char that we are processing
    int position=0; // Position in string
    int zeros=0; // N zeros
    int ones=0; // N ones
        
    // If the memory allocation failed
    if(userInput==NULL){
        // Print error message
        printf("Failed allocating memory\n");
        // Exit gracefully
        return 0;
    }
    
    // Prompt the user
    printf("Please provide a number: ");
    
    // While the current char is not a newline nor eof
    while( ( c=fgetc(stdin) ) !='\n' && c!=EOF){
        // If an increase of position will overflow allocation
        if((position+1)>allocation){
            // Increase the allocation two-fold
            allocation=allocation*2;
            // Reallocate the user input with the new amount
            userInput=realloc(userInput,allocation);
            // If the reallocation failed
            if(userInput==NULL){
                // Print an error message
                printf("Failed allocating memory\n");
                // Exit gracefully
                return 0;
            }
        }
        // If the current char is outside of the valid range
        if(c>'9' || c<'0'){
            // Print error message
            printf("Invalid input\n");
            // Exit gracefully
            return 0;
        }
        // Set the current char at the current position of the array
        userInput[position]=(char) c;
        // Increment position counter
        position++;
    }
    
    // Convert the string into a number
    number=atoi(userInput);
    
    // Free the occupied heap memory
    free(userInput);

    // Print the number
    printf("Number: %d\n",number);
    
    // Print the binary prefix
    printf("Binary: 0b");
    
    // Calculate the bit size of the number
    length=getBitSize(number);
    
    // From the length of the number down to the zero
    for(i=length-1;i>=0;i--){
        // Create a mask by shifting 1 i places to the left
        // effectively isolating a bit so that we can use bitwise AND
        // to check if they are the same.
        int mask=1<<i;
        
        // If the bit at mask is active in number, it means its a 1
        if(number & mask){
            // Print 1
            printf("1");
            // Increment n ones
            ones++;
        } else {
            // If the bit at mask is not active in number it means its a 0
            // Print 0
            printf("0");
            // Increment n zeros
            zeros++;
        }
    }
    // Print newline
    printf("\n");
    // Print number of zeros
    printf("Number of 0s: %d\n",zeros);
    // Print number of ones
    printf("Number of 1s: %d\n",ones);
    
    // Exit gracefully
    return 0;
}

int getBitSize(int number){
    int length=0; // To store the "length" / bit size of number
    
    // While the number still has valuable bits
    while(number!=0){
        // Shift the number one bit to the right
        number=number>>1;
        // Increment the length
        length++;
    }
    
    // Return the length
    return length;
}

