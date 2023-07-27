parametrosCompilacao=-Wall -std=c99 -D_DEFAULT_SOURCE #-Wshadow
arquivos=forca.o
all: forca

forca: $(arquivos)
	gcc -o forca $(arquivos) $(parametrosCompilacao)

.o: .c
	gcc -c *.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch forca 

purge: clean
	-rm -f forca