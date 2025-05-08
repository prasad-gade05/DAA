#include <stdio.h>
#include <string.h>

// Function to compute the LPS (Longest Prefix Suffix) array
void computeLPSArray(char *pattern, int M, int *lps)
{
    int length = 0; // length of the previous longest prefix suffix
    lps[0] = 0;     // LPS[0] is always 0
    int i = 1;

    // Build the LPS array
    while (i < M)
    {
        if (pattern[i] == pattern[length])
        {
            length++;
            lps[i] = length;
            i++;
        }
        else
        {
            // (pattern[i] != pattern[length])
            if (length != 0)
            {
                length = lps[length - 1]; // Try the previous longest prefix suffix
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Function to implement KMP algorithm
void KMPSearch(char *text, char *pattern)
{
    int N = strlen(text);
    int M = strlen(pattern);

    // Create an array to hold the longest prefix suffix values
    int lps[M];

    // Preprocess the pattern to fill the LPS array
    computeLPSArray(pattern, M, lps);

    int i = 0; // Index for text
    int j = 0; // Index for pattern
    while (i < N)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }

        // If j == M, it means the entire pattern is matched
        if (j == M)
        {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        }
        // Mismatch after j matches
        else if (i < N && pattern[j] != text[i])
        {
            // Do not match lps[0..lps[j-1]] characters, they will match anyway
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }
}

int main()
{
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABABCABAB";

    KMPSearch(text, pattern);

    return 0;
}
