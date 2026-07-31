/*
It prevents the contents of the 'GPA_H' from being processed
multiple times if it has been included in the header file
*/
#ifndef GPA_H
/*
Defines the 'GPA_H' macro. It prevents any future '#ifndef GPA_H'
from running to avoid duplicate definition errors.
*/
#define GPA_H

// Maximum number of courses the GPA calculator can store
#define MAX_COURSES 15

// Structure for storing credit hour and grade point of each course
typedef struct
{
    int creditHour;
    float gradePoint;

} GpaRecord;


void savechgp(GpaRecord gpaStorage[], int index, float creditHour, float gradePoint); // Function prototype for saving credit hour and grade point

int getnumcrs(void);                               // Function prototype for 'getnumcrs'. Returns an integer value representing the number of courses.
char *getcrs(void);                                // Function prototype for 'getcrs'. Returns a pointer to a character string representing the course name.
float getch(void);                                 // Function prototype for 'getch'. Returns a float value representing the number of credit hours.
int getscr(void);                                  // Function prototype for 'getscr'. Returns an integer value representing the score.
char *scrconv(int score);                          // Function prototype for 'scrconv'. Returns a pointer to a character string.
float gpcalc(float gradeValue, float creditHours); // Function prototype for 'gpcalc'. Returns a float grade value.
float lgconv(char *letterGrade);                   // Function prototype for 'lgconv'. Returns a float value representing the letter grade.
float tgpcalc(float gradePoint, float gradeValue);

/*
Closes the '#ifndef' conditional block and ends the definition of the
'GPA_H' macro. It ensures that the contents of the header file are only
included once during compilation, preventing duplicate definition errors.
*/
#endif