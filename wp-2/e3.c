// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 2
// Exercise 3
// Submission code: 


/**
* This program manages a database of people. It offers the user options about writing people's data
* into a binary file and reading it in different ways.
*
* Purpose: Reading and writing to binary files.
* DIT632
* 
* 
**/


// Include section
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// -----typedefs -------
// Define a structure for a person
typedef struct {
char firstname[20]; // First name of the person
char famname[20];   // Last name of the person
char pers_number[13]; // Personal number with the format yyyymmddnnnc
} PERSON;

// Function declaration

PERSON input_record(void); // Reads a person’s record.
void write_new_file(PERSON *inrecord); // Creates a file and writes the first record
void printfile(void); // Prints out all persons in the file
void search_by_firstname(char *name); // Prints out people from the file with the given first name
void append_file(PERSON *inrecord); // Appends a new person to the file
void search_by_secondname(char *name); // Prints out people from the file with the given family name

// Main function of the program
int main(void){
// Variable declarations
PERSON ppost; // Creates a person pointer
int option; // The option the user chooses

    do { // Do the following as long as the input is between 1 and 4. (5 exits the program)
    // Print the menu with option 1-5.
    printf("\nChoose one of the following: \n 1. Create a new and delete the old file.\n 2. Add a new person to the file.\n 3. Search for a person in the file. \n 4. Print out all in the file.\n 5. Exit the program.\n");

    // Save the user's answer in the option variable.
    scanf("%d", &option); 
    // Clear buffer
    while (fgetc(stdin)!= '\n');
    // Depending on the option, select the case.
    switch(option) {
        // If the users chooses option 1 
        case 1: 
        // Set first name of the person structure to John.
        strcpy(ppost.firstname, "John");
        // Set family name of the person structure to Doe.
        strcpy(ppost.famname, "Doe");
        //Set personnummer of the person structure.
        strcpy(ppost.pers_number, "200001011234");

        // Write a new file and pass in the created person.
        write_new_file(&ppost);
        break; 

        // If the user chooses option 2.
        case 2:
            // Call the input record method which lets the user to input the person details.
            ppost = input_record();
            // Append this person to the file.
            append_file(&ppost);
            break; 
        // If the user chooses option 3.
        case 3:
            printf("Choose below through which option you would like to search for a person in the file\n");
            // If the user chooses 1, they can search by first name
            printf("1. Search by first name.\n");
            // If the user chooses 2, they can search by family name
            printf("2. Search by second name.\n"); 

            int choice; // Choice of the user
            char name[20]; // The user inputted name

            //Scan and save their choice
            scanf("%d", &choice);
            // Clear buffer
            while (fgetc(stdin)!= '\n');
            // If the user chooses 1
            if(choice == 1) {
                //Ask the user to enter the first name of the person they want to search for in the file
                printf("Enter the first name of the person you are searching for: \n");

                // Save the inputted name in the name variable.
                scanf("%s", name);
                // Clear buffer
                while (fgetc(stdin)!= '\n');
                // Search for that name in the file.
                search_by_firstname(name);
            } 
            // If the user chooses 2
            else if(choice == 2) {
                //Ask the user to enter the last name of the person they want to search for in the file
                printf("Enter the second name of the person you are searching for: \n");

                // Save the inputted name in the name variable.
                scanf("%s", name);
                // Clear buffer
                while (fgetc(stdin)!= '\n');
                // Search for that name in the file.
                search_by_secondname(name);

            } else {
            // If the choice is not valid. print error message.
                printf("Invalid choice!! Please enter either 1 or 2.");
                return 0;
            }
            break; 
        // If the user chooses 4
        case 4: 
            //Print out all people in the file
            printfile();  
            break;
    }
    //Do that as long as the input is between 1 and 4 (5 and other inputs exit the program).
    } while (option >= 1 && option <= 4);
    
return(0);
}

// This function creates a new binary file, it takes as parameter a person and writes it to the file.
void write_new_file(PERSON *inrecord){
    // Create opening for the file
    FILE *file; 
    // Open the file and call it database.bin
    file = fopen("database.bin", "wb");
    // If there is no file found, print error message and return.
    if(file == NULL){
        printf("Error opening the file");
        return;
    }
    // Write the person from the method parameters to the file.
    fwrite(inrecord, sizeof(PERSON), 1, file);
    // Close the file.
    fclose(file);
}

// This method asks the user for a person's details and returns the PERSON structure.
PERSON input_record(void){
    PERSON new_person; // Declare new person

    // Ask the user to enter the user details
    printf("Enter first name: \n");

    //Assign the input to new_person's first name
    scanf("%19s", new_person.firstname);
    // Clear buffer
    while (fgetc(stdin)!= '\n');

    // Ask the user to enter the user details
    printf("Enter family name: \n");

   //Assign the input to new_person's familu name
    scanf("%19s", new_person.famname);
    // Clear buffer
    while (fgetc(stdin)!= '\n');

    // Ask the user to enter the user details
    printf("Enter the person's social security number(ssn): \n");

    // Assign the inserted social security number to the new_persons pers_number
    scanf("%12s", new_person.pers_number); 
    // Clear buffer
    while (fgetc(stdin)!= '\n');

    // Return the new person
    return new_person;
}

