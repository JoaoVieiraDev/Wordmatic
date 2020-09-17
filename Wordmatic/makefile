CFLAGS= -O3 -Wall -pedantic

wordmatic: main.o Projecto.o Matrix.o
	gcc $(CFLAGS) -o wordmatic Matrix.o Projecto.o main.o

main.o: main.c Projecto.h Matrix.h
	gcc $(CFLAGS) -c main.c

Projecto.o: Projecto.c Projecto.h
	gcc $(CFLAGS) -c Projecto.c 

Matrix.o: Matrix.c Matrix.h Defs.h
	gcc $(CFLAGS) -c Matrix.c

clean:
	rm -f *.o *.~ wordmatic *.gch
