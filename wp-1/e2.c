// Exercise 2

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Main function in the program

/*
* Purpose: 
*
* Authors: Kaisa Arumeel, Alexander Säfström, Omid Khodaparast
*/
int main(int argc, char *argv[]) {

    int limit,
    i,
    ascii;
    char insertedText[limit],
    encryptedText[limit];

    if (argc != 2){
       printf("Please enter the number of characters you wish to encrypt \n");
       return 0;
    }

    limit = atoi(argv[1]);

    do
    {
       printf("Type a text to encrypt with maximum length of %i \n", limit);
       scanf("%s", insertedText);

       for (i = 0; i < limit; i++)
       {
        ascii = (int)insertedText[i];
            // if current character is within a and m
            if (ascii >= 97 && ascii <=  109){
                // add "13" to ascii code to get encrypted character and store in solution char array
                encryptedText[i] = (char) (ascii + 13);
            //if current character is within n and z
            } else if (ascii >= 110 && ascii <= 122){
                // substract "13" to ascii code to get encrypted character and store in solution char array
                encryptedText[i] = (char) (ascii - 13);
            // if current character is within A and M
            } else if (ascii >= 65 && ascii <= 77){
                // substract "13" to ascii code to get encrypted character and store in solution char array
                encryptedText[i] = (char) (ascii + 13);
            // if current character is within N and Z
            } else if (ascii >= 78 && ascii <= 90){
                // substract "13" to ascii code to get encrypted character and store in solution char array
                encryptedText[i] = (char) (ascii - 13);
            }else {
                // if not a letter, leave it as it is
                encryptedText[i] = insertedText[i];
            }
       }
       printf("%s\n", encryptedText);
       
    }  while ((strcmp(insertedText, "^Z") != 0) || (strcmp(insertedText, "^d") != 0));
    
}