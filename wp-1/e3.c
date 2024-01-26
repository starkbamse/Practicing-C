// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 1
// Exercise 3
// Submission code: xxxxxx (provided by your TA-s)

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Define Section
#define MAX_NUMBER 3
#define MAX_METHOD_REPLAY 3

// function declarations
int generateRandInt(void);
int isValidInput(char *providedArg);
void guessNumber(void);
char *readInputStr(void);
char askUserToReplay(int methodReplay);
void clearBuffer(void);

// main function (where the program starts)
int main(int argc, char *argv[]) {

    // start by asking user to guess
    // the method uses other methods to control the logic of the game
    guessNumber();

    // return 0 on program finish
    return 0;
}

int generateRandInt(void) {
    int randNum;  // variable to hold random number between 1 and 100 (included)

    // seed the randomiser
    srand(time(0));
    // get modulo of 100 and add 1 to get a numb between 1 and 100
    randNum = (rand() % 100) + 1;

    // return the random number
    return randNum;
}

int isValidInput(char *providedArg) {
    const int ASCIIZeroVal = 48; // value for zero in ASCII
    const int ASCIINineVal = 57; // value for nine in ASCII
    int argLength;  // The length of the argument string
    int charASCIIVal; // variable to hold a char's ASCII value
    const int maxLength = 3; // the user can only guess between 1...100 and the max length is 3
    int numOfTrailingZeros; // this variable holds the number of trailing zeros
    int nonZeroNumExistance; // this variable acts as a boolean to indicate if a non-zero number has been read

    // get the input length
    argLength = strlen(providedArg);
    // indicate that no non-zero number has been read by having this variable set to false (0)
    nonZeroNumExistance = 0;

    if (argLength == 0) {
        printf("You must provide an argument.\n");
        return 0;
    }

    // for loop to go over the chars of the string provided by the user
    for (int i = 0; i < argLength; i++) {

        // if no non-zero number has been seen and the current index holds a 0, increment trailing 0 variable
        if (providedArg[i] == '0' && nonZeroNumExistance == 0) {
            numOfTrailingZeros++;
        }

        if (providedArg[i] != '0') {
            nonZeroNumExistance = 1;
        }

        // if the first char is '-', continue as a negative number is still a number
        if (providedArg[0] == '-') {
            continue;
        }

        // get the ith char and get its ASCII val
        charASCIIVal = (int) providedArg[i];

        // if the ASCII val does not indicate a number return 0 to indicate invalid input
        if (charASCIIVal < ASCIIZeroVal || charASCIIVal > ASCIINineVal) {
            printf("You must provide numbers only.\n");
            return 0;
        }

    }

    // if the input number is bigger than 100 or less than 1 (excluding trailing 0s) print error message
    if ((argLength - numOfTrailingZeros) > maxLength || providedArg[0] == '-' || (providedArg[0] == '0' && argLength == 1)) {
        printf("You must provide numbers between and including 1 and 100 .\n");
        return 0;
    }

    // return 1 to indicate valid input number
    return 1;
}

void guessNumber(void) {
    int numToGuess; // this variable holds the number that is to be guessed
    int numOfGuesses; // this variable hold the number of guesses the user has made
    char *userInput; // this variable holds the user input
    int finishIndicator = 1; // this variable is used to finish the program based on user's input
    int guessedNum; // this variable holds the number guessed by the user
    int guessIsRight = 0; // a boolean variable to  be set to 1 when the user guesses correctly
    char userReplayAnswer; // this variable holds user's answer to replay

    while (finishIndicator) {
        // initialise random num
        numToGuess = generateRandInt();
        // set guesses to 0 every time the user starts guessing
        numOfGuesses = 0;

        // ask the user to guess the random generated number
        printf("A random number has been generated. Please guess the number by entering numbers using the keyboard.\n");

        // let the user guess until they have guessed the max number of times
        while (numOfGuesses < MAX_NUMBER) {

            // read the user's guess
            userInput = readInputStr();
            // if userinput is valid

            if (isValidInput(userInput)) {

                // since input is valid, turn the string to a number
                guessedNum = atoi(userInput);
                // increment the number of times the user has guessed
                numOfGuesses++;
                // print the amount fo times the user has guessed
                printf("You have guessed %d times and your guess is ", numOfGuesses);

                // if the guess is lower, tell the user
                if (guessedNum < numToGuess) {
                    printf("incorrect.\nYour guess is too low.\n");
                // if the fuess is higher, tell the user
                } else if (guessedNum > numToGuess) {
                    printf("incorrect.\nYour guess is too high.\n");
                // else the guess is correct
                } else {
                    printf("correct\n");
                    // set the guess is right variable to 1 to indicate the correctness of the guess
                    guessIsRight = 1;
                    // break the guess loop as the guess was right
                    break;
                }

            }

            // ask user to guess if they have not lost all their chances
            if (numOfGuesses < MAX_NUMBER) {
                printf("Please guess again.\n");
            }

        }

        if (!guessIsRight) {
            printf("You only had %d chances and you did not guess the number.\nThe number was %d.\n", MAX_NUMBER, numToGuess);
        }

        // ask the user to play again
        userReplayAnswer = askUserToReplay(0);

        // if the user answered with 'n' finish the programe
        if (userReplayAnswer == 'n') {
            finishIndicator = 0;
        }
        // clear the buffer before reading again
        clearBuffer();

        // set the guessIsRoght to false for future rounds
        guessIsRight = 0;

    }

}

