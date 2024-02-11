// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 3
// Exercise 6
// Submission code:

//Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #include <io.h>
#else
    #include <unistd.h>
#endif

//Define section
#define MAX_CHARS 20 // Maximum number of chars in the string.
//Main program section

/**
* This program allows the user to input a string either
* through the terminal or using input redirection.
* The string is then copied to another string and
* outputted to the user.
* 
* Purpose: To practice input redirection in C as well
* as the process of copying strings.
* DIT632
* 
**/

// Copies a string from its source to destination.
void copyString(char* src,char*dest);

int main(int argc, char* argv[]) {
    // Variable declarations
    char* input=malloc(MAX_CHARS+1); // Users input on heap
    char* copiedString=malloc(MAX_CHARS+1); // The copied string on heap
    char* copiedString2=malloc(MAX_CHARS+1); // The 2nd copied string on heap

    // If memory allocation failed
    if(input==NULL || copiedString==NULL){
        // Print error message
        printf("Memory allocation has failed.\n");
        // Exit with problem code
        return 1;
    }

    // If on windows
    #ifdef _WIN32
    // Get the file descriptor of stdin and then
    // Check if that file descriptor is a TTY (teletype writer)
    if (_isatty(_fileno(stdin))) {
        // Print to stdout
        printf("Enter string, (max %d characters): ",MAX_CHARS);
    }
    #else // On other systems (unix assumed)
    // Check if the standard input is a TTY (teletype writer)
    if (isatty(STDIN_FILENO)) { 
        // Print to stdout
        printf("Enter string, (max %d characters): ",MAX_CHARS);
    }
    #endif

    // Read 20 characters
    scanf("%20s",input);

    // Copy the received string using a builting method.
    strcpy(copiedString,input);

    // Copy the received string into the new string.
    copyString(input,copiedString2);
    
    // Print the string to stdout
    printf("strcpy: %s\n",copiedString); 

    // Print the string to stdout
    printf("copyString: %s\n",copiedString); 

    // Free occupied heap memory.   
    free(input);
    free(copiedString);
    free(copiedString2);

    // Exit gracefully
    return 0;
}

void copyString(char*src,char*dest){
    // While the src pointer does not point to null terminator
    while(*src!='\0'){
        // Set the value of src to be value of destination
        *dest=*src;
        // Increment pointer
        src++;
        // Increment pointer
        dest++;
    }
}