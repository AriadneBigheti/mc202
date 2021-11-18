#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void le_dados(int M, double **dados, char **termo, int l){
    scanf("%s", termo[l]);

    for (int x=0; x<M; x++){
        scanf("%lf", &dados[l][x]);
    }   
}

void analisa_dados(int N, int M, char **termo, double **dados, char **bot, char **surpreendente, char **normal, char **local, char **irrelevante, int *qtd_termos, int k){
    double maximo = dados[k][0], minimo = dados[k][0], media = 0 , desvio_padrao=0;
    int l;

    for(int i=0; i<M; i++){
        media += dados[k][i]/M;
        if (dados[k][i]<=minimo)
            minimo = dados[k][i];
        if (dados[k][i]>=maximo)
            maximo = dados[k][i];
    }
    for(int i=0; i<M; i++){
        desvio_padrao += pow((dados[k][i]-media), 2.0)/M;
    }
    desvio_padrao = sqrt(desvio_padrao);

    printf("%s ", termo[k]);
    printf("%.2f %.2f %.2f %.2f\n", maximo, minimo, media, desvio_padrao);
    
    if (media>=60 && desvio_padrao>15){
        l = qtd_termos[0];
        qtd_termos[0]++;
        bot[l] = termo[k];
    }else if(media>=60 && desvio_padrao<=15){
        l = qtd_termos[1];
        qtd_termos[1]++;
        surpreendente[l] = termo[k];
    }else if (media<60 && maximo>=80 && minimo>20){
        l = qtd_termos[2];
        qtd_termos[2]++;
        normal[l] = termo[k];
    }else if (media<60 && maximo>=80 && minimo<=20){
        l = qtd_termos[3];
        qtd_termos[3]++; 
        local[l] = termo[k];
    }else if (media<60 && maximo<80){
        l = qtd_termos[4];
        qtd_termos[4]++;
        irrelevante[l] = termo[k];
    }
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    double **dados= malloc(N* sizeof(double*));
    char **termo= malloc(N * sizeof(char *));
    char **bot = malloc(N * sizeof(char *)), **surpreendente= malloc(N * sizeof(char *)), **normal= malloc(N * sizeof(char *)), **local= malloc(N * sizeof(char *)), **irrelevante= malloc(N * sizeof(char *));
    int *qtd_termos = malloc(5 * sizeof(int)); 

    for (int k=0; k<5; k++)
        qtd_termos[k] =0;

    for(int i=0; i<N; i++){
        termo[i] = malloc(28 * sizeof(char));
        dados[i] = malloc(M* sizeof(double));
    }

    for (int k=0; k<N; k++)
        le_dados(M, dados, termo, k);

    for (int k=0; k<N; k++)
        analisa_dados(N, M, termo, dados, bot, surpreendente, normal, local, irrelevante, qtd_termos, k);
    
    printf("\n");
    printf("RESULTADO:\n");
    printf("Bot (%d):", qtd_termos[0]);
    for (int i=0; i<(qtd_termos[0]); i++)
        printf(" %s", *&bot[i]);
    printf("\n");

    printf("Surpreendente (%d):", qtd_termos[1]);
    for (int i=0; i<(qtd_termos[1]); i++)
        printf(" %s",*&surpreendente[i]);
    printf("\n");
    
    printf("Normal (%d): ", qtd_termos[2]);
    for (int i=0; i<(qtd_termos[2]); i++)
        printf(" %s",*&normal[i]);
    printf("\n");

    printf("Local (%d): ", qtd_termos[3]);
    for (int i=0; i<(qtd_termos[3]); i++)
        printf(" %s", *&local[i] );
    printf("\n"); 

    printf("Irrelevante (%d): ", qtd_termos[4]);
    for (int i=0; i<(qtd_termos[4]); i++)
       printf(" %s", *&irrelevante[i]);
    printf("\n");
  
    for(int i=0; i<N; i++){
        free(termo[i]);
        free(dados[i]);
    }free(termo);
    free(dados);

    free(bot);
    free(surpreendente);
    free(normal);
    free(local);
    free(irrelevante); 
    free(qtd_termos);

    return 0;
}