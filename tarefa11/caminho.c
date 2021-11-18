#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX 500   ///dimensão maxima possivel da nossa matriz

typedef struct{   ///estrutura dos nossos vertices
    char parada[10];  //tipo de parada (pokestop ou lugia)
    float x, y;   //coordenadas x e y da origem do ponto
    int distancia; ///distancia da origem até o destino (de um ponto ao outro)
}vertice;

typedef struct{  //estrutura do nosso grafo
    vertice **adj;  ///define a matriz de vertices
    int tam;  //indica a dimensão atual da nossa matriz
}Grafo;

typedef Grafo * p_grafo;

p_grafo criar_grafo(){  //função que aloca memória para o grafo
    p_grafo g = malloc (sizeof(Grafo)); //aloca uma estrutura do tamanho Grafo
    g->adj = calloc (MAX, sizeof(vertice *)); ///aloca um vetor de ponteiros pros vertices
    for(int i=0; i<MAX; i++)
        g->adj[i]= calloc(MAX, sizeof(vertice)); //aloca um vetor do tipo vertice dentro dos outros vetores
    g->tam = 0; //inicializa o tamnho da matriz com 0
    return g;
}

void destroi_grafo(p_grafo g){ //funçao que desaloca o grafo da memória
    for(int i=0; i < MAX; i++) //primeiro a matriz
        free(g->adj[i]);
    free(g->adj);
    free(g); //depois o grafo
}

int calcula_distancia(vertice a, vertice b){  //calcula a distancia euclidiana entre dois vertices e devolve o teto desse valor
    float x = pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
    return ceil(sqrt(x));
}

int insere_vertice(p_grafo g, float x, float y, char parada[]){  //insere os vertices no grafo/insere os elementos na matriz de adjacencia; devolve a maior distancia calculada a partir do vertice inserido
    int atual, max = 0; //variaveis auxiliares
    int k = g->tam;  //posição da matriz na qual devemos inserir o novo elemento
    strcpy(g->adj[k][k].parada, parada);  //guarda os elementos na diagonal da matriz
    g->adj[k][k].x = x;
    g->adj[k][k].y = y;
    g->adj[k][k].distancia = 0; //distancia entre k e ele mesmo é 0
    g->tam++; //incrementa o tamanho da matriz
    
    for (int i=0; i < g->tam; i++){ //laço que vai calcular as distâncias entre os vertices, aproveitando as propriedades da matriz de adjacências
        if(i!=k){  //para o caso em que k==1 a distancia é 0, então podemos excluir esse caso
        atual = calcula_distancia(g->adj[k][k], g->adj[i][i]);  //calcula a distância entre os vertices k e i
        g->adj[i][k].distancia = g->adj[k][i].distancia = atual;  //distancia de i para k e distância de k para i recebem o valor de 'atual'
        strcpy(g->adj[i][k].parada, g->adj[k][k].parada); //se estamos indo de i->k iremos chegar no ponto de parada de k, então guardamos o valor da parada(pokestop ou lugia) de k em [i][k]
        strcpy(g->adj[k][i].parada, g->adj[i][i].parada); //se estamos indo de k->i iremos chegar no ponto de parada de i, então guardamos o valor da parada(pokestop ou lugia) de i em [k][i]
        if (atual>max) //se a distancia entre i e k é maior que as outras, guardamos em 'max' esse valor
            max = atual;
        }
    }
    return max; //retornamos a distancia maxima calculada, cujo ponto de partida/chegada é k
}

