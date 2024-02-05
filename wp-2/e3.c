// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 2
// Exercise 3
// Submission code: xxxxxxx (provided by your TA-s)

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

// Define section
#define FILE_NAME "persons"

// --- Type definitions ---
// Struct to define a person's abstraction
// There are limits on the length of first name and last name.
// Personnumer is 13 chars (including the hyphen)
typedef struct {
    char firstName[21];
    char lastName[21];
    char prsonNumer[14];
} PERSON;
// --- Type definitions ---

// --- Function declarations ---
// This function reads person data inputed by the user
PERSON input_record(void);
// Clear extra chars from the buffer
void clearBuffer(void);
// Creates a new file and writes the first record in it
void write_new_file(PERSON *inrecord);
// Prints out all persons in the file
void printFile(void);
// Prints out the person with given first name, if in the list
void search_by_firstname(char *name);
// Appends a new person to the file
void append_file(PERSON *inrecord);
// Does the file exist?
int doesFileExist(void);
// Validate personnumer
int isValidPrNum(char *prNum);
// Print the menu and options the user can take
void printMenu(void);
// --- Function declarations ---

/**
 * This program keeps a database of PERSONS (whihc have first name, last name, and personnumer)
 * in form of a binary file. There are operations that the programe supports including
 * reading from the binary file, searching based on first name, writing user input to the file,
 * deleting the file and creating a new one, and appending new PERSONS to the file.
*/

int main (void) {
    PERSON person; // Variable that holds the data used to save a person
    int exitPro = 1; // Variable to see if the user wants how exist the programe
    int chosenOption = 0; // Variable to save the option chosen by the user, initialised by 0
    char searchName[21]; // Variable to save the search name used by the user

    // Ask the user for input
    do {
        // Print the menu
        printMenu();
        // Get user's chosen option
        scanf("%d", &chosenOption);
        // Go to the next line
        printf("\n");
        // Clear the buffer for future input taking
        clearBuffer();

        // Using a switch case, and based on the option inputed by the user, different menu options are executed
        switch (chosenOption) {
            case 1: 
                // Get person input from the user
                person = input_record();
                // Overwrite the file and add the new input
                write_new_file(&person);
                break;
            case 2:
                // Get person input from the user
                person = input_record();
                // Append the input
                append_file(&person);
                break;
            case 3:
                // Ask the user to give you a first name to search
                printf("Enter the first-name by which you want to search the database.\n");
                // Read the name
                scanf("%20s", searchName);
                // Clear buffer for future input taking
                clearBuffer();
                // Search using the name the user entered
                search_by_firstname(searchName);
                break;
            case 4:
                // Print all there is in the file
                printFile();
                break;
            case 5:
                // Set exitPro to 0, to indicate that the program has finished
                exitPro = 0;
                break;
            default:
                printf("Please enter a number between and including 1 and 5.\n");
                break;
        }
    } while (exitPro);

    // Upon program finish, return 0 to indicate successful finish.
    return 0;
}

PERSON input_record(void) {
    PERSON pr; // Variable to hold the attributes of a person inputed by the user

    // Print the prompt to the user
    printf("Please enter the person's first name:\n");
    // Get user input. Note that first name cannot be more than 21 chars
    // Last char is \0. So read only 20 chars
    scanf("%20s", pr.firstName);
    // Set the null char as the last char
    pr.firstName[20] = '\0';

    // Clear the buffer before reading again.
    clearBuffer();

    // Print the prompt to the user
    printf("Please enter the person's last name:\n");
    // Get user input. Note that last name cannot be more than 21 chars
    // Last char is \0. So read only 20 chars
    scanf("%20s", pr.lastName);
    // Set the null char as the last char
    pr.lastName[20] = '\0';

    // Clear the buffer before reading again.
    clearBuffer();

    do {
        // Print the prompt to the user
        printf("Please enter the person's personnumer:\n");
        // Get user input. Note that personnumer cannot be more than 14 chars
        // Last char is \0. So read only 13 chars
        scanf("%13s", pr.prsonNumer);
        // Set the null char as the last char
        pr.lastName[13] = '\0';

        // Clear the buffer before reading again.
        clearBuffer();

    } while (isValidPrNum(pr.prsonNumer) == 0);

    // Return the person inputed
    return pr;
}

void clearBuffer(void) {
    char temp; // Variable to hold the char read from stdin

    // Read chars until you reach \n
    while ((temp = getchar()) != '\n');
}

void write_new_file(PERSON *inrecord) {
    FILE *file; // Variable to hold the file pointer

    // Create a binary file called FILE_NAME for writing and reading
    // If the file already exists, its content are overwritten
    file = fopen(FILE_NAME, "wb+");
    // Add the given person data to the file
    fwrite(inrecord, sizeof(PERSON), 1, file);
    // Close the file
    fclose(file);
}

