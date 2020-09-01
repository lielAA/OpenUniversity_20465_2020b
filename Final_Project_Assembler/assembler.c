#include "miscellaneousUtils.h"
/* "######  Author: Liel Adir
   "######  Student ID: 20-280253
   "#####   Date: 19/08/2020 */

#include "globalDef.h"
#include "methodDec.h"
#include "structuresUtils.h"

/*global vars as external*/
int fail,fail2P;
ptrLabel tableOfSym;
boolean flagFailed, entF, extF,isFlagLabel; 
int IC, DC,tmpIC;
unsigned int structDataArea[MEM_SIZE][WORD_SIZE];
unsigned int structMemoryArea[MEM_SIZE][WORD_SIZE];
unsigned int wordArr[WORD_SIZE];
unsigned int DataArr[MEM_SIZE];
int wordToEncodeSeconePass[MEM_SIZE];
ptrExtern externLabelAddress;
int wordArrIndex,L,dataArrIndex;

int main(int argc, char *argv[])
{
    int i;
    if (argc == 1)
    {
        printf("Cant find assembly files - please insert legal assembly files");
        exit(0);
    }
    /*send each file names to assmbly praser*/
    for (i = 1; i < argc; i++)
    {
        asmRFiles(argv[i]);
    }
    return 0;
}
/*initial global variables*/
void initGlobalVars()
{
    extF = FALSE;
    entF = FALSE; 
    flagFailed = FALSE;
    tableOfSym = NULL;
    externLabelAddress = NULL;
    isFlagLabel = FALSE;
    wordArrIndex = 0;
    dataArrIndex = 0;
    L = 0;
}