// This method appends a person that is passed in the method parameters to the file.
void append_file(PERSON *inrecord){
    // Create opening for the file
    FILE * file;
    // Open the binary file
    file = fopen("database.bin", "ab");
    // If the file is not found, print error message and return.
    if (file == NULL){
        printf("Unable to open the file \n");
        return;
    }
    // Write the person from the method parameters to the file.
    fwrite(inrecord, sizeof(PERSON), 1, file);
    // Close the file.
    fclose(file);
}



// This method prints all the people and their information in the file.
void printfile(void){
    // Create opening for the file
    FILE * file;

    int records=0; // Number of records in the file

    // Open the binary file
    file = fopen("database.bin", "rb");
    // If the file is not found, print error message and return.
    if (file == NULL){
        printf("Unable to open the file \n");
        return;
    }

    // Declare person pointer.
    PERSON *person;
    //Allocate memory to the person
    person  = malloc(sizeof(PERSON));

    // Check for errors in allocating memory.
    if (person == NULL) {
        printf("Error allocating memory.\n");
        return;
    }



    //While there is a record to read in the file of a person
    while (fread(person, sizeof(PERSON), 1, file) == 1) {
        //Printing the first name of the person record found
        printf("First name: %s\n", person -> firstname);
        //Printing the family name of the person record found
        printf("Family name: %s\n", person -> famname);
        //Printing the personal number of the person record found
        printf("Personal number: %s\n\n", person -> pers_number);
        records++;
    }

    // Check if the file is empty
    if(!records) {
        // Print a message that the list is empty.
        printf("\nInput file is empty.\n");
    }

    //Close the file
    fclose(file);
    //Free the memory allocated in the heap for the reading of each record.
    free(person);
}

// This method prints out all of the people from the file that match the first name passed in the method parameters.
void search_by_firstname(char *name){
    // Create opening for the file
    FILE * file;
    // Declare person pointer.
    PERSON * person;
    // Allocate memory to the person
    person = malloc(sizeof(PERSON));
    // Initialise number of matcher to 0.
    int num_matches = 0;
    // Check for errors in allocating memory.
    if (person == NULL) {
        printf("Error allocating memory.\n");
        return;
    }
    // Open the binary file
    file = fopen("database.bin", "rb");
    // Check for errors in opening the file, if not found, print error message and return.
    if (file == NULL){
        printf("Unable to open the file \n");
        return;
    }

    //While there is a record to read in the file of a person
     while (fread(person, sizeof(PERSON), 1, file) == 1) {
        //Checking whether the first name of the person read equals the first name provided by the user
        if (strcmp(person -> firstname, name) == 0) {
            //If the first name or last name of the user read and the name provided match then print all of the attributes of that person
            //Print the first name of the person record found
            printf("\nFirstname: %s\n", person -> firstname);
            //Print the family name of the person record found
            printf("Famname: %s\n", person -> famname);
            //Print the personal number of the person record found
            printf("Personal Number: %s\n", person -> pers_number);
            //Increment the number of matches
            num_matches++;
        }
    }
    // If there are no matches found, print appropriate message.
    if (num_matches == 0) {
        printf("\n%s not found.\n\n", name);
    } else {
        //Print the number of matches found
        printf("\n%d matches found.\n\n", num_matches);
    }
    //Close the file
    fclose(file);
    //Freeing the memory allocated in the heap
    free(person);

}



void search_by_secondname(char *name){
    // Create opening for the file
    FILE * file;
    // Declare person pointer.
    PERSON * person;
    // Allocate memory to the person
    person = malloc(sizeof(PERSON));
    // Initialise number of matcher to 0.
    int num_matches = 0;
    // Check for errors in allocating memory.
    if (person == NULL) {
        printf("Error allocating memory.\n");
        return;
    }
    // Open the binary file
    file = fopen("database.bin", "rb");
    // Check for errors in opening the file, if not found, print error message and return.
    if (file == NULL){
        printf("Unable to open the file \n");
        return;
    }

    //While there is a record to read in the file of a person
     while (fread(person, sizeof(PERSON), 1, file) == 1) {
        //Checking whether the family name of the person read equals the name provided by the user
        if (strcmp(person -> famname, name) == 0) {
            //If the first name or last name of the user read and the name provided match then print all of the attributes of that person
            //Print the first name of the person record found
            printf("\nFirstname: %s\n", person -> firstname);
            //Print the family name of the person record found
            printf("Famname: %s\n", person -> famname);
            //Print the personal number of the person record found
            printf("Personal Number: %s\n", person -> pers_number);
            //Increment the number of matches
            num_matches++;
        }
    }
    // If there are no matches found, print appropriate message.
    if (num_matches == 0) {
        printf("\n%s not found.\n\n", name);
    } else {
        //Print the number of matches found
        printf("\n%d matches found.\n\n", num_matches);
    }
    //Close the file
    fclose(file);
    //Freeing the memory allocated in the heap
    free(person);

}