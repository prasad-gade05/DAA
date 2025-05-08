#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct
{
    int weight;
    int profit;
    float ratio;
} Item;

typedef struct
{
    int level;
    int profit;
    int weight;
    float bound;
} Node;

int n, capacity;
Item items[MAX];

int cmp(const void *a, const void *b)
{
    Item *item1 = (Item *)a;
    Item *item2 = (Item *)b;
    if (item2->ratio > item1->ratio)
        return 1;
    else
        return -1;
}

float bound(Node u)
{
    if (u.weight >= capacity)
        return 0;

    float profit_bound = u.profit;
    int j = u.level + 1;
    int totweight = u.weight;

    while (j < n && totweight + items[j].weight <= capacity)
    {
        totweight += items[j].weight;
        profit_bound += items[j].profit;
        j++;
    }

    if (j < n)
        profit_bound += (capacity - totweight) * items[j].ratio;

    return profit_bound;
}

void knapsack()
{
    Node u, v;
    int maxProfit = 0;

    // Root node
    v.level = -1;
    v.profit = 0;
    v.weight = 0;
    v.bound = bound(v);

    Node queue[MAX];
    int front = 0, rear = 0;
    queue[rear++] = v;

    while (front < rear)
    {
        v = queue[front++];

        if (v.level == n - 1)
            continue;

        u.level = v.level + 1;
        u.weight = v.weight + items[u.level].weight;
        u.profit = v.profit + items[u.level].profit;

        if (u.weight <= capacity && u.profit > maxProfit)
            maxProfit = u.profit;

        u.bound = bound(u);
        if (u.bound > maxProfit)
            queue[rear++] = u;

        u.weight = v.weight;
        u.profit = v.profit;
        u.bound = bound(u);
        if (u.bound > maxProfit)
            queue[rear++] = u;
    }

    printf("Maximum Profit = %d\n", maxProfit);
}

int main()
{
    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);

    printf("Enter weight and profit of each item:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &items[i].weight, &items[i].profit);
        items[i].ratio = (float)items[i].profit / items[i].weight;
    }

    // Sort items by profit/weight ratio in descending order
    qsort(items, n, sizeof(Item), cmp);

    knapsack();

    return 0;
}
