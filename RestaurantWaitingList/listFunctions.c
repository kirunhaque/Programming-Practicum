#include "waitinglist.h"
/* This void funtion will append to the link list when a new customer is wants to be on the list
 Parameters: groupPtr *hd, int size, char* name, int status */
void addToList(groupPtr *hd, int size, char* name, int status){
    
    group *newGroup = (group*)malloc(sizeof(group)); //allocate space for the new node
    group *last = *hd;
    
    newGroup->groupSize = size;
    newGroup->name = name;
    newGroup->status = status;
    newGroup->next = NULL;
    
    if (*hd == NULL){   //Check if the first node will be appended
        *hd = newGroup;
        return;
    }
    
    while(last->next != NULL){  //append the list at the end if list is not empty
        if (debugMode == TRUE){
            debugModeInfo(last);
        }
        last = last->next;
    }
    last->next = newGroup;
}

/* Void function will return true or false to see if the name exist in the waiting list
 parameters: groupPtr head, char* name*/
int doesNameExist(groupPtr head, char* name){
    if (head == NULL) return FALSE;
    while(head != NULL){
        
        if(debugMode == TRUE){
            debugModeInfo(head);
        }
        
        //use strcmp to check if the name is in the list
        if (strcmp(name, head->name) == 0) return TRUE;
        head = head->next;
    }
    return FALSE;
}


/*Void function that will update the status if the call ahead group is in the restaurant
 return true, if the status is updated or false if the group was already marked as arrived
 parameters:groupPtr head, char* name  */
int updateStatus(groupPtr head, char* name){
    while (head != NULL){
        if (debugMode == TRUE){
            debugModeInfo(head);
        }
        //will return true if the name was found and status was false
        if(strcmp(head->name, name) == 0){
            if(head->status == FALSE){
                head->status = TRUE;
                return TRUE;
            }
        }
        head = head->next;
    }
    return FALSE;
}


/* Char* function will return the name of the group that now will recieve a table or
 message if there's no valid group size for table size (n seats)
 parameters: groupPtr *head, int tableSize */
char* retrieveAndRemove(groupPtr *head, int tableSize){
    groupPtr curr = *head;
    groupPtr prev = NULL;
    
    char* groupName = NULL;
    if((*head) == NULL){
        return groupName;
    }
    //Check if the first node will be deleted
    if ((curr->groupSize <= tableSize) && curr->status == TRUE){
        if (debugMode == TRUE){
            debugModeInfo(curr);
        }
        if (curr != NULL){
            groupName = ((*head)->name);
            *head = (*head)->next;
            free(curr);
            return groupName;
        }
    }
    
    //This will delete the node after the first one.
    while(curr->next != NULL){
        if (debugMode == TRUE){
            debugModeInfo(curr);
        }
        
        if((curr->next->groupSize <= tableSize) && (curr->next->status == TRUE)){
            groupName = curr->next->name;
            prev = curr->next;
            curr->next = prev->next;
            free(prev);
            return groupName;
        }
        curr = curr->next;
    }
    return 0;
}

/*int function that will return a integer of how many group are ahead of the given group name
 parameters: groupPtr head,char* name */
int countGroupsAhead(groupPtr head,char* name){
    int count = 0;
    if (head == NULL){
        printf("The list is empty\n");
    }
    //Use strcmp to stop at the given name
    while (head != NULL && (strcmp(head->name, name) != 0)){
        if (debugMode == TRUE){
            debugModeInfo(head);
        }
        
        count++;
        head = head->next; //point to the next node
    }
    return count;
}

/*void function that will display the groups that are ahead of the given group name
 parameters: groupPtr head,char* name */
void displayGroupAhead(groupPtr head, char* name){
    if (head == NULL){
        printf("The list is empty\n");
    }
    while (head != NULL &&(strcmp(head->name, name) != 0)){
        if (debugMode == TRUE){
            debugModeInfo(head);
        }
        printf("Group size: %d\n\n", head->groupSize);
        head = head->next;
    }
}

/*This void function will display the waiting list information
 parameters: groupPtr head*/
void displayListInformation(groupPtr head){
    //Check if the list is empty
    if(head == NULL){
        printf("Sorry the waiting list is empty\n");
        return;
    }
    
    //Traverse throught the list to display information
    while(head != NULL){
        if(debugMode == TRUE){
            debugModeInfo(head);
        }
        printf("Name: %s\nThe group size: %d\nThe status: ", head->name, head->groupSize);
        if (head->status == FALSE){
            printf("The group has not arrived");
        }
        else{
            printf("Group has arrived");
        }
        head = head->next; //point to the next node
        printf("\n\n");
    }
}

//Function for debugging and will take a groupPtr as its parameters
void debugModeInfo(groupPtr hd){
    printf("debugMode is on:\n");
    printf("Group name: \"%s\"\n", hd->name);
    printf("Group size %d: \n", hd->groupSize);
    printf("Group status (false = 0, true = 1) %d: \n", hd->status);
}
