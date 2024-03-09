/******************************************************************************

Write a program in C that reads 10 strings from a console, stores them in an array and finds the
shortest string in the array.

The program should contain a function that takes as parameter the array, find the shortest string,
remove it and return the array that is shorter by one element.

The program should read the strings from the console.

The program should have a separate function for finding and removing the string.

The program should write the string that has been removed to the console. 

The program should
also write all elements of the array before and after removal of the shortest string.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITAL_MEMORY_ALLOCATION 10
#define MAX_STRINGS 10

char** removeShortest(char** array);

int main()
{
    int i; // To keep track of where we are in loop
    int x; // To keep track of where we are in loop
    int c; // Current char we are working on
    int position; // Position in array
    size_t allocation; // N bytes we allocate to the string
    char** stringArr=malloc(MAX_STRINGS*sizeof(char*)); // Allocate memory for the strings
    
    // If the allocation failed
    if(stringArr==NULL){
        // Print error message
        printf("Failed allocating memory \n");
        // Exit gracefully
        return 0;
    }
    // Loop through all strings
    for(i=0;i<MAX_STRINGS;i++){
        // Set init position to 0 in the string
        position=0;
        // Set/reset initial allocation
        allocation=INITAL_MEMORY_ALLOCATION;
        
        // Allocate heap memory for the string
        stringArr[i]=malloc(allocation);
        // If the allocation failed
        if(stringArr[i]==NULL){
            // Print error message
            printf("Failed allocating memory \n");
            // Loop through previous allocations
            for(x=0;x<i;x++){
                // Free the previous allocations
                free(stringArr[i]);
                // Free array
                free(stringArr);
            }
            // Exit gracefully
            return 0;
        }
        // Prompt the user
        printf("Enter string %d: ",i+1);
        
        // While the current char is not a newline nor eof
        while( (c=fgetc(stdin))!='\n' && c!=EOF ){
            // If an increase to the position will overflow the allocation
            if((position+2)>allocation){
                printf("realloc\n");
                // Increase the allocation two-fold
                allocation=allocation*2;
                // Reallocate the string with more memory on heap
                stringArr[i]=realloc(stringArr[i],allocation);
                // If reallocation failed
                if(stringArr[i]==NULL){
                    // Print error message
                    printf("Failed allocating memory \n");
                    // Loop through previous allocations
                    for(x=0;x<i;x++){
                        // Free previous allocations
                        free(stringArr[i]);
                        // Free array
                        free(stringArr);
                    }
                    // Exit gracefully
                    return 0;
                }
            }
            // Set the current char to be in the current position in the element in the string
            stringArr[i][position]=(char)c;
            stringArr[i][position+1]='\0';
            // Increment the position
            position++;
        }
    }
    
    // Loop through all the strings
    for(i=0;i<MAX_STRINGS;i++){
        // Print each string
        printf("%s\n",stringArr[i]);
    }
    
    // Remove the shortest string
    stringArr=removeShortest(stringArr);
    
    // If the string returned is null it means there was an error
    if(stringArr!=NULL){
        // Loop through all strings
        for(i=0;i<MAX_STRINGS-1;i++){
            // Print the string
            printf("%s\n",stringArr[i]);
            // Free the string from heap after printing
            free(stringArr[i]);
        }
        // Free the occupied mem for array
        free(stringArr);
    } else {
        // Print error message
        printf("An error occurred.\n");
    }

    // Exit gracefully
    return 0;
    
}


char** removeShortest(char** array){
    int i; // To keep track of where we are in loop
    int shortestAt=-1; // The index of shortest element
    int shortestLength=-1; // The shortest length in array
    int x; // To keep track of where we are in loop
    int position=0; // The position of the new array
    char** modArray=malloc((MAX_STRINGS-1)*sizeof(char*)); // Allocate memory for the new array
    // If allocation failed
    if(modArray==NULL){
        // Print error message
        printf("Failed allocating memory \n");
        // Return null signifying error
        return NULL;
    }
    
    // Loop through all strings
    for(i=0;i<MAX_STRINGS;i++){
        // If the current element is shortest than the shortest or if shortest is -1
        if(strlen(array[i])<shortestLength || shortestLength==-1){
            // Set the shortest length to be the current element
            shortestLength=strlen(array[i]);
            // Set the index of the shortest element
            shortestAt=i;
        }
    }
    // Print which string we will remove
    printf("Removed shortest string: %s\n",array[shortestAt]);
    
    // Loop through all strings
    for(i=0;i<MAX_STRINGS;i++){
        // If we are not at the shortest element
        if(i!=shortestAt){
            // Allocate heap memory for the new string and make space for null term.
            modArray[position]=malloc(strlen(array[i])+1);
            
            // If the allocation failed
            if(modArray[position]==NULL){
                // Loop through previous allocations in new array
                for(x=0;x<position;x++){
                    // Free occupied heap memory from new array
                    free(modArray[x]);
                }
                
                // Loop through the rest of the strings in the old array
                for(x=i;x<MAX_STRINGS;x++){
                    // Free occupied heap memmory from old array
                    free(array[x]);
                }
                
                // Free the old array's occupied memory
                free(array);
                
                // Print error message
                printf("Failed allocating memory \n");
                
                // Return null signifying error
                return NULL;
            }
            
            // Copy the string from old array to the new array
            strcpy(modArray[position],array[i]);
            
            // Free the old string 
            free(array[i]);
            
            // Increment position index
            position++;
        }
    }
    
    // Free the old array
    free(array);

    // Return the new array
    return modArray;
    
    
    
}

