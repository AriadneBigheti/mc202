#ifndef SALA_DE_ESPERA_H
#define SALA_DE_ESPERA_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct ficha_paciente{
    char nome[50];
    int preferencial; 
    char atendimentos[50];
    int atendimento_atual;
    int num_chegada;
    int tempo;
    struct ficha_paciente *prox;
} ficha_paciente;

typedef ficha_paciente *p_paciente;

typedef struct {
    int tamanho;
    int max; 
    p_paciente ini, fim;
} Fila;

typedef Fila *p_fila;

/// funcoes de lista ligada
p_paciente criar_ficha (char nome[], char prefencial[], char atendimentos[], int num_chegada);

void destruir_ficha(p_paciente ficha);

/// funcoes de deque

p_fila criar_fila(int tamanho_max);

void destruir_fila(p_fila f);

void enfileira (p_fila f , p_paciente paciente, int p);

p_paciente desenfileira (p_fila f);

void ordena_fila(p_fila f);

#endif