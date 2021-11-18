#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define PAI(i) ((i-1)/2) //macro que calcula a posição do pai de i no heap
#define F_ESQ(i) (2*i+1) //macro que calcula a posição do filho esquerdo de i no heap
#define F_DIR(i) (2*i+2) //macro que calcula a posição do filho direito de i no heap

typedef struct localizacao{ //estrutura que indica as coordenadas x e y
    int x;
    int y;
} local;

typedef struct cliente{   //estrututura dos elementos do nosso heap
    char nome[17];
    double avaliacao;
    local posicao;
    local destino;
}cliente;

typedef cliente *p_cliente;  //ponteiro para a estrutura do cliente

typedef struct {   //estrutura do nosso heap
    p_cliente v;   //aponta o endereço para o primeiro elemento do vetor
    int n, tamanho;   //n indica o tamanho atual do heap, e tamanho indica o tamanho max do heap
}fp;

typedef fp * p_fp;   //ponteiro para a estrutura do heap

void troca (cliente *a, cliente *b){  //troca dois elementos de endereço
    cliente t = *a;
    *a = *b;
    *b = t;
}

p_fp criarHEAP (int tam){  //função que irá criar o heap
    p_fp heap = malloc(sizeof(fp));  //aloca uma estrutura de heap
    heap->v = malloc(tam * sizeof(cliente));  //aloca tam posiçoes em nosso vetor
    heap->n = 0;  //tamanho atual do heap é zero
    heap->tamanho = tam; //tamanho maximo do heap é tamanho
    return heap;
}

void sobenoHEAP(p_fp fp, int k){   //funco que sobe elemento no heap até encontrar seu local adequado
    if(k>0 && fp->v[PAI(k)].avaliacao < fp->v[k].avaliacao){   //se k nao for o unico elemento do heap e o pai de k tiver avaliacao maior que a dele faremos a troca
        troca(&fp->v[k], &fp->v[PAI(k)]);   //trocamos o pai com o filho
        sobenoHEAP(fp, PAI(k));  //continuamos a subir o elemento que agora está na posição PAI(k) no heap
    }
}

void insereHEAP (p_fp fp, cliente cliente){   //função que insere elemento no final do heap
    fp->v[fp->n] = cliente;
    fp->n++;  //incrementa o tamanho atual do heap
    sobenoHEAP(fp, fp->n -1);   //conserta o heap (se necessário) subindo seu ultimo elemento 
}

void descenoHEAP(p_fp fp, int k){   //funçao que arruma o heap descendo a raiz
    int maior_filho;  //vamos encontrar o maior filho da nossa raiz
    if (F_ESQ(k) < fp->n){   //se houver filho esquerdo ele pode ser o maior filho, caso contrario k é o ultimo elemento do heap e nao há filhos, então nao precisará descer
        maior_filho = F_ESQ(k);
        if (F_DIR(k) < fp->n && fp->v[F_ESQ(k)].avaliacao < fp->v[F_DIR(k)].avaliacao) // se houver filho direito e ele tiver maior avaliacao que o esquerdo então o filho direito é o maior filho, caso contrario o filho esquerdo tem a maior avaliacao e é o maior filho
            maior_filho = F_DIR(k); 
        if (fp->v[k].avaliacao < fp->v[maior_filho].avaliacao){  //se o maior filho tiver avaliacao maior que a do pai, faremos a troca entre os dois
            troca(&fp->v[k], &fp->v[maior_filho]);   //trocamos os dois de lugar
            descenoHEAP(fp, maior_filho);  //chamamos a função recursivamente para arrumar o resto do heap descendo o elemento novo que está na posição maior_filho do heap
        }
    }
}

cliente Remove_Cliente (p_fp fp, char nome[]){   //função que remove um elemento do heap a partir da chave nome
    int i = 0;
    cliente q;
    while(strcmp(fp->v[i].nome, nome)!=0){    //vamos procurar o elemento de chave igual a "nome", enquanto a chave nao for igual ao nome continuaremos a procura no heap
        i++;
    }
    q = fp->v[i];  //q recebe o cliente a ser removido do heap
    troca(&fp->v[i], &fp->v[fp->n -1]); //troca o elemento i com o ultimo elemento do heap
    fp->n--; //decrementa a quantidade de elementos no heap
    descenoHEAP(fp, i); ///conserta o heap descendo o novo elemento que está na posição i
    return q;  //retorna o cliente que foi removido
}

int distancia_Manhattan (local a, local b){   //calcula a distância de manhattan entre duas posições (em coordenadas cartesianas)
    int r;
    r = abs(a.x - b.x) + abs(a.y - b.y);
    return r;
}

