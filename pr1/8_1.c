#include <stdio.h>
#include <string.h>

#define V 6 // Number of vertices in the graph

// A utility function to perform DFS on the residual graph and find if there is a path from source to sink
int dfs(int graph[V][V], int s, int t, int parent[], int visited[])
{
    visited[s] = 1;

    // If we reach the sink, return true
    if (s == t)
        return 1;

    for (int v = 0; v < V; v++)
    {
        if (!visited[v] && graph[s][v] > 0)
        {                  // If not visited and there is remaining capacity
            parent[v] = s; // Store the path
            if (dfs(graph, v, t, parent, visited))
                return 1;
        }
    }
    return 0;
}

// Function to implement Ford-Fulkerson algorithm using DFS
int fordFulkerson(int graph[V][V], int source, int sink)
{
    int u, v;

    // Create a residual graph and initialize it as a copy of the original graph
    int residualGraph[V][V];
    for (u = 0; u < V; u++)
    {
        for (v = 0; v < V; v++)
        {
            residualGraph[u][v] = graph[u][v];
        }
    }

    int parent[V];   // Array to store the path from source to sink
    int maxFlow = 0; // Initialize max flow as 0

    // Augment the flow while there is a path from source to sink
    while (dfs(residualGraph, source, sink, parent, (int[]){0}))
    {
        int pathFlow = 999999; // Initialize the path flow as a large value

        // Find the maximum flow through the path found by DFS
        for (v = sink; v != source; v = parent[v])
        {
            u = parent[v];
            pathFlow = (pathFlow < residualGraph[u][v]) ? pathFlow : residualGraph[u][v];
        }

        // Update residual graph and reverse edges
        for (v = sink; v != source; v = parent[v])
        {
            u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        // Add path flow to the overall flow
        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main()
{
    // Graph represented as an adjacency matrix
    int graph[V][V] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}};

    int source = 0; // Source vertex
    int sink = 5;   // Sink vertex

    printf("The maximum possible flow is %d\n", fordFulkerson(graph, source, sink));

    return 0;
}
