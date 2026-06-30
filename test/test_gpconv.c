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
    printf("===== GPA Converter Tests =====\n\n");

    testCase(100, "A+");
    testCase(90, "A+");
    testCase(85, "A+");
    testCase(80, "A");

    return 0;
}