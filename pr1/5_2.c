#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// Structure to represent an edge
struct Edge
{
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset
{
    int parent;
    int rank;
};

// Function to compare two edges (used for sorting edges)
int compareEdges(const void *a, const void *b)
{
    return ((struct Edge *)a)->weight - ((struct Edge *)b)->weight;
}

// Find the set of an element using path compression
int find(struct Subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union of two subsets (union by rank)
void unionSets(struct Subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Kruskal's algorithm to find MST
void kruskalMST(struct Edge edges[], int V, int E)
{
    struct Edge result[V]; // To store the MST
    int e = 0;             // Count of edges in MST
    int i = 0;             // Initial index of sorted edges
    struct Subset *subsets = (struct Subset *)malloc(V * sizeof(struct Subset));

    // Step 1: Sort all edges in non-decreasing order of their weight
    qsort(edges, E, sizeof(edges[0]), compareEdges);

    // Initialize subsets
    for (i = 0; i < V; i++)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    // Step 2: Pick the smallest edge. Check if it forms a cycle with the MST formed so far.
    i = 0;
    while (e < V - 1)
    {
        struct Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does not cause a cycle, include it in the result and take the union
        if (x != y)
        {
            result[e++] = next_edge;
            unionSets(subsets, x, y);
        }
    }

    // Step 3: Print the MST
    printf("Edge \tWeight\n");
    for (i = 0; i < e; i++)
        printf("%d - %d \t%d\n", result[i].src, result[i].dest, result[i].weight);
}

// Main function
int main()
{
    int V = 4; // Number of vertices
    int E = 5; // Number of edges

    struct Edge edges[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}};

    kruskalMST(edges, V, E);
    return 0;
}
