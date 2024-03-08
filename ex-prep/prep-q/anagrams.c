
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INITAL_MEMORY_ALLOCATION 10

int main()
{
    // The first input string
    char* first;
    // The second input string
    char* second;
    // Dyn. mem. allocation for first string
    size_t allocationFirst;
    // Dyn. mem. allocation for second string
    size_t allocationSecond;
    // Current char
    int c;
    // Current position in first input string
    int positionFirst;
    // To keep track of where we are in array
    int i;
    // To keep track of where we are in array
    int x;
    // Current position in second input string
    int positionSecond;
    // Number of matches between the two strings
    int matches;
    
    // Set the allocation of the first input string to the defined default alloc.
    allocationFirst=INITAL_MEMORY_ALLOCATION;
    
    // Set the allocation of the second input string to the defined default alloc.
    allocationSecond=INITAL_MEMORY_ALLOCATION;
    
    // Allocate memory for the first string
    first=malloc(allocationFirst);

    // Allocate memory for the second string
    second=malloc(allocationSecond);
    
    // If memory allocation failed
    if(first==NULL || second==NULL){
        // Print error message
        printf("Failed allocating memory!\n");
        // Exit with error code
        return 1;
    }
    
    // Prompt the user
    printf("Input the first string: ");
    
    // While the current char is not a newline nor EOF
    while((c=fgetc(stdin))!='\n' && c!= EOF){
        // If an increase to the position will overflow the allocation
        if((positionFirst+1)>allocationFirst){
            // Increase allocation two-fold
            allocationFirst=allocationFirst*2;
            // Reallocate memory 
            first=realloc(first,allocationFirst);
            // If reallocation failed 
            if(first==NULL){
                // Print error message
                printf("Failed allocating memory!\n");
                // exit with error code
                return 1;
            }
        }
        // Set the char to the current position in the string
        first[positionFirst]=(char)c;
        // Increment the index
        positionFirst++;
    }
    
    // Prompt the user
    printf("Input the second string: ");
    
    // While the current char is not a newline nor EOF
    while((c=fgetc(stdin))!='\n' && c!= EOF){
        // If an increase to the position will overflow the allocation
        if((positionSecond+1)>allocationSecond){
            // Increase allocation two-fold
            allocationSecond=allocationSecond*2;
            // Reallocate memory 
            second=realloc(second,allocationSecond);
            // If reallocation failed 
            if(second==NULL){
                // Print error message
                printf("Failed allocating memory!\n");
                // exit with error code
                return 1;
            }
        }
        // Set the char to the current position in the string
        second[positionSecond]=(char)c;
        // Increment the index
        positionSecond++;
    }
    
    // Number of checked characters in the first string
    char checkedChars[positionFirst];
    
    // Loop through the first string    
    for(i=0;i<positionFirst;i++){
        // Loop through the second string
        for(x=0;x<positionSecond;x++){
            // If the first and second element are matching
            // and the element has not been checked before
            if(first[i]==second[x] && first[i]!=checkedChars[i]){
                // Increment matches                
                matches++;
                // Add the char to the checkedChars array
                checkedChars[i]=first[i];
            } 
        }
    }
    
    // If n matches dont match the first string
    if(matches != positionFirst){
        // print 
        printf("%s and %s are not Anagram\n",first,second);
    } else {
        printf("%s and %s are Anagram\n",first,second);

    }
    free(first);
    free(second);
    
    

    return 0;
}
