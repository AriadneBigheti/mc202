#include "sala_de_espera.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprime_registro_horarios (p_paciente paciente, int horario_chegada){
    int x = paciente->tempo;
    while (x>=60){
        x -=60;
        horario_chegada += 1;
    }
    printf("%.2d:%.2d ", horario_chegada, x);
    for(int i=0; paciente->nome[i]!='"'; i++){
        printf("%c", paciente->nome[i]);
    }printf("\n");
}

void acrescenta_tempo (p_fila f, int x){
    p_paciente paciente = f->ini;
    while(paciente!=NULL){
            paciente->tempo += x; 
            paciente = paciente->prox;
        }
}

void encaminha_para_medico(p_paciente paciente, p_fila Clinico_Geral, p_fila Radiologista,  p_fila Enfermeiro, p_fila Otorrinolaringologista, p_fila Pneumologista, p_fila Dermatologista, p_fila Neurologista, p_fila Oncologista, p_fila Psiquiatra, p_fila Fila_de_Saida){
        int i = paciente->atendimento_atual; //// i diz em qual atendimento do dia o paciente está conforme a posiçao do ID do atendimento no vetor atendimentos
        
        if (paciente->atendimentos[i] == '1'){
            enfileira(Clinico_Geral, paciente, 1);
            return;
        }
        else if (paciente->atendimentos[i] == '2'){
            enfileira(Radiologista, paciente, 1);
            return;
        }
        else if (paciente->atendimentos[i] == '3'){
            enfileira(Enfermeiro, paciente, 1);
            return;
        }
        else if (paciente->atendimentos[i] == '4'){
            enfileira(Otorrinolaringologista, paciente, 1);
            return;
        }
        else if (paciente->atendimentos[i] == '5'){
            enfileira(Pneumologista, paciente, 1);
            return;
        }
        else if (paciente->atendimentos[i] == '6'){
            enfileira(Dermatologista, paciente, 1);
            return;
        }
        else if (paciente->atendimentos[i] == '7'){
            enfileira(Neurologista, paciente, 1);
            return;
        }
        else if (paciente->atendimentos[i] == '8'){
            enfileira(Oncologista, paciente, 1);
            return;
        }
        else if (paciente->atendimentos[i] == '9'){ 
            enfileira(Psiquiatra, paciente, 1);
            return;
        }
        else{
            enfileira(Fila_de_Saida, paciente, 0);
            return;
        }
}

void chegada_paciente(p_fila f, int num_chegada){
    p_paciente paciente=NULL;
    char nome[50]={};
    char preferencial[17]={};
    char atendimentos[50]={};
    scanf("%c", &nome[0]);
    for (int i=1; nome[i-1]!= '"'; i++){
        scanf("%c", &nome[i]); 
    }
    scanf("%s ", preferencial);
    fgets(atendimentos, 50, stdin);
    paciente = criar_ficha(nome, preferencial, atendimentos, num_chegada);
    enfileira(f, paciente, 0);
}

