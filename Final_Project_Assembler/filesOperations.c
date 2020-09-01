#include "miscellaneousUtils.h"
#include "methodDec.h"
#include "globalDef.h"

boolean flagFailed;
/*This method received file asm file name from arguments command line, open it and manage all behivor for files - input and outputs*/
void asmRFiles(char *asmfileName)
{
    FILE *asmFD;
    char* tmpAsmFileName = (char*)malloc(sizeof(asmfileName));  /*allocate memory*/
    char *originFileName = (char *)malloc(sizeof(asmfileName)); /*allocate memory*/
    if(!tmpAsmFileName || !originFileName)
    {
        fprintf(stderr, "FATAL ERROR - memory alocation failed - EXIT PROGRAM\n");
        exit(0);
    }
    strcpy(tmpAsmFileName,asmfileName);
    strcpy(originFileName, asmfileName);
    strcat(tmpAsmFileName, ".as"); /*add .as file extenssion*/
    if (!(asmFD = fopen(tmpAsmFileName, "r")))
    {
        fprintf(stderr, "Opened file failed!\n");
        free(originFileName);
        free(tmpAsmFileName);
        free(asmFD);
        return;
    }
    else
    {
        firstAsmPass(asmFD); /*go to firs pass*/
        if (!flagFailed)
        {
            rewind(asmFD);                     /*return to head of file*/
            secondAsmPass(asmFD, tmpAsmFileName); /*go to second pass - there is no erros*/
            if (!flagFailed)
            {
                generateOutputFiles(originFileName); /*generate .ob .ent .ext output files*/
            }
        }
    }
    freeTableOfSymLabels(&tableOfSym);
    freeExternTableLabel(&externLabelAddress);
    free(originFileName);
    free(tmpAsmFileName);
    fclose(asmFD);
    return;
}
/*This method generate/create output files*/
void generateOutputFiles(char *asmfileName)
{
    FILE *outFile;
    outFile = openOutFile(objFile, asmfileName); /*open file with permission*/
    generateFile_obj(outFile);                   /*write data to .ob file*/
    fclose(outFile);

    if (extF)
    {
        outFile = openOutFile(extFile, asmfileName); /*open file with permission*/
        generateFile_ext(outFile);                   /*write data to .ext file*/
        fclose(outFile);
    }

    if (entF)
    {
        outFile = openOutFile(entFile, asmfileName); /*open file with permission*/
        generateFile_ent(outFile);                   /*write data to .ent file*/
        fclose(outFile);
    }
}
/*This method open file depend on file type*/
FILE *openOutFile(typeOfFile typeF, char *fileName)
{
    FILE *outFile;
    char *fullName = (char *)malloc(EXTENSSION_LEN + strlen(fileName));
    if (!fullName)
    {
        exit(FALSE);
    }
    strcpy(fullName, fileName);
    switch ((int)typeF)
    {
    case objFile: /*open/create .ob file*/
    {
        strcat(fullName, ".ob");
        outFile = fopen(fullName, "w");
        break;
    }
    case entFile: /*open/create .ent file*/
    {
        strcat(fullName, ".ent");
        outFile = fopen(fullName, "w");
        break;
    }
    case extFile: /*open/create .ext file*/
    {
        strcat(fullName, ".ext");
        outFile = fopen(fullName, "w");
        break;
    }
    }
    if (!outFile) /*failed to open file*/
    {
        fprintf(stderr, "Opened file failed\n");
        exit(FALSE);
    }
    free(fullName);
    return outFile;
}
/*This method write data to .ob file*/
void generateFile_obj(FILE *objFileName)
{
    int i, d;
    char *memoryConverted, *dataConverted;

    fprintf(objFileName, "     %d %d\n", L, DC);
    IC = 0;
    /*write memory area to file*/
    for (i = 0; i < L; i++)
    {
        memoryConverted = convertBinToHex(FALSE); /*convert binary data to hex*/
        IC++;
        fprintf(objFileName, "%07d %s\n", i + MEM_BEGIN_ADDRESS, memoryConverted); /*write data to file*/
        free(memoryConverted);
    }
    d = DC;
    DC = 0;
    /*write data area to file*/
    for (i = 0; i < d; i++)
    {
        dataConverted = convertBinToHex(TRUE); /*convert binary data to hex*/
        DC++;
        fprintf(objFileName, "%07d %s\n", i + L + MEM_BEGIN_ADDRESS, dataConverted); /*write data to file*/
        free(dataConverted);
    }
}
/*This method write extern label data to .ext file*/
void generateFile_ext(FILE *extFileName)
{
    ptrExtern ptr = externLabelAddress;
    while (ptr)
    {
        fprintf(extFileName, "%s %07d\n", ptr->labelName, (ptr->address) + MEM_BEGIN_ADDRESS);
        ptr = ptr->nextExtern;
    }
}
/*This method write entry label data to .ent file*/
void generateFile_ent(FILE *entFileName)
{
    ptrLabel ptr = tableOfSym;
    while (ptr)
    {
        if (ptr->entLabel)
        {
            fprintf(entFileName, "%s %07d\n", ptr->labelName, ptr->labelAddress);
        }
        ptr = ptr->nextNode;
    }
}
