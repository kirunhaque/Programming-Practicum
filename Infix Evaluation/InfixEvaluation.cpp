/* This file contains the user interface code for the Infix Evaluation Project
 *  Project 5 for CS 211 for Fall 2017
 *
 * Date: 10/21/17
 *
 * Author: Pat Troy
 *
 */

/**************************************************************/
/*                                                            */
/*  The Code below this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/

#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;
// Enumarated Type specifying all of the Tokens
enum TokenType{
    ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOFILE
};

void printCommands()
{
    printf ("The commands for this program are:\n\n");
    printf ("q - to quit the program\n");
    printf ("? - to list the accepted commands\n");
    printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}



// Class to hold the Token information
class Token
{
private:
    TokenType type;
    char      op;       // using '$' as undefined/error
    int       val;      // using -999 as undefined/error
    
public:
    
    // Default to initialize to the ERROR TokenType
    Token()
    {
        type = ERROR;
        op = '$';
        val = -999;
    }
    
    // Initialize to a specific TokenType
    Token (TokenType t)
    {
        type = t;
        op = '$';
        val = -999;
    }
    
    // Set to a specific TokenType
    void setToType(TokenType t)
    {
        type = t;
        op = '$';
        val = -999;
    }
    
    // Set to a OPERATOR TokenType with specific operator value
    void setToOperator(char c)
    {
        type = OPERATOR;
        op = c;
        val = -999;
    }
    
    // Set to a VALUE TokenType with a specific numeric value
    void setToValue(int v)
    {
        type = VALUE;
        op = '$';
        val = v;
    }
    
    // return true if the Current Token is of the given TokenType
    bool equalsType(TokenType t)
    {
        if (type == t)
            return true;
        else
            return false;
    }
    
    // return true if the Current Token is of the OPERATOR TokenType
    //     and contains the given operator character
    bool equalsOperator(char c)
    {
        if (type == OPERATOR && op == c)
            return true;
        else
            return false;
    }
    
    // Return the Operator for the current Token
    //   verify the current Token is of the OPERATOR TokenType
    char getOperator ()
    {
        if (type == OPERATOR)
            return op;
        else
            return '$';   // using $ to indicate an error value
    }
    
    // Return the Value for the current Token
    //   verify the current token is of the value TokenType
    int getValue()
    {
        if (type == VALUE)
            return val;
        else
            return -999;  // using -999 to indicate an error value
    }
};


class TokenReader
{
private:
    char inputline[300];  // this assumes that all input lines are 300 characters or less in length
    bool needline;
    int pos;
    
    
public:
    
    // initialize the TokenReader class to read from Standard Input
    TokenReader()
    {
        // set to read from Standard Input
        inputline[0] = '\0';
        pos = 0;
        needline = true;
    }
    
    // Force the next getNextToken to read in a line of input
    void clearToEoln()
    {
        needline = true;
    }
    
    // Return the next Token from the input line
    Token getNextToken()
    {
        char* endCheck;
        
        //printf ("getToken %d, %d, %s\n", pos, needline, inputline);
        
        // get a new line of input from user
        if (needline)
        {
            endCheck = fgets ( inputline, 300, stdin);
            
            if (endCheck == NULL )
            {
                printf ("Error in reading");
                Token t(EOFILE);
                return t;
            }
            
            for (int i = 0 ; i < strlen(inputline) ; i++)
                if ('\n' == inputline[i])
                    inputline[i] = ' ';
            strcat (inputline , " ");    // add a space at end to help deal with digit calculation
            needline = false;
            pos = 0;
        }
        
        // skip over any white space characters in the beginning of the input
        while ( pos < strlen(inputline) && isspace(inputline[pos]) )
        {
            pos++;
        }
        
        // check for the end of the current line of input
        if (pos >= strlen(inputline))
        { // at end of line
            needline = true;
            Token t(EOLN);
            return t;
        }
        
        // Get the next character from the input line
        char ch = inputline[pos]; pos++;
        
        // check if 'q' or 'Q' was entered ==> QUIT Token
        if ( 'q' == ch || 'Q' == ch )
        {
            return Token (QUIT);
        }
        
        // check if "?" was entered ==> HELP Token
        if ( '?' == ch )
        {
            return Token (HELP);
        }
        
        // check for Operator values of: + - * / ( )  ==> OPERATOR Token
        if ( ('+' == ch) || ('-' == ch) || ('*' == ch) ||
            ('/' == ch) || ('(' == ch) || (')' == ch) )
        {
            Token t;
            t.setToOperator( ch );
            return t;
        }
        
        // check for a number  ==> VALUE Token
        if (isdigit(ch))
        {
            int number = int (ch) - int('0');  // subtract ascii value of ch from ascii value of '0'
            ch = inputline[pos]; pos++;
            while (isdigit(ch))
            {
                number = number * 10 + int (ch) - int('0');
                ch = inputline[pos]; pos++;
            }
            pos--; // since number calcuation check one character after the last digit
            Token t;
            t.setToValue( number );
            return t;
        }
        
        // Input in not valid if code get to this part ==> ERROR Token
        return Token (ERROR);
    }
    
};




/**************************************************************/
/*                                                            */
/*  The Code above this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/

void processExpression (Token inputToken, TokenReader *tr, bool debugMode);

int main(int argc, char *argv[])
{
    /***************************************************************/
    /* Add code for checking command line arguments for debug mode */
    //Traverse argument values to check debugMode is on
    bool debugMode = false;
    for (int i = 0; i < argc; i++){
        if (strcmp( argv[i], "-d") == 0){
            debugMode = true;
        }
    }
    
    Token inputToken;
    TokenReader tr;
    
    printf ("Starting Expression Evaluation Program\n\n");
    printf ("Enter Expression: ");
    
    
    inputToken = tr.getNextToken ();
    
    while (inputToken.equalsType(QUIT) == false)
    {
        /* check first Token on Line of input */
        if(inputToken.equalsType(HELP))
        {
            printCommands();
            tr.clearToEoln();
        }
        else if(inputToken.equalsType(ERROR))
        {
            printf ("Invalid Input - For a list of valid commands, type ?\n");
            tr.clearToEoln();
        }
        else if(inputToken.equalsType(EOLN))
        {
            printf ("Blank Line - Do Nothing\n");
            /* blank line - do nothing */
        }
        else
        {
            processExpression(inputToken, &tr, debugMode);
        }
        
        printf ("\nEnter Expression: ");
        inputToken = tr.getNextToken ();
    }
    
    printf ("Quitting Program\n");
    return 1;
}

