#include <stdio.h>
#include <stdlib.h>

#define INITAL_MEMORY_ALLOCATION 10 // Inital bytes allocated to heap

int main()
{
    // To store the current heap allocation
    size_t allocation;
    // To store the input
    char* userInput;
    // Defined vowels in the alphabet
    char vowels[]={'a','o','u','e','i','y'};
    // N found vowels
    int vowelsCount;
    // N found consonants
    int consonantsCount;
    
    // The current char that user entered
    int c;
    
    // Position in the string
    int position=0;
    
    // Set the initial allocation
    allocation=INITAL_MEMORY_ALLOCATION;
    
    // Request to allocate memory on heap
    userInput=malloc(allocation);

    // If memory allocation failed
    if(userInput==NULL){
        // Print error message
        printf("Memory allocation failed!\n");
        // Exit with error code
        return 1;
    }
    
    // Prompt the user
    printf("Input a string: ");
    
    // While the current char is not a newline or EOF
    while ((c=fgetc(stdin))!='\n' && c!= EOF) {
        // If adding to the string will overflow the allocated memory
        if((position+1)>allocation){
            // Increase the allocation by two-fold
            allocation=allocation*2;
            // Attempt to reallocate memory
            userInput=realloc(userInput,allocation);
        }
        // If memory allocation failed
        if(userInput==NULL){
            // Print error message
            printf("Memory allocation failed!\n");
            // Exit with error code
            return 1;
        }
    
        // Set the current char at the current position in the string
        userInput[position]=(char)c;
        
        // Increment the position
        position++;
    }
    
    // From 0 to the end of the string
    for(int i=0;i<position;i++){
        // Assume it is not a vowel
        int isVowel=0;
        
        // Loop through all the vowels
        for(int j=0;j<sizeof(vowels);j++){
            // If the current user input is a vowel
            if(userInput[i]==vowels[j]){
                // Increment the vowel count
                vowelsCount++;
                // Prove the previous assumption false
                isVowel=1;
                // Go to next iteration in loop
                continue;
            }
        }
        // If the character is not a vowel
        if(!isVowel){
            // Increment consonants
            consonantsCount++;
        }
    }
    // Print the number of vowels
    printf("Number of vowels: %d\n",vowelsCount);
    
    // Print the number of consonants
    printf("Number of consonants: %d\n",consonantsCount);
    
    // Free the occupied heap memory
    free(userInput);
    
    // Exit gracefully
    return 0;
}
