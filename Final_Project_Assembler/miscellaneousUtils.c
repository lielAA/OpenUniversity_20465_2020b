#include "miscellaneousUtils.h"
#include "structuresUtils.h"
#include "methodDec.h"
#include "globalDef.h"
#include "assembler.h"

/*This metod detect if var is one of registers*/
TofR detectRegister(char *varToDetect)
{
    if (strlen(varToDetect) == 0)
        return unRecognized_R;
    else if (!strcmp(varToDetect, "r0"))
        return r0;
    else if (!strcmp(varToDetect, "r1"))
        return r1;
    else if (!strcmp(varToDetect, "r2"))
        return r2;
    else if (!strcmp(varToDetect, "r3"))
        return r3;
    else if (!strcmp(varToDetect, "r4"))
        return r4;
    else if (!strcmp(varToDetect, "r5"))
        return r5;
    else if (!strcmp(varToDetect, "r6"))
        return r6;
    else if (!strcmp(varToDetect, "r7"))
        return r7;
    else
        return unRecognized_R;
}
/*this method detect if var is one of directives - .extern .entry .string .data else return unreconize*/
TofD detectDirective(char *varToDetect)
{
    if (strlen(varToDetect) == 0)
        return unRecognized_LT;
    else if (!strcmp(varToDetect, ".extern"))
        return extD;
    else if (!strcmp(varToDetect, ".entry"))
        return entD;
    else if (!strcmp(varToDetect, ".string"))
        return stringD;
    else if (!strcmp(varToDetect, ".data"))
        return dataD;
    else
        return unRecognized_LT;
}
/*This method detect if var is one of commands names*/
TofC detectCommand(char *commandToDetect)
{
    if (!strcmp(commandToDetect, "mov"))
        return mov;
    else if (!strcmp(commandToDetect, "cmp"))
        return cmp;
    else if (!strcmp(commandToDetect, "add"))
        return add;
    else if (!strcmp(commandToDetect, "sub"))
        return sub;
    else if (!strcmp(commandToDetect, "lea"))
        return lea;
    else if (!strcmp(commandToDetect, "clr"))
        return clr;
    else if (!strcmp(commandToDetect, "not"))
        return not ;
    else if (!strcmp(commandToDetect, "inc"))
        return inc;
    else if (!strcmp(commandToDetect, "dec"))
        return dec;
    else if (!strcmp(commandToDetect, "jmp"))
        return jmp;
    else if (!strcmp(commandToDetect, "bne"))
        return bne;
    else if (!strcmp(commandToDetect, "jsr"))
        return jsr;
    else if (!strcmp(commandToDetect, "red"))
        return red;
    else if (!strcmp(commandToDetect, "prn"))
        return prn;
    else if (!strcmp(commandToDetect, "rts"))
        return rts;
    else if (!strcmp(commandToDetect, "stop"))
        return stop;
    else
        return unRecognized_C;
}
/*This method detect if this line is comment line*/
boolean isCommentLine(char *singleL)
{
    if (!singleL)
        return FALSE;
    if (singleL[0] == ';')
    {
        return TRUE;
    }
    return FALSE;
}
/*This method detect if this line is empty line*/
boolean isEmptyLine(char *singleL)
{
    int i = 0;
    if (singleL == NULL)
        return TRUE;
    do
    {
        i++;
    } while (isspace(singleL[i]));
    if (singleL[i] != '\0' && singleL[i] != '\n')
    {
        return FALSE;
    }
    return TRUE;
}
/*This method detect if error was found*/
boolean isWrongLine(boolean isFirstP)
{
    if (isFirstP)
        return (fail != FALSE); /*IF fail != FALSE  --> a fail was found*/
    return (fail2P != FALSE);
}
/*This method detect if this is a legal label following to roles*/
boolean isLegalLabel(char *varInLIne, boolean colonRequired)
{
    int i = 0;
    char tmpLabel[MAX_ASM_LINE];
    memset(tmpLabel, '\0', MAX_ASM_LINE);
    strncpy(tmpLabel, varInLIne, strlen(varInLIne) - 1);
    tmpLabel[strlen(tmpLabel)] = '\0';
    if (strlen(varInLIne) - 1 > MAX_LABEL) /*if label name is tool long*/
    {
        fail = too_long_label_length;
        return FALSE;
    }
    if (strlen(varInLIne) == 0) /*empty label*/
    {
        return FALSE;
    }
    while (isspace(*varInLIne)) /*skip white letters*/
    {
        varInLIne++;
        i++;
    }
    if (!isalpha(*varInLIne) && (*varInLIne) != '.') /*if its not letter or '.'*/
    {
        fail = label_first_char; /*set fail*/
        return FALSE;
    }
    while (i <= strlen(varInLIne))
    {
        if (isalnum(varInLIne[i])) /*if it number or letter*/
        {
            i++;
            continue;
        }
        if (colonRequired && (varInLIne[i] == ':') && (i == strlen(varInLIne) - 1)) /*if last char in label is ":"*/
        {
            if (detectCommand(tmpLabel) != unRecognized_C) /*if this label compare to command name*/
            {
                fail = label_duplicate_command;
                return FALSE;
            }
            if (detectRegister(tmpLabel) != unRecognized_R) /*if this label compare to register name*/
            {
                fail = label_duplicate_register;
                return FALSE;
            }
            return TRUE;
        }
        if ((!colonRequired) && (varInLIne[i - 1] != ':') && (i == (strlen(varInLIne))))
        {
            return TRUE;
        }
        i++;
    }
    return FALSE;
}
/*This method return true if we reached to the end of line*/
boolean tagEndLine(char *singleLine)
{
    if (singleLine == NULL || *singleLine == '\n' || *singleLine == '\0')
    {
        return TRUE;
    }
    return FALSE;
}
/*this method mark the end of var with '\0'*/
char *markVarEOL(char *varInLine)
{
    char *tmpVar;
    tmpVar = strtok(varInLine, " \t\n");
    tmpVar[strlen(varInLine)] = '\0';
    return tmpVar;
}
/*This method print errors to stderr following to error that found */
void printErrInLine(int lineNum, int failType)
{
    printf("\nError at line %d: ", lineNum);
    switch (failType)
    {
    case err:
        printf("Incorrect first char in line\n");
        break;
    case label_duplicate:
        printf("Duplicate in labeles names\n");
        break;
    case label_duplicate_command:
        printf("Duplicate names between label and command\n");
        break;
    case label_duplicate_register:
        printf("Duplicate names between label and register\n");
        break;
    case missing_command:
        printf("Missing command\n");
        break;
    case not_belong_char_to_command:
        printf("Ilegal chars for command syntax\n");
        break;
    case unmatch_command_num_of_var:
        printf("Too many operands for command\n");
        break;
    case missing_num_in_data:
        printf("data not contain number\n");
        break;
    case multiple_commas_in_data:
        printf(".data contain multiple commas after number\n");
        break;
    case unrecognized_comma_in_data:
        printf(".data contain unnecessary comma\n");
        break;
    case unrecognized_command:
        printf("Unrecognized command\n");
        break;
    case label_first_char:
        printf("Ilegal first char in label\n");
        break;
    case label_alpha:
        printf("Label contain non-alphanumeric chars\n");
        break;
    case unmatching_num_of_param_for_instruction:
        printf("Ilegal number of vars for instruction\n");
        break;
    case missing_params_for_instruction:
        printf("Ilegal number OR type of vars for command type\n");
        break;
    case too_many_vars_for_string:
        printf("Too many vars for .string\n");
        break;
    case unrecognized_var_for_string:
        printf("Unrecognized var for .string\n");
        break;
    case missing_label_for_extern:
        printf("Missing label for .extern\n");
        break;
    case unrecognized_label_for_extern:
        printf("Unrecognized label for .extern\n");
        break;
    case unrecognized_label_for_entry:
        printf("Unrecognized label for .entry\n");
        break;
    case unmatching_var_for_extern:
        printf("Ilegal number of vars for .extern\n");
        break;
    case entery_defined_as_extern:
        printf(".entry received label that defined as .extern\n");
        break;
    case missing_vars_after_label:
        printf("Misssing vars after label\n");
        break;
    case missing_apostrophes_at_end_of_string:
        printf("Misssing apostrophes at the end of string\n");
        break;
    case missing_apostrophes_at_start_of_string:
        printf("Misssing apostrophes at the start of string\n");
        break;
    case unrecognized_var_for_data:
        printf("Unrecognized var for .data\n");
        break;
    case unrecognized_Method_for_command:
        printf("unrecognized address for var in command\n");
        break;
    case unmatch_method_for_commad:
        printf("unmatch method for command type\n");
        break;
    case too_long_label_length:
        printf("label name is too long\n");
        break;
    case missing_comma_in_data:
        printf("missing comma after number in .data\n");
        break;
    case missing_entry_label:
        printf("missing label for .entry\n");
        break;
    case missing_string:
        printf("missing string for .string\n");
        break;
    case ilegal_number_in_data:
        printf("ilegal number for .data\n");
        break;
    case data_size_out_of_range:
        printf("DATA OVERFLOW - data size is out of range - legal data size should be between -8388608 to 8388607\n");
        break;
    case imediate_data_size_out_of_range:
        printf("IMEDIATE DATA OVERFLOW - imediate data size is out of range - legal data size should be between -1048576 to 1048575\n");
        break;
    case extern_defined_as_local:
        printf(".extern received label that defined as local\n");
        break;
    }
}
/*This method recognize type of directive*/
TofD recognizeDirective(char *varInLine)
{
    char tmpVar[MAX_ASM_LINE];
    int i = 0;
    TofD directiveType = unRecognized_LT;
    if (varInLine == NULL)
    {
        return unRecognized_LT;
    }
    while (isspace(*varInLine))
    {
        varInLine++;
    }
    if (*varInLine != '.') /*if NUll or first char is not '.'*/
        return unRecognized_LT;
    while (isspace(*varInLine)) /*skip whitespace*/
    {
        varInLine++;
    }
    while (!isspace(*varInLine)) /*save command to detect it*/
    {
        tmpVar[i] = *varInLine;
        varInLine++;
        i++;
    }
    tmpVar[i] = '\0';
    directiveType = detectDirective(tmpVar);
    return directiveType;
}
/*This method detect command */
TofC recognizeCommand(char *varInLine)
{
    char tmpVar[MAX_ASM_LINE];
    int i = 0;
    TofC commandType = unRecognized_C;
    if (varInLine == NULL)
        return unRecognized_C;
    while (isspace(*varInLine)) /*skip whitespace*/
    {
        varInLine++;
    }
    while (!isspace(*varInLine)) /*save command to detect it*/
    {
        tmpVar[i] = *varInLine;
        varInLine++;
        i++;
    }
    tmpVar[i] = '\0';
    commandType = detectCommand(tmpVar); /*detect command that was found*/
    return commandType;
}
/*This method verify if string is legal for .string roles*/
boolean isLegalString(char *strToAnalyze)
{
    int i = 0;
    if (!strToAnalyze) /*empty string*/
    {
        fail = unrecognized_var_for_string;
        return FALSE;
    }
    if (strToAnalyze[0] != '"') /*first char must to be '"'*/
    {
        fail = missing_apostrophes_at_start_of_string;
        return FALSE;
    }
    i++;
    while (i < strlen(strToAnalyze) && strToAnalyze[i] != '"') /*skip letters till we found '"'*/
    {
        i++;
    }

    if (strToAnalyze[i] != '"') /*if we ddint found '"'*/
    {
        fail = missing_apostrophes_at_end_of_string;
        return FALSE;
    }
    return TRUE;
}
/*This method skip ',' and return next var*/
char *varInLineM(char *dest, char *line)
{
    char *temp = dest;
    if (tagEndLine(line))
    {
        dest[0] = '\0';
        return NULL;
    }
    while (isspace(*line))
    {
        line++;
    }
    if (*line == ',') /*if we found ','*/
    {
        strcpy(dest, ",");
        return ++line;
    }
    while (!tagEndLine(line) && *line != ',' && !isspace(*line))
    {
        *temp = *line;
        temp++;
        line++;
    }
    *temp = '\0';
    return line;
}
/*This method verify if var is legal number to .data or for imediate numbers*/
boolean isLegalNumInData(char *numToVerify)
{
    int i = 0;
    if (tagEndLine(numToVerify))
    {
        return FALSE;
    }
    if (numToVerify[i] == '-' || numToVerify[i] == '+') /*if we found + or - before number*/
    {
        i++;
        if (!isdigit(numToVerify[i])) /*if it not digit*/
        {
            return FALSE;
        }
    }
    while (numToVerify[i] != '\0' && numToVerify[i] != '\n' && numToVerify != NULL)
    {
        if (!isdigit(numToVerify[i]))
        {
            return FALSE;
        }
        i++;
    }
    return TRUE;
}
/*This method convert type of commands to it string command and retuen it*/
char *convertCommandToString(TofC toConvert)
{
    switch (toConvert)
    {
    case mov:
        return "mov";
    case cmp:
        return "cmp";
    case add:
        return "add";
    case sub:
        return "sub";
    case lea:
        return "lea";
    case clr:
        return "clr";
    case not:
        return "not";
    case inc:
        return "inc";
    case dec:
        return "dec";
    case jmp:
        return "jmp";
    case bne:
        return "bne";
    case jsr:
        return "jsr";
    case red:
        return "red";
    case prn:
        return "prn";
    case rts:
        return "rts";
    case stop:
        return "stop";
    default:
        return "unRecognized_C";
    }
}
/*This method convert type of directive to its directive name and retuen it*/
char *convertDircetiveToString(TofD toConvert)
{
    switch (toConvert)
    {
    case extD:
        return ".extern";
    case entD:
        return ".entry";
    case stringD:
        return ".string";
    case dataD:
        return ".data";
    default:
        return "unRecognized_LT";
    }
}
/*This method detect method type and return it*/
typeOFMethod detectMeth(char *VarToDetect)
{
    int intNumToVerify = 0;
    if (tagEndLine(VarToDetect))
    {
        return unknownM;
    }
    if (detectRegister(VarToDetect) != unRecognized_R) /*check if it register method*/
    {
        return registerM;
    }
    else if (VarToDetect[0] == '#') /*check if it immediate method*/
    {
        VarToDetect++;
        if (isLegalNumInData(VarToDetect)) /*verify for legal NUmber*/
        {
            intNumToVerify = atoi(VarToDetect);
            if (intNumToVerify < MIN_IMEDIATE_DATA_SIZE || intNumToVerify > MAX_IMEDIATE_DATA_SIZE) /*limit size of imediate numbers*/
            {
                fail = imediate_data_size_out_of_range;
                return FALSE;
            }
            return imediateM;
        }
    }
    else if (VarToDetect[0] == '&') /*check if it relative method*/
    {
        VarToDetect++;
        if (isLegalLabel(VarToDetect, FALSE)) /*verify for legal label*/
        {
            return relativeM;
        }
    }
    else if (isLegalLabel(VarToDetect, FALSE)) /*check if it direct method*/
    {
        return directM;
    }
    fail = unrecognized_Method_for_command;
    return unknownM;
}
/*This method verify if the number of var for commands is legal*/
boolean legalVarForCommand(boolean firstVar, boolean secondVar, TofC comType)
{
    switch (comType)
    {
    /*instruction required 2 vars*/
    case stop:
    case rts:
        return !secondVar && !firstVar;
    /*instruction required 1 vars*/
    case clr:
    case not:
    case inc:
    case dec:
    case jmp:
    case bne:
    case jsr:
    case red:
    case prn:
        /*instruction required 0 vars*/
        return !secondVar && firstVar;
    case mov:
    case cmp:
    case add:
    case sub:
    case lea:
        return secondVar && firstVar;
    case unRecognized_C:
        return FALSE;
    }
    return FALSE;
}
/*This method verify if var methods are legal for this command*/
boolean legalMetForCommand(typeOFMethod firstVar, typeOFMethod secondVar, TofC comType)
{
    switch (comType)
    {
    case stop:
    case prn:
    case rts:
    case cmp:
        return TRUE;
    case lea:
        return (firstVar == directM) && (secondVar == directM || secondVar == registerM);
    case add:
    case sub:
    case mov:
        return (firstVar == imediateM || firstVar == registerM || firstVar == directM) &&
               (secondVar == registerM || secondVar == directM);
    case clr:
    case not:
    case inc:
    case dec:
    case red:
        return (firstVar == registerM) || (firstVar == directM);
    case jmp:
    case bne:
    case jsr:
        return (firstVar == directM) || (firstVar == relativeM);
    case unRecognized_C:
        return FALSE;
    }
    return FALSE;
}
/*This method skip to rest of string in line*/
char *skipToRestOfString(char *command, char *fullLine)
{
    while (isspace(*fullLine))
    {
        fullLine++;
    }
    while (*fullLine == *command)
    {
        fullLine++;
        command++;
    }
    return fullLine;
}
/*This method skip to next var in line*/
char *skipToNextVar(char *singleLine)
{
    if (singleLine == NULL)
    {
        return NULL;
    }
    while (!tagEndLine(singleLine) && !isspace(*singleLine))
    {
        singleLine++;
    }
    if (!tagEndLine(singleLine))
    {
        return singleLine;
    }
    return NULL;
}
/*this method set ARE word*/
void defineARE(typeOfARE areType, wordP firstW)
{
    firstW->ARE = areType;
}
/*This method create full first word*/
void createFullDecWord(wordP word)
{
    CreateFullBinWord(word->opcode, opcodeSize, FALSE);       /*create opcode*/
    CreateFullBinWord(word->sourceMethod, methodSize, FALSE); /*create source meth*/
    CreateFullBinWord(word->sourceR, AREregisterSize, FALSE); /*create source register*/
    CreateFullBinWord(word->targetMethod, methodSize, FALSE); /*create target meth*/
    CreateFullBinWord(word->targetR, AREregisterSize, FALSE); /*create target register*/
    CreateFullBinWord(word->funct, functSize, FALSE);         /*create funct*/
    CreateFullBinWord(word->ARE, AREregisterSize, FALSE);     /*create ARE*/

    insertWordToMemory(); /*insert created word to memory*/
    free(word);
}
/*This method convert decimal to binary based on size operands*/
void CreateFullBinWord(unsigned int numToConvert, size bitSize, boolean isData)
{
    int i = 0;
    unsigned int mask = (1 << ((bitSize)-1));
    while (mask) /*mask!=0*/
    {
        if (numToConvert & mask)
        {
            if (isData) /*if it supposed to be store in data area*/
                structDataArea[DC][i++] = 1;
            else
                wordArr[wordArrIndex++] = 1;
        }
        else
        {
            if (isData) /*if it supposed to be store in data area*/
                structDataArea[DC][i++] = 0;
            else
                wordArr[wordArrIndex++] = 0;
        }
        mask >>= 1;
    }
}
/*This method insert created bin word to memory*/
void insertWordToMemory()
{
    wordArrIndex = 0;
    while (wordArrIndex < WORD_SIZE)
    {
        structMemoryArea[IC][wordArrIndex] = wordArr[wordArrIndex];
        wordArrIndex++;
    }
    wordArrIndex = 0;
    IC++;
    L++;
}
/*This method insert label address to memory in the relevant locations*/
void insertLabelAddressToMeM(ptrLabel label, unsigned int dist, int index, typeOfARE AREsize)
{
    CreateFullBinWord((label->labelAddress - dist), WORD_WITHOUT_ARE, FALSE); /*create 21 bits number*/
    CreateFullBinWord(AREsize, AREregisterSize, FALSE);         /*create ARE*/
    wordArrIndex = 0;
    while (wordArrIndex < WORD_SIZE) /*insert eord to memory*/
    {
        structMemoryArea[index][wordArrIndex] = wordArr[wordArrIndex];
        wordArrIndex++;
    }
    wordArrIndex = 0;
    tmpIC++;
}
