#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
// structure describing one node of the list
struct node {
    int data;
    int key;
    struct node* next;
};
// pointing to the beginning of the list and the current node
struct node* head = NULL; // Point head to NULL pointer
struct node* current = NULL; // Point current node to NULL pointer

int length() {
    struct node* ptr = head; // Make a copy of head
    int length=0; // Initial length is zero
    int lastNode=0; // Whether or not we are on the last node
    
    // If the list is empty return 0
    if (head == NULL) return 0;
    
    // While we are not on the lastNode
    while (!lastNode) {
        // Increment the length
        length++;
        // If the next pointer is a pointer to itself
        if(ptr->next == ptr){
            // We are on the last node
            lastNode=1;
        }
        // Set the pointer to point to the next pointer
        ptr = ptr->next;
    }

    // Return length of list
    return length;
}


//insert link at the first location
void insertFirst(int key, int data) {
    //create a link
    struct node* link = (struct node*)malloc(sizeof(struct node));
    // Set the key value
    link->key = key;
    // Set data value
    link->data = data;
    
    // If length is 0
    if (length()==0) {
        // Set the head to point to the first element
        head = link;
        // Set the pointer of head to point to head
        head->next = head;
    } else {
        //point it to old first node
        link->next = head;
        //point first to new first node
        head = link;
    }
}

//delete first item
struct node* deleteFirst() {
    //save reference to first link
    struct node* tempLink = head;
    
    // If the next pointer is a pointer to itself
    if (head->next == head) {
        // Set head to NULL pointer
        head = NULL;
        // Return the pointer copy
        return tempLink;
    }
    //mark next to first link as first
    head = head->next;
    //return the deleted link
    return tempLink;
}
//display the list
void printList() {
    // Make a copy of the pointer
    struct node* ptr = head;
    // Print opening bracket
    printf("\n[ ");
    
    // We are not on the last node
    int lastNode=0;
    //start from the beginning
    if (head != NULL) {
        // If the list is not empty
        while (!lastNode) { // While we are on the last node
            // Print key and value of current node
            printf("(%d,%d) ", ptr->key, ptr->data);
            
            // If the next pointer points to the current item
            if(ptr->next == ptr){
                // We are on the last node
                lastNode=1;
            }
            // Set pointer to point to the next pointer
            ptr = ptr->next;
        }
    }
    // Print closing bracket
    printf(" ]");
}

int main() {
    int i; // To keep track of where we are in loop
    int listLength; // The length of the list
    // Program logic
    insertFirst(1, 10); // Insert item in the beginning of list
    insertFirst(2, 20); // Insert item in the beginning of list
    insertFirst(3, 30); // Insert item in the beginning of list
    insertFirst(4, 1); // Insert item in the beginning of list
    insertFirst(5, 40); // Insert item in the beginning of list
    insertFirst(6, 56); // Insert item in the beginning of list
    
    // Print the first part
    printf("Original List: ");
    //print list
    printList();
    
    // Calculate length of linked list
    listLength=length();
    
    // From 0 to the end of the list
    for(i=0;i<listLength;i++){
        // Delete the first element
        deleteFirst();
    }

    // Print the first part
    printf("\nList after deleting all items: ");
    
    // Print the list
    printList();
    
    // Exit gracefully
    return 0;
}