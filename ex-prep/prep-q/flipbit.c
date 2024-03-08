/******************************************************************************

Write a C program to input any number from user and toggle or invert or flip nth bit of the given
number using bitwise operator.

*******************************************************************************/
#include <stdio.h>

int main()
{
    int number; // The number of which bits we want to flip
    int bitToFlip; // The bit that we want to flip
    int mask; // The mask that we use to isolate the bit.
    
    // Prompt the user
    printf("Input number: ");
    // Read an integer from the user
    scanf("%d",&number);
    
    // Prompt the user
    printf("Input nth bit to toggle: ");
    // Read an integer from the user
    scanf("%d",&bitToFlip);
    
    // Create a mask of the bit that we want to flip
    mask = 1 << bitToFlip;
    
    // If bit is 1
    if(mask & number){
        // Perform bitwise XOR on the number.
        number= mask ^ number;
    } else {
        // If the bit is 0
        // Set the bit to 1.
        number = mask | number;
    }
    // Print the new bit
    printf("After toggling nth bit: %d (in decimal)",number);
    
    // Exit gracefully
    return 0;
}
