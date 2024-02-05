//Include section
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 
//Main program section

/**
* This program accepts an abbreviation of the day,
* and a week number from 1 to 5. It then prints out
* each day in those weeks from start to finish, with an
* interval of 1 second.
* 
* Purpose: To practice the use of enums in the C programming
* language.
* DIT632
* 
* Author: Alexander Säfström, 2024
* 
**/

// An enumeration that stores all the days in a week.
// Made global to allow access from all functions.
typedef enum {
    Mon,
    Tue,
    Wed,
    Thu,
    Fri,
    Sat,
    Sun
} Day;

// An enumeration that stores all the weeks.
// Made global to allow access from all functions.
typedef enum {
    Week1,
    Week2,
    Week3,
    Week4,
    Week5
} Week;

// Used to print a day in string format
// by receiving the day enum.
void printDay(Day day);

// Used to print the string representation
// of a week from the Week enum.
void printWeek(Week week);

// Converts a string to the Day enum.
Day stringToDay(char day[3]);

int main(int argc, char* argv[]) {
    // Variable declarations
    Week startingWeek; // The week that we start counting from.
    Day startingDay; // The day that we start counting from.

    // Program logic
    scanf("%u",&startingWeek); // Get the starting week.
    while ((getchar()) != '\n');
    scanf("%u",&startingDay); // Get the starting day.

    // If the sum is greater than 5
    // or 0.
    if((startingWeek-1)>Week5 || startingWeek==0){
        // Print error
        printf("invalid week");
        return 0;
    }

    // If the sum is greater than 7
    // or 0.
    if((startingDay-1)>Sun || startingDay==0){
        // Print error
        printf("invalid day");
        return 0;
    }

        
    // Start from starting week-1 (due to indexing)
    // to the end of the week.
    for(int i=startingWeek-1;i<=Week5;i++){
        // If we have passed the first week we will
        // reset the day to monday.
        if(i>startingWeek-1) {
            startingDay=Mon; // Set day to Monday. 
        } else {
            startingDay-=1; // Whatever the user inputted - 1 since first enum starts at 0.
        }
        // For each week, print the day including sunday.
        for(int x=startingDay;x<=Sun;x++){
            // Halt execution for one second.
            sleep(1);
            printWeek(i); // Print the current week.
            printf(", "); // Print a separator
            printDay(x); // Print the current day.
            printf("\n"); // Print a newline.
        }
    }

    // Exit gracefully.
    return 0;
}

void printDay(Day day){
    switch (day) {
        case Mon: // If 0 print Monday
            printf("Monday");
        break;
        case Tue: // If 1 print Tuesday
            printf("Tuesday");
        break;
        case Wed: // If 2 print Wednesday
            printf("Wednesday");
        break;
        case Thu:// If 3 print Thursday
            printf("Thursday");
        break;
        case Fri:// If 4 print Friday
            printf("Friday");
        break;
        case Sat:// If 5 print Saturday
            printf("Saturday");
        break;
        case Sun:// If 6 print Sunday
            printf("Sunday");
        break;
        default:
            // No need to throw error here.
            break;
    }
}

void printWeek(Week week) {
    switch (week){
        case Week1: // If 0 print Week 1
            printf("Week 1");
        break;
        case Week2: // If 1 print Week 2
            printf("Week 2");
        break;
        case Week3: // If 2 print Week 3
            printf("Week 3");
        break;
        case Week4: // If 3 print Week 4
            printf("Week 4");
        break;
        case Week5: // If 4 print Week 5
            printf("Week 5");
        break;
        default:
            // No need to print error.
            break;
    }
}