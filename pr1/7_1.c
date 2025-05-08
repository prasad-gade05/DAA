#include <stdio.h>
#include <string.h>

#define d 256 // Number of characters in the input alphabet (assuming ASCII)
#define q 101 // A prime number to perform modulo operation

// Function to search for pattern in the text using Rabin-Karp algorithm
void rabinKarp(char *text, char *pattern)
{
    int M = strlen(pattern);
    int N = strlen(text);
    int i, j;
    int patternHash = 0; // Hash value for the pattern
    int textHash = 0;    // Hash value for the text
    int h = 1;

    // Precompute h = pow(d, M-1) % q
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of the pattern and the first window of text
    for (i = 0; i < M; i++)
    {
        patternHash = (d * patternHash + pattern[i]) % q;
        textHash = (d * textHash + text[i]) % q;
    }

    // Slide the pattern over the text one by one
    for (i = 0; i <= N - M; i++)
    {
        // If the hash values match, check the characters one by one
        if (patternHash == textHash)
        {
            for (j = 0; j < M; j++)
            {
                if (text[i + j] != pattern[j])
                    break;
            }
            // If pattern is found
            if (j == M)
                printf("Pattern found at index %d\n", i);
        }

        // Calculate the hash value for the next window of text
        if (i < N - M)
        {
            textHash = (d * (textHash - text[i] * h) + text[i + M]) % q;

            // We might get negative values of textHash, so we make it positive
            if (textHash < 0)
                textHash = (textHash + q);
        }
    }
}

int main()
{
    char text[] = "ABABABACDABABCABAB";
    char pattern[] = "ABABCABAB";

    rabinKarp(text, pattern);

    return 0;
}
