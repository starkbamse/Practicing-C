//Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define section
#define FIRST_NAME_LENGTH 20 // Max length of the first name
#define FAM_NAME_LENGTH 20 // Max length of the family name
#define PERS_NUMBER_LENGTH 13 // Max length of the personal number
#define PROMPT_DESCRIPTION_LENGTH 50 // Max length of descriptions / user prompts
#define FILE_MODE_LENGTH 2 // Max length of file open mode specification
#define DEFAULT_DB_NAME "users.db" // Default name of the database file

//Main program section

/**
* This program allows the user to handle and manage
* a limited database that allows storing first name,
* last name and a personal number. It allows the creation,
* addition and searching of users in the database.
* 
* Purpose: To create a miniature DBMS in C.
* DIT632
* 
**/

// -----typedefs -------
typedef struct {
    char firstname[FIRST_NAME_LENGTH]; // First name of the user 
    char famname[FAM_NAME_LENGTH]; // Family name of the user
    char pers_number[PERS_NUMBER_LENGTH]; // yyyymmddnnnc
} PERSON;

typedef struct {
    char option[PROMPT_DESCRIPTION_LENGTH]; // A description of the menu option.
    void(*handler)(); // The handler function for the option
} OPTION;

typedef struct {
    PERSON* records; // A pointer to all the records.
    size_t recordSize; // The number of records.
} dbRecords;

// Function declaration (to be extend)

// Reads a person’s record.
PERSON input_record(void);

// Creates a file and writes the first record
void write_new_file(PERSON *inrecord); 

// Prints out all persons in the file
void printfile(void); 

// Prints out the person if in list
void search_by_firstname(char *name); 

// appends a new person to the file
void append_file(PERSON *inrecord); 

// Used to dynamically print the menu.
void printMenu(OPTION * options,int * arraylen); 

// Wrapper function for adding a new person to the list.
void add_person();

// Wrapper function for searching for a person in the list.
void search_record();

// Wrapper function for creating a new file
void write_file();

// Function for reading from the database.
dbRecords readDB();

// Function for writing to the database.
void writeDB(PERSON*record,char mode[FILE_MODE_LENGTH]);

// Helper function to print the records.
void printRecord(PERSON*record);

// Reads n characters into a pointer omitting the newline character.
void readIntoPointer(char prompt[PROMPT_DESCRIPTION_LENGTH],char*dest,int length);

int main(int argc,char*argv[]){
    // Variable declarations
    int doRun=0; // If this is 1 we shall show the menu again.
    int nOptions; // Number of menu options.
    OPTION menuOptions[] = {
        {
            "Create a new and delete the old file.", // Option description
            &write_file // Handler function for creating files
        },
        {
            "Add a new person to the file.", // Option description
            &add_person // Handler function for adding persons
        },
        {
            "Search for a person in the file.", // Option description
            &search_record // Handler function for searching
        },
        {
            "Print out all in the file.", // Option description
            &printfile // Handler for dumping db to stdout
        }
    };

    // The size of the entire struct divided by the size of a single struct
    // yields the number of menu options.
    nOptions=sizeof(menuOptions)/sizeof(OPTION); 

    // Program logic

    // Runs at least once.
    do {  

        // Print the menu
        printMenu(menuOptions,&nOptions);

        // Read an integer from stdin.
        scanf("%d",&doRun);

        // Purge the buffer from newlines or EOF.
        while(fgetc(stdin)!='\n' && fgetc(stdin)!=EOF );

        // If user's option is within the boundaries of the array.
        if((doRun-1)<nOptions){
            // Access the users selected element and call its handler function.
            (menuOptions+(doRun-1))->handler();
        }
    } while (doRun<=nOptions); // As long as doRun is less than the number of options

    // Exit gracefully.
    return 0;
}

// Reading functions

dbRecords readDB(){
    FILE* ptr; // A pointer to the file.

    size_t allocation= sizeof(PERSON); // Initial allocation of the person.

    PERSON * records = malloc(sizeof(PERSON)); // Pointer to reserved memory.

    PERSON * head=records; // A copy of the reserved memory's beginning.

    dbRecords result; // Here we will store the result of the db read.

    ptr=fopen(DEFAULT_DB_NAME,"rb"); // Read the file in binary mode.

    if(ptr==NULL){ // If its null
        // Print error message.
        printf("Could not open file, no such file or directory.\n");
        result.records=NULL; // Set to null pointer
        result.recordSize=0; // There are no records
        return result; // Return empty data.
    }

    // As long as we have not reached the end of the file
    while(!feof(ptr)){ 

        // Fread a single record of size person
        // If fread returns a read size of > 0
        if(fread(records,sizeof(PERSON),1,ptr)){

            // Increment the allocation by the size of a person
            // to make space for the next person.
            allocation+=sizeof(PERSON);

            // Perform reallocation.
            head=realloc(head,allocation);

            // If the reallocation failed
            if(records==NULL){
                // Print error message.
                printf("Memory reallocation failed!\n");
                result.records=NULL; // Set to null pointer
                result.recordSize=0; // There are no records
                return result; // Return empty data.
            }
            // Increment the pointer, to the next address block.
            records++;
        }
    }

    // The allocation is always optimistically
    // incrementing the size of the allocation by 1,
    // since we do not know when feof call will return true.
    allocation-=sizeof(PERSON);

    // Close the file
    fclose(ptr);

    // Make the result point to the head of the allocated memory
    result.records=head;

    // Calculate the number of records by dividing the
    // reserved memory by a the size of a single PERSON.
    result.recordSize=allocation/sizeof(PERSON);

    // Return the result.
    return result;
}

