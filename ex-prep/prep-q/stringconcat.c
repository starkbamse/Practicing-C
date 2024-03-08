/******************************************************************************

Write a C program to concatenate two strings in single string. You cannot use the built-in function
here. You should use dynamic memory allocation at the heap

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initial memory allocation on the heap
#define INITIAL_MEMORY_ALLOCATION 10

// Used to read input from the user
char* readInput();

// Used to concatenate two strings
char* concatenateString(char* string1, char* string2);
int main()
{
    char* string1; // First string
    char* string2; // Second string
    char* concatenatedString; // Concatenated string
    // Prompt the user
    printf("Input string1: ");
    
    // If the return value is NULL
    if( (string1=readInput())==NULL ) {
        // Exit with code 1
        return 1;
    }
    // Prompt the user
    printf("Input string2: ");
    
    // If the return value is NULL
    if( (string2=readInput())==NULL ) {
        // Exit with code 1
        return 1;
    }
    
    concatenatedString=concatenateString(string1,string2);
    // Print the concatenated string
    printf("Concatenated string: %s\n",concatenatedString);
    
    // Free memory on heap
    free(string1);
    // Free memory on heap
    free(string2);
    // Free memory on heap
    free(concatenatedString);

    // Exit gracefully
    return 0;
}

char*concatenateString(char* string1, char*string2){
    int i; // To keep track of where we are in loop
    int position; // The position of the new string
    // The combined length of both strings and the null terminator
    int combinedLength=strlen(string1)+strlen(string2)+1; 
    
    // Allocate memory for the new string on the heap
    char* combined=malloc(combinedLength);
    
    // If memory allocation failed
    if(combined==NULL){
        // Print error message
        printf("Memory allocation failed!\n");
        // Return null pointer
        return NULL;
    }
    
    // From 0 to the end of the first string
    for(i=0;i<strlen(string1);i++){
        // Set the string at index i to current pos. of the new string
        combined[position]=string1[i];
        // Increment position index in new string
        position++;
    }
    // From 0 to the end of the second string
    for(i=0;i<strlen(string2);i++){
        // Set the string at index i to current pos. of the new string
        combined[position]=string2[i];
        // Increment position index in new string
        position++;
    }
    
    // Return the new string
    return combined;
}

char* readInput(){
    // Allocation for the dyn. memory
    size_t allocation=INITIAL_MEMORY_ALLOCATION;
    int position=0; // The position index of the string
    int c; // The current char

    // Users input allocated on heap
    char* intoString=malloc(allocation);
    // If memory allocation failed
    if(intoString==NULL){
        // Print error message
        printf("Memory allocation failed!\n");
        // Return null pointer
        return NULL;
    }
    
    // While the current char is not a newline nor EOF    
    while((c=fgetc(stdin))!='\n' && EOF){
        // If adding 1 to the positition will overflow the allocation
        if((position+1)>allocation){
            // Increase the allocation two fold
            allocation=allocation*2;
            
            // Reallocate the memory with more allocation
            intoString=realloc(intoString,allocation);
            if(intoString==NULL){
                // Print error message
                printf("Memory allocation failed!\n");
                // Return null pointer
                return NULL;
            }
        }
        // Set the char at the current index of the string
        intoString[position]=(char)c;
        // Increment the position
        position++;
    }
    
    // Return the read string.
    return intoString;
}