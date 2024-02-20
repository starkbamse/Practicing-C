// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 4
// Exercise 4
// Submission code: 527499

// Include section
#include <stdio.h>
#include <stdlib.h>

// --- Function declarations ---
// Linear search Function
int search_number(int number, int tab[], int size);
// Bubble sort Function
void sort(int size, int tab[]);
// Swaps two elements in the array provided
void swap(int tab[], int indexOneToSwap, int indexTwoToSwap);
// --- Function declarations ---

/**
 * This program is meant to implement two functions: a) linear search function: given a number n, and array tab[]
 * and the size of the array, find the index of the first time n is repeated, otherwise return -1
 * b) Given an array tab[] and its size, sort the array using bubble sort. In the bubble sort, either the smallest elements
 * or the biggest elements bubble up in the array. 
*/

// Main function, where the program starts
int main(void) {
    // Test arr
    int tab[] = {1, 2, 34, 5, 67, 3, 23, 5, 13, 10};
    int num; // Number to search for
    int index; // Index returned by the linear search method

    // Search for number 3
    num = 5;
    // search for the number. The length of the array is the size of it divided by the size of int
    // (40 / 4 = 10)
    index = search_number(num, tab, sizeof(tab) / sizeof(int));
    // Print the index and verify that the linear search function works correctly
    printf("Index should be 3.\nIndex -> %d\n", index);

    // Set num to a number that does not exist
    num = 20;
    // Index should be -1
    index = search_number(num, tab, sizeof(tab) / sizeof(int));
    // Print the index and verify that it is -1
    printf("Index should be -1.\nIndex -> %d\n", index);

    // Sort the array
    sort(sizeof(tab) / sizeof(int), tab);

    // Print the array elements and verify that they are sorted from max to main
    for (int i = 0; i < sizeof(tab) / sizeof(int); i++) {
        printf("%d  ", tab[i]);
    }
    // Go to the next line
    printf("\n");

    // Return 0 upon program finish to indicate success
    return 0;
}

int search_number(int num, int tab[], int size) {
    // Traverse through the elements, if any of them equals provided num,
    // then return its index
    for (int i = 0; i < size; i++) {
        if (tab[i] == num) {
            return i;
        }
    }
    
    // If the number to search for does not exist, then return -1
    return -1;
}

void sort(int size, int tab[]) {
    // Bas case. If the size is less than or equal to 1, return, as the arr is already sorted
    if (size <= 1) {
        return;
    }
    // Traverse through the array size - 1 times.
    // The reason fro traversing size - 1 is that we use i + 1 in the loop
    // and if traverse as many times as the size, the in the last iteration, tab[i + 1] will
    // cause segmentation fault as the index would be higher than the last element's index 
    for (int i = 0; i < size - 1; i++) {
        // We want to bubble the smallest elements up
        // So if element held at index i is smaller than the element held at i + 1,
        // swap them
        if (tab[i] > tab[i + 1]) {
            swap(tab, i, i + 1);
        }
    }
    // Recursively call the function until all elements are sorted
    // Since the smallest element is at the top, we do not need to check it again
    // So the size of unsorted elements is size - 1.
    sort(size - 1, tab);
}

void swap(int tab[], int indexOneToSwap, int indexTwoToSwap) {
    int temp; // Hold value held at indexOneToSwap

    // Hold the value at indexOneToSwap n temp, so is not lost
    temp = tab[indexOneToSwap];
    // Set the value held at indexOneToSwap to that held at indexTwoToSwap
    tab[indexOneToSwap] = tab[indexTwoToSwap];
    // Set the value held at indexTwoToSwap to what indexOneToSwap held before
    tab[indexTwoToSwap] = temp;
}