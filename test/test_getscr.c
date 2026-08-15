#include <stdio.h>
#include "gpa.h"

/*
 * test_getsrc.c
 * Test file for the getsrc function

 * 0      → lower boundary
 * 100     → upper boundary
 * 50      → normal valid value
 * 50.5    → valid number + invalid decimal numbers
 * 50abc   → valid number + invalid trailing characters
 * -1      → just below range
 * 101     → just above range
 * abc     → completely invalid input
 */

int test_getscr(void)
{
    int score = getscr();

    return score;
}

int main()
{
    int score;

    printf("\n===================== GETSRC Function Tests =====================\n\n");

    printf("Test Case 1: Valid Input (0) Lower Boundary.\n");
    score = test_getscr();
    if (score == 0)
    {
        printf("\n[Score Entered: %d]\n", score);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 2: Valid Input (100) Upper Boundary.\n");
    score = test_getscr();
    if (score == 100)
    {
        printf("\n[Score Entered: %d]\n", score);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 3: Valid Input (50) Normal Value.\n");
    score = test_getscr();
    if (score == 50)
    {
        printf("\n[Score Entered: %d]\n", score);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 4: Invalid Input (50.5) Valid + Invalid Decimal Numbers.\n");
    score = test_getscr();
    if (score == 50)
    {
        printf("\n[Score Entered: %d]\n", score);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 5: Invalid Input (50abc) Valid + Invalid Characters.\n");
    score = test_getscr();
    if (score == 50)
    {
        printf("\n[Score Entered: %d]\n", score);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 6: Invalid input samples (-1, 101, abc) Below Range,\nAbove Range and Completely Invalid.\n");
    test_getscr();
    printf("\n[PASS] = Two range errors and one invalid input error.\n");
    printf("[FAIL] = If there are less than three error messages.\n");

    printf("\n=========================== Test End ===========================\n");

    return 0;
}