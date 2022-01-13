


#include <stdio.h>
#include "algo.h"

int main()
{
    char ch;
    int src;
    int dest;

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
            shortestPath(src, dest);
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