#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include "structuresUtils.h"

/*first pass methods*/
boolean isWrongLine(boolean);
void printErrInLine(int,int);
ptrLabel insertLabel(char *, ptrLabel*, unsigned int, boolean);
boolean isDuplicateLables(char *,ptrLabel);
boolean tagEndLine(char *);
TofD recognizeDirective(char *);
TofD detectDirective(char *);
void removeLabelFromList(char*,ptrLabel*);
TofC recognizeCommand(char *);
TofC detectCommand(char *);
TofR detectRegister(char *);
boolean isLegalString(char *);
char * varInLineM(char *, char*);
boolean isLegalNumInData(char*);
char * convertCommandToString(TofC);
typeOFMethod detectMeth(char *);
boolean legalVarForCommand(boolean,boolean,TofC);
boolean legalMetForCommand(typeOFMethod, typeOFMethod,TofC);
char *skipToRestOfString(char *,char*);
char *skipToNextVar(char*);
char * convertDircetiveToString(TofD);
void defineARE(typeOfARE, wordP);

/*second pass methods*/
void createFullDecWord(wordP);
void CreateFullBinWord(unsigned int, size, boolean);
void insertWordToMemory();
void insertLabelAddressToMeM(ptrLabel,unsigned int , int,typeOfARE);
void setLabelAsEntry(char *, ptrLabel*);
ptrLabel getLabelByName(char *);
char* convertBinToHex(boolean isData);
char bin4DigitToHex(char *);
void insertExternalLabel(ptrExtern*,ptrLabel,int);
void freeTableOfSymLabels(ptrLabel *);
void freeExternTableLabel(ptrExtern *);

