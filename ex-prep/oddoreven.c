/******************************************************************************

Write a C program to input any number and check whether the given number is even or odd using
bitwise operator.

*******************************************************************************/
#include <stdio.h>

int main()
{
    int number; // The number that we are checking
    
    // Prompt the user
    printf("Input number: ");
    
    // Read an integer
    scanf("%d",&number);
    
    // If LSB is 1
    if(number&1){
        // Print number is odd
        printf("%d is odd\n",number);
    } else {
        // Print that number is even
        printf("%d is even\n",number);
    }

    // Gracefully exit
    return 0;
}
