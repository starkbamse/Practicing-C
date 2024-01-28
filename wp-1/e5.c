#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX 100         // Defines the maximum number of the values in the table
#define MAXNUMBER 20    // Defines the maximum value of random numbers


/*
* Purpose: This program generates a 100 random integers with values from 0 to 20.
* The program counts the fequency of occurance of each value and plots them in a histogram
*
* Authors: Kaisa Arumeel, Alexander Säfström, Omid Khodaparast
*/



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


// ------ Function definitions ----------

void create_random(int *tab ){
    // Make sure the generation of numbers is random and does not repeat
    srand(time(NULL));
    // Iterate over numbers from 0 to 100.
    for (int i = 0; i < MAX; i++)
    {
        // Create a random number between 0 and 20 and store it in the table at the position of the loop.
         tab[i] = rand() % (MAXNUMBER + 1);
    }

}

void count_frequency(int *tab, int *freq ){

    
    int *temp = tab;    // Copy of the address of the table
    int i, j;           // Index of the loop
    // Iterate over each number from 0 to 20
    for (i = 0; i <= MAXNUMBER; ++i)
    {
        // Set the frequency to be 0
        *freq = 0;
        // Loop through every random number in table (100 numbers)
        for (j = 0; j < MAX; ++j)
        {
            // Check if the number in the table is equal to i (which is numbers from 0 to 20)
            if (*temp==i)
            {
                // Increment frequency by one
                *freq+=1;
            }
            // Go to next address in tab array
            temp++;
        }
        // Go back to the start of the tab array
        temp = tab;
        // Go to the next freq address
        freq++;
    }

}


void draw_histogram(int *freq ){

  int i, j; // Index of the loop
  
  // Loop through all possible values between 0 and 20.
    for (i = 0; i <= MAXNUMBER; i++)
    {
        // Check if the frequency of that value is not zero
        if (freq[i] != 0) {
            // If not zero, then do the following:
            // Then print the number and x's
            printf("%2d  ", i); 

        // Loop through the frequency of a value occuring
            for (j = 0; j < freq[i]; j++)
            {
                // Print an x for every occurance.
                printf("%c", 'x'); 
            }
        }
        // Empty line between columns
        printf("\n"); 
    }
}

    
// ------ Main --------------------------
// The main entry point for the program
//
int main (void){
    
    int table[MAX];             // Stores the table of 100 entries
    int frequency[MAXNUMBER];   // Stores the frequency of the 20 values

    // Generate 100 random values into the table
    create_random(table);
    // Count the occurances of the 20 different values in the table
    count_frequency(table,frequency);
    // Draw a histogram showing the frequency of each value
    draw_histogram(frequency);        
}