/*Author: Liel Adir
  Student ID: 20-280253
  Date: 30/05/2020
                                        ################ File  Description ################ 
                        This mycompUtilities.c file contain only utilities method for validation process that every command pass through
                        Its intended only as "service provider"*/
#include "complex.h"

commandType cType;                   /*represent type of current comand type: A = "str A,B"     B = "str A,double"      C = "str A,double,double"       D = "str A"*/
char temp_command[MAX_PART_COMMAND]; /*array for only string command without complex params, commas and digits*/
complexP head;                       /*pointer to start of complex vars array - array is in sizeof 6 vars (A-F)*/
complexP tempComplexAddArr[TWO];     /*array that save the address of complex vars that the user enter in the command*/
char digitArr[MAX_CHAR_DIGIT];       /*array that save only the numbers (in chars) the user enter in the command*/
double doubleDigitArr[TWO];          /*array that save only the numbers (in double) the user enter in the command*/

/*          ##### Method Description #####
 initializeComplexP method create array in size of 6 complex vars in the heap ,initialize every complex var attribute (reNum & imNum) to 0
 In the end return the address head of the the array to the main*/
complexP initializeComplexP()
{
    int i;
    complexP head;

    head = (complexP)calloc(SIX, sizeof(item));
    /* verify allocation passed successfully */
    if (!head)
    {
        printf("\nMemory allocation Failed!");
        return NULL;
    }
    for (i = 0; i < SIX; i++)
    {
        (&head[i])->reNum = ZERO; /*set complex var attribute reNum to 0*/
        (&head[i])->imNum = ZERO; /*set complex var attribute reNum to 0*/
    }
    return head;
}
/*          ##### Method Description #####
 initializeArray method initialize all arrays after any command,these arrays store the data we capture during the command*/
