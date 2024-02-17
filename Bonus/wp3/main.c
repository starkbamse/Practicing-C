//Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define section
#define MAX_CHARS 10 // Maximum allowed chars for input

//Main program section

/**
* This program prints the permutations of all strings less
* than 10 characters.
* 
* Purpose: To be able to know all the different ways
* a string can be arranged.
* DIT632
* 
* Author: Alexander Säfström, 2024
*
**/

// To permute a string and calculate its permutations
void permute(char* str,int start,int end,char* largeArray[],int* pos);

// To calculate the factorial value of an integer.
int factorial(int number);

// To swap an items value with another item
void swap(char* item1,char* item2);

int main(int argc,char*argv[]){

    // Variable declarations
    int inputLength; // The length of the argument
    int nPermutations; // Calculate the number of permutations we expect
    int arrayPosition=0; // Current position in the large array
    char ** largeArray; // An array of pointers. 
    int i; // Used to keep track of where we are in loop.

    // If less than two args, entered.
    if(argc<2){
        // Print error message
        printf("invalid\n");
        // Exit gracefully
        return 0;
    }

    inputLength=strlen(argv[1]);

    // If the argument length is bigger than maximum
    if(inputLength>MAX_CHARS){
        // Print error message
        printf("invalid\n");
        // Exit gracefully
        return 0;
    }

    // Calculate the number of permutations expected
    nPermutations=factorial(inputLength);

    // Allocate memory for large array
    largeArray=malloc(sizeof(char*)*nPermutations);

    // If the memory allocation failed.
    if(largeArray==NULL){
        // Print error message
        printf("Memory allocation failed!");
        // Exit with problem code.
        return 1;
    }

    // Start printing requested output.
    printf("All permutations of the string %s are:  ",argv[1]);

    // Permute the string in argv[1], set start to be 0 index
    // end to be the length of array, use the largeArray to store
    // data and give the address of the arrayPosition to keep track of
    // where we should put data next.
    permute(argv[1],0,inputLength-1,largeArray,&arrayPosition);

    // From 0 until the last permutation
    for(i=0;i<arrayPosition;i++){
        // Print the permutation
        printf("%s  ",largeArray[i]);

        // Free the occupied memory for the string on the heap.
        free(largeArray[i]);
    }

    // Free the occupied heap memory for the array.
    free(largeArray);
    // Print newline
    printf("\n");

    // Exit gracefully
    return 0;
}

void swap(char* item1,char* item2){
    char item1Copy,item2Copy; // Used for copies

    // Make a copy of item1
    item1Copy=*item1;

    // Make a copy of item2;
    item2Copy=*item2;

    // Set value of item1 to be value of item2.
    *item1=item2Copy; 

    // Set value of item2 to be value of item1
    *item2=item1Copy;
}

int factorial(int number){
    // If the number is less than or eq. to 1 return 1.
    if(number<=1) return 1;
    // Call the function again with one less than before,
    // making it do n!.
    return number*factorial(number-1);
}

void permute(char*str,int start,int end,char* largeArray[],int* pos){
    // If the start == end we cannot do any more permutations, in the set/subset.
   if(start==end) {
        // Allocate memory on the heap at the current position,
        // taking the null pointer into account.
        // end is equal to the last index, so we need to increment by 1
        // to get the length of the input, but then one more time
        // to take the null pointer into account.
        largeArray[*pos]=malloc(end+2);

        // If the memory allocation failed.
        if(largeArray[*pos]==NULL){
            // Print error message
            printf("Memory allocation failed!");
            // Exit with problem code.
            return;
        }

        // Copy the string into the newly allocated memory.
        strcpy(largeArray[*pos],str);

        // Increment the position in the array
        *pos+=1;

        // Return to the original callee.
        return;
    }
    
    // From provided start until end.
    for(int i=start;i<=end;i++){ // 0 - 1
        // Swap the provided start with the current element
        swap(&str[start],&str[i]);

        // Recursively call but now make sure the current element at start,
        // is "fixed", i.e. will not move.
        permute(str,start+1,end,largeArray,pos);

        // To allow for "backtracking", trying another option if the
        // current one returns, in this case if start is equal to array.
        // Essentially we are resetting to how the array was before the swap.
        swap(&str[start],&str[i]);
    }

}