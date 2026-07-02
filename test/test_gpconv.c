#include <stdio.h>
#include <string.h>
#include "gpa.h"

void testCase(int score, char *expected)
{
    char *result = gpconv(score);

    if (strcmp(result, expected) == 0) // string compare = strcmp
    {
        printf("[PASS] Score: %3d -> %s\n", score, result);
    }
    else
    {
        printf("[FAIL] Score: %3d -> Expected %s but got %s\n", score, expected, result);
    }
}

int main()
{
    int i;

    printf("===== GPA Converter Tests =====\n\n");
    // running tests for each range
    for (i = 100; i >= 85; i--)
    {
        testCase(i, "A+");
    }

    printf("\n");
    for (i = 84; i >= 80; i--)
    {
        testCase(i, "A");
    }

    printf("\n");
    for (i = 79; i >= 75; i--)
    {
        testCase(i, "B+");
    }

    printf("\n");
    for (i = 74; i >= 70; i--)
    {
        testCase(i, "B");
    }

    printf("\n");
    for (i = 69; i >= 65; i--)
    {
        testCase(i, "C+");
    }

    return 0;
}