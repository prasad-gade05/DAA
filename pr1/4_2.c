#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node
{
    char ch;
    int freq;
    struct Node *left, *right;
};

// Min-heap node
struct MinHeap
{
    int size;
    struct Node *array[MAX];
};

// Create new node
struct Node *newNode(char ch, int freq)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->ch = ch;
    temp->freq = freq;
    temp->left = temp->right = NULL;
    return temp;
}

// Swap nodes
void swap(struct Node **a, struct Node **b)
{
    struct Node *t = *a;
    *a = *b;
    *b = t;
}

// Heapify
void heapify(struct MinHeap *heap, int i)
{
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < heap->size && heap->array[l]->freq < heap->array[smallest]->freq)
        smallest = l;
    if (r < heap->size && heap->array[r]->freq < heap->array[smallest]->freq)
        smallest = r;

    if (smallest != i)
    {
        swap(&heap->array[i], &heap->array[smallest]);
        heapify(heap, smallest);
    }
}

// Extract min node
struct Node *extractMin(struct MinHeap *heap)
{
    struct Node *temp = heap->array[0];
    heap->array[0] = heap->array[--heap->size];
    heapify(heap, 0);
    return temp;
}

// Insert node into heap
void insertHeap(struct MinHeap *heap, struct Node *node)
{
    int i = heap->size++;
    while (i && node->freq < heap->array[(i - 1) / 2]->freq)
    {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->array[i] = node;
}

// Build min heap
struct MinHeap *buildHeap(char chars[], int freqs[], int n)
{
    struct MinHeap *heap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    heap->size = 0;

    for (int i = 0; i < n; i++)
        heap->array[heap->size++] = newNode(chars[i], freqs[i]);

    for (int i = (heap->size - 2) / 2; i >= 0; i--)
        heapify(heap, i);

    return heap;
}

// Build Huffman Tree
struct Node *buildHuffman(char chars[], int freqs[], int n)
{
    struct MinHeap *heap = buildHeap(chars, freqs, n);

    while (heap->size > 1)
    {
        struct Node *left = extractMin(heap);
        struct Node *right = extractMin(heap);

        struct Node *merged = newNode('$', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        insertHeap(heap, merged);
    }

    return extractMin(heap);
}

// Print Huffman codes
void printCodes(struct Node *root, int code[], int top)
{
    if (root->left)
    {
        code[top] = 0;
        printCodes(root->left, code, top + 1);
    }

    if (root->right)
    {
        code[top] = 1;
        printCodes(root->right, code, top + 1);
    }

    if (!root->left && !root->right)
    {
        printf("%c: ", root->ch);
        for (int i = 0; i < top; i++)
            printf("%d", code[i]);
        printf("\n");
    }
}

int main()
{
    char chars[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freqs[] = {5, 9, 12, 13, 16, 45};
    int n = sizeof(chars) / sizeof(chars[0]);

    struct Node *root = buildHuffman(chars, freqs, n);

    int code[MAX];
    printCodes(root, code, 0);

    return 0;
}
