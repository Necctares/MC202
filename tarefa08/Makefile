CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: listas_legais

listas_legais: listas_legais.o abb.o
	gcc $(CFLAGS) -o listas_legais listas_legais.o  abb.o $(LDFLAGS)

listas_legais.o: listas_legais.c abb.h
	gcc $(CFLAGS) -c listas_legais.c $(LDFLAGS)

abb.o: abb.c abb.h
	gcc $(CFLAGS) -c abb.c $(LDFLAGS)

clean:
	rm -f listas_legais
	rm -f *.o
