#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "libpilha.h"
#define TAM 10

/* funcao que le e retorna a operacao  */
int le_operacao(void){
    int operacao;
    
    printf("\nTabela de comandos:\n");
    printf("Inserir valor: 1 | Remover valor: 2 | Mostrar elemento do topo: 3 | Mostrar numero de elementos da pilha: 4 | Imprimir pilha: 5 | Parar execução: 0\n");
    printf("Comando: ");
    scanf("%d", &operacao);

    return operacao;
}

/* funcao que executa a operacao requerida  */
void realizar_operacao(pilha_t* p, int operacao){
    int valor;
    int saida;

    /* insere o elemento */
    if (operacao == 1){
	    printf("Insira um numero na pilha: ");
	    scanf("%d", &valor);
        
        saida = push(p, valor);
        if (saida == -1)
            printf("Pilha Cheia!\n");
	    else
            printf("Número de elementos: %d\n", saida);
    } 
    /* remove elemento */
    else if (operacao == 2){
        saida = pop(p);
        if (! saida)
	        printf("Pilha Vazia!\n");
	    else 
	        printf("Elemento retirado: %d\n", saida);
    } 
    /* mostra elemento do topo  */
    else if (operacao == 3){
        printf("Elemento do topo: %d\n", pilha_topo(p));
    } 
    /* mostra numero de elementos */
    else if (operacao == 4){
        printf("Numero de elementos da pilha: %d\n", pilha_tamanho(p));
    }
    /* imprime a pilha  */
    else if (operacao == 5){
        pilha_imprime(p);
    }
    else {
        printf("Valor inválido, digite novamente!\n");
    }
    
}

int main(){
    pilha_t* p;
    int valor;
    int operacao;
    
    /* aloca e verifica falha na alocacao */
    if (! (p = pilha_cria(TAM))){
        printf("Falha na alocação da pilha!");
	    return 1;
    }

    /* inicia-se inserindo um elemento */
    printf("Insira um número na pilha: \n");
    scanf("%d", &valor);
    push(p, valor);

    operacao = le_operacao();

    while(operacao != 0){
	    realizar_operacao(p, operacao);
        operacao = le_operacao();
    }

    pilha_imprime(p);

    pilha_destroi(p);

    return 0;
}
