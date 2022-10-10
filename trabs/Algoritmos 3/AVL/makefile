CFLAGS = -Wall 
 
all: myavl

myavl: t1main.o libs.o
	gcc -o myavl t1main.o libs.o $(CFLAGS)

t1main.o: t1main.c
	gcc -c t1main.c $(CFLAGS)

libs.o: libs.c
	gcc -c libs.c $(CFLAGS)

clean:
	rm -f *.o *.gch myavl
