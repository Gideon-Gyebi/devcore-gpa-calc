#include "GPA.h"

// Stores one course's credit hour and grade point into the record array
void savechgp(CourseResult gpaStorage[], int index, float creditHour, float gradePoint, char courseName[100], int score, char letterGrade[3], float gradeValue)
{
    // Save credit hour at the specified array position
    gpaStorage[index].creditHour = creditHour;

    // Save grade point at the specified array position
    gpaStorage[index].gradePoint = gradePoint;

    // Save course name at the specified array position
    gpaStorage[index].courseName = courseName;

    // Save score at the specified array position
    gpaStorage[index].score = score;

    // Save letter grade at the specified array position
    gpaStorage[index].letterGrade = letterGrade;

    // Save grade value at the specified array position
    gpaStorage[index].gradeValue = gradeValue;

    // Function returns automatically because it is void
}