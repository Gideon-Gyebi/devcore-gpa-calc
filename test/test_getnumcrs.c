#include <stdio.h>
#include "gpa.h"


/*
 * test_getnumcrs.c
 * Test file for the getnumcrs function
 
 * 1       → lower boundary
 * 15      → upper boundary
 * 8       → normal valid value
 * 7abc    → valid number + invalid trailing characters
 * 0       → just below range
 * 16      → just above range
 * abc     → completely invalid input
 */


int test_getnumcrs(void)
{
    int numCourses = getnumcrs();

    return numCourses;
}


int main()
{
    int numCourses;

    printf("\n===================== GETNUMCRS Function Tests =====================\n\n");

    printf("Test Case 1: Valid input (1) Lower Boundary.\n");
    numCourses = test_getnumcrs();
    if (numCourses == 1)
    {
        printf("\n[Number of Courses Entered: %d]\n", numCourses);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 2: Valid input (15) Upper Boundary.\n");
    numCourses = test_getnumcrs();
    if (numCourses == 15)
    {
        printf("\n[Number of Courses Entered: %d]\n", numCourses);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 3: Valid input (8) Normal Valid Value.\n");
    numCourses = test_getnumcrs();
    if (numCourses == 8)
    {
        printf("\n[Number of Courses Entered: %d]\n", numCourses);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 4: Valid input (7abc) Valid Number + Invalid Trailing Characters.\n");
    numCourses = test_getnumcrs();
    if (numCourses == 7)
    {
        printf("\n[Number of Courses Entered: %d]\n", numCourses);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 5: Invalid input samples (0, 16, abc) Below Range,\nAbove Range and Completely Invalid.\n");
    test_getnumcrs();
    printf("\n[PASS] = Two range errors and one invalid input error.\n");
    printf("[FAIL] = If there are less than three error messages.\n");
    
    printf("\n=========================== Test End ===========================\n");

    return 0;
}