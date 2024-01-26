//Include section
#include <stdio.h>

//Define section
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100 // Defines the maximum number of the values in the table
#define MAXNUMBER 20 // Defines the maximum value of random numbers

//Main program section

/**
* This program is a useful program because it is used
* in very useful situations, therefore you should
* use it.
* 
* Purpose: Being useful is a good trait
* DIT632
* 
* Author: A useful person, 2024
*
* Note: all variable decl at the top of each method.
* define where the program logic starts.
* 
**/

// ------ Function declarations ----------

// This function generates a set of random numbers
// and fills the table *tab with these numbers
void create_random(int *tab );
// This function takes the *tab of random numbers
// and creates a table with the frequency counts for these numbers
void count_frequency(int *tab, int *freq );
// This function takes the frequency count table
// and draws a histogram of the values in that frequency table
void draw_histogram(int *freq );
// Validates the user arguments
int validateInput(int*argc,char**argv[]);

// ------ Function definitions ----------

// ------ Main --------------------------
// The main entry point for the program
int main (int argc, char* argv[]) {
    //Variable declarations
    int table[MAX], n ;
    int frequency[MAXNUMBER];


    // Program logic
    create_random(&table);
}



void create_random(int *tab){
    for(int i=0;i<MAX;i++){
        *(tab+i)=rand()%MAXNUMBER;
    }
}