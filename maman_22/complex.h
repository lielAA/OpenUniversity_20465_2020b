/*Author: Liel Adir
  Student ID: 20-280253
  Date: 30/05/2020
                                            ################ Program Description ##############
This program is interactive program, that received from the user different commands for different operations on complex numbers.
First the user enter his command (taken from defined command), this command pass through validation process (based on definition for every command)
In the end if validation process passed successfully its move to calculation process (following to user request).
Any command contain: 1.string command 2.complex variable(s) 3. comma(s) 4.double number(s).
Command Description & Explanation:
1. String command could be only one of the next nine commands: 1.read_comp 2.print_comp 3.add_comp 4.sub_comp 5.mult_comp_comp 6.mult_comp_real 7.miult_comp_img 8.abs_comp 9.stop
Any command execute different operation on his variables. The program stop only when the user enter "stop" command, othewise - an additional command request will be made.
2.Complex variable(s) - each of variable is type of structure that contain real double number and image double number, there is only 6 complex variables that represent by chars A-F (A,B,C,D,E,F).
3.The variables in the command seperated by comma(s).
4.double number represent the real and image number, and also some operation on complex variables
commads examples: read_comp A,2,3         --> command description: this command set real_number of A var to 2 and image_number to 3, and print A var at next structure: A = 2 + (3)i
                  print_comp    C         --> command description: this command print (for example) C complex var at next structure: -3.12 + 153.8  
                  add_comp E,   C         --> command description: this command sum real_number of E and real_number of C ; and sum image_number of E and image_number of C ; and print the result at next structure: 9.12 + (6.12)i
                  mult_comp_real D,-21.33
                  read_comp B,  -8.12,  32.14*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Defintions: @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@@@@@@@@ constants , typedef , enum , structures @@@@@@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

#define MAX_FULL_LINE_COMMAND 1000
#define MAX_PART_COMMAND 14
#define INT_MAX 2147483647
#define MAX_CHAR_DIGIT 100

typedef enum{FALSE,TRUE} boolean; /*bollean parameter FALSE=0 ; TRUE=1*/
enum{NEGATIVE = -1,ZERO = 0,ONE = 1,TWO = 2,THREE = 3,FOUR = 4,FIVE = 5,SIX = 6,SEVEN = 7,EIGHT = 8,
     NINE = 9,TEN = 10,THIRTEEN = 13,FOURTENN = 14,MINLOWERCASE = 97,MAXLOWERCASE = 122} commandLen;/*defined enum for different constants in program*/

typedef enum{A,B,C,D} commandType; /*var represent commad type --> A = "command A,B"     B = "command A,double"      C = "command A,double,double"       D = "command A"*/

typedef struct complex *complexP; /*pointer to complex struct*/
typedef struct complex            /*defined struct of complex that contain double real and image numbers*/
{
  double reNum;
  double imNum;
} item;

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@@@@@@@@ mycomp.c and mycompUtilities.c methods @@@@@@@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/*          ##### Method Description #####
 initializeComplexP method create array in size of 6 complex vars in the heap ,initialize every complex var attribute (reNum & imNum) to 0
 In the end return the address head of the the array to the main*/
complexP initializeComplexP();
/*          ##### Method Description #####
 initializeArray method initialize all arrays after any command,these arrays store the data we capture during the command*/
void initializeArray(char[MAX_FULL_LINE_COMMAND]);
/*          ##### Method Description #####
This method execute a first validation and sorting to user command, first it capture only the first string in the command (read_comp, print_comp etc) 
validate this string is legal following to definitions, and send every command continue the validation according to command type and params*/
boolean commandValidation(char[MAX_FULL_LINE_COMMAND]);
/*          ##### Method Description #####
 sortCommandType method received command type (A,B,C,D), the last index of temp_command (when the next part of command begin) and char array
 following to command type it send it continue validate as based on the next params(complexVar, commas, digits).
 any var return integer number that represent the index that the next var supposed to validate, if it return -1 --> its mean the validation Failed and the command Wrong*/
boolean sortCommandType(commandType, int, char[MAX_FULL_LINE_COMMAND]);
/*          ##### Method Description #####
 complexVarValidation method Test validation of the command from the end of str_command up to complexVar
 its received the last index from str_command, and strcommand array, and return the index after the complexVar 
 if Validation failed - return -1*/
