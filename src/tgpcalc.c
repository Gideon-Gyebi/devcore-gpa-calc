#include "gpa.h"

// Calculates the total grade points of all stored courses
float tgpcalc(GpaRecord gpaStorage[], int numCourses)
{
    float totalGradePoint = 0.0;
    int index;
    // Sum the grade points of all stored courses
    for (index = 0; index < numCourses; index++)
    {
        totalGradePoint += gpaStorage[index].gradePoint;
    }

    return totalGradePoint;
}