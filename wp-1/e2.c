// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 1
// Exercise 2
// Submission code: xxxxxx (provided by your TA-s)

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
char encryptChar(int shifValue, char charToShift);
void validateChar(char character);
void printEncryptedStr(int shiftValue);
void validateArg(int argc, char *argv[]);

// the main function (where the program starts)
int main(int argc, char *argv[]) {
    int shiftValue; // the number of characters that the user wants to shift characters by

    // validate the argument given by the user
    validateArg(argc, argv);

    // initialise the shiftValue variable using the provided arguent
    shiftValue = atoi(argv[1]);
    // print the encrypted string entered by the suer
    printEncryptedStr(shiftValue);

    // upon successfull execution, return 0
    return 0;
}


char encryptChar(int shiftValue, char charToShift) {
    const int capitalAASCIIVal = 65; // decimal value of 'A' in ASCII
    const int capitalZASCIIVal = 90; // decimal value of 'Z' in ASCII
    const int lowerAASCIIVal = 97; // decimal value of 'a' in ASCII
    const int lowerZASCIIVal = 122; // decimal value of 'z' in ASCII
    const int numbOfAlpha = 26; // number of letters in the English alphabet
    int charASCIIVal = (int) charToShift; // turning char to its corresponding decimal int in ASCII
    int encryptedCharASCIIVal; // the ASCII value of the inverted char
    char encryptedChar; // the encrypted char

    // shift the character by the number provided by the user
    encryptedCharASCIIVal = charASCIIVal + shiftValue;
    // see if the char is upper case and its encrypted value is bigger than capital 'Z'
    // in that case add the remainder of the divsion (modulo) of the difference between the encrypted value and capital 'A'
    // to capital 'A' value
    if (charASCIIVal <= capitalZASCIIVal && charASCIIVal >= capitalAASCIIVal && encryptedCharASCIIVal > capitalZASCIIVal) {
        encryptedCharASCIIVal = capitalAASCIIVal + ((encryptedCharASCIIVal - capitalAASCIIVal) % numbOfAlpha);
    }

    // see if the char is lower case and its encrypted value is bigger than lower 'z'
    // in that case add the remainder of the divsion (modulo) of the difference between the encrypted value and lower 'a'
    // to lower 'a' value
    if (charASCIIVal <= lowerZASCIIVal && charASCIIVal >= lowerAASCIIVal && encryptedCharASCIIVal > lowerZASCIIVal) {
        encryptedCharASCIIVal = lowerAASCIIVal + ((encryptedCharASCIIVal - lowerAASCIIVal) % numbOfAlpha);
    }

    // turn ASCII decimal integer to char
    encryptedChar = (char) encryptedCharASCIIVal;

    // return the encrypted char
    return encryptedChar;
}

void printEncryptedStr(int shiftValue) {
    char enteredChar; // the entered char by the user.
    char *encryptedStr;  // the encrypted string (to be printed later on)
    int counter; // counter to go over the chars of the pointer
    char encryptedChar; // variable to hold the encrypted character
    int encryptedStrSize; // the buffer size of the pointer to the argument provided

    // initialise by getting the first character enetered by the user
    enteredChar = getchar();

    // the programme will run until the user enters Crtl + Z or Ctrl + d
    while (enteredChar != EOF) {
        encryptedStrSize = 10; // start by occupying 10 bytes of memory
        encryptedStr = (char*)calloc(encryptedStrSize, sizeof(char)); // allocating 50 char (50n * 1 byte) of memory to the string
        counter = 0; // initialising the counter with 0 every time we want to read a new str printed by the user

        // check if memory is allocated. If not exit with status code 0.
        if (encryptedStr == NULL) {
            printf("Memory allocation failed.\n");
            exit(0);
        }

        // get new char by getting the first character enetered by the user
        enteredChar = getchar();

        // read chars until user puts enter
        while (enteredChar != '\n') {
            // if the counter is getting close to the end of the memory allocated
            // use realloc to increase the size of the pointer
            if ((encryptedStrSize - counter) < encryptedStrSize) {
                // increase the size variable by 10
                encryptedStrSize = encryptedStrSize + 10;
                encryptedStr = realloc(encryptedStr, encryptedStrSize * sizeof(char));
                // check if memory is allocated. If not exit with status code 0.
                if (encryptedStr == NULL) {
                    printf("Memory allocation failed.\n");
                    exit(0);
                }
            }

            // check the validity of the char typed by the user
            validateChar(enteredChar);
            // get the encrypted char using the encrypt char method
            encryptedChar = encryptChar(shiftValue, enteredChar);
            // save encrypted char at the counter index
            encryptedStr[counter] = encryptedChar;

            // increment counter to count for the char that was just read
            counter++;
            // get new char
            enteredChar = getchar();
        }

        // if counter is 0, it means that the user just pressed enter
        // so nothing should be printed
        if (counter != 0) {
            // insert the end of a string char \0 at the index after the last index that holds a char
            encryptedStr[counter] = '\0';
            // print the encrypted str
            printf("%s\n", encryptedStr);
        }

        // free the allocated memory to the encryptedStr string
        free(encryptedStr);
    }
}

void validateChar(char character) {
    const int capitalAASCIIVal = 65; // decimal value of 'A' in ASCII
    const int capitalZASCIIVal = 90; // decimal value of 'Z' in ASCII
    const int lowerAASCIIVal = 97; // decimal value of 'a' in ASCII
    const int lowerZASCIIVal = 122; // decimal value of 'z' in ASCII
    int charASCIIVal = (int) character; // turning character to its corresponding decimal int in ASCII
    // if the ASCII value of the char that is to be encrypyted indicates an English alphabet letter, return
    if ((charASCIIVal <= capitalZASCIIVal && charASCIIVal >= capitalAASCIIVal) || (charASCIIVal <= lowerZASCIIVal && charASCIIVal >= lowerAASCIIVal)) {
        return;
    }
    // Otherwise exit and print a message that the user needs to type english alphabet letters only
    printf("Please print english alphabet letters.\n");
    exit(0);
}

void validateArg(int argc, char *argv[]) {
    const int ASCIIZeroVal = 48; // value for zero in ASCII
    const int ASCIINineVal = 57; // value for nine in ASCII
    char *providedArg; // variable to hold the provided argument
    int argLength;  // The length of the argument string
    int charASCIIVal; // variable to hold a char's ASCII value

    // if one argument is not provided, exit with 0 exit code
    if (argc < 2 || argc > 2) {
        printf("You must provide one argument.\n");
        exit(0);
    }

    // save the provided argument in its variable
    providedArg = argv[1];
    // get the argument's length
    argLength = strlen(providedArg);

    // for loop to go over the chars of the string provided by the user
    for (int i = 0; i < argLength; i++) {
        // get the ith char and get its ASCII val
        charASCIIVal = (int) providedArg[i];
        // if the ASCII val does not indicate a number exit with 0 exit code
        if (charASCIIVal < ASCIIZeroVal || charASCIIVal > ASCIINineVal) {
            printf("You must provide numbers only.\n");
            exit(0);
        }
    }
}