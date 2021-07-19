CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: mensageiro

mensageiro: mensageiro.o arvore.o
	gcc $(CFLAGS) -o mensageiro mensageiro.o  arvore.o $(LDFLAGS)

mensageiro.o: mensageiro.c arvore.h
	gcc $(CFLAGS) -c mensageiro.c $(LDFLAGS)

arvore.o: arvore.c arvore.h
	gcc $(CFLAGS) -c arvore.c $(LDFLAGS)

clean:
	rm -f mensageiro
