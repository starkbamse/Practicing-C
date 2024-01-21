// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 0
// Exercise 3
// Submission code: XXXXXX (provided by your TA-s)

//Include section
#include <stdio.h>
#include <string.h>

//Main program section
/*
    Purpose:
    This program takes one argument provided by the user, and
    concatenates it with the string "Hello World! - I'm %s!" and
    replaces %s with the provided argument. If the user uses the -h argument
    then the program will display a help message. If no argument or more than one
    argument was used, an error message will be displayed.
*/

// This method provides info on the terminal when -h is typed by the user
void provideInfo(void) {
    printf("This program can print a help message\n");
    printf("In order to use this program, write ./a.out <YourName> (Unix) and ./e3.exe <YourName>\n");
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
        // The first arg is always the program's name along with its full path
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
    // Returning 0 as a successful excution of the program
    return 0;
}



