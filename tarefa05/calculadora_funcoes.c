#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>

p_no criar_lista(){
    return NULL;
}

void destruir_lista( p_no lista){         // desaloca a lista
    if (lista!=NULL){
        destruir_lista(lista->prox);
        free(lista);
    }
}

p_no adicionar_elemento(p_no lista, int x){         //adiciona elemento na lista (no começo)
    p_no novo;
    novo = malloc(sizeof(no));
    novo -> dado = x;
    novo -> prox = lista;
    return novo;
}

void imprime(p_no lista){     //imprime do começo para o fim da lista
    if (lista!=NULL){
        printf("%d", lista->dado);
        imprime(lista->prox);
    }
}

void imprime_lista(p_no lista){     //// função de imprimir que analisa se há zeros no começo da lista
    if (lista!=NULL){
        if (lista->dado != 0){ ////// se o elemento mais significativo for !=0, imprime a lista normal
            imprime(lista);   //// chama outra função para imprimir que imprime do começo para o fim da lista
        }else{
            while(lista->dado==0 && lista->prox!=NULL){
                lista = lista->prox;                    /// enquanto houver zeros à esquerda, a lista avança
            }
            if (lista->prox==NULL){ //// se todos os elementos forem iguais a zero então imprime um unico zero
                printf("0");
            }else{
                imprime(lista); ///// se houver um numero na lista !=0 mas com uma quantidade de zeros à esquerda, ele irá imprimi-lo normal sem os zeros do começo (00012 = 12)
            }    
        } printf("\n");
    }
}

p_no inverter_lista(p_no lista){           // inverte a ordem dos elementos da lista
    p_no atual, ant, invertida = NULL;
    atual = lista;
    while (atual!=NULL){
        ant = atual;
        atual = ant->prox;
        ant->prox = invertida;
        invertida = ant;
    }
    return invertida;
}

p_no quem_eh_maior (p_no numero1, p_no numero2){ /// função que analisa quem eh maior pelo tamanho das listas, se ambas tiverem o mesmo tamanho começa a analisar quem é maior pelos algarismos mais significativos
    p_no op1 = numero1;
    p_no op2 = numero2;
    
    do{
        op1 = op1->prox;
        op2 = op2->prox;
    }while (op1 != NULL && op2 != NULL);

    if (op1 == NULL && op2 != NULL){
        return numero2;
    }else if (op1 != NULL && op2 == NULL){
        return numero1;
    }else if (op1 == NULL && op2 == NULL){      //ambos vetores tem mesmo tamanho
        op1 = numero1;
        op2 = numero2;
        while (op1!= NULL){
            if (op1->dado > op2->dado){
                return numero1;
            }else if (op1->dado < op2->dado){
                return numero2;
            }else{                          // se os algarismos forem iguais, passa para o proximo algarismo
                op1 = op1->prox;
                op2 = op2->prox;
            }
        }
    } return numero1;
} 

p_no adc(p_no operando1, p_no operando2, p_no resultado, int carry){
    int soma = 0;
    if (operando1!= NULL && operando2!=NULL){
        soma = (operando1->dado + operando2-> dado + carry);
        carry = 0;         // apos somar o carry ele é zerado
        if (soma>=10){
            soma -= 10;
            carry = 1;     /// "sobe um" se a soma for maior que 10
        }
        resultado = adicionar_elemento(resultado, soma);    // adiciona o algarismo resultante na lista do resultado
        resultado = adc(operando1->prox, operando2->prox, resultado, carry);   // passa para a soma dos proximos algarismos recursivamente
        return resultado;
    }else if (operando2==NULL && operando1!=NULL){
        soma = (operando1->dado +carry);
        carry = 0;
        if (soma>=10){
            soma -= 10;
            carry = 1;
        }
        resultado = adicionar_elemento(resultado, soma);
        resultado = adc(operando1->prox, operando2, resultado, carry);
        return resultado;
    }else if (operando1==NULL && operando2!=NULL){
        soma = (operando2->dado +carry);
        carry = 0;
        if (soma>=10){
            soma -= 10;
            carry = 1;
        }
        resultado = adicionar_elemento(resultado, soma);
        resultado = adc(operando1, operando2->prox, resultado, carry);
        return resultado;
    }else if (operando1==NULL && operando2==NULL){    
        if (carry == 1){   /// caso em que chegamos ao final das listas mas sobrou um carry
            soma = (carry);
            resultado = adicionar_elemento(resultado, soma);
            return resultado;
        }
    }return resultado;   
}

