

#include <stdio.h>

int addFraction(int a,int c, int b, int d);
int subFraction(int a,int c, int b, int d);
int mulFraction(int a, int c, int b ,int d);
int addOrSubFraction(int a, int c, int b, int d, int add);
int simplifyFraction(int* nominator,int* denominator);

int main()
{
    
    // Add 1/3 and 3/9
    addFraction(1,3,3,9);
    
    // Subtract 1/1-1/3
    subFraction(1,1,1,3);
    
    // Subtract 1/3 - 1/3
    subFraction(1,1,3,3);
    
    // Multiply 1/3 * 1/3
    mulFraction(1,1,3,3);

    // Multiply -1/-3 * -1/-3
    mulFraction(-1,-1,-3,-3);

    // Add 13/25 and 31/9
    addFraction(13,31,25,9);

    return 0;
}

int subFraction(int a, int c, int b, int d){
    addOrSubFraction(a,c,b,d,0);
}

int addFraction(int a, int c, int b, int d){
    addOrSubFraction(a,c,b,d,1);
}

int mulFraction(int a, int c, int b, int d){
    //Variable decl
    int nominator= a*c; // Calculating nominator
    int denominator = b*d; // Calculating denominator

    simplifyFraction(&nominator,&denominator);
    printf("%d/%d\n",nominator,denominator);

}

int simplifyFraction(int* nominator,int* denominator){
    int simple=0; // To store whether or not the current number is simplest form
    int i; // To keep track of where we are in loop

    // While the number is not in the simplest form
    while(!simple){
        // Assume it will be simplest after this iteration
        simple=1;
        // From 2 to 9 
        for(i=2;i<=9;i++){
            // If the nominator and denominator are divisible by the current i
            if(*nominator % i==0 && *denominator % i ==0){
                // Divide the nominator by current i
                *nominator=*nominator/i;
                // Divide the denominator by current i
                *denominator=*denominator/i;
                // Since we have made the number more simple, it was not simple
                simple=0;
            }
        }
    }
}

int addOrSubFraction(int a, int c, int b, int d, int add){
    //Variable decl
    int nominator; // Calculating nominator
    int denominator = c*d; // Calculating denominator
    
    // If we want to add
    if(add){
        // Add the nominators
        nominator=(a*d)+(b*c);
    } else{
        // Subtract the nominators
        nominator=(a*d)-(b*c);
    }
    
    // If the nominator is 0 the fraction is 0
    if(nominator==0){
        printf("0\n");
        return 1;
    }
    
    simplifyFraction(&nominator,&denominator);

    // Print the new fraction
    printf("%d/%d\n",nominator,denominator);
    
    // Return 1 indicating success
    return 1;
}