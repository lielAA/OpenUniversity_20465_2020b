#include "miscellaneousUtils.h"
#include "methodDec.h"
#include "globalDef.h"
/*pass all file lines -  second pass algorithem*/
void secondAsmPass(FILE *asmFD, char *asmfileName)
{
    char singleLine[MAX_ASM_LINE];
    int lineNum = 1;
    flagFailed = FALSE;
    IC = 0;
    tmpIC = 0;

    while (fgets(singleLine, MAX_ASM_LINE, asmFD))
    {
        fail2P = FALSE;
        if (!(isCommentLine(singleLine)) && !(isEmptyLine(singleLine))) /*skip comments and empty lines*/
        {
            analyzeSingleLineSecPass(singleLine); /*analyze line*/
        }
        if (isWrongLine(FALSE)) /*if error was found*/
        {
            flagFailed = TRUE;
            printErrInLine(lineNum, fail2P);
        }
        lineNum++;
    }
}
/*this method analyze single line following to roles*/
void analyzeSingleLineSecPass(char *singleLine)
{
    char varInLineTmp[MAX_ASM_LINE];
    char *varInLine, *tmpVar;
    TofC commandType = unRecognized_C;    /*defined command type*/
    TofD directiveType = unRecognized_LT; /*defined directivve type*/

    strcpy(varInLineTmp, singleLine);
    varInLine = strtok(singleLine, " \t\n"); /*detect first var in line*/

    if (isLegalLabel(varInLine, TRUE)) /*skip label*/
    {
        varInLine = skipToNextVar(varInLineTmp);
        while (isspace(*varInLine))
            varInLine++;
    }
    else if (strcmp(varInLine, ".extern") == 0 || strcmp(varInLine, ".data") == 0 || strcmp(varInLine, ".string") == 0) /*skip .extern .data and .string lines*/
    {

        return; /*skip next line*/
    }

    directiveType = recognizeDirective(varInLine); /*if this var is directive*/
    commandType = recognizeCommand(varInLine);     /*if this var is command*/
    if (directiveType != unRecognized_LT && directiveType == entD)
    {
        tmpVar = varInLine;
        if (strcmp(varInLine, ".entry") == 0) /*if it .entry line*/
        {
            while (isspace(*varInLine))
                varInLine++;
            varInLine = skipToRestOfString(tmpVar, varInLineTmp);
            while (isspace(*varInLine))
                varInLine++;
        }
        else
        {
            varInLine = skipToNextVar(varInLine);
            while (isspace(*varInLine))
                varInLine++;
        }
        varInLine[strlen(varInLine) - 1] = '\0';
        setLabelAsEntry(varInLine, &tableOfSym); /*set label as entry in the table*/
    }
    else if (commandType != unRecognized_C) /*if its a command line*/
    {
        tmpVar = convertCommandToString(commandType); /*convert command to string*/
        varInLine = skipToRestOfString(tmpVar, varInLine);
        IC++;
        analyzeCommandSP(varInLine, commandType); /*analyze command for ssecond pass*/
    }
}
/*This method analyze line following to roles*/
void analyzeCommandSP(char *varInLine, TofC commandType)
{
    char AVar[MAX_ASM_LINE], BVar[MAX_ASM_LINE];
    char *tmpVar = NULL;
    boolean firstVar = FALSE, secondVar = FALSE;
    ptrLabel labelA, labelB;

    while (isspace(*varInLine))
        varInLine++;
    varInLine = varInLineM(AVar, varInLine); /*detect first var*/
    /*#######################################################################################################*/
    if (!tagEndLine(AVar)) /*if after first var there is second*/
    {
        firstVar = TRUE;
        varInLine = varInLineM(BVar, varInLine);
        if (BVar[0] == ',') /*search for ',' after first var*/
        {
            varInLine = varInLineM(BVar, varInLine);
            if (!tagEndLine(BVar))
            {
                secondVar = TRUE; /*second avr is found*/
            }
        }
    }
    /*#######################################################################################################*/
    if (commandType == jmp || commandType == bne || commandType == jsr) /*behivor for relatives commands*/
    {
        if (firstVar && AVar[0] == '&') /*char '&' is found --> address*/
        {
            tmpVar = AVar;
            tmpVar++;
            if (isLegalLabel(tmpVar, FALSE) && (labelA = getLabelByName(tmpVar))) /*this label supposed to be legal label and supposed to be inside table*/
            {
                insertLabelAddressToMeM(labelA, wordToEncodeSeconePass[tmpIC] + MEM_BEGIN_ADDRESS - 1, wordToEncodeSeconePass[tmpIC], ABS); /*calculate diff between current line to label line and insert it as address*/
            }
            else
            {
                fail2P = missing_entry_label;
                return;
            }
        }
    }
    /*#######################################################################################################*/
    if (firstVar && isLegalLabel(AVar, FALSE)) /*first var is found*/
    {
        if ((labelA = getLabelByName(AVar))) /*search it in table*/
        {
            if (labelA->extLabel) /*if it mark as extern label*/
            {
                insertExternalLabel(&externLabelAddress, labelA, wordToEncodeSeconePass[tmpIC]); /*insert it to external table labels*/
                insertLabelAddressToMeM(labelA, 0, wordToEncodeSeconePass[tmpIC], EXT);          /*insert to memory*/
            }
            else
                insertLabelAddressToMeM(labelA, 0, wordToEncodeSeconePass[tmpIC], REL); /*insert label to memory*/
        }
        else if (detectRegister(AVar))
        {
        } /*if it register - continue*/
        else
        {
            fail2P = missing_entry_label;
            return;
        }
    }
    /*#######################################################################################################*/
    if (secondVar && isLegalLabel(BVar, FALSE)) /*if second var is found and its legal label*/
    {
        if ((labelB = getLabelByName(BVar))) /*search it in table*/
        {
            if (labelB->extLabel) /*if it mark as extern label*/
            {
                insertExternalLabel(&externLabelAddress, labelB, wordToEncodeSeconePass[tmpIC]); /*insert it to external table labels*/
                insertLabelAddressToMeM(labelB, 0, wordToEncodeSeconePass[tmpIC], EXT);          /*insert to memory*/
            }
            else
                insertLabelAddressToMeM(labelB, 0, wordToEncodeSeconePass[tmpIC], REL); /*insert label to memory*/
        }
        else if (detectRegister(BVar))
        {
        } /*if it register - continue*/
        else
        {
            fail2P = missing_entry_label;
            return;
        }
    }
}
