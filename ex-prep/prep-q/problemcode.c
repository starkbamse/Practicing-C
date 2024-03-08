/*
The following program has two mistakes in it, please find them, explain why these are mistakes
and correct them

*/

#include <stdio.h>
#define MAX_SIZE 5 //Maximum size of the array
int main(){
    int arr[MAX_SIZE]; //Declares an array size
    int i, num;
    
    //Enter size of array
    printf("Enter size of the array: ");
    scanf("%d", &num);
    
    //Reading elements of array
    printf("Enter elements in array: ");
    
    for(i=0; i<num; i++){
        scanf("%d", &arr[i]);
        /*
        The mistake was that the buffer was not being cleared after reading 
        integer using scanf. Since scanf will stop consuming buffer after an
        integer is read, it is necessary to clear the buffer after each read if
        multiple reads are required.
        */
        while(fgetc(stdin)!='\n'); // Consume the buffer until newline is seen.
    }
    
    printf("\nAll negative elements in array are: ");
    
    for(i=0; i<num; ++i){
        //Printing negative elements
        if(arr[i] < 0) {
            printf("%d\t", arr[i]);
        }
    }
    return 0;
}