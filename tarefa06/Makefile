CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: sala_de_espera

sala_de_espera: sala_de_espera.o paciente.o
	gcc $(CFLAGS) -o sala_de_espera sala_de_espera.o  paciente.o $(LDFLAGS)

sala_de_espera.o: sala_de_espera.c paciente.h
	gcc $(CFLAGS) -c sala_de_espera.c $(LDFLAGS)

paciente.o: paciente.c paciente.h
	gcc $(CFLAGS) -c paciente.c $(LDFLAGS)

clean:
	rm -f sala_de_espera
