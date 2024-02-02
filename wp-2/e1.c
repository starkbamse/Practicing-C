// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 2
// Exercise 1
// Submission code: xxxxxxx (provided by your TA-s)

//Include section
#include <stdio.h>
#include <stdlib.h>

// Define section
#define END_CHAR 'a'
// This will be used to get the modulu of an angle as angles bigger than 270 are not allowed
#define CIRCLE_ANGLE 360

// --- Type definitions ---
enum DIRECTION {N, E, S, W}; // directions written in terms of enums

// Struct named ROBOT to hold the robot attributes
typedef struct {
    int xpos;
    int ypos;
    enum DIRECTION dir;
} ROBOT;
// --- Type definitions ---

// --- Function declarations ---
// This function moves the robot based on its direction
void move(ROBOT *robo);
// This function changes the robot's direction clockwise
void turn(ROBOT *robo);
// Clear the buffer
void clearBuffer();
// Read input from the user
char readInput(char *promt);
// Validate the input provided by the user
int validateInput(char userInput);
// Print the position of the robot
void printRoboPos(ROBOT robo);
// --- Function declarations ---

/**
 * This program simulates the movements of a robot as asked by users
 * Users enter 't' or 'm' to indicate 'turn' and 'move'.
 * Program moves the robot based on the direction and changes direction 
 * when asked by the users. Directions change 90 degrees by 90 degrees
 * Hence, there are only N, E, S, and W directions
*/

// Main fucntion, where the programe starts its execution
int main(void) {
    ROBOT robo = {0, 0, N};  // Declare and initialise the robot with north dir and 0 for xa dn y positions
    char userInput; // Variable to hold the input entered by the user

    // Ask the user to 'm' or 't' until they input 'a'
    do {

        // Get user input
        userInput = readInput("Please enter the char 'm' to move the robot, char 't' to change the robot's direction or char 'a' to finish the programe.");
        // If the user input is valid, then perform move or turn functions

        if (validateInput(userInput)) {
            // if the input is 'm' move the robo based on its dir
            if (userInput == 'm') {
                move(&robo);
            }
            // if the input is 't' then turn 90 degrees
            if (userInput == 't') {
                turn(&robo);
            }
        }

        // Print the robo's position each iteration
        printRoboPos(robo);
    } while (userInput != 'a');

    // Return 0n upon successful termination
    return 0;
}

void move(ROBOT *robo) {
    // Using this switch case, based on the direction of the robot, we move the robot.
    // Note that, there is a need to deference the pointer first, in order to access the attributes needed
    switch ((*robo).dir) {
        case N:
            // If robot is pointing to NORTH, increment y position
            (*robo).ypos++;
            break;
        case E:
            // If robot is pointing to EAST, increment x position
            (*robo).xpos++;
            break;
        case S:
            // If robot is pointing to SOUTH, decrement y position
            (*robo).ypos--;
            break;
        case W:
            // If robot is pointing to WEST, decrement x position
            (*robo).xpos--;
            break;
        default:
            // If the direction is not any of the above, an error has happened. Exit with status code 1
            printf("ERROR -> direction does not exist.\n");
            exit(1);
            break;
    }
}

void turn(ROBOT *robo) {
    // We need to increment the dir by one. THis is the same as turning 90 degrees clockwise
    // Note that, the modulo of 4 is used to get numbers between 0 and 3 (including) only
    (*robo).dir = ((*robo).dir + 1) % 4;
}

void clearBuffer() {
    char temp; // Variable to hold the char read from stdin

    // Read chars until you reach \n
    while ((temp = getchar()) != '\n');
}

char readInput(char *promt) {
    char usrInput; // Variable to hold the user input

    // Print the promt on the console
    printf("%s\n", promt);
    // Get the first char that the user types
    usrInput = getchar();
    // Clear the buffer for later times
    clearBuffer();

    // Return the char that was read
    return usrInput;
}

int validateInput(char userInput) {
    // If the char is not 'a', 'm', or 't' return false and print a message
    if (userInput != 'a' && userInput != 'm' && userInput != 't') {
        printf("Please enter 'm' to move the robot, 't' to turn the robot by 90 degrees, and 'a' to exit the programe.\n");
        return 0;
    }
    // The char is one of the above, return true
    return 1;
}

void printRoboPos(ROBOT robo) {
    char *dir; // Variable to hold the direction string
    // Use a switch construct to get the direction and save it s a string
    switch (robo.dir) {
        case N:
            dir = "North";
            break;
        case E:
            dir = "East";
            break;
        case S:
            dir = "South";
            break;
        case W:
            dir = "West";
            break;
        default:
            // If the direction is not any of the above, an error has happened. Exit with status code 1
            printf("ERROR -> direction does not exist.\n");
            exit(1);
            break;
    }
    // Print the robo's positionf and direction on seperate lines
    printf("x-pos: %d\ny-ps: %d\ndir: %s\n", robo.xpos, robo.ypos, dir);
}