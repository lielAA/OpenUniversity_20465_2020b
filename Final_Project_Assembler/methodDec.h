#ifndef METHOD_DEC
#define METHOD_DEC
#include <stdlib.h>
#include <stdio.h>
#include "structuresUtils.h"

/*sirdt pass methods*/
void firstAsmPass(FILE *);
void asmRFiles(char *);
void generateOutputFiles(char *);
FILE* openOutFile(typeOfFile,char*);
void generateFile_obj(FILE*);
void generateFile_ext(FILE*);
void generateFile_ent(FILE*);
void initGlobalVars();
boolean isCommentLine(char *);
boolean isEmptyLine(char *);
void analyzeSingleLine(char *);
boolean isLegalLabel(char *, boolean);
char *markVarEOL(char *);
TofD analyzeDirectiveOperands(char *, TofD);
TofC analyzeCommandOperands(char *, TofC);
int analyzeExternD(char *);
int analyzeEntryD(char *);
int analyzeStringD(char *);
int analyzeDataD(char *);
void saveString(char *);
wordP createFirstWord(boolean,boolean,typeOFMethod,typeOFMethod,char *,char *,TofC);
int saveFreeSpaceForMoreWords(boolean,boolean,typeOFMethod,typeOFMethod,char *,char *);





/*Second Pass Methods*/
void secondAsmPass(FILE *, char *);/*not in used - DELETE */
void tmpFunct();

void analyzeSingleLineSecPass(char *);
void defineFinalAddress(boolean, ptrLabel*, int);
void analyzeCommandSP(char *, TofC);
#endif
