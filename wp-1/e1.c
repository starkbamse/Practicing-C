/*EXERCISE 1: IF-STATEMENTS
Write a program that reads in an integer number between 1 and 5 from the keyboard and prints out one of
existing five sentences on the console depending on what number was entered. You can invent the sentences
as you want, but each sentence should be unique.
The program continues to ask for a new number and exits if number isn ́t in the interval 1 to 5.*/


// Include section
#include <stdio.h>

// Main function in the program

/*
* Purpose: This program reads an integer number between 1 and 5 and prints out a sentence for 
* each of the options. 
* The program continues to ask for a new number and exits if number isn ́t in the interval 1 to 5.
*
*
* Authors: Kaisa Arumeel, Alexander Säfström, Omid Khodaparast
*/
int main() {
    // Variable declarations
    int input; // Input integer of the user

    do
    {
        printf("Please input a number from 1 to 5 \n");
        //Scan the input from the user
        scanf("%d", &input);
        // Case for input 1
        if(input == 1){
            printf("Input is 1 \n");
        }
        // Case for input 2
        else if(input == 2){
            printf("Input is 2 \n");
        }
        // Case for input 3
        else if(input == 3){
            printf("Input is 3 \n");
        }
        // Case for input 4
        else if(input == 4){
            printf("Input is 4 \n");
        }
        // Case for input 5
        else if(input == 5){
            printf("Input is 5 \n");
        }
    // Prompt the user with the sentence until the input is between 1 and 5.
    } while (input > 0 && input < 6);

}