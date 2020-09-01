/*Author: Liel Adir
  Student ID: 20-280253
  Date: 30/05/2020
                                    ################ Program Description ##############
This program is interactive program, that received from the user different commands for different operations on complex numbers.
First the user enter his command (taken from defined command), this command pass through validation process (based on definition for every command)
In the end if validation process passed successfully its move to calculation process (following to user request).
Any command contain: 1.string command 2.complex variable(s) 3. comma(s) 4.double number(s).
1. String command could be only one of the next nine commands: 1.read_comp 2.print_comp 3.add_comp 4.sub_comp 5.mult_comp_comp 6.mult_comp_real 7.miult_comp_img 8.abs_comp 9.stop
Any command execute different operation on his variables. The program stop only when the user enter "stop" command, othewise - an additional command request will be made.
2.Complex variable(s) - each of variable is type of structure that contain real double number and image double number, there is only 6 complex variables that represent by chars A-F (A,B,C,D,E,F).
3.The variables in the command seperated by comma(s).
4.double number represent the real and image number, and also some operation on complex variables
commads examples: read_comp A,2,3         --> this command set real_number of A var to 2 and image_number to 3, and print A var at next structure: A = 2 + (3)i
                  print_comp    C         --> this command print (for example) C complex var at next structure: -3.12 + 153.8  
                  add_comp E,   C         --> this command sum real_number of E and real_number of C ; and sum image_number of E and image_number of C ; and print the result at next structure: 9.12 + (6.12)i
                  mult_comp_real D,-21.33
                  read_comp B,  -8.12,  32.14*/

#include "complex.h"

commandType cType;                   /*represent type of current comand type: A = "str A,B"     B = "str A,double"      C = "str A,double,double"       D = "str A"*/
char temp_command[MAX_PART_COMMAND]; /*array for only string command without complex params, commas and digits*/
complexP head;                       /*pointer to start of complex vars array - array is in sizeof 6 vars (A-F)*/
complexP tempComplexAddArr[TWO];     /*array that save the address of complex vars that the user enter in the command*/
double doubleDigitArr[TWO];          /*array that save only the numbers (in double) the user enter in the command*/

int main()
{
    char strcommand[MAX_FULL_LINE_COMMAND]; /*char array contain user command input*/

    head = (complexP)initializeComplexP(); /*initialize complex array (6 variables A-F) save pointer to start of array in head*/

    printf("\nEnter one of the following next commands with relevant parameters for each:\n1. read_comp \n2. print_comp \n3. add_comp \n4. sub_comp \n5. mult_comp_real \n6. mult_comp_img \n7. mult_comp_comp \n8. abs_comp \n9. stop\n");
    printf("\nExamples for different commands:\n--------------------------------\nread_comp A,20,3\nprint_comp C\nsub_comp B,D\nmult_comp_real E,-51.22\n--------------------------------\nInsert command here:\n");
    while (fgets(strcommand, MAX_FULL_LINE_COMMAND, stdin) != NULL)
    {
        printf("\nTyped Command: \n%s", strcommand);
        if (commandValidation(strcommand) == TRUE) /*if command validation pass successfully*/
        {
            if (sendParamsToCalc(tempComplexAddArr[ZERO], tempComplexAddArr[1]) == FALSE) /*send params to calculation*/
            {
                continue;
            }
            /*printf("\nPASS");*/
        }
        else
        {
            if ((strncmp(temp_command, "stop", FOUR) == ZERO) && (strlen(temp_command) == FOUR)) /*if user input is "stop" command*/
            {
                break;
            }
            /*printf("\nFAILED");*/
        }
        initializeArray(strcommand); /*initialize utilities array that stored relevant data for validation*/
        printf("\n#############################\nPlease enter another command:\n");
    }
    free(head); /*Free array memory*/
    return 0;
}

/*          ##### Method Description #####
 sendParamsToCalc method execute after user command validation passed successfully.
 it received one OR two complexVar(s) (depend on command type) and send it to complex.c methods.
 The method return TRUE --> if calculation and memory allocation passed successfully, and FALSE if not*/
