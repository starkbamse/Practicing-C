// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 1
// Exercise 1
// Submission code: xxxxxx (provided by your TA-s)

// Include section
#include <stdio.h>

// function declarations
void printSentences(int number);
int readInteger(char *prompt);
void validateProgFinish(void);

// the main function (where the program starts)
int main(int argc, char *argv[]) {

    // validate the end of the program
    validateProgFinish();

    // upon successfull execution, return 0
    return 0;
}

/**
 * This function prints sentences based on the integer passed to it. If the integer is between and including
 * 1 and 5 sentences corresponding sentences are printed. Otherwise, nothing is printed.
 * @param numb integer passed to the function whihc determines which sentence is to be printed.
*/
void printSentences(int number) {
    // using a switch-case construct, based on the number argument passed to the function
    // corresponding sentences are printed that showcase what the user typed.
    // if the the user does not print any number between and including 1 and 5, nothing is printed.
    switch (number) {
        case 1:
            printf("This sentence is printed because you entered number 1.\n");
            break;
        case 2:
            printf("This sentence is printed because you entered number 2.\n");
            break;
        case 3:
            printf("This sentence is printed because you entered number 3.\n");
            break;
        case 4:
            printf("This sentence is printed because you entered number 4.\n");
            break;
        case 5:
            printf("This sentence is printed because you entered number 5.\n");
            break;
    }
}

/**
 * This function reads an integer entered by the user and returns it to its caller.
 * @param prompt This is a string that is passed to the method and is used as a prompt for the user
 * @returns The integer entered by the user.
*/
int readInteger(char *prompt) {
    int inputNum; // the number entered by the user will be saved in this variable
    // the fucntion gets a string as a argument whihc is a prompt to the user.
    // this printf prints the prompt on the console.
    printf("%s: ", prompt);
    // read the number entered by the user
    scanf("%d", &inputNum);
    // return it to the caller
    return inputNum;
}

/**
 * This method prompts the user to keep entering a umber until
 * they enter a number that is not between and including 1 and 5.
 * In that case, the programe finishes.
*/
void validateProgFinish(void) {
    int inputNum; // variable to save integer input entered by the user
    // call readInteger to read the integer entered by the user
    inputNum = readInteger("Please enter a number between (including) 1 and 5");
    // While loop to keep asing the user to enter a number until they
    // enter a number that is not between and including 1 and 5
    while (inputNum >= 1 && inputNum <= 5) {
        // Print a sentence based on the integer entered by the user
        printSentences(inputNum);
        // prompt the user to enter another integer
        inputNum = readInteger("Please enter a number between (including) 1 and 5");
    }
}