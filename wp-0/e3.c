// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 0
// Exercise 3
// Submission code: XXXXXX (provided by your TA-s)
// Using the stdio and string Macros, we include the declarations and definitions for 
// input/output and string functions and utilities
#include <stdio.h>
#include <string.h>

// This method provides info on the terminal when -h is typed by the user
void provideInfo(void) {
    printf("1- Please compile the programme using your compiler first");
    printf(" (note that compilation can be different on different operating systems).\n");
    printf("2- Depending on the way you have compiled the system and on your OS execute the following:\n");
    printf("    - On Windows, after compilation, you have a .exe file. You need to run this file and provide one argument.\n");
    printf("      $ [name].exe [provided argument]\n");
    printf("    - On Unix systems (Mac and Linux) you can run the program using one the following commands:\n");
    printf("      $ a.out [provided argument]\n");
    printf("      $ ./[provided name] [provided argument]\n");
    printf("3- Please note that if you use the -o flag and provide a name hen compiling using a Unix system,\n");
    printf("   then you cannot run the programme using a.out, but rather the second option only works.\n");
    printf("4- Note that you must provide only one argument. If none or more than one arguments are provided, the programme does not work.\n");
}

/**
 * This method takes two arguments. One is the number of arguments and the other 
 * the array of arguments provided to the programme. If it is more than 2,
 * then the programme prints an error message along with info on the existence of a -h flag for help.
 * The same happens if no arguments are provided. If the user enters -h as the argument,
 * then the programme provides text information regarding how the programme is used, otherwise
 * a greeting sentence is typed on the terminal by the programme.
 * @param argc The number of arguments provided to the programme
 * @param argv The array of arguments provided to the programme
*/
void validateInput(int argc, char *argv[]) {
    if (argc > 2) {
        printf("Error - More than one argument provided. Type -h for help.\n");
    } else if (argc < 2) {
        printf("Error - No argument provided. Type -h for help.\n");
    } else {
        // The first arg is always the programme's name along with its full path
        // This means that the provided arg is the second argument
        char *providedArg = argv[1];
        // strcmp(str1, str2) is used to compare two strings. It returns 0 if they are equal.
        int is_h = strcmp("-h", providedArg);
        if (is_h == 0) {
            provideInfo();
        } else {
            // Print a greeting sentence to the console
            printf("Hello World! - I'm %s!\n", providedArg);  // Note: double quotes
        }
    }
}

// Main function in the program, no program arguments supported
int main(int argc, char *argv[]) {

    // Validate the provided argument by the user and print corresponding messages
    validateInput(argc, argv);
    // Returning 0 as an succefull execuation of the programme
    return 0;
}



