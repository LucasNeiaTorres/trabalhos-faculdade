parametrosCompilacao=-Wall #-Wshadow
nomePrograma=tp6

all: $(nomePrograma)

$(nomePrograma): tp6.o libpilha.o
	gcc -o $(nomePrograma) tp6.o libpilha.o $(parametrosCompilacao)

tp6.o: tp6.c
	gcc -c tp6.c $(parametrosCompilacao)

libpilha.o: libpilha.h libpilha.c
	gcc -c libpilha.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
