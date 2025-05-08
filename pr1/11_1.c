#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX];
int visited[MAX];
int n, e;

void vertexCoverApprox()
{
    int cover[MAX] = {0};

    for (int u = 0; u < n; u++)
    {
        if (!visited[u])
        {
            for (int v = 0; v < n; v++)
            {
                if (graph[u][v] && !visited[v])
                {
                    // Pick edge (u, v)
                    visited[u] = 1;
                    visited[v] = 1;
                    cover[u] = 1;
                    cover[v] = 1;
                    break;
                }
            }
        }
    }

    printf("Approximate Vertex Cover:\n");
    for (int i = 0; i < n; i++)
    {
        if (cover[i])
            printf("%d ", i);
    }
    printf("\n");
}

int main()
{
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &n, &e);

    printf("Enter the edges (u v):\n");
    for (int i = 0; i < e; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    vertexCoverApprox();

    return 0;
}
