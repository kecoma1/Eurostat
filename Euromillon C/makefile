CC = gcc -ansi -pedantic
FLAGS = -Wall -g

all: main.o EUROSTAT

main.o:
	$(CC) $(FLAGS) -c main.c -lm

EUROSTAT:
	$(CC) $(FLAGS) main.o -o EUROSTAT -lm

clean:
	rm -f *.o EUROSTAT

run:
	./EUROSTAT Resultados.txt