p_no sub(p_no operando1, p_no operando2, p_no resultado, int carry){
    int soma = 0;
    if (operando1!= NULL && operando2!=NULL){
        soma = (operando1->dado - operando2-> dado + carry);
        carry = 0;       
        if (soma<0){
            soma += 10;
            carry = -1;    /// "empresta um" se a subtracao der negativo
        }
        resultado = adicionar_elemento(resultado, soma);    // adiciona o algarismo resultante na lista do resultado
        resultado = sub(operando1->prox, operando2->prox, resultado, carry); /// passa para a subtracao do proximo algarismo, recursivamente
        return resultado;
    }else if (operando2==NULL && operando1!=NULL){
        soma = (operando1->dado + carry);
        carry = 0;
        if (soma<0){
            soma += 10;
            carry = -1;
        }
        resultado = adicionar_elemento(resultado, soma);
        resultado = sub(operando1->prox, operando2, resultado, carry);
        return resultado;
    }else if (operando1==NULL && operando2!=NULL){
        soma = (operando2->dado +carry);
        carry = 0;
        if (soma<0){
            soma += 10;
            carry = -1;
        }
        resultado = adicionar_elemento(resultado, soma);
        resultado = sub(operando1, operando2->prox, resultado, carry);
        return resultado;
    }else if (operando1==NULL && operando2==NULL){
        if (carry == -1){
            soma = (carry);
            resultado = adicionar_elemento(resultado, soma);
            return resultado;
        }
    }return resultado;

}

p_no multp(p_no numero1, p_no numero2, p_no resultado, int carry){
    int soma = 0, pula_ncasas = 0;
    p_no operando1 = numero1;    // variavel auxiliar para rodar a lista sem perder seu começo
    p_no operando2 = numero2;
    
    if (operando1!= NULL && operando2!=NULL){                           //// vai realizar a multiplicação do operando1 pelo algarismo menos significativo do operando2 e vai gerar a lista resultado
        while (operando1!=NULL){
            soma = (operando1->dado * operando2->dado) + carry;
            carry = 0;
            while (soma>=10){
                soma -= 10;
                carry += 1;
            }
            resultado = adicionar_elemento(resultado, soma);
            soma = 0;
            operando1 = operando1->prox;
        }
        if (carry !=0){     //// caso em que sobra um carry depois de terminada as somas
            resultado = adicionar_elemento(resultado, carry);          /// resultado da primeira multiplicação -- o algarismo mais siginificativo está no começo da lista
            carry = 0;
       }                              
    }
    
    if (operando2->prox == NULL){
        return resultado;
    }

    pula_ncasas +=1;                     /// pula uma casa para iniciar a proxima multiplicação
    operando2 = operando2->prox;
    operando1 = numero1;
    resultado = inverter_lista(resultado);      ///// inverte o resultado de forma que o primeiro elemento da lista seja o algarismo menos significativo
    p_no resultado_temporario = resultado;     //// variavel auxiliar que vai ser usada para somar ao resultado anterior e para percorrer todos os elementos da lista "resultado" sem perder o começo da lista

    while (operando2!=NULL){  
        
        for (int i=0; i<pula_ncasas; i++){      //// pula as casas necessarias para iniciar a nova multiplicação
            if (resultado_temporario->prox == NULL){
                resultado_temporario = inverter_lista(resultado_temporario);
                resultado_temporario = adicionar_elemento(resultado_temporario, 0);   //// adiciona elemento novo na lista quando nao ha mais casas existentes, mas como o algarismo mais significativo está no final, invertemos a lista para que ele fique no começo e possamos usar a função adiciona_elemento()
                resultado_temporario = inverter_lista(resultado_temporario);
            }
            resultado_temporario = resultado_temporario->prox;
        }

        while (operando1!=NULL){
            soma = (operando1->dado * operando2->dado) + carry;   // realiza a multiplicação normal
            soma += resultado_temporario->dado;    // soma ao resultado da multiplicação anterior
            carry = 0;
            while (soma>=10){
                soma -= 10;
                carry += 1;         // calcula os carrys
            }
            resultado_temporario->dado = soma;   /// atualiza o valor depois de realizada a multiplicação
            soma = 0;
            if (resultado_temporario->prox == NULL){
                resultado_temporario = inverter_lista(resultado_temporario);
                resultado_temporario = adicionar_elemento(resultado_temporario, 0);
                resultado_temporario = inverter_lista(resultado_temporario);
            }
            resultado_temporario= resultado_temporario->prox;
            operando1 = operando1->prox;
        }
        if (carry !=0){
            resultado_temporario->dado += carry;
            carry = 0;
        } 
        resultado_temporario = resultado;  
        operando1 = numero1;
        operando2 = operando2->prox;
        pula_ncasas +=1;  
    }
    resultado = inverter_lista(resultado);  ///// inverte o resultado de forma que o primeiro elemento da lista seja o algarismo mais significativo
    return resultado;
}

