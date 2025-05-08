#include <stdio.h>
#include <string.h>

#define MAX 6 // Number of vertices in the bipartite graph

// A utility function to perform DFS on the residual graph and find if there is a path from source to sink
int dfs(int graph[MAX][MAX], int u, int matchR[], int visited[])
{
    for (int v = 0; v < MAX; v++)
    {
        if (graph[u][v] && !visited[v])
        {
            visited[v] = 1;
            if (matchR[v] == -1 || dfs(graph, matchR[v], matchR, visited))
            {
                matchR[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

// Function to find maximum bipartite matching using DFS
int maxBPM(int graph[MAX][MAX])
{
    int matchR[MAX];                    // Array to store the match for right side vertices
    memset(matchR, -1, sizeof(matchR)); // Initialize matchR as -1, meaning no match

    int result = 0; // Initialize result

    // Try to find a matching for each vertex on the left side
    for (int u = 0; u < MAX; u++)
    {
        // Create a visited array to keep track of visited vertices during DFS
        int visited[MAX];
        memset(visited, 0, sizeof(visited));

        // Find if there is a matching for vertex u
        if (dfs(graph, u, matchR, visited))
        {
            result++;
        }
    }
    return result;
}

int main()
{
    // Bipartite graph represented as an adjacency matrix
    // Graph has left vertices as 0,1,2,3 and right vertices as 0,1,2,3
    // graph[u][v] = 1 means there is an edge between u (left) and v (right)
    int graph[MAX][MAX] = {
        {1, 0, 1, 0}, // Vertex 0 on left side is connected to vertices 0 and 2 on right side
        {0, 1, 0, 1}, // Vertex 1 on left side is connected to vertices 1 and 3 on right side
        {1, 0, 0, 1}, // Vertex 2 on left side is connected to vertices 0 and 3 on right side
        {0, 1, 1, 0}, // Vertex 3 on left side is connected to vertices 1 and 2 on right side
    };

    printf("The maximum number of matches is %d\n", maxBPM(graph));

    return 0;
}
