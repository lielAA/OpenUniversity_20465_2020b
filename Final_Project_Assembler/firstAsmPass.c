#include "miscellaneousUtils.h"
#include "methodDec.h"
#include "globalDef.h"

/*pass all file lines -  first pass algorithem*/
void firstAsmPass(FILE *asmFD)
{
    char singleLine[MAX_ASM_LINE];
    int lineNum = 1;
    DC = 0;
    IC = 0;
    tmpIC = 0;
    while (fgets(singleLine, MAX_ASM_LINE, asmFD))
    {
        fail = FALSE;
        isFlagLabel = FALSE;
        if (!(isCommentLine(singleLine)) && !(isEmptyLine(singleLine))) /*skip comments and empty lines*/
        {
            analyzeSingleLine(singleLine); /*analyze line*/
        }
        if (isWrongLine(TRUE)) /*if error was found*/
        {
            flagFailed = TRUE;
            printErrInLine(lineNum, fail);
        }
        lineNum++;
    }
    defineFinalAddress(FALSE, &tableOfSym, MEM_BEGIN_ADDRESS);     /*define address for labels memory area*/
    defineFinalAddress(TRUE, &tableOfSym, IC + MEM_BEGIN_ADDRESS); /*define address for data labels area */
}
/*this method analyze single line following to roles*/
void analyzeSingleLine(char *singleLine)
{
    char *varInLine;
    char varInLineForData[MAX_ASM_LINE];
    char *tmpVar;
    ptrLabel nodeLabelInList = NULL;
    TofC commandType = unRecognized_C;    /*defined command type*/
    TofD directiveType = unRecognized_LT; /*defined directivve type*/

    /*validate first char in line*/
    strcpy(varInLineForData, singleLine);
    varInLine = strtok(singleLine, " \t\n");
    if (!isalpha(varInLine[0]) && varInLine[0] != '.') /*first char is not letter or '.'*/
    {
        fail = err;
        return;
    }
    if (isLegalLabel(varInLine, TRUE)) /*search for label with colon*/
    {
        varInLine[strlen(varInLine) - 1] = '\0'; /*insert label to table without ':'*/
        isFlagLabel = TRUE;
        nodeLabelInList = insertLabel(varInLine, &tableOfSym, 0, FALSE); /*insert label to table*/
        if (nodeLabelInList == NULL)                                     /*duplicate between labeles*/
        {
            return;
        }
        varInLine = skipToNextVar(varInLineForData);
        if (tagEndLine(varInLine)) /*end of line mean the line contain only label - ilegal syntax*/
        {
            fail = missing_vars_after_label;
            return;
        }
    }
    if (isWrongLine(TRUE)) /*if error was found*/
    {
        return;
    }
    directiveType = recognizeDirective(varInLine); /*if this var is directive*/
    /*@@@@@@@@@@@@@@@@@*/
    commandType = recognizeCommand(varInLine); /*if this var is command*/
    /*################################################################################*/
    if (directiveType == unRecognized_LT && commandType == unRecognized_C)
    {
        fail = unrecognized_command;
        return;
    }
    /*################################################################################*/
    else if (directiveType != unRecognized_LT) /*recognize if it is a directive type*/
    {

        if (isFlagLabel) /*if it is a directive and we found before it a label*/
        {
            if (directiveType == entD || directiveType == extD) /*if this directive is of .entry or .extern type --> ilegal syntax*/
            {
                removeLabelFromList(nodeLabelInList->labelName, &tableOfSym);
            }
            else /*directive is a .string or .data*/
            {
                nodeLabelInList->labelAddress = DC; /*his address its the DC counter*/
                nodeLabelInList->typeOfLabel = directive;
            }
        }
        tmpVar = convertDircetiveToString(directiveType); /*convert command to string*/
        if (!isFlagLabel)
        {
            varInLine = skipToRestOfString(tmpVar, varInLineForData); /*skip to next var*/
        }
        else
        {
            varInLine = skipToRestOfString(tmpVar, varInLine);
        }
        analyzeDirectiveOperands(varInLine, directiveType); /*analyze var for directive*/
    }
    /*################################################################################*/
    else if (commandType != unRecognized_C)
    {
        if (isFlagLabel) /*if it is a command and we found before it a label*/
        {
            nodeLabelInList->labelAddress = IC; /*his address its the IC counter*/
            nodeLabelInList->typeOfLabel = instruction;
        }
        tmpVar = convertCommandToString(commandType); /*convert command to string*/
        varInLine = skipToRestOfString(tmpVar, varInLine);
        analyzeCommandOperands(varInLine, commandType); /*analyze var for command*/
    }
}

