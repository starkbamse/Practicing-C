// Exercise 3

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define section
#define MAX_NUMBER 10


// Main function in the program

/*
* Purpose: This program generates a random number between 1 and 100.
* The user can guess the number and the program responds whether the guess
* is too low, high or correct. There is a set number of maximum guesses.
* After the game has finished, the user can either play again or exit the program.
*
* Authors: Kaisa Arumeel, Alexander Säfström, Omid Khodaparast
*/


// Main function
int main(int argc, char *argv[]) {

// Initalise the random generation of numbers so that it does not return the same number every execution 
srand ( time(NULL) );
//Create a random number from between 1 and 100 (included).
int randomNumber =  rand() %100 + 1;

// Variable declarations
int input,           // User input
playAgain,           // Flag for whether the user wants to play again
numberOfGuesses = 0; // Counter for number of made guesses

do
{
   // Ask user for a number and save the input
   printf("Enter a number between 1 and 100: \n");
   scanf("%d", &input);
   printf("%d", input);
   // If the input is not in the range, ask for a valid input.
    if ( input > 100 || input < 1) {
        printf("Please enter a valid integer between 1 and 100.\n");
    }
    // Guess is lower than the random number
    else if(input < randomNumber) {
        printf("Your guess is too low.\n");
        // Increase number of guesses count
        numberOfGuesses += 1;
    }
    // Guess is higher that the random number
    else if(input > randomNumber) {
        printf("Your guess is too high.\n");
        // Increase number of guesses count
        numberOfGuesses += 1;
    }
    // Guess is correct
    else {
        // Increase number of guesses count
        numberOfGuesses += 1;
        printf("You have guessed %d times and your guess is correct.\n", numberOfGuesses);
        // Ask whether the user wants to play again
        printf("Press 1 to play again, 0 to finish the game: ");
        scanf("%d", &playAgain);
        // If the user pressed 1, create a new random number and reset the number of guesses counter.
        if (playAgain == 1) {
            randomNumber = rand() % 100 + 1;
            numberOfGuesses = 0;
        }
    }

    // User has guessed maximum number of times.
    if(numberOfGuesses == MAX_NUMBER) {
        printf("%s\n", "You have run out of tries. \n");
        // Ask whether the user wants to play again
        printf("Press 1 to play again, 0 to finish the game: ");
        scanf("%d", &playAgain);
        // If the user pressed 1, create a new random number and reset the number of guesses counter.
        if (playAgain == 1) {
            randomNumber = rand() % 100 + 1;
            numberOfGuesses = 0;
        }
    }
// Do this as long as the guess is not correct and the number of guesses does not exceed maximum number of tries.
} while (input != randomNumber && numberOfGuesses < MAX_NUMBER);


return 0;
}