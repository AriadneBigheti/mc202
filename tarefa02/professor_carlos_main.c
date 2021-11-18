#include "professor_carlos.h"
#include <stdio.h>

Aluno guarda_aluno (){
    Aluno A;
    scanf("%s ", A.nome);
    scanf("%s ", A.sobrenome);
    scanf("%d", &A.nascimento.dia);
    scanf("%d", &A.nascimento.mes);
    scanf("%d", &A.nascimento.ano);
    return A;
}

void le_dados(int n, Turma t[]){
    int m;
    for (int j=0; j<n; j++){
        scanf("%d \n", &m);
        for (int i=0; i<m; i++){
           t[j].alunos[i] = guarda_aluno();
           t[j].qtd +=1;
        }
    }
}

void faz_operacoes (int n, int k, Turma t[]){
    for (int i=0; i<k; i++){
        int a, j, aux;
        Aluno x;
        char padrao[5];
        scanf("%d", &a);
        if (a==1){
            scanf("%d", &j);
            x = procura_novo_na_turma(t, n, j);
            printf ("%s \n", x.nome);
        }else if (a==2){
            scanf("%d", &j);
            x= procura_velho_na_turma(t, n, j);
            printf ("%s \n", x.sobrenome);
        }else if (a==3){
            x = procura_velho_todas_turmas(t, n);
            printf ("%s \n", x.nome);
        }else if (a==4){
           x= procura_novo_todas_turmas(t, n);
            printf ("%s \n", x.sobrenome);
        }else if (a==5){
            scanf("%s \n", padrao);
            aux = conta_substrings(t, n, padrao);
            printf ("%d \n", aux);
        }else if (a==6){
            scanf("%d", &j);
            x = guarda_aluno();
            aux = add_aluno(t, x, j);
            printf ("%d \n", aux);
        }else if (a==7){
            scanf("%d", &j);
            aux = remove_aluno(t, j);
            printf ("%d \n", aux);
        }
    }
}

int main(){
    int n, k;
    Turma t[50];
    scanf("%d %d \n", &n, &k );
    le_dados (n, t);
    faz_operacoes(n, k, t);
    return 0;
}

