#ifndef GPA_H // It prevents the contents of the 'GPA_H' from being processed multiple times if it has
// been included in the header file
#define GPA_H // Defines the 'GPA_H' macro. It prevents any future '#ifndef GPA_H' from running to avoid
// duplicate definition errors.

char *gpconv(int a); // Declares the function name 'gpconv.c' and tells the compiler that this function
                     // accepts an integer (int a) as an input and returns a pointer to a character string (char *).

#endif // Closes the '#ifndef' conditional block and ends the definition of the 'GPA_H' macro. It ensures
// that the contents of the header file are only included once during compilation, preventing duplicate
// definition errors.
