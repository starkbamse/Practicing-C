/**
 * 
 * Write a C program to add two matrix (e.g.: 2x2) using pointers or arrays (max size should be 4x4). C program to input two matrix from user and find sum of both matrices using pointers.

Input matrix1: 
1 2 
4 5 

Input matrix2: 
9 8 
6 5 
Sum of both matrices:
10 10
10 10 
The input to the program should be provided in the following way:

Input the size: 2 2
Input elements of matrix 1: 1 2 4 5
Input elements of matrix 2: 9 8 6 5

The sum is: 
10 10 
10 10
Please remember about the error handling if the elements are not numbers or if the number of elements in the matrix is not as specified in the size.
 * 
*/

//Include section
#include <stdio.h>
#include <stdlib.h>

//Define section
#define MAX 5
#define INITIAL_MEMORY_ALLOCATION 1
#define NINE 57
#define ZERO 48
#define MAX_ROW_SIZE 4
#define MAX_COL_SIZE 4
#define MIN_ROW_SIZE 1
#define MIN_COL_SIZE 1
//Main program section

/**
* This program is a useful program because it is used
* in very useful situations, therefore you should
* use it.
* 
* Purpose: Being useful is a good trait
* DIT632
* 
* Author: A useful person, 2024
*
* Note: all variable decl at the top of each method.
* define where the program logic starts.
* 
**/

typedef struct {
    char* number;
    int size;
} number;

int readIntoMatrix(number*matrix,size_t allocation,int expectedSize);
void processMatrix(int* dest,number*src,int size);
int main(int argc,char*argv[]) {
    int c=0;
    size_t allocation=INITIAL_MEMORY_ALLOCATION;
    number* rMatrix1;
    number* rMatrix2;
    int* pMatrix1;
    int* pMatrix2;
    int* resultMatrix;
    int position=0;

    int rowsNCols[2]={0,0};
    int setElement=0;
    int size;
    printf("Input the size: ");

    while((c=fgetc(stdin))!='\n' && c!=EOF){
        if(c>ZERO && c<NINE){
            if(setElement<2){
                rowsNCols[setElement]=c-ZERO;
            }
            setElement++;
        }
    }

    if(rowsNCols[0]==0 
    || rowsNCols[1] ==0 
    || setElement>2
    || rowsNCols[0] > MAX_ROW_SIZE
    || rowsNCols[1] > MAX_COL_SIZE 
    || rowsNCols[0] < MIN_ROW_SIZE
    || rowsNCols[1] < MIN_COL_SIZE    ) {
        printf("Invalid size specified\n");
        return 0;
    }

    size=rowsNCols[0]*rowsNCols[1];

    
    rMatrix1=malloc(sizeof(number)*size);
    rMatrix2=malloc(sizeof(number)*size);



    printf("Input elements of matrix 1: ");
    if(readIntoMatrix(rMatrix1,allocation,size)==0){
        return 0;
    }
    printf("Input elements of matrix 2: ");
    if(readIntoMatrix(rMatrix2,allocation,size)==0){
        return 0;
    } 

    pMatrix1=malloc(size);
    pMatrix2=malloc(size);
    resultMatrix=malloc(size);
    
    processMatrix(pMatrix1,rMatrix1,size);
    processMatrix(pMatrix2,rMatrix2,size);
    free(rMatrix1);
    free(rMatrix2);

    for(int i=0;i<size;i++){
        resultMatrix[i]=pMatrix1[i]+pMatrix2[i];
    }
    printf("The sum is:\n"); // 1 2 3 4
    for(int x=0;x<rowsNCols[0];x++){
        for(int i=0;i<rowsNCols[1];i++){
            printf("%d ",resultMatrix[i]);

        }
        printf("\n");
    }
    
    free(pMatrix1);
    free(resultMatrix);
    free(pMatrix2);

    return 0; 
}

int readIntoMatrix(number* matrix,size_t allocation,int expectedSize) {
    int currentNumber=0;
    int position=0;
    int allocated=0;
    int c;
    int prevC;
    int i;

    for(i=0;i<expectedSize;i++){
        matrix[i].number=malloc(allocation);
        matrix[i].number[0]='*';
    }

    while((c=fgetc(stdin))!='\n'&& c!=EOF){
            if(c!=' '){
                if((position+1)>allocation){
                    allocation*=2;
                    matrix[currentNumber].number=realloc(matrix[currentNumber].number,allocation);
                    if(matrix[currentNumber].number==NULL){
                        return 0;
                    }
                }
                if(c<ZERO || c>NINE){
                    printf("Invalid input: %c\n",c);
                    return 0;
                }
                matrix[currentNumber].number[position]=(char) c;
                position++;
                prevC=c;
            } else {
                if(position>0){
                    matrix[currentNumber].number[position]='\0';
                    position=0;
                    currentNumber++;
                }
            }
    }
    currentNumber++;

    if((currentNumber)<expectedSize){
        printf("invalid\n");
        return 0;
    }
    return 1;
    
}

void processMatrix(int* dest,number*src,int size){
     for(int i=0;i<size;i++){
        dest[i]=atoi(src[i].number);
     }
}