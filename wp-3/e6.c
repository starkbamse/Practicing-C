// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 (2024)
// Work package 3
// Exercise 5
// Submission code: 

#include <stdio.h>
#include <string.h>

/* The method body of the copystring() function, that copies contents from one string to another */
void copystring(char copy[], char input[]) {
   
    int i = 0;  // Index of the loop

    // Loop as long as the input string is not empty
    do {
        // Add the current character to the copy string
        copy[i] = input[i];
        // Go to the next character
        i++; 
    } 
    // Do it as long as the end of string character is encountered.
    while(input[i] != '\0'); 
    copy[i] = '\0';
}

int main(int argc, char * argv[])
{
    char input[21]; // User inputted string of 20 characters - end of string character
    char copy1[21]; // Copy of the user inputted string using strcopy
    char copy2[21]; // Copy of the user inputted string using our own method


    printf("\nEnter a string (maximum 20 characters): ");
    // Scan the input and save it in the variable.
    scanf("%s", input);

    // Check if the input is too long
    if(strlen(input) > 20) {
        // Print error message and return with error code.
        printf("Enter a maximum of 20 characters. \n");
        return 1;
    }
    

    // Print the received input
    printf("\nReceived string: %s\n", input);


    // Copying the input string to the variable "copy"
    strcpy(copy1, input);
    // Print the copied string.
    printf("Copied string via strcpy(): %s\n", copy1);
    // Call the method copystring to make a copy of the inputted string.
    copystring(copy2, input);
    printf("Copied string via copystring() method: %s\n", copy2);

    /* End of function */
    return 0;
}