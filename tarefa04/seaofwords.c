#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nao_usou_letra(char **vetor, char *endereco, int tamanho){
    for(int i=0; i<tamanho; i++){
        if (vetor[i] == endereco){
            return 0;
        }
    }return 1;
}

int procura_adjacentes(char **texto, int i, int j, char *palavra, int pos, int n, int m, char **posicoes_usadas){
    if (pos == strlen(palavra)){
        return 1;
    }
    if (i>0){
        if (texto[i-1][j]==palavra[pos]){
            if (nao_usou_letra(posicoes_usadas, &texto[i-1][j], pos)){
                posicoes_usadas[pos] = &texto[i-1][j];
                if (procura_adjacentes(texto, i-1, j, palavra, pos+1, n, m, posicoes_usadas)){
                    return 1;
                }    
            }  
        }
    }
    if (i<n-1){
        if (texto[i+1][j]==palavra[pos]){
            if (nao_usou_letra(posicoes_usadas, &texto[i+1][j], pos)){
                posicoes_usadas[pos] = &texto[i+1][j];
                if (procura_adjacentes(texto, i+1, j, palavra, pos+1, n, m, posicoes_usadas)){
                    return 1;
                }
            }
        }
    }
    if (j>0){
        if (texto[i][j-1]==palavra[pos]){
            if (nao_usou_letra(posicoes_usadas, &texto[i][j-1], pos)){
                posicoes_usadas[pos] = &texto[i][j-1];
                if (procura_adjacentes(texto, i, j-1, palavra, pos+1, n, m, posicoes_usadas)){
                    return 1;
                }
            }
        }
    }
    if (j<m-1){
        if (texto[i][j+1]==palavra[pos]){
            if (nao_usou_letra(posicoes_usadas, &texto[i][j+1], pos)){
                posicoes_usadas[pos] = &texto[i][j+1];
                if (procura_adjacentes(texto, i, j+1, palavra, pos+1, n, m, posicoes_usadas)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

void procura_palavra(char *palavra, char **texto, int nlinhas, int ncolunas){
    int existe_palavra=0;
    char **posicoes_usadas = malloc(20 * sizeof(char *));
    
    for (int i=0; i<nlinhas; i++){
        for(int j=0; j<ncolunas; j++){
            if (texto[i][j] == palavra[0]){
                posicoes_usadas[0] = &texto[i][j];
                existe_palavra = procura_adjacentes(texto, i, j, palavra, 1, nlinhas, ncolunas, posicoes_usadas);
                if (existe_palavra){
                    printf("sim \n");
                    free(posicoes_usadas);
                    return;
                }
            }
        }
    }
    printf("nao \n");
    free(posicoes_usadas);
    return;
}

int main(){
    int n=0, m=0, q=0;
    char ** texto;
    char *palavra;

    scanf("%d %d %d", &n, &m, &q);

    texto = malloc(n * sizeof(char*));
    for(int i=0; i<n; i++){
        texto[i] = malloc((m+1)* sizeof(char));
        scanf("%s", texto[i]);
    }

    for(int x=0; x<q; x++){
        palavra= malloc(21 * sizeof(char));
        scanf("%s", palavra);
        procura_palavra(palavra, texto, n, m); 
        free(palavra);
    }

    for(int t=0; t<n; t++)
        free(texto[t]);
    free(texto);

    return 0;
}
