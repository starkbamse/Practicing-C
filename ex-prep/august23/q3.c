/******************************************************************************
Write a calendar program using enums.
Your task is to write a program that will use separate enums for days of the week (Mon, Tue, etc)
and Weeks (week 1, week 2, ..., week 5). The program should increment the day every second.
After Sunday, the week should increment as well and the counting should start from the beginning.
Once it gets to week 5, it should start from the beginning.
The program should ask the user to provide the start day and week.
Every time the program increments the day, it should write the week and day on the console, e.g.:
Week 1, Monday
Week 1, Tuesday
...
You are NOT allowed to use strings to store the days and weeks.
In this question, you can use the online compiler.
Points:
- using enums: 1p
- correct increment of weeks and days: 2p
- using interrupts on timer: 2p
- checking for correct input: 1p
- comments: 1p

*******************************************************************************/

//Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Define section
#define MAX_WEEK 5
#define MEMORY_ALLOCATION 20

// To store dates
enum Days {
    Mon,
    Tue,
    Wed,
    Thu,
    Fri,
    Sat,
    Sun
};

// To get input as a string from the user
char* getInput(char* prompt,size_t allocation);

// To convert a string day into its corresponding enum int
int dayToEnum(char* day);

// Convert an enum int into its corresponding string value
char* enumToDay(int value);

int main(){
    enum Days day; // To store the current day
    int startingWeek; // To store the starting week
    int x; //To store the current week
    int i; //To store the current day
    
    // Retrieve the user's wanted start day
    char* userDay=getInput("Enter starting day: ",MEMORY_ALLOCATION);
    
    // If the parsing attempt returns -1 it means that user input is invalid
    if(dayToEnum(userDay)==-1){
        // Print error message
        printf("Invalid day\n");
        // Free occupied heap
        free(userDay);
        // Exit gracefully
        return 0;
    }
    
    // Convert the string day representation to enum int
    day=dayToEnum(userDay);
    
    // Retrieve the user's wanted start week
    char* userWeek=getInput("Enter starting week: ",MEMORY_ALLOCATION);
    
    // Convert the string representation into a number
    startingWeek=atoi(userWeek);
    
    // If the starting week is outside valid interval
    if(startingWeek<1 || startingWeek>MAX_WEEK){
        //Print error message
        printf("Invalid week\n");
        // Free occupied heap
        free(userDay);
        // Free occupied heap
        free(userWeek);
        // Exit gracefully
        return 0;
    }
    
    // Loop from starting week until the max week
    for(x=startingWeek;x<=MAX_WEEK;x++){
        // Loop from monday to sunday
        for(i=Mon;i<=Sun;i++){
            // If we are on the absolute first iteration
            if(i==Mon && x==startingWeek){
                // Set the current day to be the user's wanted start day
                i=day;
            }
            // Print the current week and day
            printf("Week %d, %s\n",x,enumToDay(i));
            
            // Sleep for one second
            sleep(1);
        }
        // If x is equal to the maximum week
        if(x==MAX_WEEK){
            // Set the current week to the starting week-1 since we will be incrementing by one
            // after this branch is finished, effectively creating a
            // infinite loop.
            x=startingWeek-1;
        }
    }
    
    // Free occupied heap
    free(userDay);
    // Free occupied heap
    free(userWeek);
    
    // Exit gracefully
    return 0;
}
char* enumToDay(int value){
    // Depending on what the enum value is we return different things
    switch(value){
        case 0:
            // If 0 return monday
            return "Monday";
        break;
        case 1:
            // If 1 return Tuesday
            return "Tuesday";
        break;
        case 2:
            // If 2 return Wednesday
            return "Wednesday";
        break;
        case 3:
            // If 3 return Thursday
            return "Thursday";
        break;
        case 4:
            // If 4 return Friday
            return "Friday";
        break;
        case 5:
            // If 5 return Saturday

            return "Saturday";
        break;
        case 6:
            // If 6 return Sunday
            return "Sunday";
        break;
        default:
            // If no match is found return error 
            return "err";
            break;
    }
}
int dayToEnum(char* day){
    // If the current day is monday
    if(strcmp(day,"Monday")==0){
        // Return 0
        return 0;
    } else if(strcmp(day,"Tuesday")==0){
        // If Tuesday return 1
        return 1;
    } else if(strcmp(day,"Wednesday")==0){
        // If Wednesday return 2
        return 2;
    } else if(strcmp(day,"Thursday")==0){
        // If Thursday return 3
        return 3;
    } else if(strcmp(day,"Friday")==0){
        // If Friday return 4
        return 4;
    } else if(strcmp(day,"Saturday")==0){
        // If Saturday return 5
        return 5;
    } else if(strcmp(day,"Sunday")==0){
        // If Sunday return 6
        return 6;
    } else {
        // If no match is found return -1.
        return -1;
    }
}

char* getInput(char* prompt,size_t allocation){
    int c; // The current char that we are at
    int position=0; // The current position in the users input
    char* input=malloc(allocation); // Allocate heap memory for the input
    
    // If memory allocation failed
    if(input==NULL){
        // Print error message
        printf("Memory allocation failed!");
        // Return empty string because no user input was read
        return "";
    }
    // Print the prompt
    printf("%s\n",prompt);
    
    // While the current char is not a newline nor eof
    while((c=fgetc(stdin))!='\n' && c!=EOF){
        // If the position +1 is bigger than the allocated memory
        if((position+1)>allocation){
            // Print error message
            printf("Invalid input entered");
            // Free occupied heap
            free(input);
            // Return empty string because no user input was read
            return "";
        }
        // Set the current read char at the current position in the string
        input[position]=(char)c;
        // Increment the position
        position++;
    }
    
    // Return user's input
    return input;
}

