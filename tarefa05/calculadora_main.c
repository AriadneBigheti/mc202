#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>

p_no faz_operacao ( p_no operando1, p_no operando2, char operacao){  ///analisa qual operação vai ser realizada pelo cacractere especificado, e entao chama a função correspondente
    p_no resultado=0;
    if (operacao == '+'){
        resultado = adicao(operando1, operando2);
        return resultado;
    } else if (operacao == '-'){ 
        resultado = subtracao(operando1, operando2);
        return resultado;
    } else if (operacao == '*'){
        resultado = multiplicacao(operando1, operando2);
        return resultado;
    } else if (operacao == '/'){
        resultado = divisao(operando1, operando2);
        return resultado;
    }
    return resultado;
}

p_no le_operando(p_no operando){        // le o operando caractere a caractere e adiciona em lista ligada, o algarismo menos significativo fica no começo
    char algarismo;

    do{
        scanf("%c", &algarismo);
    } while (algarismo == ' ' || algarismo == '\n');   // para nao lermos quebras de linhas nem espaços sobrando

    while (algarismo != ' ' && algarismo!='\n'){
        algarismo -= '0';          // faz a tranformacao de caractere para o inteiro respectivo
        operando = adicionar_elemento(operando, algarismo);
        scanf("%c", &algarismo);
    } return operando;
}

int main(){
    char operacao;
    int qtd_op=1;
    p_no operando1, operando2, resultado;

    scanf("%d", &qtd_op);
    for (int i=0; i<qtd_op; i++){
        operando1 = criar_lista();
        operando2 = criar_lista();
        resultado = criar_lista();
        scanf(" %c", &operacao);
        operando1 = le_operando(operando1);
        operando2 = le_operando(operando2);
        resultado = faz_operacao (operando1, operando2, operacao);
        imprime_lista(resultado);
        destruir_lista(operando1);
        destruir_lista(operando2);
        destruir_lista(resultado);
    }
   return 0; 
}
