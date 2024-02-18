// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 4
// Exercise 4
// Submission code: 

//Include section
#include <stdio.h>

//Main program section

/**
* This program can search for a number within an array
* and return the first occurrence as well as sort
* an array using the bubble-sort algorithm.
* 
* Purpose: To practice algorithm development in C.
* DIT632
* 
**/

// Searches for a number in an int array given the size
int search_number(int number, int tab[], int size);

// Sorts an array based on an int array and given the size
void sort(int number, int tab[]);

int main(int argc,char* argv[]){
    // Variable declarations
    int test[] = {1,2,34,5,67,3,23,12,13,10}; // Create an int array

    // Program logic

    // Search for number 34 in the array
    printf("%d\n",search_number(34,test,10));

    // Search for number 999 in the array
    printf("%d\n",search_number(999,test,10));

    // Sort the array
    sort(10,test);
}

int search_number(int number, int tab[], int size){
    int i; // To keep track of where we are in loop

    // Loop through the array
    for(i=0;i<size;i++){
        // If the current number is equal to the sought after number
        if(number==tab[i]){
            // Return the index
            return i;
        }
    }

    // If nothing has been found, return -1
    return -1;
}

void sort(int number, int tab[]) {
    int i; // To keep track of where we are in loop
    int startAt=0; // Where to start in the sub-array
    int minimumAt=0; // Where the current min. is at
    int oldMin=0; // Where the old min. is at

    // While startAt is less than the size of array
    while(startAt<number){
        // Loop through the array
        for(i=startAt;i<number;i++){
            // If a new minimum is found
            if(tab[i]<tab[minimumAt]){
                // Update the location of the current minimum
                minimumAt=i;
            }
        }
        // Set the old minimum var to be the current minimum
        oldMin=tab[startAt];
        // Set the new minimum to be new minimum found.
        tab[startAt]=tab[minimumAt];
        // Set the old minimum to be in the new minimum's found previous pos.
        tab[minimumAt]=oldMin;
        
        // Increment the left boundary
        startAt++;
        // Reset minimumAt to be at the start of the sub-array for the next iter.
        minimumAt=startAt;
    }
    // Loop through the array
    for(i=0;i<number;i++){
        // Print each value
        printf("%d ",tab[i]);
    }
    // Print newline.
    printf("\n");

}