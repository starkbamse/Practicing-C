/******************************************************************************

Write a C program to input a number from user and count total number of ones (1s) and zeros (0s)
in the given number using bitwise operator.

*******************************************************************************/
#include <stdio.h>

int main()
{
    int number; // The number that we are checking
    int zeros; // N zeros
    int ones; // N ones
    
    // Prompt the user
    printf("Input any number: ");

    // Read integer from user    
    scanf("%d",&number);
    
    // While the number is greater than 0
    while(number>0){
        // If number's LSB is 1
        if(number & 1){
            // Increment n ones
            ones++;
        } else {
            // If LSB is 0
            // Increment n zeros
            zeros++;
        }
        number=number>>1;
    }    
    
    // Print n ones
    printf("Output number of ones: %d\n",ones);
    // Print n zeros
    printf("Output number of zeros: %d\n",zeros);
    
    // Gracefully exit
    return 0;
}
