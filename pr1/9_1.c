#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 8

int x[N + 1]; // x[k] represents the column position of the queen in row k

int Place(int k, int i)
{
    for (int j = 1; j < k; j++)
    {
        if (x[j] == i || abs(x[j] - i) == abs(j - k))
            return 0; // Conflict in column or diagonal
    }
    return 1; // Safe position
}

void printBoard(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (x[i] == j)
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

void NQueens(int k, int n)
{
    for (int i = 1; i <= n; i++)
    {
        if (Place(k, i))
        {
            x[k] = i;
            if (k == n)
            {
                printBoard(n);
            }
            else
            {
                NQueens(k + 1, n);
            }
        }
    }
}

int main()
{
    NQueens(1, N);
    return 0;
}
