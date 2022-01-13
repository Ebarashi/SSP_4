


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
        else if(ch == 'n') {
            createGraph();
        }
        else if(ch == 'B') {
            addNode();
        }
        else if(ch == 'D') {
            scanf("%d", &src);
            deleteNode(src);
        }
        else if(ch == 'S') {
            scanf("%d", &src);
            scanf("%d", &dest);
            ans = shortestPath(src, dest);
            printf("Dijsktra shortest path: %d \n", ans);
        }
        else if(ch == 'T') {
            scanf("%d", &src);
            TSP(src);
        }
        else if(ch == '\n') {
            deleteGraph();
            break;
        }

    }
    return 0;
}