int complexVarValidation(int, char[MAX_FULL_LINE_COMMAND]);
/*          ##### Method Description #####
commaValid method validate comma between variables. 
its received the last index from the last var(number or complexVar), and strcommand array, and return the index after the comma 
if Validation failed - return -1*/
int commaValid(int, char[]);
/*          ##### Method Description #####
 endOfCommand method validate the end of command. 
its received the last index from the last var (numver or complexVar), and strcommand array, and return TRUE if Pass successfully 
if Validation failed - return -1*/
int endOfCommand(int, char[]);
/*          ##### Method Description #####
isDigit method validate double numbers. 
its received the last index from the last comma, and strcommand array, and return the index after the number 
if Validation failed - return -1*/
int isDigit(int, char[]);
/*          ##### Method Description #####
 isNegative method verify if the returned number from various validation is NEGATIVE
 if NEGATIVE return TRUE   ;  else return FALSE*/
boolean isNegative(int);
/*          ##### Method Description #####
 setComplexVar method received the capture name (that complexVarValidation sent) and match it to its address in complex vars array*/
void setComplexVar(char);
/*          ##### Method Description #####
 setDigit method converted the char positive digits (from digitArr[]) to double positive digits (to doubleDigitArr[])*/
void setDigit();
/*          ##### Method Description #####
 setMinusDigit method converted the negative char digits (from digitArr[]) to negative double digits (to doubleDigitArr[])*/
void setMinusDigit();
/*          ##### Method Description #####
 initDigitArr method initialize char digitArr before enter to isDigit()*/
void initDigitArr();
/*          ##### Method Description #####
 sendParamsToCalc method execute after user command validation passed successfully.
 it received one OR two complexVar(s) (depend on command type) and send it to complex.c methods.
 The method return TRUE --> if calculation and memory allocation passed successfully, and FALSE if not*/
boolean sendParamsToCalc(complexP, complexP);
/*          ##### Method Description #####
 printComplexVar method print complexVar name (A-F) accordance to tempComplexAddArr its received from sendParamsToCalc()
 It reffer only to command of type C (read_temp)*/
void printComplexVar(complexP);

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@@@@@@@@ complex.c methods @@@@@@@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/*          ##### Method Description #####
read_comp method received complexVar, and two double number from the user command,
and set first double number as real number at complexVar location in the memory, 
and second double number as image number at complexVar location in the memory*/
void read_comp(complexP, double, double);
/*          ##### Method Description #####
print_comp method received complexVar from user command and print the content from this complexVar(real and image number)
For example: 2.42 + (-18.74)i */
void print_comp(complexP);
/*          ##### Method Description #####
add_comp method received two complexVars from user command and sum both complexVars at the next structure:
sum_real_num = real_num_1 + real_num_2
sum_image_num = image_num_1 + image_num_2
Save it in temp complexVar (not run over existing complexVar) and return temp complexVar to main()*/
complexP add_comp(complexP, complexP, complexP);
/*          ##### Method Description #####
sub_comp method received two complexVars from user command and subtraction both complexVars at the next structure:
sub_real_num = real_num_1 - real_num_2
sub_image_num = image_num_1 - image_num_2
Save it in temp complexVar (not run over existing complexVar) and return temp complexVar to main()*/
complexP sub_comp(complexP, complexP, complexP);
/*          ##### Method Description #####
mult_comp_real method received one complexVar from user command and multiple complexVars with real number from the command at the next structure:
mult_real_num = complexVar->real_num * real_num(user input)
mult_image_num = complexVar->image_num * real_num(user input)
Save it in temp complexVar (not run over existing complexVar) and return temp complexVar to main()*/
complexP mult_comp_real(complexP, complexP, double);
/*          ##### Method Description #####
mult_comp_img method received one complexVar from user command and multiple complexVars with image number from the command at the next structure:
mult_real_num = (-1) * (complexVar->img_num * image_num(user input))
mult_image_num = complexVar->real_num * image_num(user input)
Save it in temp complexVar (not run over existing complexVar) and return temp complexVar to main()*/
complexP mult_comp_img(complexP, complexP, double);
/*          ##### Method Description #####
mult_comp_comp method received two complexVars from user command and multiple both complexVars at the next structure:
mult_real_num = (real_num_1 * real_num_2) - (image_num_1 * image_num_2)
mult_image_num = (real_num_1 * image_num_2) + (image_num_1 * real_num_2)
Save it in temp complexVar (not run over existing complexVar) and return temp complexVar to main()*/
complexP mult_comp_comp(complexP, complexP, complexP);
/*          ##### Method Description #####
abs_comp method received one complexVar from user command and calculate the absulte value of complexVar at the next structure:
complexVar->reNum = sqrt(pow(complexVar_1->reNum, TWO))
complexVar->imNum = sqrt(pow(complexVar_1->imNum, TWO))
Save it in temp complexVar (not run over existing complexVar) and return temp complexVar to main()*/
complexP abs_comp(complexP, complexP);
/*          ##### Method Description #####
allocate 1 temp complexVar (sizeof 1 item) to save all methos calculation*/
complexP tempMemAllocate();