void initializeArray(char strcommand[MAX_FULL_LINE_COMMAND])
{
    int i;
    /*set strcommand array cells to NULL*/
    for (i = 0; i < MAX_FULL_LINE_COMMAND; i++)
    {
        strcommand[i] = '\0';
    }
    /*set tempComplexVarArr array cells to NULL*/
    for (i = 0; i < TWO; i++)
    {
        tempComplexAddArr[i] = NULL;
    }
    /*set doubleDigitArr array cells to NULL*/
    for (i = 0; i < TWO; i++)
    {
        doubleDigitArr[i] = '\0';
    }
}
/*          ##### Method Description #####
commandValidation method execute a first validation and sorting to user command, first it capture only the first string in the command (read_comp, print_comp etc) 
validate this string is legal following to definitions, and send every command continue the validation according to command type and params*/
boolean commandValidation(char strcommand[MAX_FULL_LINE_COMMAND])
{
    int i;
    int lowerCaseIndex = INT_MAX /*legal char index*/, ilegalIndex = -1; /*ilegal char index*/
    boolean flag = FALSE;                                                /*var to be returned - return TRUE if validate is pass ; else return FALSE*/

    for (i = 0; i < (int)strlen(strcommand); i++)
    {
        /*if didnt found legal vars at all*/
        if (((lowerCaseIndex == INT_MAX) && (ilegalIndex != NEGATIVE)) || ((i == (strlen(strcommand) - ONE)) && (lowerCaseIndex == INT_MAX) && (ilegalIndex == NEGATIVE)))
        {
            printf("\nUndefined command name\n");
            return FALSE;
        }
        /*if found legal vars and also ilegal vars*/
        else if ((lowerCaseIndex != INT_MAX) && (lowerCaseIndex < ilegalIndex || (ilegalIndex == NEGATIVE)))
        {
            break;
        }
        /*if found legal vars - save his index in lowerCaseIndex*/
        if ((strcommand[i] >= MINLOWERCASE) && (strcommand[i] <= MAXLOWERCASE))
        {
            lowerCaseIndex = i;
        }
        /*if found ilegal vars - save his index in ilegalIndex*/
        else if (((strcommand[i] < MINLOWERCASE) || (strcommand[i] > MAXLOWERCASE)) && (strcommand[i] != '\t') && (strcommand[i] != ' '))
        {
            ilegalIndex = i;
        }
    }
    /*###########################################################################################################################*/

    /*set temp_array cells to NULL - initialize*/
    for (i = 0; i < MAX_PART_COMMAND; i++)
    {
        temp_command[i] = '\0';
    }
    /*after validatin is passed successfully -> save command string (only first part without params, commas and digits) in temp_command array*/
    for (i = 0; i < strlen(strcommand); i++)
    {
        if (strcommand[i + lowerCaseIndex] == '\t' || strcommand[i + lowerCaseIndex] == ' ' || strcommand[i + lowerCaseIndex] == '\n' || strcommand[i + lowerCaseIndex] == ',')
        {
            break;
        }
        else
        {
            temp_command[i] = strcommand[i + lowerCaseIndex];
        }
    }
    /*###########################################################################################################################*/
    /*###########################################################################################################################*/
    /*after temp_command array contain the command string - we send the command continue validate, following to its type*/
    /*READ_COMP*/
    if ((strncmp(temp_command, "read_comp", NINE) == ZERO) && (strlen(temp_command) <= NINE))
    {
        cType = C; /*"read_comp" command is type of C --> its structure is: read_comp complexVar,double,double*/
        flag = sortCommandType(cType, lowerCaseIndex + NINE, strcommand);
        return (flag == FALSE ? FALSE : TRUE);
    }
    /*PRINT_COMP*/
    else if ((strncmp(temp_command, "print_comp", TEN) == ZERO) && (strlen(temp_command) <= TEN))
    {
        cType = D; /*"print_comp" command is type of D --> its structure is: print_comp complexVar*/
        flag = sortCommandType(cType, lowerCaseIndex + TEN, strcommand);
        return (flag == FALSE ? FALSE : TRUE);
    }
    /*ADD_COMP*/
    else if ((strncmp(temp_command, "add_comp", EIGHT) == ZERO) && (strlen(temp_command) <= EIGHT))
    {
        cType = A; /*add_comp" command is type of A --> its structure is: add_comp complexVar double,double*/
        flag = sortCommandType(cType, lowerCaseIndex + EIGHT, strcommand);
        return (flag == FALSE ? FALSE : TRUE);
    }
    /*SUB_COMP*/
    else if ((strncmp(temp_command, "sub_comp", NINE) == ZERO) && (strlen(temp_command) <= NINE))
    {
        cType = A; /*sub_comp" command is type of A --> its structure is: sub_comp complexVar double,double*/
        flag = sortCommandType(cType, lowerCaseIndex + NINE, strcommand);
        return (flag == FALSE ? FALSE : TRUE);
    }
    /*MULT_COMP_REAL*/
    else if ((strncmp(temp_command, "mult_comp_real", FOURTENN) == ZERO) && (strlen(temp_command) <= FOURTENN))
    {
        cType = B; /*mult_comp_real" command is type of B --> its structure is: mult_comp_real complexVar,double*/
        flag = sortCommandType(cType, lowerCaseIndex + FOURTENN, strcommand);
        return (flag == FALSE ? FALSE : TRUE);
    }
    /*MULT_COMP_IMG*/
    else if ((strncmp(temp_command, "mult_comp_img", THIRTEEN) == ZERO) && (strlen(temp_command) <= THIRTEEN))
    {
        cType = B; /*mult_comp_img" command is type of B --> its structure is: mult_comp_img complexVar,double*/
        flag = sortCommandType(cType, lowerCaseIndex + THIRTEEN, strcommand);
        return (flag == FALSE ? FALSE : TRUE);
    }
    /*MULT_COMP_COMP*/
    else if ((strncmp(temp_command, "mult_comp_comp", FOURTENN) == ZERO) && (strlen(temp_command) <= FOURTENN))
    {
        cType = A; /*mult_comp_comp" command is type of A --> its structure is: mult_comp_comp complexVar double,double*/
        flag = sortCommandType(cType, lowerCaseIndex + FOURTENN, strcommand);
        return (flag == FALSE ? FALSE : TRUE);
    }
    /*ABS_COMP*/
    else if ((strncmp(temp_command, "abs_comp", EIGHT) == ZERO) && (strlen(temp_command) <= EIGHT))
    {
        cType = D; /*"abs_comp" command is type of D --> its structure is: abs_comp complexVar*/
        flag = sortCommandType(cType, lowerCaseIndex + NINE, strcommand);
        return (flag == FALSE ? FALSE : TRUE);
    }
    else if ((strncmp(temp_command, "stop", FOUR) == ZERO) && (strlen(temp_command) == FOUR))
    {
        return FALSE;
    }
    else
    {
        printf("\nUndefined command name");
    }
    return FALSE;
}
/*          ##### Method Description #####
 sortCommandType method received command type (A,B,C,D), the last index of temp_command (when the next part of command begin) and char array
 following to command type it send it continue validate as based on the next params(complexVar, commas, digits).
 any var return integer number that represent the index that the next var supposed to validate, if it return -1 --> its mean the validation Failed and the command Wrong*/
