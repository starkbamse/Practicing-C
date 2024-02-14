// (C) Omid Khodaparast, Alexander Säfström, Kaisa Arumeel - Group 2 
// Work package 4
// Exercise 4
// Submission code: 

#include <stdio.h>
#include <stdlib.h>

/*
* This program creates a test array and allows the user to search for a number in that array.
* The program also uses bubble sort to sort the array.
*
* Purpose: Lists and sorting.
* DIT632
*/

// Task a
// The method searches for a number that is passed in, in an array of a specified size
int search_number(int number, int tab[], int size) 
{
    // Loop through each element in the array
    for (int i = 0; i < size; i++) {
        // Check if any element is the number we are looking for
        if (tab[i] == number) {
            // Return the index
            return i;
        }
    }
    // If it does not exist, return -1
    return -1;
}

// Task b
// This methods sorts an array in ascending order using bubble sort.
void sort (int number, int tab[]) {

    int temp; // A temporary variable

    // Loop through the size of the array
    for (int i = 0; i < number; i++) {
        // Loop through the size of the array - 1
        for (int j = 0; j < number-1; j++) {
            // Set the temporary variable to the left most element of the array.
            temp = tab[j]; 
            // Check if the right element is smaller than the left element.
            if (tab[j+1] < tab[j]) {
                // If it is, then swap them.
                tab[j] = tab[j+1];
                // Set the new right-hand side index's value to the temp variable's stored value.
                tab[j+1] = temp;
            }        
        }
    }
}

// Main function of the program
int main(int argc, char * argv[]){


    // Check if there are program arguments provided
    if (argc != 2)
    {
        // If not, print error message and return error code.
        printf("Enter a number you are searching for.\n");
        return 1;
    }

    // Save the user inputter parameter into a variable as an integer.
    int number = atoi(argv[1]);
    int test[] = {1, 2, 34, 5, 67, 3, 23, 12, 13, 10}; // Array of integers
    int size = sizeof(test)/sizeof(int); // Size of the array

    // Print the test array, loop through each element in the array and print it.
    printf("Test array: ");
    for (int i = 0; i < size; i++)
    {
       printf("%d ", test[i]);
    }
    printf("\n");


    // Call the search method and save the result as index.
    int index = search_number(number, test, size);
    // Check if the number exists in the array.
    if (index != -1)
    {
        // If it does, print the index.
        printf("\nSearching for %d in test[] array. Index of %d is %d\n", number, number, search_number(number, test, size));
    } else {
        // If not, print that it does not exist in the array.
        printf("\nSearching for %d in test[] array. %d is not in the array.\n", number, number);
    }
    
    // Sort the array
    sort(size, test);
    // Print the sorted array by printing every element in the array.
    printf("\nSorted Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", test[i]);
    }
    printf("\n");

    // Return with success code.
    return 0;
}
