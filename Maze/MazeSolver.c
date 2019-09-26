/* ------------------------------------------------
 Project 3: Maze Solving
 Class: CS 211
 Author: Kirun Haque
 Lab: 12pm-1:50pm
 System:  C Mac Xcode
 ------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool debugMode = false;             //Global var for debugMode
//Maze struct definition
typedef struct mazeStruct
{
    char** darr;  /* declare dynamic array */
    int xsize, ysize;
    int xstart, ystart;
    int xend, yend;
} maze;

//linked struct definition
typedef struct linkedStruct
{
    int xElem;
    int yElem;
    struct linkedStruct* pNext;
    
}linked;
typedef linked* linkedPtr;


/*Void function will initialize the maze with correct coordinates and sizes
 Parameters: maze* m1, FILE *src*/
void initMaze(maze* m1, FILE *src){
    /* read in the size, starting and ending positions in the maze */
    int i, j;
    while(!feof(src)){
        fscanf (src, "%d %d", &m1->xsize, &m1->ysize);
        if((m1->xsize < 1) || (m1->ysize < 1)){
            fprintf(stderr,"Invalid: Maze sizes must be greater than 0\n");
            continue;
        }
        else {
            //Allocate space after the sizes are assigned
            m1->darr = (char**)malloc(sizeof(char*) * (m1->xsize + 2));
            for(int i = 0; i < m1->xsize + 2; i++){
                m1->darr[i] = (char*) malloc(sizeof(char) * (m1->ysize + 2));
            }
    
            /* initialize the maze to empty */
            for (i = 0; i < m1->xsize+2; i++)
                for (j = 0; j < m1->ysize+2; j++)
                    m1->darr[i][j] = '.';
            /* mark the borders of the maze with *'s */
            for (i=0; i < m1->xsize+2; i++)
            {
                m1->darr[i][0] = '*';
                m1->darr[i][m1->ysize+1] = '*';
            }
            for (i=0; i < m1->ysize+2; i++)
            {
                m1->darr[0][i] = '*';
                m1->darr[m1->xsize+1][i] = '*';
            }
            break;
        }
    }
    while(!(feof(src))){
        //Initialize the correct x and y starting positions
        fscanf (src, "%d %d", &m1->xstart, &m1->ystart);
        if( (m1->xstart) > (m1->xsize) || ( (m1->xstart) < 1) ){
            fprintf(stderr,"Invalid: row %d outside of range from 1 to %d\n", m1->xstart, m1->xsize );
            continue;
        }
        if( (m1->ystart) > (m1->ysize) || ((m1->ystart) < 1) ){
            fprintf(stderr,"Invalid: column %d outside of range from 1 to %d\n", m1->ystart, m1->ysize);
            continue;
        }
        else{
            break;
        }
    }
    
    while(!(feof(src))){
        //Initialize the correct x and y ending positions
        fscanf (src, "%d %d", &m1->xend, &m1->yend);
        if( (m1->xend) > (m1->xsize) || ((m1->xend) < 1) ){
            fprintf(stderr,"Invalid: row %d outside of range from 1 to %d\n", m1->xend, m1->xsize);
            continue;
        }
        if( (m1->yend) > (m1->ysize) || ((m1->yend) < 1) ){
            fprintf(stderr,"Invalid: column %d outside of range from 1 to %d\n", m1->yend, m1->ysize);
            continue;
        }
        else{
            break;
        }
    }
    
    /* mark the starting and ending positions in the maze */
    m1->darr[m1->xstart][m1->ystart] = 's';
    m1->darr[m1->xend][m1->yend] = 'e';
    
    int xpos, ypos;
    /* mark the blocked positions in the maze with *'s */
    while (fscanf (src, "%d %d", &xpos, &ypos) != EOF)
    {
        //Initialize blocked positions in the appropiate coordinates
        if( (xpos) > (m1->xsize) || ( (xpos) < 1) ){
            fprintf(stderr,"Invalid: row %d outside of range from 1 to %d\n", xpos, m1->xsize );
            continue;
        }
        if( (ypos) > (m1->ysize) || ((ypos) < 1) ){
            fprintf(stderr,"Invalid: column %d outside of range from 1 to %d\n", ypos, m1->ysize);
            continue;
        }
        
        if(m1->darr[xpos][ypos] == 's') {
            fprintf(stderr,"Invalid: attempting to block starting position.\n");
            continue;
        }
        if(m1->darr[xpos][ypos] == 'e') {
            fprintf(stderr,"Invalid: attempting to block ending position.\n");
            continue;
        }
        m1->darr[xpos][ypos] = '*';
    }
    /* print them out to verify the input */
    printf ("size: %d, %d\n", m1->xsize, m1->ysize);
    printf ("start: %d, %d\n", m1->xstart, m1->ystart);
    printf ("end: %d, %d\n", m1->xend, m1->yend);
    
    /* print out the initial maze */
   for (i = 0; i < m1->xsize+2; i++)
    {
        for (j = 0; j < m1->ysize+2; j++)
            printf ("%c", m1->darr[i][j]);
        printf("\n");
    }
}


