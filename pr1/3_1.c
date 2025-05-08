#include <stdio.h>
#include <limits.h>

#define MAX 10

int dp[MAX][MAX];
int split[MAX][MAX];

void printParenthesis(int i, int j, int name)
{
    if (i == j)
    {
        printf("A%d", name);
        return;
    }
    printf("(");
    printParenthesis(i, split[i][j], name);
    printParenthesis(split[i][j] + 1, j, name);
    printf(")");
}

int matrixChainOrder(int dims[], int n)
{
    for (int i = 1; i < n; i++)
        dp[i][i] = 0;

    for (int len = 2; len < n; len++)
    {
        for (int i = 1; i < n - len + 1; i++)
        {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int cost = dp[i][k] + dp[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }
    return dp[1][n - 1];
}

int main()
{
    int dims[] = {40, 20, 30, 10, 30}; // 4 matrices: A1(40x20), A2(20x30), A3(30x10), A4(10x30)
    int n = sizeof(dims) / sizeof(dims[0]);

    int minCost = matrixChainOrder(dims, n);
    printf("Minimum multiplication cost: %d\n", minCost);
    printf("Optimal Parenthesization: ");
    printParenthesis(1, n - 1, 1);
    printf("\n");
    return 0;
}
