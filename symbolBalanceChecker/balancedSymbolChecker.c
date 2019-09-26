/* ------------------------------------------------
 Project 2: Balanced Symbol Checker
 Class: CS 211
 Author: Kirun Haque
 Lab: 12pm-1:50pm
 System:  C Mac Xcode
 ------------------------------------------------ */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool debugMode = false;  //Declare and initialize a global variable for debugMode

//a struct for stack
typedef struct Stack
{
    char* dynamicArr;   //pointer to dynamic array
    int size;           //amount of space that should be allocated
    int topStack;       //counts how many values are in stack, which is top numebr
} Stack;


/*Void function will initialize the struct
 and will take a struct as parameter*/
void initializeStack(Stack* s){
    s->size = 2;
    s->dynamicArr = (char*)malloc(sizeof(char) * s->size);
    s->topStack = 0;
}


/*Void function will push/add opening symbol character onto stack
 Parameter: struct Stack*  s, char balanceSymbol */
void push (Stack* s, char balanceSymbol){
    //If stack is full, the dynamically grow the array
    if(s->size == s->topStack){
        int prevSize = s->size;             //save current size
        char *temp;
        temp = (char*)malloc(sizeof(char) * (prevSize + 2)); //Allocate space in memeor
        
        for (int i = 0; i < prevSize; i++){   //copy values to the new array
            temp[i] = s->dynamicArr[i];
        }
        free(s->dynamicArr);                  //deallocate the current array
        s->dynamicArr = temp;                 //new array with more space
        s->size = prevSize + 2;               //update size
        
        //Display debug info when debugMode is on
        if (debugMode == true){
            printf("\nThe old size of the dynamic array is %d\n", prevSize);
            printf("\nThe new size of the dynamic array is %d\n", s->size);
            printf("\nThe %d characters are being copied from the current dynamic array to the new dynamic array\n", prevSize);
        }
    }
    /* add opening symbol onto stack */
    s->dynamicArr[s->topStack] = balanceSymbol;
    s->topStack = s->topStack + 1;
    
    //Display debug info when debugMode is on
    if (debugMode == true) {
        printf("\n%c is being pushed onto stack\n", s->dynamicArr[s->topStack-1]);
    }
}


/*Void function will pop/remove top character on stack
 Parameter: struct Stack* s */
void pop (Stack* s) {
    if (debugMode == true){
        char c = s->dynamicArr[s->topStack-1];
        printf("\n%c is being popped off\n", c);
    }
    s->topStack = s->topStack - 1;
}


/*Bool function will return true if the stack is empty
and false if it's not. Parameter: struct Stack* s*/
bool isEmpty(Stack* s){
    if(s->topStack == 0){  //if stackAmount is 0, then stack is empty
        return true;
    }
    else return false;
}


/*Char function will return stack's top/last character
 Parameter: struct Stack* s */
char getTop (Stack* s){
    return (  s->dynamicArr[s->topStack-1] );
}


/*Bool function will return true if char is a opening symbol
 and false if it's not. Parameter: char balanceSymbol s*/
bool isOpeningSymbol(char balanceSymbol){
    if ( (balanceSymbol == '(') || (balanceSymbol == '{') ||
        (balanceSymbol == '[') || (balanceSymbol == '<') ) return true;
    else return false;
}


/*Bool function will return true if char is a closing symbol
 and false if it's not. Parameter: char balanceSymbol s*/
bool isClosingSymbol(char balanceSymbol){
    if ( (balanceSymbol == ')') || (balanceSymbol == '}') ||
        (balanceSymbol == ']') || (balanceSymbol == '>') ) return true;
    else return false;
}


/*Char function will return corresponding symbols
 Parameter: char symbol s*/
char getMatchingSymbol(char symbol){
    //Use if statements to get corresponding symbols
    if(symbol == '(') return ')';
    if(symbol == ')') return '(';
    
    if(symbol == '{') return '}';
    if(symbol == '}') return '{';
    
    if(symbol == '[') return ']';
    if(symbol == ']') return '[';
    
    if(symbol == '<') return '>';
    if(symbol == '>') return '<';
    
    return ' ';
}


