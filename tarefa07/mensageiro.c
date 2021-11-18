#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{     ///estrutura dos nossos nós da arvore
    int dado;
    char mensagem[10000];
    struct No *esq, *dir;
} No;

typedef No *p_no;

p_no criar_arvore (int x, const char mensagem[]){    // cria uma raiz com filhos nulos, devolve a raiz
    p_no r = malloc(sizeof(No));
    r->dado = x;
    strcpy(r->mensagem, mensagem);
    r->esq = NULL;
    r->dir = NULL;
    return r;
}

p_no adiciona_folha(p_no folha, p_no arvore){   //adiciona uma nova folha a arvore
    if (arvore==NULL){   //se a arvore é nula retorna a folha
        return folha;
    }else{
        if (folha->dado < arvore->dado){   ///se o novo no é maior que o nó raiz ele vai para esquerda
            arvore->esq = adiciona_folha(folha, arvore->esq); 
        }else{                         //// se o novo no é maior que o nó raiz ele vai para a direita
            arvore->dir = adiciona_folha(folha, arvore->dir);
        } 
    }return arvore;
} 

void em_ordem(p_no raiz){    //imprime a arvore em-ordem
    if(raiz!=NULL){
        em_ordem(raiz->esq);
        printf("%s", raiz->mensagem);
        em_ordem(raiz->dir);
    }
}


p_no procurar_no (p_no raiz, int x){  ///procura um elemento de valor x na arvore e retorna seu endereço
    if(raiz==NULL || raiz->dado == x)
        return raiz;
    else if(x > raiz->dado){
        return procurar_no(raiz->dir, x);
    }else{
        return procurar_no(raiz->esq,x);
    }
}

p_no RemoveNo (p_no raiz, int x){    //remove um elemento de valor x da arvore
    if(raiz==NULL){
        return NULL;

    }else if (raiz->dado > x){
        raiz->esq = RemoveNo(raiz->esq, x);
    }else if(raiz->dado < x){
        raiz->dir = RemoveNo(raiz->dir, x);
    }else{  ///raiz->dado=x, achamos o nó a ser removido
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
           raiz->dado= aux->dado;   //vamos trocar as informações dos nós
           strcpy(raiz->mensagem, aux->mensagem);
           raiz->esq = RemoveNo(raiz->esq, aux->dado);
        }
        
    }return raiz;
}


void DestroiABB(p_no raiz){   //função que destroi a arvore binaria de busca pela raiz
    while(raiz!=NULL)
        raiz = RemoveNo(raiz, raiz->dado);
}

void troca (p_no *x, p_no *y){   //troca o valor dos ponteiros
    p_no aux = *x;
    *x = *y;
    *y = aux;
}

p_no uniao_de_nos(p_no raiz, p_no A, p_no B, p_no C){   ///funçao que vai concatenar os nós da triade
   // vamos ordenar os ponteiros de forma que A é o menor, B é o do meio, C é o maior
    if(B->dado<A->dado){
        troca(&A, &B);
    }if(B->dado>C->dado){
        troca(&B, &C);
    }if(A->dado>C->dado){
        troca(&A, &C);
    }if(B->dado<A->dado){
        troca(&A, &B);
    }
    // vamos guardar o valor numerico dos ponteiros

    int a_valor=A->dado; 
    int b_valor=B->dado; 
    int c_valor=C->dado; 

    /// vamos criar um novo nó "aux" cujo valor será a soma dos valores de A, B e C
    p_no aux = criar_arvore(a_valor + b_valor + c_valor, "");
    
    strcpy(aux->mensagem, A->mensagem);   // vamos concatenar as mensagens de A, B e C em aux
    strcat(aux->mensagem, B->mensagem);
    strcat(aux->mensagem, C->mensagem);

    raiz = RemoveNo(raiz, a_valor); /// vamos remover triade (A, B e C) da arvore
    raiz = RemoveNo(raiz, b_valor);
    raiz = RemoveNo(raiz, c_valor);

    raiz = adiciona_folha(aux, raiz); /// vamos adicionar aux(junção da triade) na arvore     
    
    return raiz;
}

