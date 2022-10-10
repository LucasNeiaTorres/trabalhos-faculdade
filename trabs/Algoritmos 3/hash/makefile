parametrosCompilacao=-Wall -std=c99 -lm #-Wshadow

all: myht

myht: myht.o libhash.o
	gcc -o myht myht.o libhash.o $(parametrosCompilacao)

myht.o: myht.c
	gcc -c myht.c $(parametrosCompilacao)

libhash.o: libhash.h libhash.c
	gcc -c libhash.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch myht