/*Void function will prepend a node on stack/linkd list
 Parameters: linkedPtr hd, int valX, int valY*/
void push (linkedPtr* hd, int valX, int valY){
    linkedPtr ptr = (linkedPtr) malloc (sizeof(linked));
    ptr->xElem = valX;
    ptr->yElem = valY;
    ptr->pNext= *hd;
    *hd = ptr;
    
    if(debugMode == true){
        printf("\n(%d, %d) is being pushed onto to stack\n", valX, valY);
    }
}


/*Void function will delete the top/first node on stack/linkd list
 Parameters: linkedPtr hd*/
void pop (linkedPtr* hd){
    if(debugMode == true){
        printf("\n(%d, %d) is being popped off of stack\n", (*hd)->xElem, (*hd)->yElem);
    }
    linkedPtr tmp = *hd;
    *hd = (*hd)->pNext;
    free (tmp);
}


/*Bool function return true if empty else false
 Parameters: linkedPt hd*/
bool isEmpty (linkedPtr hd){
    if (hd == NULL)
        return true;
    else
        return false;
}


/*Void functionn will display list in reverse order *
 Parameters: linkedPtr hd*/
void show (linkedPtr hd){
    linkedPtr prevNode, currentNode;
    currentNode = hd;
    prevNode = NULL;
    while(prevNode != hd){
        currentNode = hd;
        while(currentNode->pNext != prevNode){
            currentNode = currentNode->pNext;
        }
        prevNode = currentNode;
        printf("(%d, %d)\n", currentNode->xElem, currentNode->yElem);
        currentNode = hd;
    }
}


/* This function is intializing the stack by pushing the starting coordinate
 Parameter: linkedPtr *hd, int startX, int startY */
void initStack(linkedPtr *hd, int startX, int startY){
    push(hd, startX,startY);      //Push starting position
}


/*stuct function will return the node from the top of the list
 Parameter: linkedPtr hd*/
linked top(linkedPtr hd){
    return *hd;
}


/*This function will free the linked list and 2d array for no memory leak
 Parameter: struct maze *m1, linkedPtr *hd */
void resetStack(maze *m1, linkedPtr *hd){
    
    if(debugMode == true && isEmpty(*hd) == false) {
        printf("\nResetting the stack:\n");
    }
    //This is freeing stack/linkedlisst
    if(isEmpty(*hd) == false){
        while(hd != NULL){
            pop(hd);
            if( isEmpty(*hd) == true) break;
        }
    }
    
    //Free the 2d array where the maze was stored
    for(int i = 0; i< m1->xsize; i++){
        free(m1->darr[i]); //dellocating space
    }
    free (m1->darr);    //delocating space
}


