#include <stdlib.h>
#include <stdio.h>

int main()
{
    int chars=0; // To store n chars
    int words=0; // To store n words
    int lines=0; // To store n lines
    int c; // Current char
    int prevC; // Previous char

    // Print instructions
    printf("Enter text, finish writing by doing ctrl+d (EOF):\n");
    
    // While the current char is not EOF
    while((c=fgetc(stdin))!=EOF){
        // If c is equal to newline
        if(c=='\n'){
            // If the previous char is not a space and not a newline
            if(prevC!=' ' && prevC!='\n'){
                // Increment the words count
                words++;
            }
            // Increment the line count
            lines++;
        } else {
            // If the current char is not a newline
            // Increment the char count
            chars++;
            // If the current char is a space and the previous char is not a space
            if(c == ' ' && prevC != ' '){
                // Increment the word count
                words++;
            } 
        }
        // Set the previous char to be the current char
        prevC=c;
    }
    
    // Print statistics about text
    printf("Chars: %d\n Words: %d\n Lines: %d\n",chars,words,lines);
    
    // Exit gracefully
    return 0;
}