int busca_rec (p_grafo g, int orig, int *visitado, char str[], int max_passos){  //função que calcula se um caminho existe, 'orig' é o vertice de origem, 'visitado' é o vetor que irá indicar quais vertices ja foram visitados, 'str' guardará a palavra "Lugia", 'max_passos' é a quantidade maxima de metros que desejamos andar entre dois pontos.

//fazemos a busca de caminhos recursivamente, testando se há um caminho possível cuja maxima distancia entre dois pontos é igual a 'max_passos', se não existe esse caminho retornamos 0

    if(strcmp(g->adj[orig][orig].parada, str)==0){ ///verificamos se o vertice de origem é um lugia, se sim, chegamos no vertice desejado
        return 1; //podemos retornar 1
    }
    
    visitado[orig] = 1; //se nao, marcamos que esse vertice foi visitado no vetor 'visitado' e na posição 'orig'

    for (int w=0; w < g->tam; w++){  //vamos testar o caminho para todos os irmão do vertice 'orig'
        if (visitado[w] == 0 && g->adj[orig][w].distancia<=max_passos){  //para isso, o irmao nao pode ter sido visitado e a distancia entre 'orig' e seu irmao 'w' nao pode ser maior que 'max_passos'
            if (busca_rec(g, w, visitado, str, max_passos))  //fazemos a busca recursivamente tomando o irmao w como origem
                return 1; //se encontramos o lugia podemos retornar 1
        }
    }
    return 0; //se nao encontramos o caminho desejado, retornamos 0
}

int calcula_caminho(p_grafo g, int orig, int distancia_max){ ///função que calcula o menor maximo entre dois pontos de um caminho cujo ponto final deve ser um lugia
    ///iremos testar se há um caminho possível para uma determinada quantidade de passos desejada.
    //para nao testarmos todos os casos de 0 até a distancia maxima possível, iremos fazer busca binaria
    int ini = 0;  //o inicio vale 0
    int fim = distancia_max; ///o final vale a distancia maxima dos pontos no grafo
    int media = (ini + fim)/2; //faz a media entre o inicio e o fim escolhidos

    while (1){
        int *visitado = calloc(g->tam, sizeof(int)); //aloca um vetor de 0s, que irá auxiliar indicando quais vertices ja foram visitados, se a posiçao k vale 1 então aquele vertice do grafo ja foi visitado
        
        if (busca_rec(g, orig, visitado, "Lugia", media)){  //se a busca recursiva encontrar um caminho cujo o tamanho maximo de passos valha 'media'
            free(visitado);
            if (ini==fim) //se inicio == fim a nossa busca binaria se resume a um ponto e esse ponto é a reposta
                return media; //retorna o valor, e quebra o laço
            else{ ///se não, a busca se resume a mais de um ponto então temos que testar para os valores abaixo da media
                fim = media; //fim recebe media
                media = (ini+fim)/2;
            }
        }else{ //se nao, a busca recursiva nao encontrou um caminho cujo maximo valha 'media', então temos que buscar para os valores maiores que a media
            free(visitado);
            ini = media+1; //inicio recebe a media mais um (pois ja sabemos que o valor da media nao serve)
            media = (ini+fim)/2;
        }       
    }
    return -1;
}

int main(){
    float x_atual, y_atual, x, y; /// x/y_atual são as posições de origem do red, x/y são as posições dos pontos de parada que vao ser lidas
    int origem, aux, atual, distancia_max = 0; //variaveis auxiliares
    char parada[10]; //variavel para a string (pokestop ou lugia)
    p_grafo g = criar_grafo(); //cria nosso grafo g

    scanf("%f %f", &x_atual, &y_atual); //le as posições de origem do red

    while(scanf("%f %f", &x, &y)!=EOF){ //laço ocorrerá até quando houver entradas a serem lidas
        scanf("%s", parada);  //le a string da linha de entrada

        if (x==x_atual && y==y_atual) //se os valores do ponto de parada lido forem iguais a posição do red, encontramos a posição dele no grafo
            origem = g->tam;  //origem guarda a posição do red na matriz de adjacencias

        atual = insere_vertice(g, x, y, parada); //atual vai receber o valor maximo das distancias calculadas a partir do nó inserido

        if (atual>distancia_max) //se atual for maior que a distancia maxima anterior, a distancia maxima recebe atual
            distancia_max = atual;
    }

    aux = calcula_caminho(g, origem, distancia_max);  //aux vai receber o valor minimo entre as maximas distancias entre dois pontos no caminho para um lugia

    printf("%d", aux);  //imprimimos aux

    destroi_grafo(g); //destruimos nosso grafo, desalocando ele da memória

    return 0;
}