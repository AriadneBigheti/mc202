#ifndef CALCULADORA_H
#define CALCULADORA_H
#include <stdlib.h>
#include <stdio.h>

typedef struct no{
    int dado;
    struct no *prox;
} no;

typedef no *p_no;

p_no criar_lista();

void destruir_lista( p_no lista);

p_no adicionar_elemento(p_no lista, int x);

void imprime_lista(p_no lista);

p_no adicao(p_no operando1, p_no operando2);

p_no subtracao(p_no operando1, p_no operando2);

p_no multiplicacao(p_no operando1, p_no operando2);

p_no divisao(p_no operando1, p_no operando2);

#endif