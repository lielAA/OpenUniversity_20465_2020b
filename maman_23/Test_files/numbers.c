/*Author: Liel Adir
  Student ID: 20-280253
  Date: 10/06/2020
                                            ################ Program Description ##############
This program recieved numbers as digits in one line, every number seperate by one or more white space(s) and print the numbers in words (every word print in new line).
The user can operate the program by 3 different modes from the command line:
1. Input data (digits) received from stdin(keyboard) & output data send to stdout(screen).
2. Input data (digits) received from destined input file & output data send to stdout(screen).
3. Input data (digits) received from destined input file & output data send to destined output file(if output data not exist - the system create it).
Note1: If destined input file not exist error message print to stderr and program stop 
Note2: if user insert more than 2 files - error message print to stderr and program stop 

Different exapmles for program executing:
./numbers                                   input data = stdin ; output data = stdout 
./numbers file_I                            input data = file_I ; output data = stdout 
./numbers file_I file_O                     input data = file_I ; output data = file_O
./numbers file_I file_O fileError           Error message*/
#include "numbers.h"

int main(int argc, char *argv[])
{
    switch (argc)
    {
    case ONE:
        setfiles(ZERO, stdin, stdout); /*case user not insert files as argument - input from stdin & output to stdout*/
        break;
    case TWO:
        setfiles(ONE, argv[ONE], stdout); /*case user insert only input file as argument - input from file & output to stdout*/
        break;
    case THREE:
        setfiles(TWO, argv[ONE], argv[TWO]); /*case user insert input and output files as arguments - input from file & output to file*/
        break;
    default: /*if user insert more than 2 files*/
        fprintf(stderr, "\nYou entered more than 2 file's name - Please Re-enter\n");
        exit(0);
    }
    return 0;
}
