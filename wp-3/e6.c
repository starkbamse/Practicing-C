// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 3
// Exercise 6
// Submission code: xxxxxxx

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define section
#define MAX_STR_LEN 20

// --- Function declaration ---
/**
 * This function copies a string into another string
 * Since the function is void, you need to pass the string that you want to copy
 * and the address of the other string that will hold the string that you want to copy
 * @param strToCopy String to be copiedStr
 * @param copiedStr Add to string variable that will hold the copy
*/
void copyStr(char *strToCopy, char **copiedStr);
// Read a string from stdin or a .txt file 
void readStr(char **strAdd);
// --- Function declaration ---

// Main function, where the program starts
int main(int argc, char *argv[]) {
    char *str; // Char pointer to hold the str inputed or read from a file
    char *strCopy1; // Variable to hold the copy achieve dusing strcpy()
    char *strCopy2; // Variable to hold the copy achieved using copiedStr()

    // Allocate memory to the string variables
    // the reason for adding one is that the last index will hold '\0'
    str = (char*)calloc(MAX_STR_LEN + 1, sizeof(char));
    strCopy1 = (char*)calloc(MAX_STR_LEN + 1, sizeof(char));
    strCopy2 = (char*)calloc(MAX_STR_LEN + 1, sizeof(char));

    // Check that memory is allocated. if not, print error msga nd exit with satus code 1
    if (str == NULL || strCopy1 == NULL || strCopy2 == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Read a string and put in str
    readStr(&str);
    // Print str
    printf("original: %s\n", str);
    // Use c strcpy() to copy the string and get the pointer which points to the str
    strCopy1 = strcpy(strCopy1, str);
    // Print the copy
    printf("Copy using string.h: %s\n", strCopy1);
    // Use own method to copy the string
    copyStr(str, &strCopy2);
    // Print the second copy
    printf("Coyp using copyStr(): %s\n", strCopy2);

    // Free the memory
    free(str);
    free(strCopy1);
    free(strCopy2);

    // Return 0 upon finish of the program, to indicate successfull finish
    return 0;
}

void copyStr(char *strToCopy, char **copiedStr) {
    int i = 0; // Array index counter

    // Loop until the null char is seen
    while (strToCopy[i] != '\0') {
        // Copy char at i index
        (*copiedStr)[i] = strToCopy[i];
        // Increment i 
        i++;
    }
}

void readStr(char **strAdd) {
    int i = 0; // loop condition variable

    // MAx of chars to read is MAX_STR_LEN
    while (i < MAX_STR_LEN) {
        // Get char and put at pos i
        (*strAdd)[i] = getchar();
        // Increment counter
        i++;
    }
    // Insert \0 at the last index
    (*strAdd)[i] = '\0';
}
