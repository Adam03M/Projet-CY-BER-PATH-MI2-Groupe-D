all : prog


main.o : main.c fonctions.h
	gcc -c main.c -o main.o

fonctions.o : fonctions.c fonctions.h
	gcc -c fonctions.c -o fonctions.o



prog : main.o fonctions.o
	gcc *.o -o prog
