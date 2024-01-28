//Include section
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Define section
#define MAX 100 // Defines the maximum number of the values in the table
#define MAXNUMBER 20 // Defines the maximum value of random numbers

//Main program section

/**
* This program uses two initial values, a table size and a maximum
* number, and creates a randomized table with different numbers.
* The program counts the frequency of these numbers and plots
* them on a histogram.
* 
* Purpose: To discover the distribution of numbers generated
* by a pseudo-RNG using the current system time as the seed.
* DIT632
* 
* Author: Kaisa Arumeel, Omid Khodaparast, Alexander Säfström
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
    int table[MAX]; // An array of random integers.
    
    // An array storing the number of occurrences of each number in the table.
    int frequency[MAXNUMBER]; 
    
    time_t currentTime=time(NULL); // Current system time.

    // Program logic

    // Seed the random number generator.
    srand(currentTime);
    // Set frequency in table to 0.
    memset(frequency, 0, sizeof(frequency));
    // Create a randomized table
    create_random(table);
    // Count the frequency of each number
    count_frequency(table,frequency);
    // Draw a histogram of the table.
    draw_histogram(frequency);
}

void create_random(int *tab){
    // Loop from 0 to the maximum value, the size of table.
    for(int i=0;i<MAX;i++){
        // Set the current element's value to a random value modulus
        // the maximum number that we have set to be generated.
        *(tab+i)=rand()%(MAXNUMBER+1);
    }
}

void count_frequency(int *tab,int*freq) {
    // Loop from 0 to the maximum value, the size of table.
    for(int i=0;i<MAX;i++){
        // Increment the frequency of the element that is
        // the value of the element stored in tab+i.
        *(freq+*(tab+i))+=1;
    }
}

void draw_histogram(int*freq){
    // Loop from 0 to the maximum value that we can generate.
    for(int i=0;i<MAXNUMBER+1;i++){
        // Check if the frequency is bigger than 0.
        if(*(freq+i)>0){
            // Print the number.
            printf("%2d ",i);
            // Loop from 0 to the frequency of this number
            for(int x=0;x<*(freq+i);x++){
                // Print an x to stdout.
                printf("x");
            }
            // Print a newline.
            printf("\n");
        }
    }
}
