#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 150   ///tamanho do nosso vetor de hash

typedef struct{     //estrutura dos elementos do nosso vetor de hash
    char palavra[27]; ///variavel que guardadrá a palavra do dicionario
    int colisao; ///variavel auxiliar que indicará se houve colisão com este elemento na hora de inserir palavras no dicionario
}palavra;

typedef palavra * p_palavra;  //ponteiro para a estrutura dos elementos do hash

typedef struct {
    p_palavra vetor[MAX];  //estrutura do hash é um vetor de ponteiros de tamanho 150, eles vao apontar para a estrutura palavra
}Hash;

typedef Hash * p_hash;  //ponteiro para o hash

int hash(char *chave){  //função que calcula o hash de uma string "chave", utilizando base 256
    int n=0;
    for (int i=0; i<strlen(chave); i++)
        n = (256 * n + chave[i]) % MAX;
    return n;
}

p_hash criarHASH(){  ///função que aloca o nosso hash na memoria
    p_hash h = malloc(sizeof(Hash));
    for (int i=0; i<MAX; i++){
        h->vetor[i] = malloc(sizeof(palavra));
        h->vetor[i]->palavra[0] = '\0';  //vamos inicializar as palavras do nosso dicionario com '\0'
        h->vetor[i]->colisao = 0; ///por enquanto nao houve nenhuma colisaão entre as palavras então "colisão" recebe 0
    }    
    return h;
}

void inserir(p_hash t, char chave[]){  //insere uma nova palavra no hash
    int n = hash(chave); //calcula o hash da string

    while (t->vetor[n]->palavra[0]!='\0'){ ///verifica se já há uma palavra nesta posição, se sim então temos uma colisão, então iremos seguir no hash até encontrar a proxima posição vazia
        t->vetor[n]->colisao = 1; //variavel colisão recebe 1
        n++; //vamos caminhar de 1 em 1 no hash até encontrar uma posição vazia
    }///encontramos a posição n vazia

    strcpy(t->vetor[n]->palavra, chave); //guardamos a palavra em n
}


int buscar(p_hash t, char *chave){  //função que busca uma string 'chave' no hash
    int n = hash(chave); //calcula o hash dessa alavra

    if (t->vetor[n]->colisao==1){ //verifica se já houve colisão nessa palavra, pois se houve pode ser que a palavra está correta mas houve colisão ao adiciona-la no dicionario
        while (strcmp(t->vetor[n]->palavra, chave)!=0 && n<MAX-1) ///se houve colisão e as palavras são diferentes, vamos seguir de 1 em 1 no hash até encontrar a palavra ou até o fim do hash
            n++;
    }//se não houve colisão nesta posição do hash já sabemos que a palavra está ou certa ou errada, pois ela não pode estar em outra posição
    return strcmp(t->vetor[n]->palavra, chave); //retorna a comparação entre a chave e a palavra na poisção n do hash, se forem iguais vai retornar 0
}

int adicionar_letra(p_hash t, char chave[]){  //funçao que adiciona uma nova letra na chave
    char alfabeto[27] = "abcdefghijklmnopqrstuvwxyz"; //variavel que guarda o alfabeto em letras minusculas
    int x = strlen(chave); // variavel que guarda o tamanho da chave
    char aux[27]= " "; //variavel auxiliar

    strcpy(aux, chave); //copia a chave em auxiliar

    for (int j=0; j<x+1; j++){  //vamos percorrer x+1 posiçoes da chave adicionando uma letra do alfabeto

        strcpy(&aux[j+1], &chave[j]); //abre um espaço na posição j na variavel auxiliar, antes de j ela já está igual a chave, depois de j devemos copiar o que está na chave a partir de j de forma que elas fiquem iguais exceto pela posição j em aux

        for (int a=0; a<26; a++){ //vamos testar todas as letras do alfabeto nesta posição j
            aux[j]=alfabeto[a];
            if (buscar(t, aux)==0)  //vamos buscar se esta palavra está no hash
                return 0; //se sim, retorna 0
        }

        strcpy(aux, chave); // copia de novo a chave em auxiliar
    }
    return 1; //não encontramos a palavra no hash e devolvemos 1
}

