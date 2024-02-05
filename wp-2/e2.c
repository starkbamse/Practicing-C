//Include section
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Define section
#define MAX 5 // Maximum nodes in linked list
#define MAX_RANDOM 100 // Maximum random value

/**
* This program creates a random linked list of a specified size
* that is filled with random numbers generated within a specified
* interval. The contents of this linked list is then printed, and 
* finally a new element is placed on the head of the linked list.
* 
* Purpose: To showcase how a complex data structure can be created
* through the use of pointers and structs in C.
* DIT632
* 
* 
**/

// ##### typedefs ####
typedef struct q{ 
    int number; // Number stored in element of linked list.
    struct q *next; // Next node.
    struct q *prev; // Previous node.
} REGTYPE;
// ##### Function declarations #####

// Creates a linked list and fills it with random numbers.
REGTYPE* random_list(void);

// Takes a value and creates a new node and places it
// on the head of the linked list.
REGTYPE* add_first(REGTYPE* temp, int data);

//###### Main program #######
int main(int argc, char *argv[])
{
    int nr=0; // Counter for current position in linked list.
    // act_post is the current node, whilst head is
    // the first element in the list.
    REGTYPE *act_post , *head=NULL; 
    srand(time(0)); // Random seed
    head=random_list(); // Create a random linked list.
    act_post=head; // Set to point to first element.
    
    // While we still have a node that pointed to a non-null node.
    while( act_post!=NULL){
        // Print to stdout.
        printf("\n Post nr %d : %d" , nr++, act_post->number);
        // Update the current node to be node that the current
        // node points to.
        act_post=act_post->next;
    }

    // Create a new node and make it the first element,
    // and set the value to 123.
    head=add_first(head,123);

    // Print to stdout. This prints new head value as well as what the
    // new head points to, the old head.
    printf("\nHead - value: %d points to value: %d\n",head->number,head->next->number);

    // --- Free the allocated memory ---
    while((act_post=head)!=NULL){ 
        // Update the head to point to the node that the current head
        // points to.
        head=act_post->next;
        free(act_post); // Free occupied heap memory.
    }
    // Exit gracefully.
    return 0;
}
// ==== End of main ======================================
REGTYPE* random_list(void ){

    int nr, i=0; // Index and number value

    REGTYPE *top, *old, *item; // Three empty nodes.
    
    // Allocate memory on heap for node of struct size.
    top=malloc(sizeof(REGTYPE));

    // A head cannot have a previous node.
    top->prev=NULL;

    // Generate a random number
    nr=rand()%(MAX_RANDOM+1);

    // Update the value of the head node.
    top->number=nr;

    // Mark the top as the old node.
    old=top;

    // From 0 until the max
    for (i=0;i<MAX;i++){
        // Allocate memory on heap for node of struct size.
        item=malloc(sizeof(REGTYPE));

        // Ensure next is pointing to a null pointer.
        item->next=NULL; 

        // Generate a new random number
        nr=rand()%(MAX_RANDOM+1);

        // Update the number of the new node.
        item->number=nr;

        // Set the current old's next node to be the 
        // newly created node
        old->next=item;

        // Now, the current new node becomes the old node.
        old=item;
    }
    
    // Return the head of the list.
    return(top);
}
//==========================================================
REGTYPE* add_first(REGTYPE* temp, int data){
    // Allocate memory for the new node.
    REGTYPE *new=malloc(sizeof(REGTYPE));

    // Assume the new node is already the head,
    // so point to the old head.
    new->next=temp;

    // Update the number of the new head to the argument.
    new->number=data;

    // Make the temp pointer point to the new head.
    temp=new;

    // Return new head.
    return temp;
}