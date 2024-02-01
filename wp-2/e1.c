//Include section
#include <stdio.h>
#include <stdlib.h>

//Define section
#define MOVE 109 // ASCII code for lowercase m
#define TURN 116 // ASCII code for lowercase t
#define MAX_INTERVAL 99 // Maximum coordinate
#define MIN_INTERVAL 0 // Minimum coordinate

//Main program section

/**
* This program simulates a robot that we can spawn,
* in some specified coordinates. After this, we can
* give instructions to the robot, on whether it should turn
* or move. The robot will move 90deg clockwise and 1 step at a time,
* always.
* 
* Purpose: To explore the boundarys of C's capabilities to simulate
* robots and their behavior.
* DIT632
* 
* 
**/

enum DIRECTION {N,O,S,W}; // Different directions that the robot can be in.
typedef struct {
    int xpos; // Robots x position
    int ypos; // Robots y position
    enum DIRECTION dir; // Current direction that the robot is facing.
} ROBOT; // Contains robot information, x pos, y pos and direction.

// Moves the robot by 1 step in the current direction.
void move(ROBOT* robot);

// Turns the robot clockwise 90deg.
void turn(ROBOT* robot);

// Asks the user to input coordinates.
int promptCoordinates(int* ptr);
int promptInstructions(ROBOT* robot);

int main(int argc,char*argv[]){
    //Variable declarations
    ROBOT robot={0}; // Robot, initialized to null.
    int doRun=1; // As long as this is 1, the program will repeatedly run.
    
    //Program logic
    do{
        // If any of the function calls return 0 it means that the user
        // has requested to exit.

        // Reset position to north
        robot.dir=N;

        // Print to stdout
        printf("Enter starting position x: ");

        // Request initial x coordinates from user.
        if((doRun=promptCoordinates(&robot.xpos))==0) return 0; 

        // Print to stdout
        printf("Enter starting position y: ");

        // Request initial y coordinates from user.
        if((doRun=promptCoordinates(&robot.ypos))==0) return 0;

        // Print to stdout
        printf("Enter instructions (m to move, t to turn): ");
        
        // Request robot instructions from user.
        if((doRun=promptInstructions(&robot))==0) return 0;
        
    } while(doRun); // While doRun is 1 we keep running the program.

}

int promptInstructions(ROBOT*robot){
    int c=0; // Stores the next character value.

    // While the current char is not EOF nor \n
    while((c=fgetc(stdin))!='\n' && c != EOF) {
        // Do a switch case on the current char
        switch (c) {
        case MOVE:
            // If its move, we move the robot in the current direction.
            move(robot);
            break;
        case TURN:
            // If its turn, we should turn the robot 90deg.
            turn(robot);
            break;
        default:
            // If unknown input is received return 0,
            // which signals that the user wants to exit.
            return 0;
            break;
        }
    }
    // Output the robot's new position.
    printf("Robot's new position, x: %d, y: %d\n",robot->xpos,robot->ypos);
    return 1;
}

int promptCoordinates(int*ptr){
    // If we can successfully parse the int.
    if(scanf("%d",ptr)==1) {
        // Check if the value is within the max and min intervals
        if(*ptr>MAX_INTERVAL || *ptr<MIN_INTERVAL){
            // Print error message.
            printf("Invalid interval. Specify a coordinate between 0 and 99.\n");
            return 0;
        }

        // We empty the buffer, it will always contain an extra \n.
        while((fgetc(stdin))!='\n');
        // Return successful status code.
        return 1;
    }
    // Signal to shutdown the program.
    return 0;
}

void turn(ROBOT* robot){
    // Dereference and check if the direction is west.
    if(robot->dir==W) {
        // "Loop" over by setting it to be N.
        robot->dir=N;
        return;
    }
    // Increment the direction to turn clockwise.
    robot->dir++;
}

void move(ROBOT* robot){
    switch(robot->dir){ // Dereference and get direction
        case N:
            // Dereference and increase y pos by 1.
            robot->ypos++;
        break;
        case O:
            // Dereference and increase x pos by 1.
            robot->xpos++;
        break;
        case S:
            // Dereference and decrease y pos by 1.
            robot->ypos--;
        break;
        case W:
            // Dereference and decrease x pos by 1.
            robot->xpos--;
        break;
        default:
        break;
    }
}