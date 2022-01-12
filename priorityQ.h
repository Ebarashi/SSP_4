#include "graph.h"
#ifndef PRIORITYQ_H
#define PRIORITYQ_H

//node of the quqe that has data is priorty and the next node
typedef struct PQNode {
    PNode data;
    int priority;
    struct PQNode *next;
} pqNode;


pqNode* newNode(PNode d, int p);
pqNode* peek(pqNode** head);
void pop(pqNode** head);
void push(pqNode** head, PNode d, int p);
int isEmpty(pqNode** head);






#endif