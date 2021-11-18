CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: sala_de_espera

sala_de_espera: sala_de_espera_main.c
	gcc $(CFLAGS) -c sala_de_espera_funcoes.c $(LDFLAGS)
	gcc $(CFLAGS) -c sala_de_espera_main.c $(LDFLAGS)
	gcc $(CFLAGS) -o sala_de_espera sala_de_espera_main.o sala_de_espera_funcoes.o $(LDFLAGS)

clean:
	rm -f sala_de_espera
	rm -f *.o