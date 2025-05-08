#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 4
#define MAX_QUEUE 10000

// Direction vectors
int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};
char *dir[] = {"Down", "Left", "Up", "Right"};

typedef struct
{
    int mat[N][N];
    int x, y;        // Blank tile coordinates
    int cost;        // Heuristic cost
    int level;       // Depth of node
    char path[1000]; // Path string
} Node;

// Target configuration
int final[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}};

// Min Heap for priority queue
Node heap[MAX_QUEUE];
int heapSize = 0;

int isSafe(int x, int y)
{
    return x >= 0 && x < N && y >= 0 && y < N;
}

int manhattan(int mat[N][N])
{
    int dist = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (mat[i][j] != 0)
            {
                int val = mat[i][j] - 1;
                dist += abs(i - val / N) + abs(j - val % N);
            }
    return dist;
}

void copyMatrix(int src[N][N], int dest[N][N])
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dest[i][j] = src[i][j];
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void push(Node node)
{
    int i = heapSize++;
    while (i && node.cost < heap[(i - 1) / 2].cost)
    {
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap[i] = node;
}

Node pop()
{
    Node root = heap[0];
    Node temp = heap[--heapSize];
    int i = 0, child;
    while ((child = 2 * i + 1) < heapSize)
    {
        if (child + 1 < heapSize && heap[child + 1].cost < heap[child].cost)
            child++;
        if (temp.cost <= heap[child].cost)
            break;
        heap[i] = heap[child];
        i = child;
    }
    heap[i] = temp;
    return root;
}

int isGoal(int mat[N][N])
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (mat[i][j] != final[i][j])
                return 0;
    return 1;
}

void solve(int initial[N][N], int x, int y)
{
    Node root;
    copyMatrix(initial, root.mat);
    root.x = x;
    root.y = y;
    root.level = 0;
    root.cost = manhattan(root.mat);
    strcpy(root.path, "");
    push(root);

    while (heapSize)
    {
        Node min = pop();
        if (isGoal(min.mat))
        {
            printf("Solved in %d moves:\n%s\n", min.level, min.path);
            return;
        }

        for (int i = 0; i < 4; i++)
        {
            int newX = min.x + row[i];
            int newY = min.y + col[i];

            if (isSafe(newX, newY))
            {
                Node child;
                copyMatrix(min.mat, child.mat);
                swap(&child.mat[min.x][min.y], &child.mat[newX][newY]);

                child.x = newX;
                child.y = newY;
                child.level = min.level + 1;
                child.cost = child.level + manhattan(child.mat);

                snprintf(child.path, sizeof(child.path), "%s%s ", min.path, dir[i]);
                push(child);
            }
        }
    }
    printf("No solution found.\n");
}

int main()
{
    int initial[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 12},
        {13, 14, 11, 15}};

    int x, y;
    // Find position of blank (0)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (initial[i][j] == 0)
            {
                x = i;
                y = j;
            }

    solve(initial, x, y);
    return 0;
}
