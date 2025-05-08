#include <stdio.h>
#include <limits.h>

#define V 5

// Function to find the vertex with the minimum distance
int minDistance(int dist[], int sptSet[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
    {
        if (sptSet[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to implement Dijkstra's Algorithm
void dijkstra(int graph[V][V], int src)
{
    int dist[V];   // Array to store the shortest distance from src to each vertex
    int sptSet[V]; // Shortest path tree set (true if vertex is included in SPT)

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    // Distance from the source to itself is always 0
    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update the dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++)
        {
            // Update dist[v] if and only if it is not in sptSet, there is an edge from u to v,
            // and the total weight of the path from src to v through u is smaller than the current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the calculated shortest distances
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
    {
        printf("%d \t %d\n", i, dist[i]);
    }
}

int main()
{
    // Graph represented as an adjacency matrix
    int graph[V][V] = {
        {0, 10, 0, 0, 0},
        {10, 0, 20, 0, 0},
        {0, 20, 0, 10, 0},
        {0, 0, 10, 0, 5},
        {0, 0, 0, 5, 0}};

    int source = 0; // Source vertex for SSSP
    dijkstra(graph, source);
    return 0;
}
