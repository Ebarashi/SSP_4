#include <stdio.h>
#include "algo.h"

int main()
{
    char ch;
    int src;
    int dest;
    int ans = 0;

    while (1)
    {
        scanf("%c", &ch);
        if (ch == 'A') {
            scanf("%d", &src);
            createNodes(src);
        }
        if(ch == 'n') {
            createGraph();
        }
        if(ch == 'B') {
            addNode();
        }
        if(ch == 'D') {
            scanf("%d", &src);
            deleteNode(src);
        }
        if(ch == 'S') {
            scanf("%d", &src);
            scanf("%d", &dest);
            ans = shortestPath(src, dest);
            printf("Dijsktra shortest path: %d \n", ans);
        }
        if(ch == 'T') {
            scanf("%d", &src);
            TSP(src);
        }
        if(ch == '\n') {
            deleteGraph();
            break;
        }

    }

    return 0;
}