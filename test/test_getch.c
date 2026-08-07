#include <stdio.h>
#include "gpa.h"


/*
 * test_getch.c
 * Test file for the getch function
 
 * 1       → lower boundary
 * 3       → upper boundary
 * 2       → normal valid value
 * 0       → just below range
 * 4       → just above range
 * abc     → completely invalid input
 * 2abc    → valid number + invalid trailing characters
 * 2.5     → valid floating-point input
 */


void test_getch(void)
 {
     float creditHours = getch();
     printf("Credit Hours Entered: %.2f\n", creditHours);
 }


int main()
{
    printf("===== GETCH Function Tests =====\n\n");

    printf("Test Case 1: Valid input (1) Lower Boundary\n");
    test_getch();

    printf("\nTest Case 2: Valid input (3) Upper Boundary\n");
    test_getch();

    printf("\nTest Case 3: Valid input (2) Normal Value\n");
    test_getch();

    printf("\nTest Case 4: Invalid input (0) Below Range\n");
    test_getch();

    printf("\nTest Case 5: Invalid input (4) Above Range\n");
    test_getch();

    printf("\nTest Case 6: Invalid input (abc) Non-numeric\n");
    test_getch();

    printf("\nTest Case 7: Invalid input (2abc) Valid + Invalid Characters\n");
    test_getch();

    printf("\nTest Case 8: Invalid input (2.5) Valid floating-point input\n");
    test_getch();

    return 0;
}