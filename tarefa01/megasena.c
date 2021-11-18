#include <stdio.h>
#define ZERO 0.0

void guardamatriz (int matriz[][10], int m){
    for (int i=0; i<6*m; i++){
        for(int j=0; j<10; j++){
            scanf("%d", &matriz[i][j]);
        }
    }
}

void lematriz(int matriz[][10], int num_sorteados[], int resultado[], int m){
    for (int participante=0; participante<m; participante++){
        int acertos=0;
        for (int i=0; i<6; i++){
            for(int j=0; j<10; j++){
                if (matriz[i + 6*participante][j] == 1){
                    int num = 10*i + j+1;
                    for (int x=0; x<6; x++){
                        if (num == num_sorteados[x])
                            acertos += 1;
                    }
                }
            }
        } if (acertos == 6){
            resultado[participante] = 6;
        } else if (acertos ==5) {
            resultado[participante] = 5;
        } else if (acertos ==4) {
            resultado[participante] = 4;
        } else{
            resultado[participante] = 0;
        }
    }
   
}

void imprime_resultado(int resultado[], int m, int n){
    int sena=0, quina=0, quadra=0;
    for (int i=0; i<m; i++){
        if (resultado[i]==6)
            sena+=1;
        else if (resultado[i]==5)
            quina+=1;
        else if (resultado[i]==4)
            quadra+=1;
    }
    for (int i=0; i<m; i++){
        if (resultado[i]>3) {
            if (resultado[i]==6) {
                printf("%.2f\n", (n*0.62)/sena);
            } else if (resultado[i] == 5) {
                printf("%.2f\n", (n*0.19)/quina);
            } else if (resultado[i]  == 4) {
                printf("%.2f\n", (n*0.19)/quadra);
            }
        } else
            printf("%.2f\n", ZERO);
    }
}


int main(){
    int m;
    float n;
    scanf("%d", &m);
    scanf("%f", &n);

    if (5>m)
        return 0;
    if (m>1000)
        return 0;      
    if (1e6>n)
        return 0;
    if (n>3e9)
        return 0;         

    int matriz[6*1000][10];
    guardamatriz(matriz, m);

    int num_sorteados[6];
    for (int s=0; s<6; s++){
        scanf("%d", &num_sorteados[s]);
    }
    int resultado[1000];
    lematriz(matriz, num_sorteados, resultado,  m);
    imprime_resultado(resultado, m, n);
    
    return 0;
} 