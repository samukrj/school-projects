#include <stdio.h>
#include <ctype.h> 

char theLine[100];   //pole znakov, do ktoreho sa ulozi text
int position = -1;  //pozicia pre takeNextCharacter



//!Funkcia, ktora vracia dalsi znak z theLine

char takeNextCharacter(void) {
    position++;   //  
    return theLine[position];
}


//!Kontrola syntaxe

int checkSyntax() {
    for (int i = 0; theLine[i] != '\0'; i++) {
        char c = theLine[i];


        //povolene len cisla, operatory a zatvorky
        if (!(isdigit(c) || c== '+' || c=='-' || c=='*' || c=='/' || c=='(' || c==')')){
            printf("Chyba: nepovoleny znak '%c'\n",c);
            return 0;
        }
    }
    return 1;
}


//!Rekurzivny vypocet pre formu: <A> <op> <B>

int compute(void) {
    char A,B, op;
    int leftValue, rightValue;

    A = takeNextCharacter();  //prve cislo

    if (A == '('){
        leftValue = compute();
        (void)takeNextCharacter();



    }else{
        leftValue = A - '0'; 
    }

    op = takeNextCharacter(); //operator + - * /



    B = takeNextCharacter(); // prave cislo 
    if(B == '(') {
        rightValue = compute();
        (void)takeNextCharacter();
    }else {
        rightValue = B - '0';
    }
    //Vypocet vysledku tejto trojice 
    int result = 0;
    if(op == '+') result = leftValue + rightValue;
    else if(op == '-') result = leftValue - rightValue;
    else if(op == '*') result = leftValue * rightValue;
    else if(op == '/') result = leftValue / rightValue;

    printf("Vypocet: %d %c %d = %d\n",leftValue, op, rightValue, result);

    return result;
}



//!Hlavny program
int main(void) {
    printf("Zadaj vyraz (napr. 8+(4*7)): ");
    scanf("%s", theLine); 

    if(!checkSyntax()){
        printf("Program konci kvoli chybe vo vyraze.\n");
        return 1;
    }

    position = -1; //reset citania
    printf("Zadal si: %s\n", theLine);
    printf("Vysledok: %d\n", compute());
    
    return 0;
}