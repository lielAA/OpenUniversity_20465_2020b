complex: complex.o mycomp.o mycompUtilities.o
	gcc -g -Wall -ansi -pedantic mycomp.o mycompUtilities.o complex.o -o mycomp -lm
mycomp.o: mycomp.c complex.h
	gcc -c -Wall -ansi -pedantic mycomp.c -o mycomp.o -lm
mycompUtilities.o: mycompUtilities.c complex.h
	gcc -c -Wall -ansi -pedantic mycompUtilities.c -o mycompUtilities.o -lm
complex.o: complex.c complex.h
	gcc -c -Wall -ansi -pedantic complex.c -o complex.o -lm
