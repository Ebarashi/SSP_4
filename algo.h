#ifndef ALGO_H
#define ALGO_H

#include<stdio.h>
#include "graph.h"

int shortestPath(int src, int dest);
PNode GetNode(int id);
PNode createNode(int id, PNode next, PEdge edges);
void createNodes(int size);
void printGraph();
void addEdges(PNode node);
void addNode();
void createGraph();
void deleteNode(int id);
void deleteGraph();
void dijkstra(int src, int dest);
void freeEdgesOfNode(PNode N);
void TSP(int numOfCities);
void swap(int *x, int *y);
void permutation(int a[], int size, int n);

#endif