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

char *scrconv(int score); // Function prototype for 'scrconv'. Returns a pointer to a character string.
float gpcalc(float gradeValue, float creditHours); // Function prototype for 'gpcalc'. Returns a float grade value.

/*
Closes the '#ifndef' conditional block and ends the definition of the 
'GPA_H' macro. It ensures that the contents of the header file are only
included once during compilation, preventing duplicate definition errors.
*/
#endif 
