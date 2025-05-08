#include <stdio.h>

struct Item
{
    int weight, value;
};

void sortByRatio(struct Item arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            float r1 = (float)arr[i].value / arr[i].weight;
            float r2 = (float)arr[j].value / arr[j].weight;
            if (r1 < r2)
            {
                struct Item temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

float fractionalKnapsack(int W, struct Item arr[], int n)
{
    sortByRatio(arr, n);

    float totalValue = 0.0;
    for (int i = 0; i < n && W > 0; i++)
    {
        if (arr[i].weight <= W)
        {
            totalValue += arr[i].value;
            W -= arr[i].weight;
        }
        else
        {
            totalValue += arr[i].value * ((float)W / arr[i].weight);
            break;
        }
    }

    return totalValue;
}

int main()
{
    struct Item items[] = {{10, 60}, {20, 100}, {30, 120}};
    int W = 50;
    int n = sizeof(items) / sizeof(items[0]);

    float maxValue = fractionalKnapsack(W, items, n);
    printf("Maximum value: %.2f\n", maxValue);
    return 0;
}
