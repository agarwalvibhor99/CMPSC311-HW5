/* Yanling Wang CMPSC311 hw5 Spring 2019 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* countNodes functions counts the number of nodes in the linked list.
 * I am using a variable count which is incrementeed by one while I iterate
 * through the linked list till till the next element is not NULL 
 */
int countNodes(const listNode *list) {
  int count = 0;
  while (list != NULL){
    list = list->next;
    count += 1;
  }
  return count; 
}

/* insertAfter insert the node with value after first findValue encountered in
 * list else at the head. I am using flag to check if the findValue is in the 
 * list or not. Using while loop till the currentPtr value is not equal to
 * findValue and then changing the node accordingly and if the flag is 1 then 
 * adding the newNode with value on head
 */
void insertAfter(listNode **listPtr, int findValue, int value) {
  int flag = 0;
  listNode *currentPtr = *listPtr;
  listNode *newNodePtr = (listNode *)malloc(sizeof(listNode));
  newNodePtr->value = value;
  newNodePtr->next = NULL;
  if (currentPtr == NULL){
    *listPtr = newNodePtr;
  }
  else{
    while(currentPtr->value != findValue) {
      if (currentPtr->next == NULL){
        flag = 1;
        break;
      }
      currentPtr = currentPtr->next;
    }
    if (flag == 0){
      newNodePtr->next = currentPtr->next;
      currentPtr->next = newNodePtr;
    }
    else{
      newNodePtr->next = *listPtr;
      *listPtr = newNodePtr;
    }    
  }
}

/* findAndMove look for findValue in the list and make it the head.
 * I am iterating thorugh the list using while loop untill findValue is found
 * in the list. If it is already at head then do nothing and return else
 * remove it from current position and make newNode as the head.
 */
void findAndMove(listNode **listPtr, int findValue) {
  listNode *currentPtr = *listPtr;
  listNode *nextPtr = currentPtr->next;
  listNode *newNodePtr = (listNode *)malloc(sizeof(listNode));
  if (currentPtr->value == findValue)
    return;
  while(nextPtr->value != findValue){
    if(nextPtr->next ==  NULL)
      return;
    currentPtr = currentPtr->next;
    nextPtr = currentPtr->next;
  }
  newNodePtr->value = nextPtr->value;
  currentPtr->next = nextPtr->next;
  newNodePtr->next = *listPtr;
  *listPtr = newNodePtr;

}
/* removeAll removes all the node with value findValue. I am iterating through
 * the complete list since we need to find all the nodes and not just the
 * first instance of that value. First while check if the findValue is at head
 * and the second while iterate through the complete list keeping record of
 * previous nodes so that the connection isn't lost.
 */ 
void removeAll(listNode **listPtr, int findValue) {
  listNode *temp = *listPtr;
  listNode *prev=NULL;
  /* This while loop checks the head and compare if the value at head is
   *  findValue and changes the head to the next node and do it untill the
   *  head value isn't equal to findValue
   */
  while(*listPtr != NULL && (*listPtr)->value == findValue){
    listNode *headTemp = *listPtr;
    *listPtr = (*listPtr)->next;
    free(headTemp);
  }
  while (temp != NULL){
    while(temp != NULL && temp->value != findValue){
      prev = temp;
      temp = temp->next;
    }
    if (temp==NULL)
      return ;
    prev->next = temp->next;
    free(temp);
    temp = prev->next;
  }
}
