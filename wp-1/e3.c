// Exercise 3

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define section
#define MAX_NUMBER 10


// Main function in the program

/*
* Purpose: 
*
* Authors: Kaisa Arumeel, Alexander Säfström, Omid Khodaparast
*/

int main(int argc, char *argv[]) {

srand ( time(NULL) );
//Create a random number from (0 - 99 as the modulo %100) + 1
int randomNumber =  rand() %100 + 1;


int input, 
playAgain,
numberOfGuesses = 0;

do
{
   printf("Enter a number between 1 and 100: \n");
   scanf("%d", &input);
   printf("%d", input);
    if ( input > 100 || input < 1) {
        printf("Please enter a valid integer between 1 and 100.\n");
        continue; // Restart the loop if the input is not valid
    }
    else if(input < randomNumber) {
        printf("Your guess is too low.\n");
        numberOfGuesses += 1;
    }
    else if(input > randomNumber) {
        printf("Your guess is too high.\n");
         numberOfGuesses += 1;
    }
    else {
        numberOfGuesses += 1;
        printf("You have guessed %d times and your guess is correct.\n", numberOfGuesses);
        printf("Press 1 to play again, 0 to finish the game: ");
        scanf("%d", &playAgain);

        if (playAgain == 1) {
            randomNumber = rand() % 100 + 1;
            numberOfGuesses = 0;
        }
    }

} while (input != randomNumber && numberOfGuesses < MAX_NUMBER);

    if(numberOfGuesses == MAX_NUMBER) {
        printf("%s\n", "You have run out of tries. \n");
        printf("Press 1 to play again, 0 to finish the game: ");
        scanf("%d", &playAgain);
        if (playAgain == 1) {
            randomNumber = rand() % 100 + 1;
            numberOfGuesses = 0;
        }
    }

return 0;
}