boolean sortCommandType(commandType cType, int lastStrIndex, char strcommand[MAX_FULL_LINE_COMMAND])
{
    int r1 = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0, r6 = 0; /*represent the returned index from next validation*/
    if (cType == A)                                     /*A = command complexVar A,B*/
    {
        r1 = complexVarValidation(lastStrIndex, strcommand); /*first find complexVar - and save it in r1*/
        if (isNegative(r1) == TRUE)                          /*if complexVarValidation returned -1 --> Failed and return FALSE*/
        {
            return FALSE;
        }
        r2 = commaValid(r1, strcommand); /*second find comma - and save it in r2*/
        if (isNegative(r2) == TRUE)      /*if commaValid returned -1 --> Failed and return FALSE*/
        {
            return FALSE;
        }
        r3 = complexVarValidation(r2, strcommand); /*third find the second complexVar - and save it in r3*/
        if (isNegative(r3) == TRUE)                /*if complexVarValidation returned -1 --> Failed and return FALSE*/
        {
            return FALSE;
        }
        r4 = endOfCommand(r3, strcommand);      /*in the end verify there is no ilegal chars at the command - and save it in r4*/
        return (r4 == NEGATIVE ? FALSE : TRUE); /*if r4 is NEGATIVE return FALSE ; else return TRUE*/
    }
    else if (cType == B) /*B = command complexVar,double*/
    {
        r1 = complexVarValidation(lastStrIndex, strcommand); /*first find complexVar - and save it in r1*/
        if (isNegative(r1) == TRUE)                          /*if complexVarValidation returned -1 --> Failed and return FALSE*/
        {
            return FALSE;
        }
        r2 = commaValid(r1, strcommand); /*second find comma - and save it in r2*/
        if (isNegative(r2) == TRUE)      /*if commaValid returned -1 --> Failed and return FALSE*/
        {
            return FALSE;
        }
        r3 = isDigit(r2, strcommand); /*third find the number - and save it in r3*/
        /*##########  if the number is < 0 ########*/
        if (r3 >= MAX_FULL_LINE_COMMAND)
        {
            r3 = r3 - MAX_FULL_LINE_COMMAND;
            setMinusDigit();
        }

        else /*if the number is >= 0*/
        {
            setDigit();
        }
        /*########################################*/
        if (isNegative(r3) == TRUE) /*if isDigit returned -1 --> Failed and return FALSE*/
        {
            return FALSE;
        }
        r4 = endOfCommand(r3, strcommand);      /*in the end verify there is no ilegal chars at the command - and save it in r4*/
        return (r4 == NEGATIVE ? FALSE : TRUE); /*if r4 is NEGATIVE return FALSE ; else return TRUE*/
    }
    else if (cType == C) /*C = command complexVar,double,double*/
    {
        r1 = complexVarValidation(lastStrIndex, strcommand); /*first find complexVar - and save it in r1*/
        if (isNegative(r1) == TRUE)                          /*if complexVarValidation returned -1 --> Failed and return FALSE*/
        {
            return FALSE;
        }
        r2 = commaValid(r1, strcommand); /*second find comma - and save it in r2*/
        if (isNegative(r2) == TRUE)      /*if commaValid returned -1 --> Failed and return FALSE*/
        {
            return FALSE;
        }
        r3 = isDigit(r2, strcommand); /*third find the first number - and save it in r3*/
                                      /*##########  if the number is < 0 ########*/
        if (r3 >= MAX_FULL_LINE_COMMAND)
        {
            r3 = r3 - MAX_FULL_LINE_COMMAND;
            setMinusDigit();
        }
        /*if the number is >= 0*/
        else
        {
            setDigit();
        }
        /*########################################*/
        if (isNegative(r3) == TRUE) /*if isDigit returned -1 --> Failed and return FALSE*/
        {
            return FALSE;
        }
        r4 = commaValid(r3, strcommand); /*find comma - and save it in r4*/
        if (isNegative(r4) == TRUE)      /*if commaValid returned -1 --> Failed and return FALSE*/
        {
            return FALSE;
        }
        r5 = isDigit(r4, strcommand); /*find the second number - and save it in r5*/
                                      /*##########  if the number is < 0 ########*/
        if (r5 >= MAX_FULL_LINE_COMMAND)
        {
            r5 = r5 - MAX_FULL_LINE_COMMAND;
            setMinusDigit();
        }
        /*if the number is >= 0*/
        else
        {
            setDigit();
        }
        /*########################################*/
        if (isNegative(r5) == TRUE) /*if isDigit returned -1 --> Failed and return FALSE*/
        {
            return FALSE;
        }
        r6 = endOfCommand(r5, strcommand);      /*in the end verify there is no ilegal chars at the command - and save it in r6*/
        return (r6 == NEGATIVE ? FALSE : TRUE); /*if r6 is NEGATIVE return FALSE ; else return TRUE*/
    }
    else if (cType == D) /*D = command complexVar*/
    {
        r1 = complexVarValidation(lastStrIndex, strcommand); /*first find complexVar - and save it in r1*/
        if (isNegative(r1) == TRUE)                          /*if complexVarValidation returned -1 --> Failed and return FALSE*/
            return FALSE;
        r2 = endOfCommand(r1, strcommand);      /*in the end verify there is no ilegal chars at the command - and save it in r2*/
        return (r2 == NEGATIVE ? FALSE : TRUE); /*if r2 is NEGATIVE return FALSE ; else return TRUE*/
    }
    return FALSE;
}
/*          ##### Method Description #####
 complexVarValidation method Test validation of the command from the end of str_command up to complexVar
 its received the last index from str_command, and strcommand array, and return the index after the complexVar 
 if Validation failed - return -1*/
