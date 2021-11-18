#include <stdio.h>
#include <stdlib.h>

enum Cor {VERMELHO, PRETO};

typedef struct No{      //estrutura da arvore rubro-negra esquerdista
    long int valor;    //informa o valor numerico do nó
    long int qtde;      ///informa quantas vezes aquele numero foi adicionado na lista legal
    enum Cor cor;      //informa a cor da arvore
    struct No *esq, *dir;
} No;

typedef No *p_no;

long int ehVermelho(p_no x){     //função utilizada para o balanceamento que informa a cor de um nó
    if (x==NULL)
        return 0;
    return x->cor == VERMELHO;
}

long int ehPreto(p_no x){   //função utilizada para o balanceamento que informa a cor de um nó
    if (x==NULL)
        return 1;
    return x->cor == PRETO;
}

p_no rotaciona_para_esq (p_no raiz){    //função utilizada para o balanceamento, rotaciona o nó para a esquerda
    p_no x = raiz->dir;
    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

p_no rotaciona_para_dir (p_no raiz){    //função utilizada para o balanceamento, rotaciona o nó para a direita
    p_no x = raiz->esq;
    raiz->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

void sobe_vermelho(p_no raiz){      //função utilizada para o balanceamento, "sobe" a cor do nó sem bagunçar o balanceamento
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}

p_no inserir_rec (p_no raiz, long int valor){      //faz a inserção recursivamente
    p_no novo=NULL;
    if (raiz ==NULL){               //se a raiz é nula, cria a raiz
        novo = malloc(sizeof(No));
        novo->valor = valor;
        novo->qtde = 1;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->cor = VERMELHO;
        return novo;
    }
    if(valor == raiz->valor){         //achamos nosso nó e incrementamos a variavel qtde, para dizer que há mais um numero como aquele na arvore
        raiz->qtde +=1;
    }else if (valor < raiz->valor){   ///se o valor é menor, vamos para a esquerda
        raiz->esq = inserir_rec(raiz->esq, valor);
    }else{
        raiz->dir = inserir_rec(raiz->dir, valor);   /// se o valor é maior vamos para a direita
    }   
    //iremos corrigir o balanceamento da arvore
    if(ehVermelho(raiz->dir) && ehPreto(raiz->esq))
        raiz = rotaciona_para_esq(raiz);
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->esq->esq))
        raiz = rotaciona_para_dir(raiz);
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->dir))
        sobe_vermelho(raiz);

    return raiz;
}

p_no insere_ABB(p_no raiz, long int valor){          //insere um elemento de valor x na arvore binaria balanceada
    raiz = inserir_rec(raiz, valor);       //chamaremos outra funçao para fazer a inserção recursivamente
    raiz->cor = PRETO;
    return raiz;
}

p_no RemoveNo (p_no raiz, long int x){    //remove um elemento de valor x da arvore (função será usada apenas para destruir a arvore, uma vez que bagunça seu balanceamento)
    if(raiz==NULL){
        return NULL;

    }else if (raiz->valor > x){
        raiz->esq = RemoveNo(raiz->esq, x);
    }else if(raiz->valor < x){
        raiz->dir = RemoveNo(raiz->dir, x);
    }else{  ///raiz->valor=x, achamos o nó a ser removido
        if (raiz->dir==NULL && raiz->esq==NULL){ ///o nó não tem filhos
            free(raiz);
            raiz = NULL;
        }else if (raiz->esq ==NULL){  //nó só tem filho direito
            p_no aux = raiz;
            raiz = raiz->dir;
            free(aux);
        }else if(raiz->dir==NULL){  //nó só tem filho esquerdo
            p_no aux = raiz;
            raiz = raiz->esq;
            free(aux);
        }else{   //nó tem os dois filhos
           p_no aux = raiz->esq;
           while(aux->dir != NULL){  //vamos procurar o maior à direita da subarvore esquerda
               aux = aux->dir;
           }
           raiz->valor= aux->valor;   //vamos trocar as informações dos nós
           raiz->esq = RemoveNo(raiz->esq, aux->valor);
        }
        
    }return raiz;
}

void DestroiABB(p_no raiz){   //função que destroi a arvore binaria balanceada pela raiz
    while(raiz!=NULL)
        raiz = RemoveNo(raiz, raiz->valor);
}


p_no procurar_no (p_no raiz, long int x){  ///procura um elemento de valor x na arvore e retorna seu endereço
    if(raiz==NULL || raiz->valor == x)
        return raiz;
    else if(x > raiz->valor){
        return procurar_no(raiz->dir, x);
    }else{
        return procurar_no(raiz->esq,x);
    }
}

long int ha_quantos_nos(p_no raiz, long int y){   ///diz quantas vezes aquele numero aparece na lista
    p_no no;
    no = procurar_no(raiz, y);
    if (no == NULL)
        return 0;
    return no->qtde;
}

long int eh_listalegal (p_no raiz){         //verifica se a arvore binaria balanceada é uma "lista legal" informando quantos nós precisam ser excluidos para que ela se torne uma "lista legal"
    long int x = 0;
    long int aux = 0;

    if(raiz == NULL){
        return 0;
    }

    aux = raiz->qtde;

    if (aux != raiz->valor){
        if(aux < raiz->valor){
            x = aux;
        }else{
            x = aux - raiz->valor;
        }
    }
    return x + eh_listalegal(raiz->dir) + eh_listalegal(raiz->esq);
}

p_no faz_operacao(p_no raiz, int m){      //função que irá realizar as operações desejadas
    long int aux=0;
    long int n=0;

    if(m==1){        //operação 1
       scanf("%ld", &n);
       raiz = insere_ABB(raiz, n);
    }else if (m==2){       //operação 2
       scanf("%ld", &n);
       aux = ha_quantos_nos(raiz, n);
       printf("%ld\n", aux);
    }else if (m==3){          ///operação 3
       aux = eh_listalegal(raiz);
       printf("%ld\n", aux);
    }
    return raiz;
}

int main(){
    long int n=0;
    long int k=0;
    long int x = 0;
    p_no arvore=NULL;

    scanf("%ld %ld", &n, &k);

    for(long int i=0; i<n; i++){     //insere os elementos na arvore
        scanf("%ld", &x);
        arvore = insere_ABB(arvore, x);
    }

    int a=0; 
    for (long int v=0; v<k; v++){           //faz as operações na arvore
        scanf("%d", &a);
        arvore = faz_operacao(arvore, a);
    }

    DestroiABB(arvore);         //destroi a arvore
    
    return 0;
}