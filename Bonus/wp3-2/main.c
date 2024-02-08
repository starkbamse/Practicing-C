//Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define section
#define MAX_ROW_SIZE 4
#define MAX_COL_SIZE 4
#define MIN_ROW_SIZE 2
#define MIN_COL_SIZE 2

//Main program section

/**
* This program accepts input to create and fill
* a matrix of maximum 4x4 size. It fills two of these
* with values that you specify and return the sum
* of the matrices.
* 
* Purpose: To explore the boundaries of mathematics
* in C.
* DIT632
* 
* Author: Alexander Säfström, 2024
* 
**/

// Used to read user's input into a matrix
int readIntoMatrix(int*matrix,int sizeToRead);

int main(int argc,char*argv[]) {
    // Variable declarations

    int* matrix1; // A pointer to the first matrix
    int* matrix1Copy; // A copy of the first matrix pointer
    int* matrix2; // A pointer to the second matrix
    int* matrix2Copy; // A copy of the second matrix pointer
    int rows=0; // Number of rows in the matrix
    int cols=0; // Number of columns in the matrix
    int size=0; // Size of the matrix
    int i; // Keeps us track in the loop
    int x; // For the second row loop

    // Program logic
    
    // Print to stdout
    printf("Input the size: "); 

    // Allocate 4 bytes of mem for the size of the matrix size
    char* userInput=malloc(4);

    // Read 4 bytes from stdin
    fgets(userInput,4,stdin);

    // Clear the buffer
    while((i=fgetc(stdin)!='\n') &&i!=EOF);

    // Parse the string into rows and cols ints
    sscanf(userInput, "%d%d", &rows, &cols);

    // If the rows or cols are outside of valid bounds
    if(rows>MAX_ROW_SIZE
        || rows<MIN_ROW_SIZE
        || cols>MAX_COL_SIZE
        || cols<MIN_COL_SIZE){
            // Print error and exit the program
            printf("invalid\n");
            return 0;
        }
    
    // Calculate matrix size
    size=rows*cols;

    // Allocate memory for matrix 1, which is an int * matrix size.
    matrix1=malloc(sizeof(int)*size);

    // Create a copy of the pointer
    matrix1Copy=matrix1;

    // Allocate memory for matrix 2, which is an int * matrix size.
    matrix2=malloc(sizeof(int)*size);

    // Create a copy of the pointer
    matrix2Copy=matrix2;

    // Prompt the user
    printf("Input elements of matrix 1: ");

    // Read user input into matrix.
    // If zero is returned, it means there was an error
    if(readIntoMatrix(matrix1,size)==0){
        return 0;
    }

    // Prompt the user
    printf("Input elements of matrix 2: ");

    // Read user input into matrix.
    // If zero is returned, it means there was an error
    if(readIntoMatrix(matrix2,size)==0){
        return 0;
    }

    // Print to stdout
    printf("The sum is:\n");

    // For each row
    for(i=0;i<rows;i++){
        // For each column
        for(x=0;x<cols;x++){
            // Print the sum of the first two elements
            printf("%d ",(*matrix1+*matrix2));

            // Increment pointers
            matrix1++;
            matrix2++;
        }
        // Print a new row
        printf("\n");
    }

    // Free occupied heap memory
    free(userInput);
    free(matrix1Copy);
    free(matrix2Copy);

    // Exit gracefully
    return 0; 
}
int readIntoMatrix(int*matrix,int sizeToRead){
    int sizeRead=0; // How much we have read
    int parsed=0; // The parsed int
    char* endptr; // Used for input validation

    // Allocate heap memory for user input
    char* userInput=malloc((MAX_ROW_SIZE*MAX_COL_SIZE*2));

    // Read user's input 
    fgets(userInput,(MAX_ROW_SIZE*MAX_COL_SIZE*2),stdin);

    // Tokenize users input by splitting the string by whitespace
    char* c = strtok(userInput," ");

    // As long as we have tokens
    while(c!=NULL){
        // If the size we have read is less than
        // the required amount
        if(sizeRead<sizeToRead){
            // Parse the string to an int
            parsed=(int) strtol(c,&endptr,10);

            // If the endptr points to start it means
            // no char was converted.
            if(c==endptr){
                // Print error message
                printf("invalid\n");
                // Return false status code.
                return 0;
            }
            // Update the value of matrix to the int
            *matrix=parsed;
            // Increment pointer
            matrix++;
            // Increase the number of size that we have read
            sizeRead++;
        }
        // Update c to get the next token
        c=strtok(NULL," ");
    }

    // If we have read not equal to the required amount.
    if(sizeRead!=sizeToRead){
        // Print error
        printf("invalid\n");
        // Free occupied heap memory
        free(userInput);
        // Return false status code
        return 0;
    }
    // Free occupied heap memory
    free(userInput);
    // Return false status code
    return 1;
}