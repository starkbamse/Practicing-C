/******************************************************************************

Write a C program to input any number from user and find highest order set bit of given number
using bitwise operator

*******************************************************************************/

#include <stdio.h>

int main()
{
    int number; // The number that we are comparing with
    int numberCopy; // A copy of that number so that we can print it out again
    int highestOrderSetBit; // The highest order set bit of given number
    int position; // Position in binary number
    
    // Prompt the user
    printf("Input any number: ");
    
    // Read integer from user
    scanf("%d",&number);
    
    // Copy the read number
    numberCopy=number;
    
    // While the number is greater than 0
    while(number>0){
        // If LSB is 1
        if(number & 1){
            // Set the highest order set bit to the current position
            highestOrderSetBit=position;
        }
        // Increment the positiion
        position++;
        // Shift the number by one bit to the right
        number=number>>1;
    }
    
    // Print which highest order set bit is in the number
    printf("Highest order set bit in %d is %d.",numberCopy,highestOrderSetBit);
    
    // Exit gracefully
    return 0;
}
