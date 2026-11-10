#include <stdio.h>
#include "gpa.h"

/*
 * test_savechgp.c
 * Test file for the savechgp.c function
 *
 * index, credithour, gradepoint
 *   0  ,     2     ,   10     →  Test Case 1 (Single course)
 *  [0,1,2] , [2.5,2,3] , [8.5,15 ,10] → Test Case 2 (Three courses)
 */

int main()
{
    GpaRecord gpaStorage[3];
    int index;
    float creditHour;
    float gradePoint;

    printf("\n===================SAVECHGP Function Tests===================\n\n");

    printf("Test Case 1: Valid Input (Single course) Normal Case.\n");
    index = 0;
    creditHour = 2.0f;
    gradePoint = 10.f;
    savechgp(gpaStorage, index, creditHour, gradePoint);

    if (gpaStorage[index].creditHour == 2.0f && gpaStorage[index].gradePoint == 10.0f)
    {
        printf("[PASS]\n");
    }
    else
    {
        printf("[FAIL]\n");
    }

    printf("--------------------------------------------------\n\n");

     printf("Test Case 2: Valid Input (Three courses) Normal Case.\n");
     
}