int trocar_letra(p_hash t, char *chave){ //função que troca o valor de uma letra na palavra
    char alfabeto[27] = "abcdefghijklmnopqrstuvwxyz"; //variavel que guarda o alfabeto em letras minusculas
    char aux[27]= " "; //variavel auxiliar
    strcpy(aux, chave); //copia a chave em auxiliar, para guardar seu valor original

    for (int i=0; chave[i]!='\0'; i++){ //laço que vai percorrer todos os elementos da chave alterando seu valor
        strcpy(chave, aux);  //copia o valor de aux pra chave, para voltar ao original
        for(int j=0; alfabeto[j]!='\0'; j++){ //laço que vai percorrer todas as letras do alfabeto e testa-las na posição i da chave
            chave[i]=alfabeto[j];   
            if (buscar(t, chave)==0) //vamos buscar se esta palavra está no hash
                return 0;    //se sim, retorna 0
        }
    }
    strcpy(chave, aux); // copia de novo o valor de auxiliar na chave, pois a chave original pode ter sido alterada
    return 1;  //não encontramos a palavra no hash e devolvemos 1
}

int remove_letra (p_hash t, char *chave){ //função que vai remover 1 letra da palavra
    int x = strlen(chave); /// variavel que guarda o tamanho da chave
    char aux[27]=" ";   //variavel auxiliar
    strcpy(aux, chave); //copia a chave em auxiliar, para guardar seu valor original

    for (int j=0; j<x; j++){ //laço que vai percorrer todos os elementos da chave
        strcpy(chave, aux);  ////copia o valor de aux pra chave, para voltar ao original
        for(int i=j; chave[i]!='\0'; i++){ //laço que vai de j até o final da string
            chave[i]=chave[i+1];   //a partir de j vamos fazer o valor chave[i] ser igual ao de chave[i+1], assim estamos eliminando um caractere da string
        }
        if (buscar(t, chave)==0){ //vamos buscar se esta palavra está no hash
            return 0;   //se sim, retorna 0
        }
    }
    strcpy(chave, aux); // copia de novo o valor de auxiliar na chave, pois a chave original pode ter sido alterada
    return 1;  //não encontramos a palavra no hash e devolvemos 1 
}

int main(){
    int n, q; //n indica o numero de palavras no dicionario, q o numero de palavras que devem ser buscadas no dicionario
    n=q=0;
    char chave[27]= " "; 
    p_hash hash = criarHASH(); //cria o nosso hash

    scanf("%d %d", &n, &q); //le os valores n e q
    
    for (int i=0; i<n; i++){ //laço que lerá e adicionará as palavras no dicionario
        scanf("%s", chave);
        inserir(hash, chave);
    }
    for(int i=0; i<q; i++){ //laço que lerá e verificará se a palavra está no dicionário
        scanf("%s", chave);

        ////vamos procurar se há uma palavra no dicionário exatamente igual à chave
        if (buscar(hash, chave)==0){
            printf("verde\n");
        }else{ ///vamos testar os outros casos
            if(remove_letra(hash, chave)==0){ ///se ao remover 1 letra da chave ela se torna igual a uma palavra do dicionario
                printf("amarelo\n"); //se sim elas são diferentes em 1 letra, então há 1 erro de digitaçao e o sinal é amarelo
            }else if (trocar_letra(hash, chave)==0){ //se ao trocar o valor de 1 letra da chave ela e torna igual a uma palavra do dicionario
                printf("amarelo\n");    //se sim elas são diferentes em 1 letra, então há 1 erro de digitaçao e o sinal é amarelo
            }else if (adicionar_letra(hash, chave)==0){ //se ao adicionar 1 letra na chave ela se torna igual a uma palavra do dicionario
                printf("amarelo\n");    //se sim elas são diferentes em 1 letra, então há 1 erro de digitaçao e o sinal é amarelo
            }else{ //caso contrário elas são diferentes em mais de 1 letra e o sinal então é vermelho
                printf("vermelho\n");
            }
        }
    }
    for (int i=0; i<MAX; i++) //percorre cada posição do vetor do hash
        free(hash->vetor[i]); //desaloca as estruturas "palavra" da memória
    free(hash); //desaloca a estrutura "Hash" da memória

    return 0;
}
