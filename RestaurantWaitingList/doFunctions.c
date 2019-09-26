#include "waitinglist.h"
void doAdd (groupPtr *head)
{
    /* get group size from input */
    int size = getPosInt();
    if (size < 1)
    {
        printf ("Error: Add command requires an integer value of at least 1\n");
        printf ("Add command is of form: a <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Add command requires a name to be given\n");
        printf ("Add command is of form: a <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    printf ("Adding In-restaurant group \"%s\" of size %d\n", name, size);
    
    // add code to perform this operation here
    if(doesNameExist(*head, name) == TRUE){
        printf("The name already exists, please choose another name");
        return;
    }
    int status = TRUE;
    addToList(head, size, name, status);
}

void doCallAhead (groupPtr *head)
{
    /* get group size from input */
    int size = getPosInt();
    if (size < 1)
    {
        printf ("Error: Call-ahead command requires an integer value of at least 1\n");
        printf ("Call-ahead command is of form: c <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Call-ahead command requires a name to be given\n");
        printf ("Call-ahead command is of form: c <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    printf ("Adding Call-ahead group \"%s\" of size %d\n", name, size);
    
    // add code to perform this operation here
    if(doesNameExist(*head, name) == TRUE){
        printf("The name already exists, please choose another name");
        return;
    }
    int status = FALSE;
    addToList(head, size, name, status);
}

void doWaiting (groupPtr head)
{
    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Waiting command requires a name to be given\n");
        printf ("Waiting command is of form: w <name>\n");
        printf ("  where: <name> is the name of the group that is now waiting\n");
        return;
    }
    
    // add code to perform this operation here
    if(doesNameExist(head, name) == FALSE){
        printf("Sorry, the name does not exist in this waiting list\n");
        return;
    }
    
    if(updateStatus(head, name) == TRUE){
        printf ("Call-ahead group \"%s\" is now waiting in the restaurant\n", name);
    }
    else{
        printf("The group is already in the restaurant\n");
    }
}


void doRetrieve (groupPtr *head)
{
    /* get table size from input */
    int size = getPosInt();
    if (size < 1)
    {
        printf ("Error: Retrieve command requires an integer value of at least 1\n");
        printf ("Retrieve command is of form: r <size>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        return;
    }
    clearToEoln();
    printf ("Retrieve (and remove) the first group that can fit at a tabel of size %d\n", size);
    
    // add code to perform this operation here
    char* name = retrieveAndRemove(head, size);
    if (name != NULL){
        printf("Group \"%s\" is now at a table\n", name);        
    }
    else{
        printf("Sorry the list is empty or there are no valid tables for any of the groups\n");
    }
}

void doList (groupPtr head)
{
    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: List command requires a name to be given\n");
        printf ("List command is of form: l <name>\n");
        printf ("  where: <name> is the name of the group to inquire about\n");
        return;
    }
    
    
    // add code to perform this operation here
    if(doesNameExist(head, name) == FALSE){
        printf("Sorry, the name does not exist in this waiting list\n");
        return;
    }
    
    printf ("Group \"%s\" is behind the following groups\n", name);
    displayGroupAhead(head, name);
    int countGroups = countGroupsAhead(head, name);
    printf("Group \"%s\" is behind the %d groups\n", name, countGroups);
}

void doDisplay (groupPtr head)
{
    clearToEoln();
    printf ("Display information about all groups\n\n");
    
    // add code to perform this operation here
    displayListInformation(head);
}





