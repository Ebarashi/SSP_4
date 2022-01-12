#include <stdio.h>
#include <stdlib.h>
#include "algo.h"
#include "graph.h"
#include "priorityQ.h"

//define infinity for our program we may need to change it 
//according to the max weight of the edges
#define INFINITY 100000000

//start node of the list of nodes of the graph
static PNode GNodes;
//so we could use the same varible in multiple funcation
static int minimumPath = INFINITY;

//print the graph for self debug
void printGraph(){
    PNode head = GNodes;
    printf("{");
    //goes troughe all the nodes
    while (head != NULL){
        printf("[id: %d, ", head->id);
        PEdge currentEdges = head->edges;
        printf("edges: ");
        //goes troughe all the edges of the node
        while (currentEdges!= NULL){
            printf("weight: %d, dest: %d, ", currentEdges->weight, currentEdges->dest->id);
            currentEdges = currentEdges->next; }
        printf("], ");
        head = head->next;}
    printf("}\n");
}

//a funcation to create a new node
PNode createNode(int id, PNode next, PEdge edges){
    PNode tempEdge = (PNode)malloc(sizeof(node));
    tempEdge->id = id;
    tempEdge->next = next;
    tempEdge->edges = edges;
    tempEdge->weight = INFINITY;
    tempEdge->prev = NULL;
    return tempEdge;
}

//a funcation to free all the memory of the edges of a serten node 
void freeEdgesOfNode(PNode N) {
    PEdge edgesToDelete = N->edges;
    //free only if there edges
    if (edgesToDelete != NULL) {
        PEdge tempEdge = edgesToDelete->next;
        //if there only one edge free and return
        if (tempEdge == NULL) {
            free(edgesToDelete);
        } 
        else {
            //else as long there is oanother edge move forward and delete the one we just passed
            while (edgesToDelete->next != NULL) {
                //remember the edge
                PEdge PtempEdge = tempEdge;
                //move forward
                edgesToDelete->next = tempEdge->next;
                //free the one we remmbered
                free(PtempEdge);
            }
            //free the last edge
            free(edgesToDelete);
        }
    }
}
//a func to add a node to the graph
void addNode(){
    int nodeId;
    int allreadyExists=0;
    scanf("%d", &nodeId);
    PNode tempNode = GNodes;
    //first we cechk if there is allready a node if the same id
    while (tempNode!=NULL){
        if (tempNode->id == nodeId){allreadyExists=1; break;}
        tempNode = tempNode->next;
    }
    //if there is no node with the same id add the node
    if (allreadyExists == 0) 
    {
        //get the last node 
        PNode lastNode = GNodes;
        while (lastNode->next != NULL){lastNode = lastNode->next;}
        PNode tempEdge = createNode(nodeId, NULL, NULL);
        //add the node as last.next, now the new node is the last node
        lastNode->next = tempEdge;
        //add edges of the new node
        addEdges(tempEdge);
    } 
    //there is a exixten node if the same id free the edges and give new ones
    else{
        PNode curr = GetNode(nodeId);
        //free all the edges of the node
        freeEdgesOfNode(curr);
        curr->edges = NULL;
        //add the new edges
        addEdges(curr);
    }
}
//a function to get a serten of the graph by id
PNode GetNode(int id){
    PNode head = GNodes;
    //go until we found the serten node
    //if there is no such id returns the last node
    while (head->id != id){head = head->next;}
    return head;
}

//a function to free all the memory related to a serten node
void deleteNode(int id) {
    PNode NodeToDelete = GetNode(id);
    PNode head = GNodes;
    //goes troughe all the nodes and deletes the nodes that our node is the dest of their edge
    while (head != NULL) {
        PEdge edge = head->edges;
        //run on all the edges and search for an edge that conatin our node
        while (edge != NULL) {
            //if we found en edge, go forward and free the edge
            if (edge->dest == NodeToDelete) {
                head->edges = edge->next;
                PEdge pe = edge;
                free(pe);
                edge = NULL;
            } 
            else {
                //else check if the edge.next is a edge that contains our edge
                //if it does connect next to the next next anf free the edge
                PEdge tempEdge = edge->next;
                if (tempEdge != NULL && tempEdge->dest == NodeToDelete) {
                    edge->next = tempEdge->next;
                    free(tempEdge);
                }
                //else move to the next edge
                else {edge = tempEdge;}
            }
        }
        //go to the next node
        head = head->next;
    }
    //makes the node that points to our node point to the node after our node
    PNode head2 = GNodes;
    if (head2 != NodeToDelete) {
        while (head2->next != NodeToDelete) {
            head2 = head2->next;
        }
        head2->next = NodeToDelete->next;
    }
    //free all the edges of the node
    freeEdgesOfNode(NodeToDelete);
    //free the node itself
    free(NodeToDelete);
}
//a funaction to delete our intire graph
void deleteGraph(){
    PNode head = GNodes;
    int nodeId;
    //go troughe all the nodes
    while (head!=NULL){
        //move forward and then free all the memory related to the node
        nodeId = head->id;
        head = head->next;
        deleteNode(nodeId);
    }
    //free the head of our graph
    free(head);
    GNodes = NULL;
}
// a function we saw on the other courses(oop,algorthims)
//for helping ti find the shorthest path faster
//we need an priority qeqe for this alghorthim
/*
    an explation from our other assignment in oop for a specific dijkstra
    our works very similar 
    This algorithm gets a source and a destination and returns the short way between them.
    The algorithm does this while going through all the vertixes as long as we have not visited them
    and the edges associated with each vertex.
    for each vertex we initialized its weight to be the shortest way to reach it from the src and the tag to be from whom we reached it
    when we finished with a vertex we marked him as visited.
    we implemented the algo we learned at algorithms course
    @param src
    @param dest
    @return the shortest path from src to dest
*/
//***instead of info black and white we use weight and visited***
void dijkstra(int src, int dest){
    PNode start = GNodes;
    //restart all the nodes propertis to the exact thing for helping the algorthim
    while (start != NULL){
        start->weight = INFINITY;
        start->prev = NULL;
        start->visited = 0;
        start = start->next;
    }
    PNode srcN = GetNode(src);
    srcN->weight = 0;
    //add the first node to the qeqe
    pqNode* priorityQN = newNode(srcN, srcN->weight);
    pqNode** head = &priorityQN;
    //run as long the qeqe is not empty
    while (isEmpty(head) == 0){
        pqNode* currentN = peek(head);
        if(currentN->data->visited == 0){
            if(currentN->data->id == dest){
                //run as long as there nodes in the quqe
                while (isEmpty(head) == 0){
                    pop(head);
                }
                //free the memory we dont need it any more
                free(priorityQN);
                return;
            }
            currentN->data->visited = 1;
            PEdge edegs = currentN->data->edges;
            //run as long there is edges left
            while (edegs!=NULL){
                int edgeWeight = edegs->weight;
                int srcWeight = currentN->data->weight;
                int destWeight = edegs->dest->weight;
                if (destWeight > srcWeight + edgeWeight){
                    edegs->dest->weight = srcWeight + edgeWeight;
                    edegs->dest->prev = currentN->data;
                }

                if(priorityQN == NULL){
                    priorityQN = newNode(edegs->dest, edegs->dest->weight);
                } else{
                    push(head, edegs->dest, edegs->dest->weight);
                }
                edegs = edegs->next;
            }
        }
        pop(head);
    }
    //free the memory left
    free(priorityQN);
}

