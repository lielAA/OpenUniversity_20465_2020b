#include "assembler.h"
#include "structuresUtils.h"


/*global variables*/
extern char *command[];
extern char *directiveArr[];
extern int DC,IC,tmpIC;
extern boolean entF,extF;
extern int fail,fail2P;
extern boolean flagFailed;
extern ptrLabel tableOfSym;
extern boolean isFlagLabel;
extern unsigned int structDataArea[MEM_SIZE][WORD_SIZE];/*area to store data from asm */
extern unsigned int structMemoryArea[MEM_SIZE][WORD_SIZE];/*area to store memory from asm*/
extern ptrExtern externLabelAddress;
extern unsigned int wordArr[];
extern int wordArrIndex;
extern unsigned int DataArr[];
extern int dataArrIndex;
extern int L;
extern int wordToEncodeSeconePass[];