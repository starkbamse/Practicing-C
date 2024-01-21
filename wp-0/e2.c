// (C) __ Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 0
// Exercise 2
// Submission code: XXXXXX (provided by your TA-s)

//Include section
#include <stdio.h>

/*
    Purpose:
    This program takes one argument provided by the user, and
    concatenates it with the string "Hello World! - I'm %s!" and
    replaces %s with the provided argument.
*/

// Main program logic
int main(int argc, char *argv[]) {

    // The first arg is always the program's name along with its full path
    // This means that the provided arg is the second argument
    char* providedArg = argv[1];
    // Print a string to the console
    printf("Hello World! - I'm %s!\n", providedArg);

    // Returning 0 as a successful execution of the program
    return 0;
}