void search_by_firstname(char* name){

    // Read list from database.
    dbRecords result = readDB();

    // Remember the start of the memory allocated to the list
    PERSON* head=result.records;
    
    // Keep track of where we are in loop.
    int i;

    // If the record is empty but the file exists
    if(result.recordSize==0 && result.records!=NULL){
        // Print error message.
        printf("Empty list!\n");
    }

    // From 0 to the size of all records
    for(i=0;i<result.recordSize;i++){

        // Compare if the searched string is in this record
        if(strcmp(result.records->firstname,name)==0) {
            // If it is print the record
            printRecord(result.records);

            // Free the occupied memory.
            free(head);
            free(name);
            return; // Break execution here
        }
        // Increment pointer
        result.records++;
    }
    // If we never broke execution earlier, it means
    // there was never a match found.
    printf("Could not find wanted user!\n");

    // Free the occupied memory.
    free(head);
    free(name);
}

void printfile(){

    // Read list from database.
    dbRecords result = readDB();

    // Copy the pointer to the head to remember where we are
    PERSON* head=result.records;

    // Keep track of where we are in the loop.
    int i;
    
    // If the record size if 0 but the file exists
    if(result.recordSize==0 && result.records!=NULL){
        // Print error message
        printf("Empty list!\n");
    }

    // From 0 to the size of the record
    for(i=0;i<result.recordSize;i++){
        // Print the current record
        printRecord(result.records);
        // Increment the pointer
        result.records++;
    }

    // Freee the occupied memory
    free(head);
}

void search_record(){
    // Allocate heap memory for the first name.
    char* firstName=malloc(FIRST_NAME_LENGTH);

    // Read first name
    readIntoPointer("Enter first name: ",
        firstName,
        FIRST_NAME_LENGTH
    );

    // Search by first name call.
    search_by_firstname(firstName);
}

// Writing functions

void writeDB(PERSON* record,char mode[2]) {

    FILE* ptr; // A pointer for the file
    
    // Open the file in the specified mode.
    ptr=fopen(DEFAULT_DB_NAME,mode);

    if(ptr==NULL) { // If the pointer is null
        // Print error message
        printf("Could not open file, no such file or directory.\n");
    }

    // Write the record of size PERSON to the file
    fwrite(record,sizeof(PERSON),1,ptr);

    // Free the occupied memory
    free(record);

    // Close the file
    fclose(ptr);
}

// Helper & Wrapper functions

void add_person(){
    // Allocate heap memory of the size of a single person.
    PERSON * record=malloc(sizeof(PERSON));
    
    // Read first name into record
    readIntoPointer("Enter first name: ",
    record->firstname,
    FIRST_NAME_LENGTH
    );

    // Read family name into record
    readIntoPointer("Enter family name: ",
    record->famname,
    FAM_NAME_LENGTH
    );

    // Read personnumber into record
    readIntoPointer("Enter personal number: ",
    record->pers_number,
    PERS_NUMBER_LENGTH
    );
    
    // Append the record to the list
    append_file(record);
}

void write_file(){
    // Allocate heap memory of the size of one person
    PERSON*record = malloc(sizeof(PERSON));
    // Set dummy data
    strncpy(record->firstname,"Bob",4);

    // Set dummy data
    strncpy(record->famname,"Bobson",7);

    // Set dummy data
    strncpy(record->pers_number,"200203058376",13);


    // Write the new file
    write_new_file(record);
}

void printMenu(OPTION * options,int * arraylen){
    int i; // Counter for number of iterations

    // While i is less than the length of the array.
    for (i=0;i<*arraylen;i++){
        // Print the option along with its description.
        printf("%d %s\n",(i+1),((options)+i)->option);
    }

    // The last option will always give the option to exit
    // the program.
    printf("%d Exit the program.\n",(*(arraylen)+1));
}

void printRecord(PERSON*record) {
    // Print struct contents to stdout
    printf("Name: %s - " \
    "Family name: %s - " \
    "Person number: %s\n",record->firstname,record->famname,record->pers_number);
}

void append_file(PERSON *inrecord) {
    // Write the argument in append binary mode
    writeDB(inrecord,"ab");
}

void write_new_file(PERSON *inrecord){
    // Write the argument in write binary mode
    // overwriting any previous file.
    writeDB(inrecord,"wb");
}

void readIntoPointer(char prompt[PROMPT_DESCRIPTION_LENGTH],char*dest,int length){
    // Prompt the user
    printf("%s",prompt);

    // Read the specified length into the destination ptr.
    fgets(dest,length,stdin);

    // Remove any newlines from the destination.
    dest[strcspn(dest,"\n")]=0;
}