int main(){
    p_fila Clinico_Geral = criar_fila(10);
    p_fila Radiologista = criar_fila(2);
    p_fila Enfermeiro = criar_fila(5);
    p_fila Otorrinolaringologista = criar_fila(3);
    p_fila Pneumologista = criar_fila(4);
    p_fila Dermatologista = criar_fila(7);
    p_fila Neurologista = criar_fila(2);
    p_fila Oncologista = criar_fila(1);
    p_fila Psiquiatra = criar_fila(4);
    p_fila Fila_de_Espera = criar_fila(-1);
    p_fila Fila_de_Saida = criar_fila(-1);
    p_paciente paciente; //variavel auxiliar
    int tempo_consulta = 10;
    int horario_chegada = 8;
    int t=1;
    char e =0;
    while(scanf("%c", &e)!=EOF){
       chegada_paciente(Fila_de_Espera, t);
       t++;
    }
    int total_pacientes = Fila_de_Espera->tamanho;


    while(Fila_de_Saida->tamanho != total_pacientes){ ///quando a fila de saida estiver cheia então todos os pacientes ja realizaram seus atendimentos
        while (Fila_de_Espera->tamanho != 0){       ///laço que vai encaminhar todos os pacientes da fila de espera para a fila de seus respectivos atendimentos
            paciente = desenfileira(Fila_de_Espera);
            encaminha_para_medico(paciente, Clinico_Geral, Radiologista, Enfermeiro, Otorrinolaringologista, Pneumologista, Dermatologista, Neurologista, Oncologista, Psiquiatra, Fila_de_Saida);
        }

        /// supoe-se que passa o tempo da consulta então acrescentamos 10 ao tempo de todos os pacientes das filas
        acrescenta_tempo(Clinico_Geral, tempo_consulta);
        acrescenta_tempo(Radiologista, tempo_consulta);
        acrescenta_tempo(Enfermeiro, tempo_consulta);
        acrescenta_tempo(Otorrinolaringologista, tempo_consulta);
        acrescenta_tempo(Pneumologista, tempo_consulta);
        acrescenta_tempo(Dermatologista, tempo_consulta);
        acrescenta_tempo(Neurologista, tempo_consulta);
        acrescenta_tempo(Oncologista, tempo_consulta);
        acrescenta_tempo(Psiquiatra, tempo_consulta);

        /// então vamos desenfileirar a quantidade de pacientes que foram atendidos 
        
        for(int v =0; v<(Clinico_Geral->max); v++){
    
            if (Clinico_Geral->tamanho!=0){
            paciente = desenfileira(Clinico_Geral);
            paciente->atendimento_atual +=2; 
            enfileira(Fila_de_Espera, paciente, 0); //manda o paciente que foi atendido de volta para a fila de espera
            }
        }
        for(int v =0; v<(Radiologista->max); v++){
            if (Radiologista->tamanho!=0){
            paciente = desenfileira(Radiologista);
            paciente->atendimento_atual +=2; 
            enfileira(Fila_de_Espera, paciente, 0);
            }
        }
        for(int v =0; v<(Enfermeiro->max); v++){
            if (Enfermeiro->tamanho!=0){
            paciente = desenfileira(Enfermeiro);
            paciente->atendimento_atual +=2; 
            enfileira(Fila_de_Espera, paciente, 0);
            }
        }
        for(int v =0; v<(Otorrinolaringologista->max); v++){
            if (Otorrinolaringologista->tamanho!=0){
            paciente = desenfileira(Otorrinolaringologista);
            paciente->atendimento_atual +=2; 
            enfileira(Fila_de_Espera, paciente, 0);
            }
        }
        for(int v =0; v<(Pneumologista->max); v++){
            if (Pneumologista->tamanho!=0){
            paciente = desenfileira(Pneumologista);
            paciente->atendimento_atual +=2; 
            enfileira(Fila_de_Espera, paciente, 0);
            }
        }
        for(int v =0; v<(Dermatologista->max); v++){
            if (Dermatologista->tamanho!=0){
            paciente = desenfileira(Dermatologista);
            paciente->atendimento_atual +=2; 
            enfileira(Fila_de_Espera, paciente, 0);
            }
        }
        for(int v =0; v<(Neurologista->max); v++){
            if (Neurologista->tamanho!=0){
            paciente = desenfileira(Neurologista);
            paciente->atendimento_atual +=2; 
            enfileira(Fila_de_Espera, paciente, 0);
            }
        }
        for(int v =0; v<(Oncologista->max); v++){
            if (Oncologista->tamanho!=0){
            paciente = desenfileira(Oncologista);
            paciente->atendimento_atual +=2; 
            enfileira(Fila_de_Espera, paciente, 0);
            }
        }
        for(int v =0; v<(Psiquiatra->max); v++){
            if (Psiquiatra->tamanho!=0){
            paciente = desenfileira(Psiquiatra);
            paciente->atendimento_atual +=2; 
            enfileira(Fila_de_Espera, paciente, 0);
            }
        }
    }

    while(Fila_de_Saida->tamanho!=0){
        paciente = desenfileira(Fila_de_Saida);
        imprime_registro_horarios(paciente, horario_chegada);
        free(paciente);
    }

    destruir_fila(Fila_de_Saida);
    destruir_fila(Fila_de_Espera);
    destruir_fila(Clinico_Geral);
    destruir_fila(Radiologista);
    destruir_fila(Enfermeiro);
    destruir_fila(Otorrinolaringologista);
    destruir_fila(Pneumologista);
    destruir_fila(Dermatologista);
    destruir_fila(Neurologista);
    destruir_fila(Oncologista);
    destruir_fila(Psiquiatra);

    return 0;
}