int main (int argc, char **argv)
{
    maze m1;
    FILE *src = NULL;
    
    /*Traverse the arguments to turn on debugMode*/
    for (int i = 0; i<argc; i++){
        if ((argv[i][0] == '-') && (argv[i][1] == 'd')){
            debugMode = true;
        }
    }
    
    //This program will always pick the first file if given more than 1 file;
    if ((argc > 2) && (strcmp(argv[2], "-d") != 0) && (strcmp(argv[1], "-d") != 0) ){
        if ((src = fopen( argv[1], "r" )) == NULL ){
            fprintf(stderr, "Can't open input file: %s\n", argv[1] );
            exit(-1);
        }
        fprintf(stderr, "First input file will be used for this program.\n");

    }
    
    //Check for two command arguments (assuming no -d command was given)
    if(argc == 2){
        if ((src = fopen( argv[1], "r" )) == NULL ){
            fprintf(stderr, "Can't open input file: %s\n", argv[1] );
            exit(-1);
        }
    }
    
    //Check if the -d is at index 1 or at index 2
    if(argc > 2){
        if(strcmp(argv[2], "-d") == 0){
            if (( src = fopen( argv[1], "r" )) == NULL ){
                fprintf(stderr, "Can't open input file: %s\n", argv[1] );
                exit(-1);
            }
        }
        else if (strcmp(argv[1], "-d") == 0){
            if ((src = fopen( argv[2], "r" )) == NULL ){
                fprintf(stderr, "Can't open input file: %s\n", argv[2] );
                exit(-1);
            }
        }
    }
    
    initMaze(&m1, src);
    linkedPtr head = NULL;          //initialize the first node
    initStack(&head, m1.xstart, m1.ystart);     //Initialize stack by pushing the first coordinate
    linked topHead = top(head);
    m1.darr[topHead.xElem][topHead.yElem] = 'V'; //mark the first coordinate as visited
    
    while(true){
        if (topHead.xElem == m1.xend && topHead.yElem == m1.yend) break;
        //Move to the right if no barrier
        if ((m1.darr[head->xElem][head->yElem + 1] != 'V') && (m1.darr[head->xElem][head->yElem + 1] != '*')){
            m1.darr[head->xElem][head->yElem + 1] = 'V';    //Mark as visited
            push(&head,head->xElem, head->yElem + 1); //prepend to the list
            topHead = top(head);
        }
        // Move down if no barriers
        else if ((m1.darr[head->xElem + 1][head->yElem] != 'V') && (m1.darr[head->xElem + 1][head->yElem] != '*')){
            m1.darr[head->xElem + 1][head->yElem] = 'V';    //Mark as visited
            push(&head,head->xElem + 1, head->yElem); //prepend to the list
            topHead = top(head);

        }
        //Move to the left if no barriers
        else if ((m1.darr[head->xElem][head->yElem - 1] != 'V') && (m1.darr[head->xElem][head->yElem - 1] != '*')){
            m1.darr[head->xElem][head->yElem - 1] = 'V';    //Mark as visited
            push(&head,head->xElem, head->yElem - 1); //prepend to the list
            topHead = top(head);
            
        }
        //Move up if no barriers
        else if((m1.darr[head->xElem - 1][head->yElem] != 'V') && (m1.darr[head->xElem - 1][head->yElem] != '*')) {
            m1.darr[head->xElem - 1][head->yElem] = 'V';    //Mark as visited
            push(&head,head->xElem - 1, head->yElem);  //prepend to the list
            topHead = top(head);

        }
        else{
            pop(&head);            // delete/pop if coordinate is surrounded by visited positions
            if (isEmpty(head) == true)break;  //if stack/linked list is empty then there's no solution
            topHead = top(head);
        }
    }
    
    if (isEmpty(head) == true){
        printf("\n*** The maze has no solution! ***\n");
    }
    else{
        printf("\nThe path coordinates from start to end is: \n");
        show(head);     //Display the stack/linked list in reverse order
    }
    printf("\n");
    resetStack(&m1, &head); //Call the function to reset array and stack for no memory leaks
}
