#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct pilha{
    int v;
    char sinal[2];
    struct pilha *prox;
}Pilha;

typedef Pilha *p_pilha;

typedef struct no{
    int l, c;
    struct no *prox;
}no;

typedef no *p_no;

typedef struct{
    int valor;
    char expressao[100];
    p_no dependentes;
}vertice;

typedef struct{
    vertice **adj;
    int linha, coluna;
}Grafo;

typedef Grafo *p_grafo;

p_pilha criar_pilha(){
    return NULL;
}

p_pilha empilhar(p_pilha p, int valor, const char * str){
    p_pilha n = malloc(sizeof(Pilha));
    n->v = valor;
    strcpy(n->sinal, str);
    n->prox= p;
    p = n;
    return p;
}

void desempilhar(p_pilha p){
    p_pilha topo = p;
    p = p->prox;
    free(topo);
}

p_no criar_lista(){
    return NULL;
}

void destruir_lista( p_no lista){         // desaloca a lista
    if (lista!=NULL){
        destruir_lista(lista->prox);
        free(lista);
    }
}

p_no insere_lista(p_no lista, int l, int c){         //adiciona elemento na lista (no começo)
    p_no novo;
    novo = malloc(sizeof(no));
    novo->l = l;
    novo->c = c;
    novo->prox = lista;
    return novo;
}

p_grafo criar_grafo(int l, int c){  //função que aloca memória para o grafo
    p_grafo g = malloc (sizeof(Grafo)); //aloca uma estrutura do tamanho Grafo
    g->adj = calloc (l, sizeof(vertice *)); ///aloca um vetor de ponteiros pros vertices
    for(int i=0; i<l; i++){
        g->adj[i]= calloc(c, sizeof(vertice)); //aloca um vetor do tipo vertice dentro dos outros vetores
        
        for (int j=0; j<c; j++)
            g->adj[i][j].dependentes = criar_lista();
        
    }
    g->coluna=0;
    g->linha=0;
    return g;
}

void destroi_grafo(p_grafo g, int l, int c){ //funçao que desaloca o grafo da memória
    for(int i=0; i < l; i++){ //primeiro a matriz
        for (int j=0; j<c; j++)
            destruir_lista(g->adj[i][j].dependentes); 

        free(g->adj[i]);
    }
    free(g->adj);
    free(g); //depois o grafo
}

vertice *le_coordenadas(p_grafo g, char str[]){
    int coluna = str[0] - 'A';
    long int linha = strtol(&str[1], NULL,10) - 1;
    
    return &g->adj[linha][coluna];
}

void insere_vertice (p_grafo g, int valor, char expressao[], int l, int c){
    int linha = g->linha;
    int coluna = g->coluna;
    int i=0;
    vertice *aux;
    
    if (expressao[0]!=33){
        while(i < strlen(expressao)){
            if(expressao[i]!='('){
                if (expressao[i]!=')'){
                    if(expressao[i]!='+'){
                        if(expressao[i]!='-'){
                            aux = le_coordenadas(g, &expressao[i]);  //aux recebe o endereço do vertice que a expressao está referenciando em suas coordenadas
                            aux->dependentes = insere_lista(aux->dependentes, linha, coluna); ///os dependentes desse vertice recebe o elemento atual
                        }
                    }
                }
            }
            i += strlen(&expressao[i]);
        }
    }
    strcpy(g->adj[linha][coluna].expressao, expressao);

    g->adj[linha][coluna].valor = valor;
    g->coluna++;

    if (g->coluna==c){
        g->coluna=0;
        g->linha++;
    }
}

int calcula_expressao (vertice * v, p_grafo g, p_pilha p){
    int i=0;
    vertice *aux;
    int op1, op2;
    int t;
    char sinal;

    if (v->expressao[0]==33){
        return v->valor;
    }

    while(i < strlen(v->expressao)){

        if(strcmp(&v->expressao[i], "(")==0){

        }else if (strcmp(&v->expressao[i], ")")==0){
            op2 = p->v;
            desempilhar(p);
            sinal = p->sinal[0];
            desempilhar(p);
            op1 = p->v;
            desempilhar(p);

            if (sinal =='+')
                op1= op1 + op2; 
            else
                op1 = op1 - op2;
        
            p =empilhar(p, op1, "!");
     
        }else if( strcmp(&v->expressao[i], "+")==0){
            p =empilhar(p, 0, &v->expressao[i]);
            
        }else if(strcmp(&v->expressao[i], "-")==0){
            p =empilhar(p, 0, &v->expressao[i]);

        }else{
            aux = le_coordenadas(g, &v->expressao[i]);
            t = calcula_expressao(aux, g, p);
            p =empilhar(p, t, "!");
        }                           
        i+= strlen(&v->expressao[i]);
    }
    t = p->v;
    desempilhar(p);
    return t;
}

void atualiza_dependentes(p_grafo g, vertice * v){
    p_no dependentes = v->dependentes;
    p_pilha p= criar_pilha();

    while(dependentes!=NULL){
        int i = dependentes->l;
        int j = dependentes->c;
        g->adj[i][j].valor = calcula_expressao(&g->adj[i][j], g, p);
        dependentes = dependentes->prox;
    }
    while(p!=NULL){
        desempilhar(p);
    }
}

int main(){
    char caracter;
    const char d = ' ';
    int valor;
    char str[100];
    int l, c;

    scanf("%s %d %d", str, &c, &l);
    p_grafo g =criar_grafo(l, c);

    /////////////////////////////
    FILE *planilha = fopen(str, "r");

    while (fscanf(planilha, "%c", &caracter) != EOF){
        char r[100];
        char *expressao;
        if (caracter==' '){
            fscanf(planilha, "%d", &valor);
            insere_vertice(g, valor, "!", l, c);
            fscanf(planilha, "%c", &caracter);
            fscanf(planilha, "%c", &caracter);
        }
        else if (caracter=='='){
            fscanf(planilha, "%c", &caracter);
            for(int i=0; r[i-1]!=','; i++){
                fscanf(planilha, "%c", &r[i]);   
            }
            expressao = strtok(r, &d);
            insere_vertice(g, 0, expressao, l, c);               
        }
    }
    fclose(planilha);
    ////////////////////////////////////
    int aux;
    int v;
    vertice * end;
    p_pilha p = criar_pilha();
    while(scanf("%s ", str) != EOF){

        if (str[0] == 'G'){
            scanf("%s ", str);
            end = le_coordenadas(g, str);
            aux = calcula_expressao(end, g, p);
            printf("%s: %d\n", str, aux);

        }else{
            scanf("%s ", str);
            scanf("%d", &v);
            end = le_coordenadas(g, str);
            aux = end->valor;
            end->valor = v;
            printf("%s: %d -> %d\n", str, aux, end->valor);
            atualiza_dependentes(g, end);
        }
    }
    while(p!=NULL){
        desempilhar(p);
    }
    destroi_grafo(g, l, c);

    return 0;
}