/*this method analyze instruction operands following to its type*/
TofC analyzeCommandOperands(char *varInLine, TofC commandType)
{
    char AVar[MAX_ASM_LINE], BVar[MAX_ASM_LINE];
    typeOFMethod AWord, BWord;
    boolean firstVar = FALSE, secondVar = FALSE;
    wordP word = NULL;
    while (isspace(*varInLine))
    {
        varInLine++;
    }
    varInLine = varInLineM(AVar, varInLine);
    if (!tagEndLine(AVar)) /*not end of line*/
    {
        firstVar = TRUE;
        varInLine = varInLineM(BVar, varInLine); /*find second var*/
        if (!tagEndLine(BVar))
        {
            if (BVar[0] != ',') /*missing ','*/
            {
                fail = not_belong_char_to_command;
                return unRecognized_C;
            }
            else /*',' is found - looking for the next var*/
            {
                varInLine = varInLineM(BVar, varInLine);
                if (tagEndLine(BVar)) /*next var must to be found because we found ','*/
                {
                    fail = missing_params_for_instruction;
                    return unRecognized_C;
                }
                else
                {
                    secondVar = TRUE;
                }
            }
        }
    }
    if (!tagEndLine(varInLine)) /*not end line*/
    {
        while (isspace(*varInLine)) /*skip white space*/
        {
            varInLine++;
        }
    }
    if (!tagEndLine(varInLine))
    {
        fail = unmatching_num_of_param_for_instruction;
        return unRecognized_C;
    }
    if (firstVar)
    {
        AWord = detectMeth(AVar); /*find method for first var*/
    }
    if (secondVar)
    {
        BWord = detectMeth(BVar); /*find method for second var*/
    }
    if (!isWrongLine(TRUE)) /*failed not found*/
    {
        if (legalVarForCommand(firstVar, secondVar, commandType)) /*check for correct num of var*/
        {
            if (legalMetForCommand(AWord, BWord, commandType)) /*check for correct method for this command*/
            {
                word = createFirstWord(firstVar, secondVar, AWord, BWord, AVar, BVar, commandType); /*create first bin word*/
                createFullDecWord(word);
                IC += saveFreeSpaceForMoreWords(firstVar, secondVar, AWord, BWord, AVar, BVar); /*save free space in array for addition word*/
            }
            else
            {
                fail = unmatch_method_for_commad;
                return unRecognized_C;
            }
        }
        else
        {
            fail = missing_params_for_instruction;
            return unRecognized_C;
        }
    }
    return TRUE;
}
/*analyze directive operands following to its type*/
TofD analyzeDirectiveOperands(char *varInLine, TofD directiveType)
{
    switch (directiveType)
    {
    /*analyze vars for .extern line*/
    case extD:
        return analyzeExternD(varInLine); /*analyze extern*/
    case entD:
        return analyzeEntryD(varInLine); /*analyze entry*/
    case stringD:
        return analyzeStringD(varInLine); /*analyze string*/
    case dataD:
        return analyzeDataD(varInLine); /*analyze data*/
    default:
        return unRecognized_LT;
    }
}
/*analyze vars for .extern line*/
int analyzeExternD(char *singleLine)
{
    ptrLabel label;
    char *expectedLabel;
    char *nextVar, *tmpNextVar;
    nextVar = expectedLabel = singleLine;
    if (tagEndLine(expectedLabel)) /*if it is end of line - it mean there is no label for .extern*/
    {
        fail = missing_label_for_extern;
        return FALSE;
    }
    while (isspace(*expectedLabel))
    {
        expectedLabel++;
    }
    /*search for label without colon*/
    if (!(isLegalLabel(expectedLabel, FALSE)))
    {
        fail = unrecognized_label_for_extern;
        return FALSE;
    }
    tmpNextVar = expectedLabel;
    tmpNextVar[strlen(tmpNextVar) - 1] = '\0'; /*cut end char of var*/
    label = getLabelByName(tmpNextVar);        /*check if label exist in table*/
    if (label && !label->entLabel)             /*if label already exist*/
    {
        fail = extern_defined_as_local;
        return FALSE;
    }
    nextVar = skipToNextVar(expectedLabel);
    if (!tagEndLine(nextVar)) /*if its not the end of line it mean there is more vars - ilegal for .extern role*/
    {
        fail = unmatching_var_for_extern;
        return FALSE;
    }
    if (insertLabel(expectedLabel, &tableOfSym, FALSE, TRUE) == NULL) /*insert label to table*/
    {
        return FALSE;
    }
    return !isWrongLine(TRUE);
}
/*analyze vars for .entry line*/
int analyzeEntryD(char *singleLine)
{
    if (tagEndLine(singleLine)) /*end of line*/
    {
        fail = missing_entry_label;
        return FALSE;
    }
    while (isspace(*singleLine)) /*skip white letters*/
    {
        singleLine++;
    }
    singleLine = skipToNextVar(singleLine); /*search for next var*/
    if (!tagEndLine(singleLine) && !isspace(*singleLine))
    {
        fail = unmatching_num_of_param_for_instruction;
        return FALSE;
    }
    return TRUE;
}
/*analyze vars for .string line*/
int analyzeStringD(char *expectedStr)
{
    char *nextVar = expectedStr;
    int apostrophesCnt = 0;

    expectedStr[strlen(expectedStr)] = '\0'; /*current string*/
    nextVar[strlen(nextVar)] = '\0';         /*next var*/
    if (tagEndLine(expectedStr))             /*end of line*/
    {
        fail = missing_string;
        return FALSE;
    }
    while (isspace(*expectedStr)) /*skip white letters*/
    {
        expectedStr++;
    }
    if (!isLegalString(expectedStr)) /*verify foe legal syntax string*/
    {
        return FALSE;
    }
    while (apostrophesCnt < TWO) /*search for 2 apostrophes*/
    {
        if (*nextVar == '"')
            apostrophesCnt++;
        nextVar++;
    }
    if (!tagEndLine(nextVar)) /*there is more than one var for .string*/
    {
        fail = too_many_vars_for_string;
        return FALSE;
    }
    else /*this is the only legal string var */
    {
        saveString(expectedStr);
    }
    return TRUE;
}
/*store the string var in data */
void saveString(char *expectedStr)
{
    int i = 1;
    if (tagEndLine(expectedStr)) /*if end of line*/
    {
        fail = too_many_vars_for_string;
        return;
    }
    while (i < strlen(expectedStr) - 2) /*insert string to structDataArea without "__" */
    {
        DataArr[dataArrIndex] = (unsigned int)expectedStr[i];
        CreateFullBinWord(DataArr[dataArrIndex], sizeof(int) * HEX_WORD_SIZE, TRUE); /*create binary word from string*/
        i++;
        dataArrIndex++;
        DC++;
    }
    DataArr[dataArrIndex++] = '\0'; /*mark end of current string by '\n'*/
    DC++;
}
/*This method analyze .data line*/
int analyzeDataD(char *expectedNum)
{
    boolean numF = FALSE;
    char num[MAX_ASM_LINE];
    boolean commaF = FALSE;
    int numToVerify = 0;

    if (tagEndLine(expectedNum)) /*end of line*/
    {
        fail = missing_num_in_data;
        return unRecognized_LT;
    }
    while (isspace(*expectedNum)) /*skip white letters*/
    {
        expectedNum++;
    }
    while (!tagEndLine(expectedNum))
    {
        expectedNum = varInLineM(num, expectedNum);
        if (strlen(num) > 0) /*var is not empty*/
        {
            if (!numF) /*if number not found*/
            {
                if (!isLegalNumInData(num)) /*ilegal numeric char*/
                {
                    if (*num == ',') /*multiple commas after number*/
                    {
                        fail = multiple_commas_in_data;
                        return FALSE;
                    }
                    fail = ilegal_number_in_data;
                    return FALSE;
                }
                commaF = FALSE;
                numF = TRUE;
                numToVerify = atoi(num);                                          /*convert number to integer*/
                if (numToVerify >= MIN_DATA_SIZE && numToVerify <= MAX_DATA_SIZE) /*limitted size of data by max & min 21 bits */
                {
                    DataArr[dataArrIndex] = (unsigned int)atoi(num);                          /*insert number to data area*/
                    CreateFullBinWord(DataArr[dataArrIndex], sizeof(unsigned int) * HEX_WORD_SIZE, TRUE); /*create binary word*/
                    dataArrIndex++;
                    DC++;
                }
                else
                {
                    fail = data_size_out_of_range;
                    return FALSE;
                }
            }
            else if (*num != ',') /*if number is found && next var is not comma*/
            {
                fail = missing_comma_in_data;
                return FALSE;
            }
            else
            {
                if (commaF) /*if comman found */
                {
                    fail = multiple_commas_in_data;
                    return FALSE;
                }
                numF = FALSE;
                commaF = TRUE;
            }
        }
    }
    if (commaF) /*end of line and we found comma*/
    {
        fail = unrecognized_comma_in_data;
        return FALSE;
    }
    return TRUE;
}
/*This mehtod create first word for relevant lines*/
wordP createFirstWord(boolean firstVar, boolean secondVar, typeOFMethod Aword, typeOFMethod Bword, char *AVar, char *BVar, TofC commandType)
{
    wordP firstW = NULL;
    firstW = (wordP)malloc(sizeof(wordS)); /*allocate memory*/

    if (!firstW) /*failed to allocate memory*/
    {
        printf("\n memory allocation failed - fatal error\n");
        exit(0);
    }
    defineARE(ABS, firstW); /*insert ARE - all first words contains absolute ARE*/
    if (commandType == mov || commandType == cmp || commandType == lea || commandType == red || commandType == prn || commandType == rts || commandType == stop)
    {
        firstW->opcode = commandType; /*insert opcode to word*/
        firstW->funct = funct0;
    }
    else
    {
        if (commandType == add || commandType == sub) /*insert opcode and funct to add & sub commands*/
        {
            firstW->opcode = opcode2;
            switch (commandType)
            {
            case add:
                firstW->funct = funct1;
                break;
            case sub:
                firstW->funct = funct2;
                break;
            default:
                break;
            }
        }
        else if (commandType == clr || commandType == not || commandType == inc || commandType == dec) /*insert opcode and funct to clr & not & int & dec commands*/
        {
            firstW->opcode = opcode5;
            switch (commandType)
            {
            case clr:
                firstW->funct = funct1;
                break;
            case not:
                firstW->funct = funct2;
                break;
            case inc:
                firstW->funct = funct3;
                break;
            case dec:
                firstW->funct = funct4;
                break;
            default:
                break;
            }
        }
        else if (commandType == jmp || commandType == bne || commandType == jsr) /*insert opcode and funct to jmp & bne & jsr commands*/
        {
            firstW->opcode = opcode9;
            switch (commandType)
            {
            case jmp:
                firstW->funct = funct1;
                break;
            case bne:
                firstW->funct = funct2;
                break;
            case jsr:
                firstW->funct = funct3;
                break;
            default:
                break;
            }
        }
    }
    /*if there are two var after instruction*/
    if (firstVar && secondVar)
    {
        firstW->sourceMethod = Aword;
        firstW->targetMethod = Bword;
        if (detectRegister(AVar))                       /*if first var is register*/
            firstW->sourceR = detectRegister(AVar) - 1; /*set as register source*/
        if (detectRegister(BVar))                       /*if second var is register*/
            firstW->targetR = detectRegister(BVar) - 1; /*set as register target*/
    }
    if (firstVar && !secondVar) /*if there is only one var after instruction*/
    {
        firstW->targetMethod = Aword;
        firstW->sourceMethod = imediateM;
        if (detectRegister(AVar)) /*if var is register*/
        {
            firstW->targetR = detectRegister(AVar) - 1; /*set register as source*/
            firstW->sourceR = unRecognized_R;
        }
    }
    if (!firstVar && !secondVar) /*if there are not var after instruction - stop command*/
    {
        firstW->targetMethod = imediateM;
        firstW->sourceMethod = imediateM;
        firstW->targetR = unRecognized_R;
        firstW->sourceR = unRecognized_R;
    }
    return firstW;
}
/*This method save free space in memory for more word that will be calculate in the next pass*/
int saveFreeSpaceForMoreWords(boolean firstVar, boolean secondVar, typeOFMethod AWord, typeOFMethod BWord, char *AVar, char *BVar)
{
    int cnt = 0;
    int i = 0;
    boolean secondIsImediate = FALSE;
    unsigned int numToConvertA = 0;
    unsigned int numToConvertB = 0;

    AVar++;
    BVar++;
    numToConvertA = atoi(AVar);
    numToConvertB = atoi(BVar);
    if (firstVar) /*if first var is found*/
    {
        if (AWord == imediateM) /*if it imediate*/
        {
            CreateFullBinWord(numToConvertA, 21, FALSE);    /*create word for 21 bits*/
            CreateFullBinWord(ABS, AREregisterSize, FALSE); /*create ARE bits*/
            insertWordToMemory();                           /*insert created word to memory*/
        }
        else if (AWord != registerM && AWord != unknownM) /*not registerand  not imediate*/
        {
            cnt++;
            L++;
            wordToEncodeSeconePass[tmpIC] = IC;
            i++;
            tmpIC++;
            if (secondVar && BWord == imediateM) /*if there is second var and it imediate*/
            {
                secondIsImediate = TRUE;
                cnt++;
            }
        }
    }
    if (secondVar) /*if second vari is found*/
    {
        if (BWord == imediateM) /*if it imediate*/
        {
            CreateFullBinWord(numToConvertB, WORD_WITHOUT_ARE, FALSE);    /*create word for 21 bits*/
            CreateFullBinWord(ABS, AREregisterSize, FALSE); /*create ARE bits*/
            IC++;
            insertWordToMemory(); /*insert created word to memory*/
            IC--;
            cnt--;
        }
        if (BWord != registerM && BWord != unknownM && !secondIsImediate) /*not register and not imediate*/
        {
            IC++;
            if (firstVar && secondVar && AWord == directM && BWord == directM) /*if both of vars are labels*/
            {
                wordToEncodeSeconePass[tmpIC] = IC;
            }
            else
                wordToEncodeSeconePass[tmpIC] = IC - 1;
            IC--;
            i++;
            tmpIC++;
            cnt++;
            L++;
        }
    }
    return cnt;
}