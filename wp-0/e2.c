// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 0
// Exercise 2
// Submission code: XXXXXX (provided by your TA-s)
#include <stdio.h>

// Main function in the program, no program arguments supported
int main(int argc, char *argv[]) {

    // The first arg is always the programme's name along with its full path
    // This means that the provided arg is the second argument
    char* providedArg = argv[1];
    // Print a string to the console
    printf("Hello World! - I'm %s!\n", providedArg);  // Note: double quotes

    // Returning 0 as an succefull execuation of the programme
    return 0;
}