//a func that returns the shorthest path between two node represnets by two id's
//the func is so short thanks to the dijkstra
int shortestPath(int src, int dest){
    dijkstra(src,dest);
    return GetNode(dest)->weight;
}
//a func to swap the content of to pointers just for comfort only been used once
void swap(int *x, int *y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
//a recursive function to calculate all the permution there is for the given arry
//and set the min path to the smallest permution sum we could find
/*in genreal this func gets a arry of cities an then calculate for each possibale 
 permution the path between every two nodes then if it is smaller then the path we allredy 
 have set it to the min and so on until we go trough all the permutions.*/
void permutation(int arr[], int size, int n){
    //stop condition
    if (size == 1){
        int sum = 0;
        //calculate sorthest path between each two nodes
        for (int j = 0; j < n-1; ++j){
            sum += shortestPath(arr[j], arr[j + 1]);
        }
        //if sum is smaller then the current min path set it as min path
        if (sum < minimumPath){
            minimumPath = sum;
            return;
        }
    }
    //else call permution recusivly inside the for 
    //so we could get all the permutions there are
    for (int i = 0; i < size; i++){
        permutation(arr, (size - 1), n);
        if (size % 2 == 1){
            swap(&arr[0], &arr[size - 1]);}
        else{
            swap(&arr[i], &arr[size - 1]);}
    }
}

//a funcation that calculate the shortest path thet go trough all the given nodes
void TSP(int numOfCities)
{
    //set min path to infinity as start condition(also because it couls change from older calculations)
    minimumPath = INFINITY;
    int path[numOfCities];
    int nodeId = -1;
    //gets all the cities we need to go trough
    for (int i = 0; i < numOfCities; i++){
        scanf("%d", &nodeId);
        path[i] = nodeId;
    }
    //calls permution to calculte the path
    permutation(path, numOfCities, numOfCities);
    //if it equals infinity then changed it to -1 because we dont have an path
    if(minimumPath == INFINITY)
    {
        minimumPath = -1;
    }
    //print the out com of the path
    printf("TSP shortest path: %d \n", minimumPath);
}

//a function to create a graph by adding the edges to the node
void createGraph(){
    int srcId;
    scanf("%d", &srcId);
    PNode node = GetNode(srcId);
    addEdges(node);
}
//a funaction to create severalnodes and connect them to each other 
void createNodes(int size){
    //if there is allready a graph delte it
    if(GNodes != NULL){
        deleteGraph();
    }
    //create the first node
    PNode tempNode = createNode(size - 1, NULL, NULL);
    for (int i = size - 2; i >= 0; i--){
        //continue to creates nodes and connecting them to each other
        PNode NewNode = createNode(i, tempNode, NULL);
        tempNode = NewNode;
    }
    //update the head node of the graph
    GNodes = tempNode;
}
//add edges to the givan node(reading from the terminal)
void addEdges(PNode node){
    int dest;
    int weight;
    char input;
    scanf("%c", &input);
    //invalid input
    if(input == '\n'){return; }
    //else create a memory size in size of edge
    PEdge Edge = (PEdge)malloc(sizeof(edge));
    if ((scanf("%d", &dest) == 1)&&(scanf("%d", &weight) == 1)){
        Edge->weight = weight;
        node->edges = Edge;
        Edge->dest = GetNode(dest);
        Edge->next = NULL;
    }
    else{return;}

    scanf("%c", &input);
    //invalid input stop func
    if(input == '\n'){return;}
    //while input is coarrect continue to connect edges
    while ((scanf("%d", &dest) == 1)&&(scanf("%d", &weight) == 1)){
        PEdge tempEdge = (PEdge)malloc(sizeof(edge));
        tempEdge->next = NULL;
        Edge->next = tempEdge;
        tempEdge->weight = weight;
        tempEdge->dest = GetNode(dest);
        Edge = tempEdge;
    
        scanf("%c", &input);
        //invalid input stop func
        if(input == '\n'){return;}
    }
    return;
}