#include <stdio.h>
#include <stdlib.h>

// Permute a string
void permute(char* item,int startAt, int length);

// Swap two chars with each other
void swap(char* item1, char* item2);

int main(int argc, char* argv[])
{
    // Permute the input argument
    permute(argv[1],0,strlen(argv[1]));
    // Exit gracefully
    return 0;
}
void swap(char* item1, char* item2){
    // Create temp a variable
    char tempA=*item1;
    
    // Create temp b variable
    char tempB=*item2;
    
    // Set item1 to temp B
    *item1=tempB;

    // Set item2 to temp A
    *item2=tempA;
 
}
void permute(char* item,int startAt, int length){
    // If the length is less than or equal to zero.
    if((length-startAt)<=0){
        // Print the current state of the string
        printf("%s\n",item);
        // Return
        return;
    }
    // From the current start to length
    for(int i=startAt;i<length;i++){
        // Swap the item at the current start with i
        swap(&item[startAt],&item[i]);
        
        // Recursively call permute but this time lock the current start in place
        permute(item,startAt+1,length);
        
        // Swap back the item at the current start with i once done, for backtracking.
        swap(&item[startAt],&item[i]); 

    }
}

