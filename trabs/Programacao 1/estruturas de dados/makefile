parametrosCompilacao=-Wall -std=c90 #-Wshadow

all: testa_pilha testa_fila testa_lista

testa_pilha: testa_pilha.o libpilha.o
	gcc -o testa_pilha testa_pilha.o libpilha.o $(parametrosCompilacao)

testa_pilha.o: testa_pilha.c
	gcc -c testa_pilha.c $(parametrosCompilacao)

libpilha.o: libpilha.h libpilha.c
	gcc -c libpilha.c $(parametrosCompilacao)

testa_fila: testa_fila.o libfila.o
	gcc -o testa_fila testa_fila.o libfila.o $(parametrosCompilacao)

testa_fila.o: testa_fila.c
	gcc -c testa_fila.c $(parametrosCompilacao)

libfila.o: libfila.h libfila.c
	gcc -c libfila.c $(parametrosCompilacao)

testa_lista: testa_lista.o liblista.o
	gcc -o testa_lista testa_lista.o liblista.o $(parametrosCompilacao)

testa_lista.o: testa_lista.c
	gcc -c testa_lista.c $(parametrosCompilacao)

liblista.o: liblista.h liblista.c
	gcc -c liblista.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch testa_pilha testa_fila testa_lista
