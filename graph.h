#ifndef GRAPH_
#define GRAPH_

typedef struct Node *PNode;

//object edge contain the weight of the edge the dest of it and the next edge we have
typedef struct edge {
    int weight;
    PNode dest;
    struct edge* next;
} edge, *PEdge;

//object node that have id weight edges of the node out anf the next node and the prev node that points to it
typedef struct Node {
    int id;
    int weight;
    PEdge edges;
    struct Node* next;
    struct Node* prev;
    int visited;
} node;

#endif
