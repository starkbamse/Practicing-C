// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 3
// Exercise 5
// Submission code:

//Include section
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Define section
#define MAX 5 // Number of elements in array
#define MAX_NUMBER 99 // Max value of a single integer
#define MIN_NUMBER 1 // Min value of a single integer

//Main program section

/**
* This program generates numbers based on a parameter
* specified in the source code. It then takes these numbers
* and puts them into an array. Statistics about the array
* are outputted and the program exits.
* 
* Purpose: To practice pointer knowledge in C.
* DIT632
* 
**/

int main(int argc,char* argv[]){
    // Variable declarations
    int* array=malloc(MAX*sizeof(int)); // Dynamic array on heap
    int* head=array; // Pointer to the head of the array
    int i; // To keep track of where we are in loop
    
    // Program logic

    // Seed the RNG
    srand(time(NULL));

    // From 0 until MAX
    for(i=0;i<MAX;i++){
        // Create a random value
        int random=(rand()%(MAX_NUMBER+1));

        // If its less than minimum, make it minimum.
        if(random<MIN_NUMBER){
            random=MIN_NUMBER;
        }

        // Set the random value in the array
        array[i]=random;
    }

    // Print statistics to stdout
    printf("The value of the address of the array (pointer) is: %p\n",array);
    printf("First integer in the array is (array[0]): %d\n",array[0]);
    printf("The last integer in the array is: %d\n",array[MAX-1]);
    printf("The size of an integer (number of bytes) is: %lu\n",sizeof(int));
    printf("The size of the whole array in bytes is: %lu\n",sizeof(int)*MAX);
    
    // Loop from 0 to MAX
    for(i=0;i<MAX;i++){
        // Dereference and multiply array value by 2.
        printf("Value: %d Value * 2: %d \n",*array,(*array)*2);
        
        // Increment pointer
        array++;
    }    

    // Free the heap memory.
    free(head);    
    
    // Exit gracefully
    return 0;
}