// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 1
// Exercise 5
// Submission code: xxxxxx (provided by your TA-s)

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 100 // Defines the maximum number of the values in the table
#define MAXNUMBER 20 // Defines the maximum value of random numbers

// ------ Function declarations ------
// This function generates a set of random numbers
// and fills the table *tab with these numbers
void create_random(int *tab);
// This function takes the *tab of random numbers
// and creates a table with the frequency counts for these numbers
void count_frequency(int *tab, int *freq);
// This function takes the frequency count table
// and draws a histogram of the values in that frequency table
void draw_histogram(int *freq);

// ------ Function definitions ------ 

// ---------- main ------------------
// The main entry point for the program
int main (void) {
    int table[MAX]; // Construct an array of size MAX
    int frequency[MAXNUMBER + 1]; // Construct an array of size MAXNUMBER + 1 (from 0 (including) to MAXNUMBER (including))
    // Set values of array to 0.
    memset(frequency,0,sizeof(frequency));

    create_random(table); 
    count_frequency(table, frequency);  
    draw_histogram(frequency);

    // Return 0 upon program finish
    return 0;
}

void create_random(int *tab) {
    int randNum;  // Variable to hold random number between 1 and 100 (included)

    // Seed the randomiser
    srand(time(0));

    // Loop through the table.
    for (int i = 0; i < MAX; i++) {
        // Get modulo of MAXNUMBER+1 to get a number between 0 and MAXNUMBER
        randNum = (rand() % (MAXNUMBER + 1));
        // Set index i value to randNum
        tab[i] = randNum;
    }
}

void count_frequency(int *tab, int *freq) {
    int randNum; // This variable holds the random number which will be used to find the index in freq

    // Go through the random number array and count the frequency of each number
    for (int i = 0; i < MAX; i++) {
        // Get the number at index i
        randNum = tab[i];
        // For this number, increment by 1
        freq[randNum]++;
    }
}

void draw_histogram(int *freq) {
    // Go through the array.
    for (int i = 0; i <= MAXNUMBER; i++) {
        // If freq[i] is 0, do not draw and continue to the next iteration
        if (freq[i] == 0) continue;

        // Print the num taking into consideration that it can need two spaces on the terminal
        printf("%2d   ", i);

        // Print x corresponding to the frequency of the current number
        for (int j = 1; j <= freq[i]; j++) {
            printf("x");
        }

        // Go to the next line
        printf("\n");
    }
}