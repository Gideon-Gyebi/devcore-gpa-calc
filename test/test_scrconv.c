#include <stdio.h> // for printf
#include <string.h> // for strcmp
#include "gpa.h" // Include the header file for GPA conversion

// Function to test the scrconv function with a given score and expected result
void testCase(float score, char *expected)
{
    // Call the scrconv function to convert the score to a letter grade
    char *result = scrconv(score);

    // Compare the result with the expected value
    if (strcmp(result, expected) == 0) // string compare = strcmp
    {
        printf("[PASS] Score: %.1f -> %s\n", score, result);
    }
    else
    {
        printf("[FAIL] Score: %.1f -> Expected %s but got %s\n", score, expected, result);
    }
}

// Main function to run the test cases for the scrconv function
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

    printf("\n Decimal and boundary tests \n");
    testCase(85.0f, "A+");
    testCase(84.9f, "A");
    testCase(79.9f, "B+");
    testCase(74.5f, "B");
    testCase(49.9f, "F");
    testCase(100.5f, "INVALID");
    testCase(-0.5f, "INVALID");

    return 0;
}