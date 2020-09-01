numbers: numbers.o numbersUtilities.o
	gcc -g -Wall -ansi -pedantic numbers.o numbersUtilities.o -o numbers
numbers.o: numbers.h numbers.c
	gcc -c -Wall -ansi -pedantic numbers.c -o numbers.o
numbersUtilities.o: numbers.h numbersUtilities.c
	gcc -c -Wall -ansi -pedantic numbersUtilities.c -o numbersUtilities.o