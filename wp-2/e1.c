#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Define possible directions as enums.
enum DIRECTION {N,E,S,W};


// Define a structure for the robot.
typedef struct {
int xpos;
int ypos;
enum DIRECTION dir;
} ROBOT;

// Function declarations
void turn(ROBOT *robot); // Function to turn the robot 90 degrees clockwise.
void move(ROBOT *robot); // Function to move the robot one step in the current direction.

void turn(ROBOT *robot){
    switch (robot->dir)
        {
        case N:
            robot->dir = E;
            break;
        case E: 
            robot->dir = S;
            break;
        case S:
            robot->dir = W;
            break;
        case W:
            robot->dir = W;
            break;
        }
}

void move(ROBOT *robot){
    switch (robot->dir)
    {
    case N:
        robot->ypos++;
        break;
    case E: 
        robot->xpos++;
         break;
    case S:
        robot->ypos--;
         break;
    case W:
        robot->xpos--;
        break;
    }
}
int main(int argc, char * argv[]){
    // Variable declarations
    
    int x; // The x-coordinate of the robot.
    int y; // The y-coordinate of the robot.
    ROBOT* robot; // The robot object.
    char orders[30]; // Orders to turn or move the robot.
    int i; // Index of the loop

    do {
    printf("\nPlease enter the initial x-coordinate of the robot (-1 to exit): ");
    scanf("%d", &x);
    if (x == -1)
    {
       printf("\nExiting program.\n");
       exit(1);
    } else if (x > 99 || x < 0)
    {
        printf("\nThe initial x-coordinate must be between 0 and 99.\n");
        return 1;
    } else {
        robot ->xpos = x;
    }
    printf("\nPlease enter the initial y-coordinate of the robot (-1 to exit): ");
    scanf("%d", &y);
    if (y == -1)
    {
       printf("\nExiting program.\n");
       exit(1);
    }else if (y > 99 || y < 0)
    {
        printf("\nThe initial y-coordinate must be between 0 and 99.\n");
        return 1;
    } else {
        robot->ypos = y;
    }

    printf("\nPlease enter a string of characters 'm' and 't', where m stands for move one step in current direction and t for turn of 90 degrees clockwise. ('-q' to exit): ");
    scanf("%s", orders);
    if (strcmp(orders, "-q")!= 0)
    {
       robot->dir = N;
       for (i = 0; i < strlen(orders); i++)
    {
        if (!(orders[i] == 'm'|| orders[i] == 't')) {
        /* If the received string has any other characters than 'm' or 't' */
        printf("\nPlease enter a string containing only 'm's or 't's in your request.\n");
        return 0;
        }
    }
    } else {
        printf("\nExiting program.\n");
        exit(1);
    }
    for (i = 0; i < strlen(orders); ++i)
        {
            switch(orders[i]){
                case 'm':
                    move(robot);
                    break;
                case 't':
                    turn(robot);
                    break;
            }
        }
    
    printf("\nNew position of the robot: x-coordinate: %d y-coordinate: %d.\n", robot->xpos, robot->ypos);
    } while (!feof(stdin));
    
    return 0;
}