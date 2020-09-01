#ifndef STRUCT_UTILS
#define STRUCT_UTILS

#include "assembler.h"

/*bollean var*/
typedef enum
{
    FALSE,
    TRUE
} boolean;
/*label type*/
typedef enum labelType
{
    instruction = 1,
    directive = 0
} LType;
/*symbos table for labels*/
typedef struct nodeLabel *ptrLabel;
typedef struct nodeLabel
{
    ptrLabel nextNode;         /*pointer to next node*/
    char labelName[MAX_LABEL]; /*name of label*/
    unsigned int labelAddress; /*address for label*/
    boolean entLabel;          /*if its entry label*/
    boolean extLabel;          /*if its external label*/
    LType typeOfLabel;         /*if label is instruction or directive */
} NLabel;
/*external table for exetern labels*/
typedef struct externType *ptrExtern;
typedef struct externType
{
    int address;
    char labelName[MAX_LABEL];
    ptrExtern nextExtern;
}EXLabel;

#endif