int main(){
    char acao = 0;   //variavel que indicará a ação a ser realizada no heap
    char cliente_atual [17] = " ";  ///variavel que indicará qual o cliente atual que o uber esta atendendo
    int km_total = 0;  //variavel que indicará a kilometragem total que o uber rodou no dia
    int km_clientes = 0;   ///variavel que indicará a kilometragem das corridas que o uber fez
    float rendimento = 0;   //variavel que calculará o rendimento bruto do uber
    float despesas = 0;  //variavel que calculará as despesas do uber
    local local_uber;  //variavel que indicará a posição atual do uber (em coordenadas cartesinas)
    cliente cliente;  //variavel auxiliar para fazer operações no heap
    p_fp heap = criarHEAP(500);  //variavel que aponta o endereço do nosso heap

    cliente_atual[0] = '\0';  //ao começar o dia o uber está atendendo ninguem
    local_uber.x = local_uber.y = 0;  //ao começar o dia o uber está nas coordenadas (0,0) 

    while (acao != 'T'){   //enquanto a acao a ser realizada não for T, o uber continua a atender 

        scanf ("%c", &acao);

        if (acao == 'A'){  //adiciona cliente
            scanf("%c", cliente.nome);   //retira os espaços sobrando 
            scanf("%s ", cliente.nome);   //lê o nome do cliente
            scanf("%lf", &cliente.avaliacao);  //lê a avaliação do cliente
            scanf("%d %d %d %d", &cliente.posicao.x, &cliente.posicao.y, &cliente.destino.x, &cliente.destino.y);  //lÊ as posições atual e de destino do cliente
            insereHEAP(heap, cliente);  //insere o cliente no heap
            printf("Cliente %s foi adicionado(a)\n", cliente.nome);  //informa que o cliente foi adcionado no heap
            if (cliente_atual[0]=='\0'){   //se o uber não está atendendo ninguém, passa a atender a pessoa de amior avaliação no heap
                strcpy(cliente_atual, heap->v[0].nome);
            }
        }else if (acao == 'F'){  //finaliza corrida
            cliente = Remove_Cliente(heap, cliente_atual);  //remove do heap cliente que está sendo atendido 
            km_total += distancia_Manhattan(local_uber, cliente.posicao);   //calcula distancia total que o uber correu
            km_total += distancia_Manhattan(cliente.posicao, cliente.destino);
            km_clientes += distancia_Manhattan(cliente.posicao, cliente.destino);  //calcula distancia da corrida do cliente
            local_uber = cliente.destino;  //atualiza a a posição atual do uber
            printf("A corrida de %s foi finalizada\n", cliente.nome);  //informa que a corrida do cliente foi finalizada
            if (heap->n > 0){   //se o heap não estiver vazio, passa a atender o cliente de avaliação maxima
                strcpy(cliente_atual, heap->v[0].nome);
            }else{  //se o heap estiver vazio, não estará atendendo ninguém
                cliente_atual[0]='\0';
            } 
        }else if (acao == 'C'){  //cancela corrida
            scanf("%c", cliente.nome); //retira os espaços sobrando 
            scanf("%s ", cliente.nome);  //lê o nome do cliente a ser retirado do heap
            cliente = Remove_Cliente(heap, cliente.nome);  //remove cliente do heap
            rendimento +=7;  //soma 7 aos rendimentos do uber
            printf("%s cancelou a corrida\n", cliente.nome);  //informa o nome do cliente que cancelou a corrida
            if (strcmp(cliente_atual, cliente.nome)==0){  //se o cliente que cancelou a corrida é cliente que o uber estava atendendo, o uber passará a atender outro: o de avaliação maxima no heap
                strcpy(cliente_atual, heap->v[0].nome);
            }
        }else if (acao == 'T'){  //finaliza a jornada
            printf("\n");
            printf("Jornada finalizada. Aqui esta o seu rendimento de hoje\n");
            printf("Km total: %d\n", km_total);  //imprime kilometragem total rodada pelo uber
            rendimento += (km_clientes*1.40); //calcula os rendimentos baseado na kilometragem rodada nas corridas dos clientes
            printf("Rendimento bruto: %.2f\n", rendimento);  //imprime rendimento bruto
            despesas = (km_total*4.104)/10 + 57;  //calcula as despesas que são: gasolina e aluguel do carro
            printf("Despesas: %.2f\n", despesas); //imprime as despesas
            printf("Rendimento liquido: %.2f\n", rendimento - despesas - rendimento*0.25);  //imprime rendimento liquido que é: rendimento bruto - despesas - taxa da uber em cima do rendimento bruto

        }
    }
    free(heap->v);  //libera o vetor do nosso heap
    free(heap);  //libera a estrutura do nosso heap
    return 0;
}