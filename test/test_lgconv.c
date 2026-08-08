#include <stdio.h>  // for printf
#include <string.h> // for strcmp
#include "gpa.h"    // Include the header file for GPA conversion

// Function to test the lgconv function with a given score and expected result
void testCase(char *letterGrade, float expected)
{
    // Call the lgconv function to convert the letter grade to a grade point value
    float result = lgconv(letterGrade);

    // Compare the result with the expected value
    if (result == expected)
    {
        printf("[PASS] Letter Grade: %s -> %.1f\n", letterGrade, result);
    }
    else
    {
        printf("[FAIL] Letter Grade: %s -> Expected %.1f but got %.1f\n", letterGrade, expected, result);
    }
}

// Main function to run the test cases for the lgconv function
int main()
{
    // Variable to iterate through the score ranges

    // Print the header for the Letter Grade Converter Tests
    printf("===== Letter Grade  Converter Tests =====\n\n");

    // Running tests for each letter grade
    testCase("A+", 5.0);
    testCase("A", 4.5);
    testCase("B+", 4.0);
    testCase("B", 3.5);
    testCase("C+", 3.0);
    testCase("C", 2.5);
    testCase("D+", 2.0);
    testCase("D", 1.5);
    testCase("F", 0.0);

    return 0;
}