int complexVarValidation(int lastStrIndex, char strcommand[MAX_FULL_LINE_COMMAND])
{
    int i;
    int indexVar /*index at arr*/, compleaxVarCounter = 0 /*legal complexVar counter*/, illegalcomVarC = 0 /*illegal complexVar counter*/;
    if (lastStrIndex == NEGATIVE) /*if the last validation returned -1*/
    {
        return FALSE;
    }
    for (i = lastStrIndex; i < (strlen(strcommand)); i++)
    {
        if (compleaxVarCounter == ONE) /*if found one legal complexVar*/
        {
            setComplexVar(strcommand[indexVar]); /*match complexVar name(A-F) to his memory allocation in complex array*/
            return indexVar;
        }
        else if ((strcommand[i] == '\t') || (strcommand[i] == ' ')) /*if white chars found*/
        {
            continue;
        }
        else if (((strcommand[i]) >= 'A') && (strcommand[i] <= 'F')) /*if complex var is legal */
        {
            indexVar = i;
            compleaxVarCounter++;
            if ((strcommand[i + ONE]) == '\n') /*if the next char is end of command*/
            {
                setComplexVar(strcommand[indexVar]); /*match complexVar name(A-F) to his memory allocation in complex array*/
                return indexVar;
            }
        }
        /*if illegal char is found*/
        else if ((((strcommand[i]) < 'A') || (strcommand[i] > 'F')) && !((strcommand[i] == '\t') || (strcommand[i] == ' ') || (strcommand[i] == '\n') || (strcommand[i] == ',')))
        {
            illegalcomVarC++;
            break;
        }
    }
    if (illegalcomVarC != ZERO) /*if illegal char is found*/
    {
        printf("\nundefined complex variable");
    }
    else if (compleaxVarCounter == 0) /*if complexVar is not found*/
    {
        printf("\nmissing parameter");
    }
    else
    {
        printf("\nUndefined parameter");
    }
    return NEGATIVE;
}
/*          ##### Method Description #####
commaValid method validate comma between variables. 
its received the last index from the last var(number or complexVar), and strcommand array, and return the index after the comma 
if Validation failed - return -1*/
int commaValid(int indexVar, char strcommand[])
{
    int i, commaCounter = 0, commanIndex = 0, illegalComVar = 0;
    if (indexVar == NEGATIVE) /*if the last validation returned -1*/
    {
        return FALSE;
    }
    for (i = indexVar + ONE; i < (strlen(strcommand)); i++)
    {
        /*if found one comma and the current char is number or complex Var*/
        if ((commaCounter == ONE) && ((isdigit(strcommand[i])) || ((strcommand[i] >= 'A') && (strcommand[i] <= 'F'))))
        {
            return i;
        }
        else if (strcommand[i] == '\t' || strcommand[i] == ' ') /*if found white char*/
        {
            continue;
        }
        else if (strcommand[i] == ',') /*if found comma*/
        {
            commanIndex = i;
            commaCounter++;
        }
        else if (commaCounter > ONE) /*if found more the one commas */
        {
            printf("\nMultuiple consecutive commas");
            break;
        }
    }
    if (commaCounter == ONE && illegalComVar == ZERO) /*if found one comma and non illegal chars*/
    {
        return commanIndex;
    }
    else if (commaCounter == ZERO) /*if comma and illegal char is not found*/
    {
        printf("\nMissing comma");
    }
    return NEGATIVE;
}
/*          ##### Method Description #####
isDigit method validate double numbers. 
its received the last index from the last comma, and strcommand array, and return the index after the number 
if Validation failed - return -1*/
int isDigit(int indexVar, char strcommand[])
{
    int i /*index in strcommand[]*/, j = 0 /*index in digitArr[]*/, dotCounter = 0 /*count dots '.' in string*/;
    if (indexVar == NEGATIVE) /*if the last validation returned -1*/
    {
        return NEGATIVE;
    }
    initDigitArr(); /*initialize double array that store the numbers*/
    for (i = indexVar; i < strlen(strcommand); i++)
    {
        if (strcommand[i] == '.') /*if found dot '.' */
        {
            dotCounter++;
            digitArr[j] = strcommand[i];
            j++;
            continue;
        }
        else if (dotCounter > ONE) /*if found more than one dot*/
        {
            printf("\nMultiple consecutive dots");
            return NEGATIVE;
        }
        /*if found white chars*/
        else if ((strcommand[i] == '\t') || (strcommand[i] == ' ') || (strcommand[i] == ','))
        {
            if (strlen(digitArr) > ZERO) /*if already found digit*/
            {
                if (strcommand[i - (strlen(digitArr) + ONE)] == '-') /*if the number < 0   --> represent by '-' char*/
                {
                    return MAX_FULL_LINE_COMMAND + (i - ONE);
                }
                else
                {
                    return i - ONE;
                }
            }
            else
            {
                printf("\nInvalid parameter - Not a Number");
                return NEGATIVE;
            }
        }
        /*if found legal char (digit or dot)*/
        else if (((strcommand[i] >= '0') && (strcommand[i]) <= '9') || (strcommand[i]) == '.')
        {
            if (dotCounter == ONE) /*if found one dot*/
            {
                digitArr[j] = strcommand[i]; /*save legal char in char digitArr*/
                j++;
                /*if found white char or end of command*/
                if ((strcommand[i + ONE] == '\t') || (strcommand[i + ONE] == ' ') || (strcommand[i + ONE] == '\n'))
                {
                    if (strcommand[i - strlen(digitArr)] == '-') /*if the number < 0   --> represent by '-' char*/
                    {
                        return MAX_FULL_LINE_COMMAND + i;
                    }
                    else
                    {
                        return i;
                    }
                }
                continue;
            }
            digitArr[j] = strcommand[i]; /*save legal char in char digitArr*/
            j++;
            /*if found white char or end of command*/
            if ((strcommand[i + ONE] == '\t') || (strcommand[i + ONE] == ' ') || (strcommand[i + ONE] == '\n'))
            {
                if (strcommand[i - strlen(digitArr)] == '-') /*if the number < 0   --> represent by '-' char*/
                {
                    return MAX_FULL_LINE_COMMAND + i;
                }
                else
                {
                    return i;
                }
            }
        }
        else
        {
            printf("\nInvalid parameter - Not a Number");
            break;
        }
    }
    return NEGATIVE;
}
/*          ##### Method Description #####
 endOfCommand method validate the end of command. 
its received the last index from the last var (numver or complexVar), and strcommand array, and return TRUE if Pass successfully 
if Validation failed - return -1*/
int endOfCommand(int indexVar, char strcommand[])
{
    int i;
    if (indexVar == NEGATIVE) /*if the last validation returned -1*/
    {
        return NEGATIVE;
    }
    for (i = indexVar + ONE; i < strlen(strcommand); i++)
    {
        /*if found white char or end of command*/
        if (strcommand[i] == '\n' || strcommand[i] == '\t' || strcommand[i] == ' ')
        {
            continue;
        }
        else
        {
            printf("\nExtraneous text after end of command");
            return NEGATIVE;
        }
    }
    return TRUE;
}
/*          ##### Method Description #####
 isNegative method verify if the returned number from various validation is NEGATIVE
 if NEGATIVE return TRUE   ;  else return FALSE*/
