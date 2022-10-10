#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "libfila.h"

/* funcao que le e retorna a operacao  */
int le_operacao(void){
    int operacao;
    
    printf("\nTabela de comandos:\n");
    printf("Inserir valor: 1 | Remover valor: 2 | Mostrar numero de elementos da fila: 3 | Imprimir fila: 4 | Parar execução: 0\n");
    printf("Comando: ");
    scanf("%d", &operacao);

    return operacao;
}

/* funcao que executa a operacao requerida  */
void realizar_operacao(fila_t* f, int operacao){
    int valor;
    int elementoRetirado = 0;

    /* insere o elemento */
    if (operacao == 1){
	    printf("Insira um numero na fila: ");
	    scanf("%d", &valor);
        if (! (queue(f, valor)))
            printf("Falha!\n");
    } 
    /* remove elemento */
    else if (operacao == 2){
        if (! (dequeue(f, &elementoRetirado)))
	        printf("Fila Vazia!\n");
	    else
	        printf("Elemento retirado: %d\n", elementoRetirado);
    }
    /* mostra numero de elementos */
    else if (operacao == 3){
        printf("Numero de elementos da fila: %d\n", fila_tamanho(f));
    }
    /* imprime a fila  */
    else if (operacao == 4){
        fila_imprime(f);
    }
    else {
        printf("Valor inválido, digite novamente!\n");
    }
    
}

int main(){
    fila_t* f;
    int valor;
    int operacao;
    
    /* aloca e verifica falha na alocacao */
    if (! (f = fila_cria())){
        printf("Falha na alocação da fila!");
	    return 1;
    }

    /* inicia-se inserindo um elemento */
    printf("Insira um número na fila: \n");
    scanf("%d", &valor);
    queue(f, valor);

    operacao = le_operacao();

    while(operacao != 0){
	    realizar_operacao(f, operacao);
        operacao = le_operacao();
    }

    fila_imprime(f);

    fila_destroi(f);

    return 0;
}