/*Bool function will return true if stack's top/last symbol matches closing symbol
 Parameter: struct Stack s, char symbol*/
bool doSymbolsMatch(Stack s, char symbol){
    char getTopSymbol = getTop(&s);
    if (getTopSymbol == symbol) return true;
    return false;
}


/*This void function will initialize stack so it can be used again.
 Parameters: struct Stack s*/
void resetStack(Stack* s){
    free(s->dynamicArr);    //free current array for no memory leaks
    initializeStack(s);
}


/*This void function will insert spaces until position reaches the error.
Parameter: int numSpaces */
void insertSpaces(int numSpaces){
    for(int i = 0; i < numSpaces; i++){  //Use a for loop to display spacess
        printf(" ");
    }
}


//This function will display user input and parameter: char array[]
void displayInput(char userInput[]){
    int i = 0;
    printf("\n");
    while(userInput[i] !='\0'){      //Use a for loop to display entire expression
        printf("%c", userInput[i]);
        i++;
    }
    printf("\n");
}


int main(int argc, const char * argv[]) {
    Stack s;                //Declare a struct Stack variable called s
    initializeStack(&s);    //Initialize s values
    int MAX = 301;          //Input less than 300, fgets include '\n', max = 301
    int a;                  //Declare int variable track each character in userInput
    char getSymbol;
    char userInput[MAX];
    //Traverse argument values to check debugMode is on
    for (int i = 0; i < argc; i++){
        if (strcmp( argv[i], "-d") == 0){
            debugMode = true;
        }
    }
    while(true){
        printf("Please enter a expression with parentheses, braces, and/or brackets: ");    //Prompt user for input
        fgets(userInput,MAX, stdin);
        if ((userInput[0] == 'Q'|| userInput[0] == 'q') && userInput[1] == '\n') exit(0); //exit program
        
        //while loop to get rid of \n, fgets last character is \n
        a = 0;
        while (userInput[a] != '\0'){
            if (userInput[a] == '\n'){
                userInput[a] = '\0';
            }
            a++;
        }
        a = 0;            //Reset int a to traverse input again
        getSymbol = '\0'; //Initialize getSybmol.
        
        //Traverse through the input/expression to check sybmol balance
        while( userInput[a] != '\0'){
            
            if(isOpeningSymbol(userInput[a]) == true){
                push(&s, userInput[a]); //push char on stack if opening symbol
            }
            
            //Check conditions when encountering a closing symbol
            else if(isClosingSymbol(userInput[a]) == true){
                getSymbol = getMatchingSymbol(userInput[a]);        //get corresponding symbol
                //If symbols match remove stack's last value
                if((!isEmpty(&s)) && doSymbolsMatch(s, getSymbol) == true) pop(&s);
                
                //if symbols don't match, get Stack's top/last value and display message of what symbol is expected
                else if(isEmpty(&s) == false && doSymbolsMatch(s, getSymbol) == false){
                    getSymbol = getMatchingSymbol(s.dynamicArr[s.topStack-1]);
                    displayInput(userInput);
                    insertSpaces(a);
                    printf("^ expecting %c\n\n", getSymbol);
                    break;          //Break loop after error message is displayed
                }
                
                //If stack is empty, get Stack's top/last value and display error message
                else if(isEmpty(&s) == true) {
                    displayInput(userInput);
                    insertSpaces(a);
                    printf("^ missing %c\n\n", getSymbol);
                    break;          //Break loop after error message is displayed
                }
            }
            a++;
        }
        //Expression/input is balanced if stack is empty and last character is '\0'
        if ((isEmpty(&s) == true && (userInput[a] == '\0'))) {
            displayInput(userInput);
            printf("Expression is balanced\n\n");
        }
        
        //Expression/input is not balanced if stack is not empty and last character is '\0'
        else if ((userInput[a] == '\0') && (isEmpty(&s) == false)){
            char missingSym = getMatchingSymbol(s.dynamicArr[s.topStack - 1]);
            displayInput(userInput);
            insertSpaces(a);
            printf(" ^ missing %c\n\n", missingSym);
        }
        resetStack(&s); //Reset everything in stack for the next reiteration
    }
    return 0;
}
