/*
 * Simple expression calculator
 * Supports expressions with basic operators and parentheses.
 * Example: 8+(4*7)
 *
 * Author: Samu
 * Description: School project demonstrating recursion, basic parsing and
 *              input validation in C.
 */

#include <stdio.h>
#include <ctype.h> 


char theLine[100];  
int position = -1;  

//! Returns next character from the line

char takeNextCharacter(void) {
    position++;   
    return theLine[position];
}

//! Checks that the expression contains only digits, operators and parentheses

int checkSyntax() {
    for (int i = 0; theLine[i] != '\0'; i++) {
        char c = theLine[i];


        
        if (!(isdigit(c) || c== '+' || c=='-' || c=='*' || c=='/' || c=='(' || c==')')){
            printf("Error: invalid character '%c'\n",c);
            return 0;
        }
    }
    return 1;
}

//! Recursive evaluation of form: <A> <op> <B>

int compute(void) {
    char A,B, op;
    int leftValue, rightValue;

    A = takeNextCharacter();  

    if (A == '('){
        leftValue = compute();
        (void)takeNextCharacter(); //consume ')'
    }else{
        leftValue = A - '0'; 
    }

    op = takeNextCharacter(); 


    B = takeNextCharacter();
    if(B == '(') {
        rightValue = compute();
        (void)takeNextCharacter();  //consume ')'
    }else {
        rightValue = B - '0';
    }
 
    int result = 0;
    if(op == '+') result = leftValue + rightValue;
    else if(op == '-') result = leftValue - rightValue;
    else if(op == '*') result = leftValue * rightValue;
    else if(op == '/') result = leftValue / rightValue;
        if (rightValue == 0) {
            printf("Error: division by zero\n");
            return 0;
        }
        result = leftValue / rightValue;


    printf("Compute: %d %c %d = %d\n",leftValue, op, rightValue, result);

    return result;
}


int main(void) {
    printf("Enter expression (e.g. 8+(4*7)): ");
    scanf("%99s", theLine); 

    if(!checkSyntax()){
        printf("Program terminated due to invalid expression.\n");
        return 1;
    }

    position = -1; 
    printf("You entered: %s\n", theLine);
    printf("Result: %d\n", compute());
    
    return 0;
}