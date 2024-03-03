/*

There are two mistakes in this program. Please find them, explain them and correct them:

*/

#include<stdio.h> //Used to include basic c library files

/*
The first mistake was that main was marked as a void function which is incorrect.
main's return exit code is the only way we can know if the program's execution
was successful or not. Therefore it must be marked as an integer as return type.
*/
int main() {
    //declaring and defining the array variables
    int a[5] = {100,101,102,103,104};
    int b[5] = {105,106,107,108,109};
    
    /*
    
    The second mistake was in the index that was being passed to the array.
    We can only access elements that are within the max index of the array,
    which in this case is less than 5, not 700 or 100.
    
    */
    
    //displaying the output
    printf("%d\n",a[0]);
    //and another element
    
    // The third mistake is that unless developer wants to print the value as
    // a char, the format string must be %d not %c
    printf("%d\n",b[1]);
}