p_no procura_C(p_no raiz, p_no A, p_no B, int p){  ///função que vai procurar o terceiro elemento da triade, quando o achar ja faz a concatenação
    p_no C;
    int x;
    x = p - A->dado - B->dado;
    C = procurar_no(raiz, x);
    if(C!=NULL){  // se achamos C ja faremos a junção da triade na arvore
        if(C!=A && C!=B){
            C = uniao_de_nos(raiz, A, B, C);
        }else{
            C = NULL;
        }
    }
    return C;
}

p_no procura_B(p_no raiz, p_no A, p_no B, int p){   //função que vai procurar o segundo elemento da triade
    p_no C=NULL;
    if (B!=A){
        C = procura_C(raiz, A, B, p);
    }if (C==NULL && B->esq!=NULL){
        C = procura_B(raiz, A, B->esq, p);
    }if(C==NULL && B->dir!=NULL){
         C= procura_B(raiz, A, B->dir, p);
    
    }return C;
}

p_no procura_A(p_no raiz, p_no A, p_no B, int p){  //função que vai procurar o primeiro elemento da triade
    p_no C=NULL;
    C = procura_B(raiz, A, B, p);
    if (C==NULL && A->esq!=NULL){
        C = procura_A(raiz, A->esq, B, p);
    }if (C==NULL && A->dir!=NULL){
        C= procura_A(raiz, A->dir, B, p);
    }return C;
}

p_no procura_triade(p_no raiz, int p){    //função que vai procurar os nós A, B, C que somados resultam em p, a função ja irá retornar a arvore com a junção da triade
    p_no A, B;
    A = raiz;
    B= raiz;
    raiz = procura_A(raiz, A, B, p);
    return raiz;
}

int main(){
    int m, n; 

    ///começamos a construir a arvore
    while( scanf("%d %d", &m, &n)!=EOF){  //laço que verificará o final do arquivo de entrada
        int p;
        int x;
        char mensagem[10000];
        p_no arvore, folha; 
        scanf("%d", &x);

        do{
            scanf("%c", &mensagem[0]);   //pula os espaços em branco entre as entradas
        }while(mensagem[0]==' '); 

        do{
            scanf("%c", &mensagem[0]);   //pula as aspas iniciais da string
        }while(mensagem[0]=='"');

        for(int i=1; mensagem[i-1]!='"'; i++)  
            scanf("%c", &mensagem[i]);

        int t=0;
        while(mensagem[t]!='"')   //exclui as aspas finais da string
            t++;
        mensagem[t]='\0';

        arvore = criar_arvore(x, mensagem); 

        /// criamos a raiz da arvore agora vamos adicionar as folhas
        for(int i=1; i<m; i++){
            char mensagem[10000] = {};

            scanf("%d", &x);

            do{
                scanf("%c", &mensagem[0]);     //pula os espaços em branco entre as entradas
            }while(mensagem[0]!='"');

            scanf("%c", &mensagem[0]);         //exclui as aspas iniciais da string

            for(int i=1; mensagem[i-1]!='"'; i++)   //faz a leitura da string
                scanf("%c", &mensagem[i]);

            int t=0;
            while(mensagem[t]!='"')   //exclui as aspas finais da string
                t++;
            mensagem[t]='\0';

            folha = criar_arvore(x, mensagem);   //cria um nó com os valores de x e mensagem
            arvore = adiciona_folha(folha, arvore);  //adiciona o nó na arvore
        }

        //faz a junção da triade para quantas autoridades de valor p tiverem
        for(int i=0; i<n; i++){
            scanf("%d", &p);
            arvore = procura_triade(arvore, p);
        }
        em_ordem(arvore);
        printf("\n");

        DestroiABB(arvore);
    }
    return 0;
}