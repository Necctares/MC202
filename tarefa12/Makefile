CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: planilha

planilha: planilha.o operacoes.o
	gcc $(CFLAGS) *.o -o planilha $(LDFLAGS)

planilha.o: planilha.c operacoes.h
	gcc $(CFLAGS) -c planilha.c $(LDFLAGS)

operacoes.o: operacoes.c operacoes.h
	gcc $(CFLAGS) -c operacoes.c $(LDFLAGS)

clean:
	rm -f operacoes
	rm -f *.o