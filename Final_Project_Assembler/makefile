assembler: assembler.o filesOperations.o firstAsmPass.o secondAsmPass.o structuresUtils.o miscellaneousUtils.o
	gcc -g -Wall -ansi -pedantic assembler.o filesOperations.o firstAsmPass.o secondAsmPass.o structuresUtils.o miscellaneousUtils.o -o assembler -lm

assembler.o: assembler.o assembler.h globalDef.h methodDec.h structuresUtils.h miscellaneousUtils.h
	gcc -c -Wall -ansi -pedantic assembler.c -o assembler.o

firstAsmPass.o: assembler.o assembler.h globalDef.h methodDec.h structuresUtils.h miscellaneousUtils.h
	gcc -c -Wall -ansi -pedantic firstAsmPass.c -o firstAsmPass.o

secondAsmPass.o:assembler.o assembler.h globalDef.h methodDec.h structuresUtils.h miscellaneousUtils.h
	gcc -c -Wall -ansi -pedantic secondAsmPass.c -o secondAsmPass.o

structuresUtils.o:assembler.o assembler.h globalDef.h methodDec.h structuresUtils.h miscellaneousUtils.h
	gcc -c -Wall -ansi -pedantic structuresUtils.c -o structuresUtils.o

miscellaneousUtils.o:assembler.o assembler.h globalDef.h methodDec.h structuresUtils.h miscellaneousUtils.h
	gcc -c -Wall -ansi -pedantic miscellaneousUtils.c -o miscellaneousUtils.o

filesOperations.o:assembler.o assembler.h globalDef.h methodDec.h structuresUtils.h miscellaneousUtils.h
	gcc -c -Wall -ansi -pedantic filesOperations.c -o filesOperations.o
