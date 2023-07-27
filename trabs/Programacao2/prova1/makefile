parametrosCompilacao=-Wall -std=c99 -D_DEFAULT_SOURCE #-Wshadow
arquivos=poema.o
all: poema

poema: $(arquivos)
	gcc -o poema $(arquivos) $(parametrosCompilacao)

.o: .c
	gcc -c *.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch poema

purge: clean
	-rm -f poema