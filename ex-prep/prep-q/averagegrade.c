/******************************************************************************

Write a C program to input marks of five subjects Physics, Chemistry, Biology, Mathematics and
Computer, calculate percentage and grade according to given conditions:
If percentage >= 90% : Grade A
If percentage >= 80% : Grade B
If percentage >= 70% : Grade C
If percentage >= 60% : Grade D
If percentage >= 40% : Grade E
If percentage < 40% : Grade F

*******************************************************************************/

// Include section
#include <stdio.h>

int main()
{
    // Variable declarations
    int physics; // The grade for physics
    int chemistry; // Chemistry grade
    int biology; // Biology grade
    int math; // Math grade
    int computer; // CS greade
    float percentage; // Average percent

    // Program logic
    
    // Prompt the user
    printf("Input marks of five subjects: ");
    
    // Read the physics grade
    scanf("%d",&physics);
    
    // Clear buffer
    while(fgetc(stdin)!='\n');
    
    // Read chemistry grade
    scanf("%d",&chemistry);
    
    // Clear buffer
    while(fgetc(stdin)!='\n');
    
    // Read biology grade
    scanf("%d",&biology);
    
    // Clear buffer
    while(fgetc(stdin)!='\n');
    
    // Read math grade
    scanf("%d",&math);
    
    // Clear buffer
    while(fgetc(stdin)!='\n');
    
    // Read computer grade
    scanf("%d",&computer);
    
    // Clear buffer
    while(fgetc(stdin)!='\n');

    // Calculate average percentage
    percentage=(physics+chemistry+biology+math+computer)/5.0;
    
    // Output percentage 
    printf("Percentage = %.2f\n",percentage);
    
    // Percentage greater or eq. to 90
    if(percentage>=90){
        printf("Grade A\n"); // Print grade A
    } else if(percentage>=80){ // if greater or eq. to 80
        printf("Grade B\n"); // Print grade B
    } else if(percentage>=70){ // if greater or eq. to 70
        printf("Grade C\n"); // Print grade C
    } else if(percentage>=60){ // if greater or eq. to 60
        printf("Grade D\n"); // Print grade D
    } else if(percentage>=40){ // if greater or eq. to 40
        printf("Grade E\n"); // Print grade E
    } else if(percentage<40){ // if less than 40
        printf("Grade F\n"); // Print grade F
    }
    
    // Exit gracefully
    return 0;
}