void printFile(void) {
    PERSON record; // Variable to hold the record read from the file
    FILE *file; // Pointer to the file that is being read
    size_t readVal; // Variable used to save the returned by fread()
    int personCounter = 1; // Variable to refer to the number of person read, initialise with 1

    // Open the file
    file = fopen(FILE_NAME, "rb+");

    // If file was not opened, an error has happened. The file must exist
    if (file == NULL) {
        printf("The file des not exist, please try again.");
        return;
    }

    // Read from the file until the end of the file is reached
    while (feof(file) == 0) {
        // Read one person from the file 
        readVal = fread(&record, sizeof(PERSON), 1, file);
        // If person data was read correctly, then print it
        // fread() returns 0 if an error happens or end of file is reached
        if (readVal) {
            // Print the person read and increment the number of persons for later prints
            printf("Person number %d:\nFisrt-name: %s\nLast-name: %s\nPersonnumer: %s\n", 
            personCounter++, record.firstName, record.lastName, record.prsonNumer);
        }
    }

    // Close the file
    fclose(file);
}

void search_by_firstname(char *name) {
    PERSON record; // Variable to hold the record read from the file
    FILE *file; // Pointer to the file that is being read
    size_t readVal; // Variable used to save the returned by fread()
    int personCounter = 1; // Variable to refer to the number of person read, initialise with 1

    // If the lnegth of the string is greater than 20, then print error message and return
    if (strlen(name) > 20) {
        printf("Name provided was too large, provide a name that has less than 20 chars.\n");
        return;
    }

    // Open the file
    file = fopen(FILE_NAME, "rb+");

    // If file was not opened, an error has happened. The file must exist
    if (file == NULL) {
        printf("The file des not exist, please try again.");
        return;
    }

    // Read from the file until the end of the file is reached
    while (feof(file) == 0) {
        // Read one person from the file 
        readVal = fread(&record, sizeof(PERSON), 1, file);
        // If person data was read correctly, then proceed to logic used on the record
        // fread() returns 0 if an error happens or end of file is reached
        if (readVal) {
            // If the record read has the same first name as one provided to the function, then print it
            if (strcmp(name, record.firstName) == 0) {
                // Print the person read and increment the number of persons for later prints
                printf("Person number %d:\nFisrt-name: %s\nLast-name: %s\nPersonnumer: %s\n", 
                personCounter++, record.firstName, record.lastName, record.prsonNumer);
            }
        }
    }

    // Close the file
    fclose(file);
}

int doesFileExist(void) {
    FILE *file; // Variable to hold the pointer to the file

    // Open the file
    file = fopen(FILE_NAME, "rb");

    // If the file does not exist, NULL is returned
    if (file == NULL) {
        printf("The file does not exist, please create a file.\n");
        return 0;
    }

    // Close the file
    fclose(file);

    // Return 1 to indicate that the file exists
    return 1;
}

void append_file(PERSON *inrecord) {
    FILE *file; // Variable to hold the pointer to the file

    // If the file does not exist, exit the function
    if (!doesFileExist()) return;

    // Open the file in append mode
    file = fopen(FILE_NAME, "ab");

    // Add the given person data to the file
    fwrite(inrecord, sizeof(PERSON), 1, file);

    // Close the file
    fclose(file);

}

int isValidPrNum(char *prNmr) {
    regex_t regEx; // Variable to hold the regEx expression
    int regComValue; // Variable to hold the compilation return valye of the regEx creation
    int matchVal; // Variable to hold the match value

    // Compile the reg expression
    regComValue = regcomp(&regEx, "^([0-9]+)(-)([0-9]+)$", REG_EXTENDED);

    // If the compilation goes right, 0 is returned
    // If complation fails, print error msg and exit
    if (regComValue != 0) {
        printf("RegEx compilation failed, exiting...\n");
        exit(1);
    }

    // Check if the personnumer maches the regex
    // If it does, 0 is returned
    matchVal = regexec(&regEx, prNmr, 0, NULL, 0);

    if (matchVal != 0) {
        // Match failed
        // return 0 to indicate bad input
        return 0;
    }

    // Personnumer matched regEx, return 1
    return 1;
}

void printMenu(void) {
    // Print the menu
    printf("Please enter one of the below options:\n\n");
    printf("1 Create a new and delete the old file.\n");
    printf("2 Add a new person to the file.\n");
    printf("3 Search for a person by their first name in the file.\n");
    printf("4 Print out all in the file.\n");
    printf("5 Exist the program.\n\n");
    printf("Your option: ");
}