boolean isNegative(int r)
{
    if (r == NEGATIVE)
        return TRUE;
    return FALSE;
}
/*          ##### Method Description #####
 setComplexVar method received the capture name (that complexVarValidation sent) and match it to its address in complex vars array*/
void setComplexVar(char tempComplexVar)
{
    /*if the first cell in tempComplexAddArr is also set --> its could be only in command with two compleVar - type B*/
    if (tempComplexAddArr[ZERO] != NULL)
    {
        switch (tempComplexVar)
        {
        case 'A':
        {
            tempComplexAddArr[ONE] = (void *)&head[ZERO];
            break;
        }
        case 'B':
        {
            tempComplexAddArr[ONE] = (void *)&head[ONE];
            break;
        }
        case 'C':
        {
            tempComplexAddArr[ONE] = (void *)&head[TWO];
            break;
        }
        case 'D':
        {
            tempComplexAddArr[ONE] = (void *)&head[THREE];
            break;
        }
        case 'E':
        {
            tempComplexAddArr[ONE] = (void *)&head[FOUR];
            break;
        }
        case 'F':
        {
            tempComplexAddArr[ONE] = (void *)&head[FIVE];
            break;
        }
        default:
        {
            printf("\nUndefined Complex Variable");
            break;
        }
        }
    }
    /*if the first cell in tempComplexAddArr is empty*/
    else
    {
        switch (tempComplexVar)
        {
        case 'A':
        {
            tempComplexAddArr[ZERO] = (void *)&head[ZERO];
            break;
        }
        case 'B':
        {
            tempComplexAddArr[ZERO] = (void *)&head[ONE];
            break;
        }
        case 'C':
        {
            tempComplexAddArr[ZERO] = (void *)&head[TWO];
            break;
        }
        case 'D':
        {
            tempComplexAddArr[ZERO] = (void *)&head[THREE];
            break;
        }
        case 'E':
        {
            tempComplexAddArr[ZERO] = (void *)&head[FOUR];
            break;
        }
        case 'F':
        {
            tempComplexAddArr[ZERO] = (void *)&head[FIVE];
            break;
        }
        default:
        {
            printf("\nUndefined Complex Variable");
            break;
        }
        }
    }
}
/*          ##### Method Description #####
 setDigit method converted the char positive digits (from digitArr[]) to double positive digits (to doubleDigitArr[])*/
