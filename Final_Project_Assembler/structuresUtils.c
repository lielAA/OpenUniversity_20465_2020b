
#include "miscellaneousUtils.h"
#include "globalDef.h"
/*This method insert label to table -> using linked list*/
ptrLabel insertLabel(char *labelName, ptrLabel *head, unsigned int address, boolean ext)
{
    ptrLabel tmpNode;
    ptrLabel aliasH = *head;
    if (isDuplicateLables(labelName, *head) && ext) /*if the label is under .extern and its also declared*/
    {
        return *head;
    }
    if (isDuplicateLables(labelName, *head) && !ext) /*if the label is not under .extern and there is duplicate in label names*/
    {
        fail = label_duplicate;
        return NULL;
    }
    tmpNode = (ptrLabel)malloc(sizeof(NLabel));
    if (!tmpNode)
    {
        exit(0); /*FATAL ERROR - program cant allocate memory - we need to exit the program*/
    }
    /*#####insert values to node#####*/
    tmpNode->labelAddress = address;
    tmpNode->extLabel = ext;
    strcpy(tmpNode->labelName, labelName);
    tmpNode->entLabel = FALSE;
    if (ext) /*.external exist*/
    {
        extF = TRUE;
    }
    else /*its instruction line - .exteranl couldnt be part of it*/
    {
        tmpNode->typeOfLabel = instruction;
    }
    if (!(*head)) /*for empty list*/
    {
        *head = tmpNode;
        tmpNode->nextNode = NULL;
        return tmpNode;
    }
    else /*for non empty list*/
    {
        while (aliasH->nextNode != NULL)
        {
            aliasH = aliasH->nextNode; /*search for the last node*/
        }
        tmpNode->nextNode = NULL;
        aliasH->nextNode = tmpNode;
        return tmpNode;
    }
}
/*if label is already exist in list with this name */
boolean isDuplicateLables(char *labelName, ptrLabel listH)
{
    while (listH)
    {
        if (strcmp(listH->labelName, labelName) == 0)
        {
            return TRUE;
        }
        listH = listH->nextNode;
    }
    return FALSE;
}
/*remove label from list, and update list pointers and positions*/
void removeLabelFromList(char *labelName, ptrLabel *listH)
{
    ptrLabel prevNode;
    ptrLabel tmpNode = *listH;
    while (tmpNode)
    {
        if (strcmp(tmpNode->labelName, labelName) == 0)
        {
            if (strcmp(tmpNode->labelName, (*listH)->labelName) == 0) /*if the label is the head of the list*/
            {
                *listH = (*listH)->nextNode; /*list point to his next*/
                free(tmpNode);
            }
            else
            {
                prevNode->nextNode = tmpNode->nextNode; /*next of prev point to next of tmp*/
                free(tmpNode);
            }
            break;
        }
        prevNode = tmpNode;
        tmpNode = tmpNode->nextNode;
    }
}
/*This method define the final address for labels*/
void defineFinalAddress(boolean isDataType, ptrLabel *currLabel, int address)
{
    ptrLabel tmpNode = *currLabel;
    int i = 0;
    while (tmpNode)
    {
        if (!(tmpNode->extLabel) && (isDataType ^ (tmpNode->typeOfLabel)))
        {
            tmpNode->labelAddress = tmpNode->labelAddress + address;
            i++;
        }
        tmpNode = tmpNode->nextNode;
    }
}
/*This method set label as .entry label in the table*/
void setLabelAsEntry(char *labelName, ptrLabel *listH)
{
    ptrLabel tmp = *listH;
    while (tmp)
    {
        if (strcmp(tmp->labelName, labelName) == 0)/*found label name in the table*/
        {
            if (tmp->extLabel)
            {
                fail2P = entery_defined_as_extern;
                return;
            }
            else
            {
                entF = TRUE;
                tmp->entLabel = TRUE;
                return;
            }
        }
        tmp = tmp->nextNode;
    }
    fail2P = missing_entry_label;
}
/*This method return label location in the table by its name*/
ptrLabel getLabelByName(char *labelName)
{
    ptrLabel tmp = tableOfSym;
    while (tmp)
    {
        if (strcmp(tmp->labelName, labelName) == 0)
        {
            return tmp;
        }
        tmp = tmp->nextNode;
    }
    return NULL;
}
/*This method convert binary word to hex word*/
char *convertBinToHex(boolean isData)
{
    int i, j = 0;
    char *fourDigitWord, *fullWord;
    char word[4];
    fourDigitWord = (char *)malloc(sizeof(char) * HEX_WORD_SIZE);

    fullWord = fourDigitWord;
    for (i = 0; i < WORD_SIZE; i++)
    {
        if (!isData)
        {
            word[j] = structMemoryArea[IC][i] + '0';
            j++;
        }
        else
        {
            word[j] = structDataArea[DC][i] + '0';
            j++;
        }
        if ((i + 1) % FOUR_DIGIT == 0)/*after collect 4 digits*/
        {
            j = 0;
            *fourDigitWord = bin4DigitToHex(word);/*convert to hex*/
            fourDigitWord++;
        }
    }
    return fullWord;
}
/*This method received 4 digit bin string and retuen it as hex code*/
char bin4DigitToHex(char *template)
{
    if (!strcmp(template, "0000"))
        return '0';
    else if (!strcmp(template, "0001"))
        return '1';
    else if (!strcmp(template, "0010"))
        return '2';
    else if (!strcmp(template, "0011"))
        return '3';
    else if (!strcmp(template, "0100"))
        return '4';
    else if (!strcmp(template, "0101"))
        return '5';
    else if (!strcmp(template, "0110"))
        return '6';
    else if (!strcmp(template, "0111"))
        return '7';
    else if (!strcmp(template, "1000"))
        return '8';
    else if (!strcmp(template, "1001"))
        return '9';
    else if (!strcmp(template, "1010"))
        return 'A';
    else if (!strcmp(template, "1011"))
        return 'B';
    else if (!strcmp(template, "1100"))
        return 'C';
    else if (!strcmp(template, "1101"))
        return 'D';
    else if (!strcmp(template, "1110"))
        return 'E';
    else if (!strcmp(template, "1111"))
        return 'F';
    return ' ';
}
/*This method insert external label to external table -> using linked list*/
void insertExternalLabel(ptrExtern *head, ptrLabel label, int address)
{
    ptrExtern tmpExtern;
    ptrExtern aliasH = *head;

    tmpExtern = (ptrExtern)malloc(sizeof(EXLabel));
    tmpExtern->address = wordToEncodeSeconePass[tmpIC];
    strcpy(tmpExtern->labelName, label->labelName);

    if (!(*head)) /*for empty list*/
    {
        *head = tmpExtern;
        tmpExtern->nextExtern = NULL;
    }
    else /*for non empty list*/
    {
        while (aliasH->nextExtern != NULL)
        {
            aliasH = aliasH->nextExtern; /*search for the last node*/
        }
        tmpExtern->nextExtern = NULL;
        aliasH->nextExtern = tmpExtern;
    }
}
/*This method free memory for all labels in linked list*/
void freeTableOfSymLabels(ptrLabel *head)
{
    ptrLabel tmpLabel;

    while(*head)
    {
        tmpLabel = *head;
        *head = (*head)->nextNode;
        free(tmpLabel);
    }
}
/*This method free memory for all external labels in linked list*/
void freeExternTableLabel(ptrExtern *head)
{
    ptrExtern tmpExtern;

    while(*head)
    {
        tmpExtern = *head;
        *head = (*head)->nextExtern;
        free(tmpExtern);
    }
}