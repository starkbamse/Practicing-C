// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 (2024)
// Work package 3
// Exercise 5
// Submission code: 


// Include section
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//#### Constants #####
#define MAX 10 // Maximum number of elements in the linked list.
#define MAX_VALUE 99 // Maximum value of an element in the linked list.


/**
* This program creates an array of integers and fills it with random numbers from 1 to 99.
* The program prints out different values of the array, using pointers.
*
* Purpose: Arrays with pointers
* DIT632
* 
* 
**/


//###### Main program #######
int main()
{
    // Variable declarations
    int array[MAX]; // Array to store the MAX amount of elements
    int *ptr; // Pointer to the array
    srand(time(0)); // Random seed to generate random numbers

    // For MAX amount of times
    for (int i = 0; i < MAX; i++)
    {
        // Create a random number between 1 and 99 and store it in the array.
       array[i] = rand() % 99 + 1;
    }
    
    // Print the address of the array.
    printf("The value of the address of the array (pointer) is: %p\n", array);
    // Print the first integer in the array
    printf("First integer in the array is (array[0]): %d\n", array[0]);
    // Print the last integer in the array
    printf("The last integer in the array is: %d\n", array[MAX-1]);
    // Print the size of an integer
    printf("The size of an integer (number of bytes) is: %d\n", (int) sizeof(int));
    // Print the size of the whole array in bytes
    printf("The size of the whole array in bytes is: %d\n", (int) sizeof(array));

    // Print all of the values in the array
    printf("Values of the array: \n");
    // For each element in the array
    for (int i = 0; i < MAX; i++)
    {
        // Set the pointer to the current element
        ptr = &array[i];
        // Print the value of the pointer
        printf("%d ", *ptr);
    }

    // Print the doubled values of the array.
    printf("\nValues of the array (doubled): \n");
    // For each element in the array
    for (int i = 0; i < MAX; i++)
    {
        // Set the pointer to the current element
        ptr = &array[i];
        // Print the value of the pointer multiplied by 2.
        printf("%d ", *ptr*2);
    }
    
    printf("\n");
    // Return success code.
    return 0;
}
