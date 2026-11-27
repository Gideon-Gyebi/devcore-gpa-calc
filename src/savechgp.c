#include "GPA.h"

// Stores one course's credit hour and grade point into the record array
void savechgp(CourseResult gpaStorage[], int index, float creditHour, float gradePoint)
{
    // Save credit hour at the specified array position
    gpaStorage[index].creditHour = creditHour;

    // Save grade point at the specified array position
    gpaStorage[index].gradePoint = gradePoint;

    // Function returns automatically because it is void
}