#include <stdio.h>
#include <stdlib.h>
#include "priorityQ.h"

//creare a new node
pqNode* newNode(PNode d, int p){
    pqNode* temp = (pqNode*)malloc(sizeof(pqNode));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;
    return temp;
}

//returns the head of the quqe
pqNode* peek(pqNode** head){ return *head;}

//extract the head of the quqe and free the memory
void pop(pqNode** head){
    pqNode* temp = *head;
    *head = (*head)->next;
    free(temp);
}

//pushes a node into the quqe by his priority
void push(pqNode** head, PNode d, int p){
    pqNode* start = (*head);
    pqNode* temp = newNode(d, p);

    if ((*head)->priority > p) {
        temp->next = *head;
        (*head) = temp;
    }
    else {
        while (start->next != NULL &&
               start->next->priority < p) {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
}

//returns if the quqe is empty
int isEmpty(pqNode** head){if((*head) == NULL)return 1; else{return 0;}}