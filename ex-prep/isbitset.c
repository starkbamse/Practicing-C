/******************************************************************************

Write a C program to input any number from user and check whether nth bit of the given number is
set (1) or not (0).

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int number; // The number that we are checking
    int bitToCheck; // The bit that we are checking
    int mask; // The mask that we make to check that bit.
    
    // Prompt the user
    printf("Input number: ");
    // Read an integer from the user
    scanf("%d",&number);
    
    // Prompt the user
    printf("Input nth bit number: ");
    // Read an integer from the user
    scanf("%d",&bitToCheck);
    
    // Create a mask depending on the bit that user wants to check.
    mask=1<<bitToCheck;
    
    // If the bit is set as in the mask using bitwise AND
    if(mask & number){
        // Print that the bit is set
        printf("%d bit of %d is set (1)",bitToCheck,number);
    } else {
        // Print that the bit is unset
        printf("%d bit of %d is not set (0)",bitToCheck,number);
    }
    
    // Exit gracefully
    return 0;
}