char *readInputStr(void) {
    int inputPointerSize; // this variable holds the size of the input
    int counter; // counter to know when to reallocate memory to the pointer
    char currentChar; // the current char entered by the user
    char *userInput; // this variable holds the user input

    // initialise the the array of chars with 10 bytes (10 chars)
    inputPointerSize = 10;
    // use calloc to give the pointer 10 bytes of memory
    userInput = (char*)calloc(inputPointerSize, sizeof(char));

    // initialising the counter with 0 every time we want to read a new str printed by the user
    if (userInput == NULL) {
        printf("Memory allocation failed.\n");
        exit(0);
    }

    counter = 0;
    // get the first character entered by the user
    currentChar = getchar();

    // read input until user inputs \n
    while(currentChar != '\n') {

        // if the counter is getting close to the end of the memory allocated
        // use realloc to increase the size of the pointer
        if ((inputPointerSize - counter) < inputPointerSize) {

            // increase the size variable by 10
            inputPointerSize = inputPointerSize + 10;
            // resize the array of chars to hold more characters
            userInput = realloc(userInput, inputPointerSize * sizeof(char));

            // check if memory is allocated. If not exit with status code 0.
            if (userInput == NULL) {
                printf("Memory allocation failed.\n");
                exit(0);
            }

        }

        // save entered char at the counter index
        userInput[counter] = currentChar;

        // increment counter to count for the char that was just read
        counter++;

        // get new char
        currentChar = getchar();

    }

    // append nul charecter to mark the end of the string
    userInput[counter] = '\0';

    return userInput;
}

/**
 * if the method is called more than MAX_METHOD_REPLAY + 2 times, then the program finishes 
 * the reason for this is that since this method is recursive, the user can cause a stack overflow error.
 * Call this by passing 0 all the time
 * @param methodReplay this variable is used to count the number of times this method is called
 * @return char 'y' or 'n'
*/
char askUserToReplay(int methodReplay) {
    char replayAnswer; // this variable holds user's answer to play again

    printf("Would you like to play another round [y/n]? ");

    // get user's answer
    replayAnswer = getchar();

    if (methodReplay == 0) {
        // The method is called two extra times compared to MAX_METHOD_REPLAY
        // This was found by experimentation
        // hence 2 is added to the method replay when it is called for the first time
        methodReplay = methodReplay + 2;
    }

    // if method has been called more than MAX_METHOD_REPLAY, return 'n'
    if (methodReplay > MAX_METHOD_REPLAY) {
        printf("You did not answer with 'y' or 'n' for %d times. Hence the program ended. Please run the program again if you wish to play.\n", MAX_METHOD_REPLAY);
        return 'n';
    }

    if (replayAnswer != 'y' && replayAnswer != 'n') {
        // increment methodReplay, as you will call the method one more time
        methodReplay++;

        // clear the buffer before asking again
        clearBuffer();

        // tell the user to answer with either 'y' or 'n' only
        printf("Please answer with 'y' or 'n'.\n");

        // call the method recursively
        return askUserToReplay(methodReplay);
    }

    // if non of above consitions is triggered, the user has entered 'y' or 'n'
    return replayAnswer;
}

// for this method We referred to the code from the first Lecture
// Clear buffer 
// This function is necessary to get rid of the \n signs 
// which can be in the buffer
void clearBuffer() {
	char currentChar; // variable to hold the current char

    // get chars until you reach EOL
	while ((currentChar = getchar()) != '\n');
}