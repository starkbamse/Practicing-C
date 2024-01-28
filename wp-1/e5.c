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
    int table[MAX]; // construct an array with size MAX
    int frequency[MAXNUMBER + 1]; // construct an array with size MAXNUMBER + 1 (from 0 (including) to MAXNUMBER (including))
    
    memset(frequency,0,sizeof(frequency));

    create_random(table);
    count_frequency(table, frequency);
    draw_histogram(frequency);

    // rtuen 0 upon program finish
    return 0;
}

void create_random(int *tab) {
    int randNum;  // variable to hold random number between 1 and 100 (included)

    // seed the randomiser
    srand(time(0));

    // now that we have the size we can assign random numbers
    for (int i = 0; i < MAX; i++) {
        // get modulo of MAXNUMBER and add 1 to get a numb between 0 and MAXNUMBER
        randNum = (rand() % (MAXNUMBER + 1));
        // set undex i value to randNum
        tab[i] = randNum;
        // printf("tab[%d] = %d\n", i, randNum);
    }
}

void count_frequency(int *tab, int *freq) {
    int randNum; // this variable holds the random number whihc will be used to find the index in freq




    // go through the random number array and count the frequency of each number
    for (int i = 0; i < MAX; i++) {
        // get the numb at index i
        randNum = tab[i];
        // for this number between 0 and MAXNUMBER add 1 to what it was before
        freq[randNum]++;
    }
}

void draw_histogram(int *freq) {
    int freqPerNum; // this variable holds frequency per number

    // go t through the array. If the freq is not 0 draw
    for (int i = 0; i <= MAXNUMBER; i++) {
        // if freq is 0, do not draw and continue to the next iteration
        // printf("freq[%d] = %d\n", i, freq[i]);
        if (freq[i] == 0) continue;
        // set freq for the current index
        freqPerNum = freq[i];
        // print the num taking into consideration that it can need two spaces on the terminal
        printf("%2d   ", i);

        // print x corresponding to the frequency of the current number
        for (int j = 1; j <= freqPerNum; j++) {
            printf("x");
        }

        // go to the next line
        printf("\n");
    }
}