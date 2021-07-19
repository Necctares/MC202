CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: diadeuber

diadeuber: diadeuber.o uber.o
	gcc $(CFLAGS) -o diadeuber diadeuber.o  uber.o $(LDFLAGS)

diadeuber.o: diadeuber.c uber.h
	gcc $(CFLAGS) -c diadeuber.c $(LDFLAGS)

uber.o: uber.c uber.h
	gcc $(CFLAGS) -c uber.c $(LDFLAGS)

clean:
	rm -f diadeuber
	rm -f *.o