boolean sendParamsToCalc(complexP var_1, complexP var_2)
{
    complexP compVar; /*temp complexVar - for returned value from calculation method in complex.c*/
    switch (cType)
    {
    case A: /*case command is type of A --> its structure is: command complexVar double,double*/
    {
        if ((strncmp(temp_command, "add_comp", EIGHT) == ZERO)) /*if current command is add_comp"*/
        {
            compVar = add_comp(tempMemAllocate(), var_1, var_2); /*allocate temp complex memory, and send it with two user complexVars to add_comp method*/
        }
        else if ((strncmp(temp_command, "sub_comp", EIGHT) == ZERO)) /*if current command is sub_comp"*/
        {
            compVar = sub_comp(tempMemAllocate(), var_1, var_2); /*allocate temp complex memory, and send it with two user complexVars to sub_comp method*/
        }
        else /*if current command is mult_comp_comp"*/
        {
            compVar = mult_comp_comp(tempMemAllocate(), var_1, var_2); /*allocate temp complex memory, and send it with two user complexVars to mult_comp_comp method*/
        }
        if (compVar == NULL) /*if memory allocation failed*/
            return FALSE;
        printf("\n%.2f + (%.2f)i", compVar->reNum, compVar->imNum); /*print complexVar attributes (real and image number) after calculation*/
        free(compVar);                                              /*free temp complexVar memory*/
        break;
    }
    case B: /*case command is type of B --> its structure is: command complexVar,double*/
    {
        if (strncmp(temp_command, "mult_comp_real", FOURTENN) == ZERO) /*if current command is mult_comp_real"*/
        {
            compVar = mult_comp_real(tempMemAllocate(), var_1, doubleDigitArr[ZERO]); /*allocate temp complex memory, and send it with one user complexVars to mult_comp_real method*/
        }
        else /*if current command is mult_comp_img"*/
        {
            compVar = mult_comp_img(tempMemAllocate(), var_1, doubleDigitArr[ZERO]); /*allocate temp complex memory, and send it with one user complexVars to mult_comp_img method*/
        }
        if (compVar == NULL) /*if memory allocation failed*/
            return FALSE;
        printf("\n%.2f + (%.2f)i", compVar->reNum, compVar->imNum); /*print complexVar attributes (real and image number) after calculation*/
        free(compVar);                                              /*free temp complexVar memory*/
        break;
    }
    case C: /*case command is type of C --> its structure is: command complexVar,double,double*/
    {
        if (var_1 == NULL) /*if complexVar is NULL*/
            return FALSE;
        printComplexVar(var_1);                                      /*first print complexVar name - following to his address*/
        read_comp(var_1, doubleDigitArr[ZERO], doubleDigitArr[ONE]); /*send complexVar and two double numbers to read_comp*/
        printf("%.2f + (%.2f)i", var_1->reNum, var_1->imNum);        /*after calculation and set the result in var_1 complexVar print its attributes (real and image number)*/
        break;
    }
    case D: /*case command is type of D --> its structure is: command complexVar*/
    {
        if (strncmp(temp_command, "print_comp", TEN) == FALSE) /*if current command is print_comp"*/
        {
            print_comp(var_1); /*send complexVar to print_comp*/
            break;
        }
        else /*if current command is abs_comp"*/
        {
            compVar = abs_comp(tempMemAllocate(), var_1); /*allocate temp complex memory, and send it with one user complexVars to abs_comp method*/
            if (compVar == NULL)                          /*if memory allocation failed*/
                return FALSE;
            printf("\n%.2f + (%.2f)i", compVar->reNum, compVar->imNum); /*print complexVar attributes (real and image number) after calculation*/
            free(compVar);                                              /*free temp complexVar memory*/
            break;
        }
    }
    default:
    {
        return FALSE;
        break;
    }
    }
    return TRUE;
}