#include "professor_carlos.h"
#include <stdio.h>


Aluno ordem_lexicografica (Aluno A, Aluno B){
    int i=0;
    while (A.nome[i]!='\0' && B.nome[i]!='\0'){
        if (A.nome[i]< B.nome[i]){
            return A;
        }else if (B.nome[i]< A.nome[i])
            return B;
        if (A.nome[i] == B.nome[i]){
            i +=1;
        }
    }i= 0;
    while (A.sobrenome[i]!='\0' && B.sobrenome[i]!='\0'){
        if (A.sobrenome[i]< B.sobrenome[i]){
            return A;
        }else if (B.sobrenome[i]< A.sobrenome[i])
            return B;
        if (A.sobrenome[i] == B.sobrenome[i]){
            i +=1;
        }
    }
    return B;
}

Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j){
    int n = t[j].qtd; 
    Aluno mais_novo = t[j].alunos[0];

    for (int i =1; i<n; i++){
        if (t[j].alunos[i].nascimento.ano == mais_novo.nascimento.ano){
            if ( t[j].alunos[i].nascimento.mes > mais_novo.nascimento.mes){
                mais_novo =  t[j].alunos[i];
            }if ( t[j].alunos[i].nascimento.mes == mais_novo.nascimento.mes){
                if ( t[j].alunos[i].nascimento.dia > mais_novo.nascimento.dia){
                    mais_novo =  t[j].alunos[i];
                } 
                if (t[j].alunos[i].nascimento.dia == mais_novo.nascimento.dia){
                    mais_novo = ordem_lexicografica (t[j].alunos[i], mais_novo);
                }
            }        
        }if  (t[j].alunos[i].nascimento.ano > mais_novo.nascimento.ano){
            mais_novo =  t[j].alunos[i];
        }
    }return mais_novo;
}


Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas){
    Aluno mais_novo =  t[0].alunos[0];

    for (int j=0; j<qtd_turmas; j++){
        int n = t[j].qtd; 
        
        for (int i =0; i<n; i++){
            if (t[j].alunos[i].nascimento.ano == mais_novo.nascimento.ano){
                if ( t[j].alunos[i].nascimento.mes > mais_novo.nascimento.mes){
                    mais_novo =  t[j].alunos[i];
                }if (t[j].alunos[i].nascimento.mes == mais_novo.nascimento.mes){
                    if ( t[j].alunos[i].nascimento.dia > mais_novo.nascimento.dia){
                        mais_novo =  t[j].alunos[i];
                    }  
                    if (t[j].alunos[i].nascimento.dia == mais_novo.nascimento.dia){
                        mais_novo = ordem_lexicografica (t[j].alunos[i], mais_novo);
                    }     
                }        
            }if  (t[j].alunos[i].nascimento.ano > mais_novo.nascimento.ano){
                mais_novo =  t[j].alunos[i];
            }
        }
    } return mais_novo;
}

Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j){
    int n = t[j].qtd;
    Aluno mais_velho =  t[j].alunos[0];

    for (int i =1; i<n; i++){
        if ( t[j].alunos[i].nascimento.ano == mais_velho.nascimento.ano){
            if (t[j].alunos[i].nascimento.mes < mais_velho.nascimento.mes){
                mais_velho =  t[j].alunos[i];
            }if (t[j].alunos[i].nascimento.mes == mais_velho.nascimento.mes){
                if ( t[j].alunos[i].nascimento.dia < mais_velho.nascimento.dia){
                    mais_velho =  t[j].alunos[i];
                }  
                if (t[j].alunos[i].nascimento.dia == mais_velho.nascimento.dia){
                    mais_velho = ordem_lexicografica (t[j].alunos[i], mais_velho);
                }     
            }        
        }if  (t[j].alunos[i].nascimento.ano < mais_velho.nascimento.ano){
            mais_velho =  t[j].alunos[i];
        }
    }return mais_velho;
}


Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas){
    Aluno mais_velho =  t[0].alunos[0];

    for (int j=0; j<qtd_turmas; j++){
        int n = t[j].qtd;
        
        for (int i =0; i<n; i++){
            if (t[j].alunos[i].nascimento.ano == mais_velho.nascimento.ano){
                if ( t[j].alunos[i].nascimento.mes < mais_velho.nascimento.mes){
                    mais_velho =  t[j].alunos[i];
                }if (t[j].alunos[i].nascimento.mes == mais_velho.nascimento.mes){
                    if ( t[j].alunos[i].nascimento.dia < mais_velho.nascimento.dia){
                        mais_velho =  t[j].alunos[i];
                    }  
                    if (t[j].alunos[i].nascimento.dia == mais_velho.nascimento.dia){
                        mais_velho = ordem_lexicografica (t[j].alunos[i], mais_velho);
                    }        
                }        
            }if  (t[j].alunos[i].nascimento.ano < mais_velho.nascimento.ano){
                mais_velho =  t[j].alunos[i];
            }
        }
    } return mais_velho;
}


int conta_substrings(Turma t[], int qtd_turmas, char padrao[]){
    int qtd_substrings=0;
    for (int j=0; j<qtd_turmas; j++){
        for(int x=0; x<t[j].qtd; x++){
            int i =0, y=0, substring = 0;
            while (padrao[i] !='\0' && t[j].alunos[x].nome[y] !='\0'){
                if (t[j].alunos[x].nome[y] == padrao[i]){
                    substring =1;
                    if (t[j].alunos[x].nome[y+1] =='\0' && padrao[i+1] !='\0' ){
                        substring=0; 
                    }
                    y +=1;
                    i +=1;      

                }else{
                    substring=0;
                    y+=1;
                    i=0;
                }        
            }
            if (substring){
                qtd_substrings +=1;
            }  
        }
    }return qtd_substrings;
}

int add_aluno(Turma t[], Aluno A, int j){
    int num_alunos = t[j].qtd;
    t[j].alunos[num_alunos] = A;
    t[j].qtd += 1;
    return t[j].qtd;
}

int remove_aluno(Turma t[], int j){
    Aluno A;
    A.nascimento.dia = 0;
    A.nascimento.mes = 0;
    A.nascimento.ano = 0;
    int num_alunos =  t[j].qtd;
    t[j].alunos[num_alunos] = A;
    t[j].qtd -= 1;
    return t[j].qtd;
}
