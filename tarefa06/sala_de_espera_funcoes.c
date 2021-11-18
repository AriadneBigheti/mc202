#include "sala_de_espera.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

p_paciente criar_ficha (char nome[], char preferencial[], char atendimentos[], int num_chegada){
    p_paciente novo=NULL;
    novo = malloc (sizeof(ficha_paciente));
    strcpy(novo->nome, nome);
    strcpy(novo->atendimentos, atendimentos);
    novo->atendimento_atual = 0;
    novo->num_chegada = num_chegada;
    novo->tempo = 0;
    novo->prox = NULL;
    if (strcmp(preferencial, "preferencial") == 0)   
        novo->preferencial = 1;         //// se o paciente é preferencial então é 1, caso contrario é 0
    else
        novo->preferencial = 0;
    return novo;
}

void destruir_ficha(p_paciente ficha){
    if (ficha!=NULL){
        destruir_ficha(ficha->prox);
        free(ficha);
    }
}

p_fila criar_fila(int tamanho_max){
    p_fila f=NULL;
    f = malloc (sizeof(Fila));
    f->tamanho = 0;
    f->max = tamanho_max;
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

void destruir_fila(p_fila f){
    destruir_ficha(f->ini);
    free(f);
}

void enfileira (p_fila f , p_paciente paciente, int p){
    paciente->prox = NULL;
    p_paciente paciente1=NULL;
    if(paciente->preferencial==0 || p==0){  //se o paciente nao é preferencial ele entra no final da fila, o parametro p serve para indicar se devemos considerar o atendimento preferencial ou nao, ele só vai ser considerado na fila dos medicos, pois as filas de saida e espera sao apenas filas auxiliares
        if(f->ini ==NULL)
            f->ini = paciente;
        else
            f->fim->prox = paciente;
        f->fim = paciente;
    }else{                         // se o paciente é prefencial ele entra no começo da fila
        if(f->ini ==NULL){
            f->ini = paciente;
            f->fim = paciente;
        }else{
           paciente1 = f->ini;
           f->ini = paciente;
           paciente->prox = paciente1; 
        }
    }
    f->tamanho+=1;
}

p_paciente desenfileira (p_fila f){
    p_paciente primeiro = f->ini;
    f->ini = f->ini->prox;
    if (f->ini == NULL)
        f->fim =NULL;
    f->tamanho-=1;
    return primeiro;        //retorna o paciente que foi retirado da fila
}
