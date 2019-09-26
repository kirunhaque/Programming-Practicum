#ifndef waitinglist_h
#define waitinglist_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

typedef struct groupInfo{
    char* name;
    int groupSize;
    boolean status;
    struct groupInfo *next;
}group;
typedef group* groupPtr;
int debugMode;

//interface functions
void clearToEoln(void);
int getNextNWSChar(void);
int getPosInt(void);
char *getName(void);
void printCommands(void);

//linked lists functions
void doAdd(groupPtr *head);
void doCallAhead(groupPtr *head);
void doWaiting (groupPtr head);
void doRetrieve (groupPtr *head);
void doList (groupPtr head);
void doDisplay (groupPtr head);

//linked list implementation
void addToList(groupPtr *hd, int size, char* name, int status);
int doesNameExist(groupPtr head, char* name);
int updateStatus(groupPtr head, char* name);
char* retrieveAndRemove(groupPtr *head, int tableSize);
int countGroupsAhead(groupPtr head,char* name);
void displayGroupAhead(groupPtr head, char* name);
void displayListInformation(groupPtr head);
void debugModeInfo(groupPtr hd);
#endif /* waitinglist_h */
