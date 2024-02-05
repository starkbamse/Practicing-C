// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 2
// Exercise 2
// Submission code: xxxxxxx (provided by your TA-s)

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define section
#define MAX 5

// --- Type definitions ---
// This is the node definition for the linked-list
// Each node has a pointer to the next, and the previous nodes
// The node saves a number of integer types as the data type that it saves
typedef struct q {
    int number;
    struct q *next;
    struct q *prev;
} REGTYPE;
// --- Type definitions ---

// --- Function declarations ---
// This method creates a random linked-list
REGTYPE* random_list(void);
// This method adds a node as the first item of the list
REGTYPE* add_first(REGTYPE* temp, int data);
// --- Function declarations ---

/**
 * This programe uses a struct definition to make a linked-list data structures
 * The programe has two methods: One of them creates a random linked-list
 * and the othe rmethod adds items to the beginning of the list
*/

// Main function, where the programe starts
int main(int argc, char *argv[]) {
    int nr = 0; // Variable to count the number of items in the list
    REGTYPE *act_post; // Variable to hold the current item of the list
    REGTYPE *head = NULL; // Variable to hold the head (first) item of the list

    srand(time(0)); // Randomise the seed for creating random numbers
    head = random_list(); // Create a random list and return the first item
    act_post = head; // The current item is the first item

    // Iterate through the list 
    while( act_post != NULL) {
        // Print each item
        printf("Post nr %d : %d\n" , ++nr, act_post->number);
        // Set current item to the next item
        act_post = act_post->next;
    }

    // Add an item to the beggining of the list
    head = add_first(head, 12);
    nr = 0;

    // Print the first element. it should have value 12
    printf("Top's value is: %d\n", head->number);
    
    act_post = head; // The current item is the first item
    // Iterate through the list 
    while( act_post != NULL) {
        // Print each item
        printf("Post nr %d : %d\n" , ++nr, act_post->number);
        // Set current item to the next item
        act_post = act_post->next;
    }


    // --- Free the allocated memory --- start by seting current to head (first item)
    while((act_post = head) != NULL){
        // Set head to the item after current
        head=act_post->next;
        // Free memory occupied by current
        free(act_post);
    }
    // Upon programe finish return 0 to note successfull finish
    return 0;
}


REGTYPE* random_list(void) {
    int i = 0; // For loop counter
    REGTYPE *top; // Variable to hold the top (first element)
    REGTYPE *old; // Variable to hold the old item
    REGTYPE *item; // Variable to hold the current item

    // Initialise old with NULL
    old = NULL;

    // Make linked elements a MAX number of times
    for (i= 0; i < MAX; i++) {
        // Allocate memory each time a new iem is added
        item = calloc(1, sizeof(REGTYPE));

        // if Memory was not allocated correctly, print error message and exit
        if (item == NULL) {
            printf("Memory allocation failed");
            exit(1);
        }
        // The number saved should be between 0 and 100. Therefore we get the modulo of 101
        item->number = rand() % 101;
        // Set the next to null as the next item has not been created yet
        item->next = NULL;
        // Set the prev to the old item which is the one before
        item->prev = old;

        // If old is not null, set old's next to the current item
        if (old != NULL) {
            // Set the old's next to the current item.
            old->next = item;
        }

        // If this is the first item we are making, set top to point to this
        if (i == 0) {
            top = item;
        }
        
        // Set old to be equal to the current item now
        old = item;
        // Set item to null
        item = NULL;
    }

    // Return the first element of the list
    return(top);
}

REGTYPE* add_first(REGTYPE* temp, int data) {
    REGTYPE *oldTop; // Variable to hold the old top which is temp
    REGTYPE *newTop; // Variable to hold the old top which is temp

    // Set olf top to temp
    oldTop = temp;
    // We do not know if the temp was the old top element
    // Continously get the prev element until the prev of an element is NULL
    // This way, we get the old top element
    while (oldTop->prev != NULL) {
        oldTop = oldTop->prev;
    }

    // Allocate memory to the new top element
    newTop = calloc(1, sizeof(REGTYPE));

    // Check that memory is allocated correctly
    if (newTop == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }

    // Temp is the old first item
    oldTop = temp;
    // Set the first item's data to the number provided to the function
    newTop->number = data;
    // Set the next item of the new first item to the old item
    newTop->next = oldTop;
    // Set the prev item to NULL as there are no items before the first item
    newTop->prev = NULL;
    // Set the oldTop's prev to the new first item
    oldTop->prev = newTop;

    // Return the new first item
    return newTop;
}
