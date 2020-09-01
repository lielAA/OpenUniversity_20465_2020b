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

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


/*Numbers Definitions*/
enum {ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,
      ELEVEN,TWELVE,THIRTEEN,FOURTEEN,FIFTEEN,SIXTEEN,SEVENTEEN,EIGHTEEN,NINETEEN,MAX_SIZE_DIGITARR=10000};

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@@@@@@@@ numbers.c and numbersUtilities.c methods @@@@@@@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/*          ##### Method Description #####
 setFiles received from main the type of input (Zero = no files ; ONE = only input files insert ; TWO = input&output files insert)
 the method open the relevant files and send it to inputdigits(), in the end close files*/
void setfiles(int,...);
/*          ##### Method Description #####
 inputdigits received from setfiles the type of input (Zero = no files ; ONE = only input files insert ; TWO = input&output files insert)
 the method catch the numbers from input file - convert it from char to integer and send only the number to convertDigitsToWords()*/
void inputdigits(int,...);
/*          ##### Method Description #####
 convertDigitsToWords received from inputdigits the number to convert as integer - and print it to the user as words (10 ==> ten)
 the prinitg execute in output file the user insert as argimnet*/
void convertDigitsToWords(int,...);
/*          ##### Method Description #####
 printDigit received from convertDigitsToWords only the digit number to convert as integer - and print it to the user as words (10 ==> ten)
 the prinitg execute in output file the user insert as argimnet*/
void printDigit(int,FILE *);