#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
    // To store the first number, allocate heap memory for it
    int* first = malloc(sizeof(int));
    // To store the second number, allocate heap memory for it
    int* second = malloc(sizeof(int));
    
    // Prompt the user    
    printf("Input the first number: ");
    
    // Read the first number
    scanf("%d",first);
    
    // Prompt the user    
    printf("Input the second number: ");
    
    // Read the second number
    scanf("%d",second);
    
    // Print the sum of the numbers
    printf("The sum of the entered numbers is : %d\n",(*first+*second));
    
    // Free occupied heap memory
    free(first);
    
    // Free ocuupied heap memory
    free(second);
    
    // Exit gracefully
    return 0;
}
