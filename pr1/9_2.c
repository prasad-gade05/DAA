#include <stdio.h>

#define MAX 100

int subset[MAX], count = 0;

void subsetSum(int arr[], int n, int index, int target, int sum, int pos)
{
    if (sum == target)
    {
        // Print the current subset
        printf("Subset %d: ", ++count);
        for (int i = 0; i < pos; i++)
            printf("%d ", subset[i]);
        printf("\n");
        return;
    }

    for (int i = index; i < n; i++)
    {
        if (sum + arr[i] <= target)
        {
            subset[pos] = arr[i];
            subsetSum(arr, n, i + 1, target, sum + arr[i], pos + 1);
        }
    }
}

int main()
{
    int arr[] = {3, 34, 4, 12, 5, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 9;

    printf("Subsets with sum %d:\n", target);
    subsetSum(arr, n, 0, target, 0, 0);

    if (count == 0)
        printf("No subsets found.\n");

    return 0;
}