//class for stack
class myStack {
private:
    int* arr;
    int size;
    int top;
public:
    void init();
    void popAndEval(myStack numStack, myStack opStack);
    bool isEmpty();
    void push(int val);
    int getTop();
    void pop();
    void resetStack();
};

void myStack :: init() {
    this->size = 2;
    this->arr = new int [this->size];
    this->top = 0;
}

bool myStack:: isEmpty(){
    if(this->top == 0){  //if stackAmount is 0, then stack is empty
        return true;
    }
    else return false;
}

void myStack:: push(int val){
    if (this->size == this->top){
        int prevSize = this->size; //store current size
        int* temp;
        temp = new int[this->size + 2];
        for (int i = 0; i < prevSize; i++){
            temp[i] = this->arr[i];
        }
        delete [] arr;
        this->arr = temp;
        this->size = prevSize + 2;
    }
    this->arr[this->top] = val;
    this->top = this->top + 1;
}

int myStack :: getTop(){
    int topVal;
    if (isEmpty() == true) return -999;
    topVal = this->arr[this->top - 1];
    return topVal;
}

void myStack:: pop(){
    this->top = this->top - 1;
}

void myStack:: resetStack(){
    delete[]this->arr;
    init();
}


/*A bool function (using pass by address) to evaluate the last two values on numStack using
 the last operator on opStack. Parameters: myStack &numStack, myStack &opStack, char op */
