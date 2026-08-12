#include <stdio.h>
#include <string.h>
#include "gpa.h"

/*
 * test_getcrs.c
 * Test file for the getcrs function
 * 
 * 1        → returns "Programming Fundamentals"
 * 2        → returns "Mathematics for Computer Science"
 * 3        → returns "Communication Skills"
 * 4        → returns "Numeracy Skills"
 * 5        → returns "Computer System Installation and Maintenance"
 * 6        → returns "Office Productivity"
 * 7        → returns "Fundamentals of Computer Science"
 * 8        → prompts the user to enter the course name manually
 *            and returns the entered course name
 * 4abc     → valid number + invalid trailing characters
 * 0        → just below range
 * 9        → just above range
 * abc      → completely invalid input
 */

char* test_getcrs(void)
{
    char* courseName = getcrs();

    return courseName;
}


int main()
{
    char* courseName;

    printf("\n===================== GETCRS Function Tests =====================\n\n");

    printf("Test Case 1: Valid input (1) -> returns \"Programming Fundamentals\".\n");
    courseName = test_getcrs();
    if (courseName != NULL && strcmp(courseName, "Programming Fundamentals") == 0)
    {
        printf("\n[Course Name Entered: %s]\n", courseName);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 2: Valid input (2) -> returns \"Mathematics for Computer Science\".\n");
    courseName = test_getcrs();
    if (courseName != NULL && strcmp(courseName, "Mathematics for Computer Science") == 0)
    {
        printf("\n[Course Name Entered: %s]\n", courseName);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 3: Valid input (3) -> returns \"Communication Skills\".\n");
    courseName = test_getcrs();
    if (courseName != NULL && strcmp(courseName, "Communication Skills") == 0)
    {
        printf("\n[Course Name Entered: %s]\n", courseName);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 4: Valid input (4) -> returns \"Numeracy Skills\".\n");
    courseName = test_getcrs();
    if (courseName != NULL && strcmp(courseName, "Numeracy Skills") == 0)
    {
        printf("\n[Course Name Entered: %s]\n", courseName);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 5: Valid input (5) -> returns \"Computer System Installation and Maintenance\".\n");
    courseName = test_getcrs();
    if (courseName != NULL && strcmp(courseName, "Computer System Installation and Maintenance") == 0)
    {
        printf("\n[Course Name Entered: %s]\n", courseName);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 6: Valid input (6) -> returns \"Office Productivity\".\n");
    courseName = test_getcrs();
    if (courseName != NULL && strcmp(courseName, "Office Productivity") == 0)
    {
        printf("\n[Course Name Entered: %s]\n", courseName);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 7: Valid input (7) -> returns \"Fundamentals of Computer Science\".\n");
    courseName = test_getcrs();
    if (courseName != NULL && strcmp(courseName, "Fundamentals of Computer Science") == 0)
    {
        printf("\n[Course Name Entered: %s]\n", courseName);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 8: Valid input (8) -> returns \"Digital Electronics\".\n");
    courseName = test_getcrs();
    if (courseName != NULL && strcmp(courseName, "Digital Electronics") == 0)
    {
        printf("\n[Course Name Entered: %s]\n", courseName);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 9: Invalid input (4abc) -> valid number + invalid trailing characters.\n");
    courseName = test_getcrs();
    if (courseName != NULL && strcmp(courseName, "Numeracy Skills") == 0)
    {
        printf("\n[Course Name Entered: %s]\n", courseName);
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("----------------------------------------------------------------\n");

    printf("\nTest Case 10: Invalid input samples (0, 9, abc) Below Range,\nAbove Range and Completely Invalid.\n");
    test_getcrs();
    printf("\n[PASS] = Two range errors and one invalid input error.\n");
    printf("[FAIL] = If there are less than three error messages.\n");

    printf("\n=========================== Test End ===========================\n");

    return 0;
}