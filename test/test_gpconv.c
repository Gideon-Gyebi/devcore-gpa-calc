#include <stdio.h> // for printf
#include <string.h> // for strcmp
#include "gpa.h" // Include the header file for GPA conversion

// Function to test the gpconv function with a given score and expected result
void testCase(int score, char *expected)
{
    // Call the gpconv function to convert the score to a letter grade
    char *result = gpconv(score);

    // Compare the result with the expected value
    if (strcmp(result, expected) == 0) // string compare = strcmp
    {
        printf("[PASS] Score: %3d -> %s\n", score, result);
    }
    else
    {
        printf("[FAIL] Score: %3d -> Expected %s but got %s\n", score, expected, result);
    }
}

// Main function to run the test cases for the gpconv function
int main()
{
    // Variable to iterate through the score ranges
    int i;

    // Print the header for the GPA Converter Tests
    printf("===== GPA Converter Tests =====\n\n");

    // Running tests for each range
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

    printf("\n");
    for ( i = 64; i >= 60; i--)
    {
        testCase(i, "C");
    }

    printf("\n");
    for (i = 59; i >= 55; i--)
    {
        testCase(i, "D+");
    }

    printf("\n");
    for (i = 54; i >= 50; i--)
    {
        testCase(i, "D");
    }

    printf("\n");
    for (i = 49; i >= 0; i--)
    {
        testCase(i, "F");
    }

    return 0;
}