#include <stdio.h>
#include <stdlib.h>

#define MAX_SETS 100
#define MAX_ELEMENTS 100

int universe[MAX_ELEMENTS];
int covered[MAX_ELEMENTS];
int sets[MAX_SETS][MAX_ELEMENTS];
int setSizes[MAX_SETS];
int selectedSets[MAX_SETS];

int n, m; // n = universe size, m = number of subsets

int isCovered() {
    for (int i = 0; i < n; i++) {
        if (!covered[i])
            return 0;
    }
    return 1;
}

int countUncovered(int setIndex) {
    int count = 0;
    for (int i = 0; i < setSizes[setIndex]; i++) {
        int elem = sets[setIndex][i];
        if (!covered[elem])
            count++;
    }
    return count;
}

void markCovered(int setIndex) {
    for (int i = 0; i < setSizes[setIndex]; i++) {
        int elem = sets[setIndex][i];
        covered[elem] = 1;
    }
}

void greedySetCover() {
    int count = 0;
    while (!isCovered()) {
        int bestSet = -1, maxCover = -1;

        for (int i = 0; i < m; i++) {
            if (!selectedSets[i]) {
                int coverCount = countUncovered(i);
                if (coverCount > maxCover) {
                    maxCover = coverCount;
                    bestSet = i;
                }
            }
        }

        if (bestSet == -1) {
            printf("No complete cover possible.\n");
            return;
        }

        selectedSets[bestSet] = 1;
        markCovered(bestSet);
        count++;
        printf("Selected Set %d\n", bestSet);
    }

    printf("Total sets selected: %d\n", count);
}

int main() {
    printf("Enter size of universe (elements 0 to n-1): ");
    scanf("%d", &n);

    printf("Enter number of subsets: ");
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        printf("Enter size of set %d: ", i);
        scanf("%d", &setSizes[i]);
        printf("Enter elements: ");
        for (int j = 0; j < setSizes[i]; j++) {
            scanf("%d", &sets[i][j]);
        }
    }

    greedySetCover();
    return 0;
}
