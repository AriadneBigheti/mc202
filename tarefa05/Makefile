CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: calculadora

calculadora: calculadora_main.c
	gcc $(CFLAGS) -c calculadora_funcoes.c $(LDFLAGS)
	gcc $(CFLAGS) -c calculadora_main.c $(LDFLAGS)
	gcc $(CFLAGS) -o calculadora calculadora_main.o calculadora_funcoes.o $(LDFLAGS)


clean:
	rm -f calculadora
	rm -f *.o
