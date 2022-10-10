#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "liblista.h"

/* funcao que le e retorna a operacao  */
int le_operacao(void){
    int operacao;
    
    printf("\nTabela de comandos:\n");
    printf("Inserir valor no início: 1 | Inserir valor no fim: 2 | Inserir valor ordenado: 3 | Remover valor do início: 4 | Remover valor do fim: 5 | Remover elemento: 6 | Verificar pertencimento: 7 | Tamanho da lista: 8 | Imprimir lista: 9 | Parar execução: 0\n");
    printf("Comando: ");
    scanf("%d", &operacao);

    return operacao;
}

/* funcao que executa a operacao requerida  */
void realizar_operacao(lista_t* l, int operacao){
    int valor;
    int elementoRetirado = 0;

    /* insere o elemento no inicio */
    if (operacao == 1){
        printf("Insira um numero no início da lista: ");
        scanf("%d", &valor);
        if (! (lista_insere_inicio(l, valor)))
            printf("Falha!\n");
    } 
    /* insere o elemento no fim */
    else if (operacao == 2){
        printf("Insira um numero no fim da lista: ");
        scanf("%d", &valor);
        if (! (lista_insere_fim(l, valor)))
            printf("Falha!\n");
    } 
    /* insere o elemento ordenado */
    else if (operacao == 3){
        printf("Insira um numero ordenado na lista: ");
        scanf("%d", &valor);
        if (! (lista_insere_ordenado(l, valor)))
            printf("Falha!\n");
    } 
    /* remove elemento do inicio */
    else if (operacao == 4){
        if (! (lista_retira_inicio(l, &elementoRetirado)))
	        printf("Lista Vazia!\n");
	    else
	        printf("Elemento retirado: %d\n", elementoRetirado);
    }
    /* remove o elemento do fim */
    else if (operacao == 5){
        if (! (lista_retira_fim(l, &elementoRetirado)))
	        printf("Lista Vazia!\n");
	    else
	        printf("Elemento retirado: %d\n", elementoRetirado);
    }
    /* remove o elemento digitado */
    else if (operacao == 6){
        printf("Insira um numero para retirar da lista: ");
        scanf("%d", &valor);
        if (! (lista_retira_elemento(l, &valor)))
	        printf("Elemento não encontrado!\n");
    }
    /* verifica se o numero digitado pertence */
    else if (operacao == 7){
        printf("Insira um numero para verificar se pertence: ");
        scanf("%d", &valor);
        if (lista_pertence(l, valor))
	        printf("Elemento pertence à lista!\n");
        else
            printf("Elemento não pertence à lista!\n");
    }
    /* mostra tamanho da lista */
    else if (operacao == 8){
        printf("Tamanho da lista: %d\n", lista_tamanho(l));
    }
    /* imprime a lista */
    else if (operacao == 9){
        lista_imprime(l);
    }
    else {
        printf("Valor inválido, digite novamente!\n");
    }
    
}

int main(){
    lista_t* l;
    int valor;
    int operacao;
    
    /* aloca e verifica falha na alocacao */
    if (! (l = lista_cria())){
        printf("Falha na alocação da lista!");
	    return 1;
    }

    /* inicia-se inserindo um elemento */
    printf("Insira um número na lista: \n");
    scanf("%d", &valor);
    lista_insere_inicio(l, valor);

    operacao = le_operacao();

    while(operacao != 0){
	    realizar_operacao(l, operacao);
        operacao = le_operacao();
    }

    lista_imprime(l);

    lista_destroi(l);

    return 0;
}