bool popAndEval(myStack &numStack, myStack &opStack, char op){
    int result = 0;
    int v2 = numStack.getTop();
    if (v2 == -999) return false; //return false if numStack is empty
    numStack.pop();
    int v1 = numStack.getTop();
    if (v1 == -999) return false;
    numStack.pop();
    
    if (op == '+'){         //Evaluate if operator is +
        result = v1 + v2;
    }
    else if(op == '-'){     //Evaluate if operator is -
        result = v1 - v2;
    }
    else if(op == '*'){     //Evaluate if operator is *
        result = v1 * v2;
    }
    else if (op == '/'){   //Evaluate if operator is /
        result = v1/v2;
    }
    opStack.pop();
    numStack.push(result);
    return true;
}

void processExpression (Token inputToken, TokenReader *tr, bool debugMode)
{
    /**********************************************/
    /* Declare both stack head pointers here      */
    myStack numStack, opStack;
    numStack.init();
    opStack.init();
    char op = '\0';
    int charVal = 0;
    char closeParentheses = ')';
    char openParentheses = '(';
    
    /* Loop until the expression reaches its End */
    while (inputToken.equalsType(EOLN) == false)
    {
        /* The expression contain a VALUE */
        if (inputToken.equalsType(VALUE))
        {
            /* make this a debugMode statement */
            if (debugMode == true){
                printf ("Val: %d, ", inputToken.getValue() );
            }
            // add code to perform this operation here
            numStack.push(inputToken.getValue());
            
        }
        
        /* The expression contains an OPERATOR */
        else if (inputToken.equalsType(OPERATOR))
        {
            /* make this a debugMode statement */
            if (debugMode == true){
                printf ("OP: %c, ", inputToken.getOperator() );
            }
            
            // add code to perform this operation here
            if (inputToken.getOperator() == '('){
                charVal = int( inputToken.getOperator() );
                opStack.push(charVal);              //If operator is open parenthesis, push on stack.
            }
            
            //push, pop and evaluate when enouctering addition/subtraction
            if (inputToken.getOperator() == '+' || inputToken.getOperator() == '-'){
                
                while(opStack.isEmpty() == false && (char( opStack.getTop()) == '+' || char( opStack.getTop()) == '-' ||
                                                     char( opStack.getTop()) == '*' || char( opStack.getTop()) == '/')){
                    op = char(opStack.getTop());
                    if(popAndEval(numStack, opStack, op) == false) break;       //break loop when numStack is empty
                }
                charVal = int( inputToken.getOperator() );
                opStack.push(charVal);
            }
            
            //push, pop and evaluate when encountering multiplication/division
            if (inputToken.getOperator() == '*' || inputToken.getOperator() == '/'){
                while(opStack.isEmpty() == false && (char( opStack.getTop()) == '*' ||
                                                     char( opStack.getTop()) == '/')){
                    op = char(opStack.getTop());
                    if(popAndEval(numStack, opStack, op) == false) break;      //break loop when numStack is empty
                }
                charVal = int( inputToken.getOperator() );
                opStack.push(charVal);
            }
            
            //push, pop and evaluate when encountering closeing parantheses
            if (inputToken.getOperator() == closeParentheses){
                while(opStack.isEmpty() == false && char(opStack.getTop() ) != openParentheses){
                    op = char(opStack.getTop());
                    if(popAndEval(numStack, opStack, op) == false) break;       //break loop when numStack is empty
                }
                if (opStack.isEmpty() == true){
                    cout << "Sorry, the operator stack is empty\n";
                }
                else{
                    opStack.pop();
                }
            }
        }
        /* get next token from input */
        inputToken = tr->getNextToken ();
    }
    
    /* The expression has reached its end */
    // add code to perform this operation here
    
    while (opStack.isEmpty() == false){
        op = char(opStack.getTop());
        if(popAndEval(numStack, opStack, op) == false) break;           //break loop when numStack is empty
    }
    if (numStack.isEmpty() == true){
        cout << "\nSorry, there's no solution due to an error in the expression (Value stack is empty).";
    }
    else{
        cout << "The solution to this expresion is: " << numStack.getTop();
    }
    printf ("\n");
    opStack.resetStack();
    numStack.resetStack();
}