void setDigit()
{
    char *digitPtr;                   /*pointer to char digitArr[]*/
    if (doubleDigitArr[ZERO] == '\0') /*if first cell is empty*/
    {
        doubleDigitArr[ZERO] = strtod(digitArr, &digitPtr); /*convert chars to double and save in doubleDigitArr[0]*/
    }
    else
    {
        doubleDigitArr[ONE] = strtod(digitArr, &digitPtr); /*convert chars to double and save in doubleDigitArr[1]*/
    }
}
/*          ##### Method Description #####
 setMinusDigit method converted the negative char digits (from digitArr[]) to negative double digits (to doubleDigitArr[])*/
void setMinusDigit()
{
    char *digitPtr;                   /*pointer to char digitArr[]*/
    if (doubleDigitArr[ZERO] == '\0') /*if first cell is empty*/
    {
        doubleDigitArr[ZERO] = (NEGATIVE)*strtod(digitArr, &digitPtr); /*convert chars to double - multiple by -1- and save in doubleDigitArr[0]*/
    }
    else
    {
        doubleDigitArr[ONE] = (NEGATIVE)*strtod(digitArr, &digitPtr); /*convert chars to double - multiple by -1- and save in doubleDigitArr[1]*/
    }
}
/*          ##### Method Description #####
 initDigitArr method initialize char digitArr before enter to isDigit()*/
void initDigitArr()
{
    int i;
    for (i = 0; i < sizeof(digitArr); i++)
    {
        digitArr[i] = '\0';
    }
}
/*          ##### Method Description #####
 printComplexVar method print complexVar name (A-F) accordance to tempComplexAddArr its received from sendParamsToCalc()
 It reffer only to command of type C (read_temp)*/
void printComplexVar(complexP complexVar)
{
    if (complexVar == &head[ZERO])
        printf("\nA = ");
    else if (complexVar == &head[ONE])
        printf("\nB = ");
    else if (complexVar == &head[TWO])
        printf("\nC = ");
    else if (complexVar == &head[THREE])
        printf("\nD = ");
    else if (complexVar == &head[FOUR])
        printf("\nE = ");
    else if (complexVar == &head[FIVE])
        printf("\nF = ");
}