// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 2
// Exercise 2
// Submission code: 


// Include section
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//#### Constants #####
#define MAX 5 // Maximum number of elements in the linked list.
#define MAX_VALUE 100 // Maximum value of an element in the linked list.


/**
* This program generates a random linked list with 5 elements. The values of each element
* are between 0 and 100. 
* The program also adds a new record to the first position of the list and prints out both, the original and the new linked list.
*
* Purpose: Linked list
* DIT632
* 
* 
**/


// ##### typedefs ####
// Defining the element in the linked list.
typedef struct q{
int number; // The value of the element-
struct q *next; // Pointer to the next element in the linked list.
struct q *prev; // Pointer to the previous element in the linked list.
} REGTYPE;

// ##### Function declarations #####
REGTYPE* random_list(void);
REGTYPE* add_first(REGTYPE* temp, int data);


//###### Main program #######
int main(int argc, char *argv[])
{
    // Variable declarations
    int nr=0; // Number of the element.
    // Act_post and head will both store the first node of the linked list.
    REGTYPE *act_post , *head=NULL; 

    srand(time(0)); // Random seed

    // Create the random list and assign it to head.
    head=random_list();
    // Assign act_post to head.
    act_post=head;

    // Loop through the linked list.
    while( act_post!=NULL){
    // Print the current element of the linked list.
    printf("\n Post nr %d : %d" , nr++, act_post->number);
   // Print the current element of the linked list.
    act_post=act_post->next;
    }


    printf("\n\nAdding a new node...\n");
    // Add a new node with a random value to the linked list.
    head = add_first(head, rand()% (MAX_VALUE + 1));
    // Assign act_post to head.
    act_post = head;
    // Set the number back to 0.
    nr = 0;

    // Loop through the linked list
    while( act_post!=NULL){
    // Print the current element of the linked list.
    printf("\n Post nr %d : %d" , nr++, act_post->number);
    // Print the current element of the linked list.
    act_post=act_post->next;
    }

    printf("\n");


    // --- Free the allocated memory ---
    while((act_post=head)!=NULL){
    head=act_post->next;
    free(act_post);
    }
    
    return 0;
}
// ==== End of main ======================================

// Create a linked list with random values.
REGTYPE* random_list(void ){
int i; // Indec of the loop
REGTYPE *top, *old, *item; // Declare REGTYPE variables and set them to NULL.

// Loop from 0 to the max value (5)
    for (i= 0; i < MAX; i++){
        // Declare a new node and allocate memory
        item = malloc(sizeof(REGTYPE));
        // Set the number of the node to a random value between 0 and 100.
        item -> number = rand()%(MAX_VALUE + 1);

    // Check if it is the first element in the linked list.
        if (i == 0)
        {
        // Then there is no top or old node, so put them all to equal each other.
           top = old = item;
        }
        // If it is not the first element in the linked list.
        else {
            // Set the current item's previous value to point to the old item.
             item->prev = old;
             // Set the old item's next to point to the current item.
             old->next = item;
             // Set the old item to equal the current item.
             old = item;
        }
    }
    // Once we are at the last element, there is no next, so we assign it to NULL.
    old->next = NULL;
// Return the first element in the linked list.
return(top);
}

// This function adds a new element to the first position of the linked list.
// It takes in as parameters the pointer to the first element in a linked list and a value.
REGTYPE* add_first(REGTYPE* temp, int data){

    // Declare a new node.
    REGTYPE *item;
    // Assign memory to the new node.
    item = malloc(sizeof(REGTYPE));

    // Set the previous of the first element of the linked list to point to the new node.
    temp->prev = item;
    // As the new node is the first element in the linked list, it does not have a previous element.
    // So we set the previous to point to NULL.
    item->prev = NULL;
    // Set the new node's next to point to the previous first element.
    item ->next = temp;
    // Set the value of the new node to the value passed in from parameters.
    item->number = data;
    // Return a pointer to the new element.
    return(item);
}