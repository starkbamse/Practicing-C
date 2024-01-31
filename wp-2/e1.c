// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 2
// Exercise 1
// Submission code: 


/**
* This program allows the user to select a robot's starting coordinates and move and turn the robot.
* The program asks the user to input the starting x and y coordinates
* and also a string consisting of m's and t's , where m stands for move one step in current direction and 
* t for turn of 90 degrees clockwise. Finally, the program outputs the new coordinates of the user.
* The program will continue to work until the user finishes the program according to the instructions or with an EOF character.
* 
* Purpose: Robot control program with enums and structures.
* DIT632
* 
* 
**/

// Include section
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



// Define possible directions of the robot as enums.
enum DIRECTION {N,E,S,W};


// Define a structure for the robot.
typedef struct {
int xpos; // Robot has a x-coordinate
int ypos; // Robot has a y-coordinate
enum DIRECTION dir; // Robot has a direction
} ROBOT;

// Function declarations
void turn(ROBOT *robot); // Function to turn the robot 90 degrees clockwise.
void move(ROBOT *robot); // Function to move the robot one step in the current direction.


void turn(ROBOT *robot){
    // Depending on the current direction of the robot, we rotate it 90 degrees clockwise.
    switch (robot->dir)
        {
        // If the current direction is North
        case N:
        // Set the new direction to East.
            robot->dir = E;
            break;
        // If the current direction is East.
        case E: 
        // Set the new direction to South.
            robot->dir = S;
            break;
        // If the current direction is South.
        case S:
        // Set the new direction to East.
            robot->dir = W;
            break;
         // If the current direction is West.
        case W:
         // Set the new direction to North.
            robot->dir = N;
            break;
        }
}

void move(ROBOT *robot){
    // Depending on the robots current direction, we move the x or y coordinates.
    switch (robot->dir)
    {
    // If the current direction is North.
    case N:
    // Move the robot "up" which means incrementing the y-coordinate by 1.
        robot->ypos++;
        break;
    // If the current direction is East.
    case E: 
    // Move the robot "right" which means incrementing the x-coordinate by 1.
        robot->xpos++;
         break;
    // If the current direction is South.
    case S:
    // Move the robot "down" which means decrementing the y-coordinate by 1.
        robot->ypos--;
         break;
    // If the current direction is West.
    case W:
     // Move the robot "left" which means decrementing the x-coordinate by 1.
        robot->xpos--;
        break;
    }
}


// Main function of the program

int main(int argc, char * argv[]){
   
    // Variable declarations
    int x; // The x-coordinate of the robot.
    int y; // The y-coordinate of the robot.
    ROBOT* robot; // The robot object.
    char orders[30]; // Orders to turn or move the robot.
    int i; // Index of the loop

    // Do the following until an EOF character is encountered:
    do {
    // Ask user to input initial x-coordinate.
    printf("\nPlease enter the initial x-coordinate of the robot (-1 to exit): ");
    // Save the result in variable x.
    scanf("%d", &x);

    // If the user inputted -1, then exit the program with appropriate message.
    if (x == -1)
    {
       printf("\nExiting program.\n");
       return 1;
    } 
    // If the input is not between 0 and 99.
    else if (x > 99 || x < 0)
    {
        // Show error message and return.
        printf("\nThe initial x-coordinate must be between 0 and 99.\n");
        return 1;
    } 
    // If the input is valid.
    else {
        // Set the robot's x position to the user inputted value.
        robot ->xpos = x;
    }

    // Ask user to input initial y-coordinate.
    printf("\nPlease enter the initial y-coordinate of the robot (-1 to exit): ");
    // Save the result in variable y. 
    scanf("%d", &y);
    // If the user inputted -1, then exit the program with appropriate message.
    if (y == -1)
    {
       printf("\nExiting program.\n");
       return 1;
    }
    // If the input is not between 0 and 99.
    else if (y > 99 || y < 0)
    {
        // Show error message and return.
        printf("\nThe initial y-coordinate must be between 0 and 99.\n");
        return 1;
    } 
    // If the input is valid.
    else {
        // Set the robot's y position to the user inputted value.
        robot->ypos = y;
    }

    // Ask the user to enter the orders to move and turn.
    printf("\nPlease enter a string of characters 'm' and 't', where m stands for move one step in current direction and t for turn of 90 degrees clockwise. ('-q' to exit): ");
    // Save the orders in a variable.
    scanf("%s", orders);
    // If the user did not input '-q' to exit the program
    if (strcmp(orders, "-q")!= 0)
    {
       // Set the robot's initial direction to North.
       robot->dir = N;

       // Loop through every character in the inputter order string.
       for (i = 0; i < strlen(orders); i++) {
        // Check if all of the characters are either m or t.
        if (!(orders[i] == 'm'|| orders[i] == 't')) {
        // If the received string has any other characters than 'm' or 't', print error message and return.
        printf("\nPlease enter a string containing only 'm's or 't's in your request.\n");
        return 1;
        }
    }
    } 
    // If the user inputted '-q' then exit the program with appropriate message.
    else {
        printf("\nExiting program.\n");
        return 1;
    }

    // Loop through each character in the orders string.
    for (i = 0; i < strlen(orders); ++i)
        {
            // Depending on the current character
            switch(orders[i]){
                // If it is m, move the robot.
                case 'm':
                    move(robot);
                    break;
                // If it is t, turn the robot.
                case 't':
                    turn(robot);
                    break;
            }
        }
    
    // Output the new coordinates of the robot.
    printf("\nNew position of the robot: x-coordinate: %d y-coordinate: %d.\n", robot->xpos, robot->ypos);
    } 
    // Do it while an EOF character is detected.
    while (!feof(stdin));
    
    // return with success code.
    return 0;
}