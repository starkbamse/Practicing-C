

#include <stdio.h>
#include <stdint.h>

// Combines two 8 bit numbers into two 16 bit
uint16_t make_16bit(uint8_t least_significant, uint8_t most_significant);

// Prints binary number
void print_bin(uint32_t number);

int main(int argc, char* argv[])
{
    // Print the binary format of concatenated 7 and 1
    print_bin(make_16bit(7,1));
    
    // Gracefully exit
    return 0;
}

void print_bin(uint32_t number){
    //Variable declarations
    int valuableBits=0; // Number of valuable bits (that are not padding zeros)
    int padWithZero=0; // Number of bits to pad with zeros
    int i; // To keep track of where we are in loop
    int j; // To keep track of where we are in loop
    int position=0; // Position in the char array of the binary format
    
    char binNumber[32];
    
    // We are doing bit shifting, so while the number is still greater
    // than 0, it means we can do more shifting.
    while(number>0){
        // Increment the number of non-padding bits.
        valuableBits++;
        
        // If the current LSB is a 1
        if(number & 1){
            // Set the current value to 1
            binNumber[position]='1';
        } else {
            // If its a zero set it to zero
            binNumber[position]='0';
        }
        // Shift the number right by one bit
        number=number>>1;
        
        // Increment the position to make space for the new bit.
        position++;
    }
    
    // The number of zeros that we need to pad with is 32 - the n valuable bits
    padWithZero=32-valuableBits;
    // From 0 to 4 which is how many groups of 8 bits there are in 32 bits
    for(i=0;i<4;i++){
        // From 0 to 8 bits which is how many bits there are in each group.
        for(j=0;j<8;j++){
            // If we need to pad with zero
            if(padWithZero>0){
                // Print zero
                printf("0");
                // Since we have just padded, decrement the amount left to pad
                padWithZero--;
            } else if(position>=0){
                // If we still have not printed the entire binary number
                // Print the current index of the number (-1 since its zero-indexed)
                printf("%c",binNumber[position-1]);
                // Decrement the index
                position--;
            }
        }
        // If i is not the last group, we can separate using a dot
        if(i<3){
            // Print dot
            printf(".");
        }
    }
    // Print new line
    printf("\n");
}



uint16_t make_16bit(uint8_t least_significant, uint8_t most_significant){
    uint16_t newNumber=0; // The new 16 bit number

    // Concatenate most_significant using bitwise OR
    newNumber=newNumber | most_significant;
    
    // Shift the number 8 places to the left
    newNumber=newNumber<<8;

    // Concatenate least_significant using bitwise OR
    newNumber=newNumber | least_significant;
    
    // Return the new number
    return newNumber;

}
