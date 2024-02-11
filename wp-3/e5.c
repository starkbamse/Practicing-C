// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 3
// Exercise 5
// Submission code: xxxxxxx

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define section
#define MAX 10
#define MAX_NUM_ALLOWED 99

// --- Function declaration ---
// This function creates randome integers between 1 and 99 (inlcuding both bounds)
int createRandInt(void);
// Fill the array with random integers
void fillArr(int **arr);
// Print array info
void printArrInfo(int **arrAdd);
// --- Function declaration ---

// main function, where the program starts
int main(void) {
    int *arr; // An array of integers

    // Set the size of the array according to MAX macro
    arr = (int*)calloc(MAX, sizeof(int));

    // Check that memory is allocated
    if (arr == NULL) {
        printf("memory allocation failed.\n");
        return 1;
    }

    // Set the seed to be able to create random integers
    srand(time(0));

    // Fill up the arr
    fillArr(&arr);
    // Print the arr info
    printArrInfo(&arr);

    // Free the mem before finishing the program
    free(arr);
    // Set pointer arr to null, so that the memory is not accessed by accident in the future
    arr = NULL;

    // Return 0 upon program finish 
    return 0;
}

int createRandInt(void) {
    // To create rand ints between 1 and 99, we get the modulo of
    // rand() by 98 and add 1 to it and ten return the rand number
    return (rand() % MAX_NUM_ALLOWED) + 1;
}

void fillArr(int **arrAdd) {
    // Go through the arr and assign a rand numb to each index
    // Note that the add of the pointer is passed, so deferrencing is needed
    for (int i = 0; i < MAX; i++) {
        (*arrAdd)[i] = createRandInt();
    }
}

void printArrInfo(int **arrAdd) {
    // Print the add of the array
    printf("The value of the address of the array is: %lu\n", (__uint64_t)arrAdd);

    // Print the first int
    printf("The first integer is: %d\n", (*arrAdd)[0]);

    // Print the last integer in the array
    printf("The last integer in the array is: %d\n", (*arrAdd)[MAX - 1]);

    // Print the size of an int var in bytes
    printf("The size of an int variable is: %ld\n", sizeof(int));

    // Print the size of the arr in bytes
    printf("The size of the whole array in bytes is: %ld\n", (sizeof(int) * MAX));
}