//// fiz funções "casca" (adicao, subtracao, multipĺicacao, divisao) para melhorar a utilização das funções pro cliente, de forma que ele nao precise especificar carry, e tambem para melhorar a implementacao com recursao
/// as funções que realmente realizam as operaçoes sao: adc, sub, multp
/// nao implementei a operação de divisao

p_no adicao(p_no operando1, p_no operando2){
    p_no resultado=NULL;
    int carry = 0;
    resultado = adc(operando1, operando2, resultado, carry); /// chama outra função para fazer a adicao com carry (de forma que o cliente nao precise especificar carry =0)
    return resultado;   
}

p_no subtracao(p_no numero1, p_no numero2){
    int carry = 0;
    p_no resultado=NULL;
    p_no op1 = inverter_lista(numero1);   // inverte os numeros de modo que os algarismos mais significativos fiquem no começo da lista
    p_no op2 = inverter_lista(numero2);
    p_no op = quem_eh_maior(op1, op2);   // chama função para analisar qual dos dois numeros é o maior
    if (op == op1){                    // se numero1>numero2 fazemos numero1-numero2
        numero1 = inverter_lista(op1); /// inverte de novo para que o algarismo menos significativo fique no começo da lista
        numero2 =inverter_lista(op2);
        return sub(numero1, numero2, resultado, carry);  // chama outra função para fazer a subtração com um carry
    }
    else{                               // se numero2>numero1 fazemos numero2-numero1
        numero1 = inverter_lista(op1);
        numero2 =inverter_lista(op2);
        return sub(numero2, numero1, resultado, carry);
    }
}

p_no multiplicacao(p_no numero1, p_no numero2){
    int carry = 0;
    p_no resultado = NULL;
    p_no op1 = inverter_lista(numero1);       // inverte os numeros de modo que os algarismos mais significativos fiquem no começo da lista
    p_no op2 = inverter_lista(numero2);
    p_no op = quem_eh_maior(op1, op2);            // chama função para analisar qual dos dois numeros é o maior
    if (op == op1){                               // se numero1>numero2 fazemos numero1*numero2
        numero1 = inverter_lista(op1);          /// inverte de novo para que o algarismo menos significativo fique no começo da lista
        numero2 =inverter_lista(op2);
        return multp(numero1, numero2, resultado, carry);  // chama outra função para fazer a multiplicação com um carry
    }
    else{                                           // se numero2>numero1 fazemos numero2*numero1
        numero1 = inverter_lista(op1);
        numero2 =inverter_lista(op2);
        return multp(numero2, numero1, resultado, carry);
    }
}

p_no divisao(p_no operando1, p_no operando2){
    p_no resultado = NULL;
    return resultado;
}
