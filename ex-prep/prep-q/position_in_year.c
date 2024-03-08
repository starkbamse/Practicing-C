// Include section
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int days; // To keep track position of the day
    int day; // The specified day
    int month; // Specified month
    int year; // Specified year

    if(argc<4){ // if n arguments less than 4
        // print error message
        printf("Required format: ./program DD MM YYYY");
        // Exit gracefully
        return 0;
    }
    // Parse days 
    day=atoi(argv[1]);
    
    // Parse month
    month=atoi(argv[2]);
    
    // Parse year
    year=atoi(argv[3]);
    
    // From the first month until the month specified
    for(int i=1;i<month;i++){
        if(i==2){ // If month 2
            // Add 28 days
            days+=28;

            if((year%4)==0) { // if leap year         
                // Add another day
                days+=1;
            }
            // Continue to the next iteration
            continue;
        }
        
        // If the month is less than the 7th month
        if(i<=7){
            // If the month is even
            if((i%2)==0){
                // Add 30 days
                days+=30;
            } else {
                // Add 31 days
                days+=31;
            }
        } else if(i>=8){
            // If the month is greater than the 8th month or eq to
            // If the month is even
            if((i%2)==0){
                // Add 31 days
                days+=31;
            } else {
                // Add 30 days
                days+=30;
            }
        }
    }
    // Add number of days specified
    days+=day;
    
    // Print position in year
    printf("%d\n",days);
    
    // Exit gracefully
    return 0;
}
