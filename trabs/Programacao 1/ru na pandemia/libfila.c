#include "libfila.h"
#include <stdio.h>
#include <stdlib.h>

fila_t* fila_cria() {
    /* aloca fila */
    fila_t* f = malloc(sizeof(fila_t));

    /* verifica falha de alocação */
    if (f == NULL)
        return NULL; 

    f->ini = NULL;
    f->fim = NULL;
    f->tamanho = 0;

    return f;
}

int fila_vazia (fila_t* f) { 
    if (f->tamanho == 0)
        return 1;
    return 0;
}

int fila_tamanho (fila_t* f) {
    return f->tamanho;
}

/* insere o elemento do final da fila */
int queue (fila_t* f, int elemento) {
    nodo_f_t* n;
    
    if (! (n = malloc(sizeof(nodo_f_t))))
        return 0;
    n->chave = elemento;
    n->prox = NULL;

    if (f->ini == NULL)
        f->ini = n;
    else
        f->fim->prox = n;

    f->fim = n;   
    f->tamanho++;

    return 1;
}

/* retira o elemento do inicio da fila */
int dequeue (fila_t* f, int* elemento) {
    nodo_f_t* n = f->ini;

    if (! fila_vazia(f)){
        f->ini = n->prox;
        n->prox = NULL;
        *elemento = n->chave;
        free(n);
        if (f->ini == NULL){
            f->fim = NULL;
        }
        f->tamanho--;
        return 1;
    }
    return 0;
}

void fila_imprime (fila_t* f) {
    nodo_f_t* tmp = f->ini;
    
    if (tmp) {
        while(tmp->prox != NULL) {
            printf("%d ", tmp->chave);
            tmp = tmp->prox;
        }
        printf("%d\n", tmp->chave);
    }
}

fila_t* fila_destroi (fila_t* f) {
    nodo_f_t* nodo;
    
    if (! fila_vazia(f)) {
        while (f->ini != NULL) {
            nodo = f->ini;
	        f->ini = f->ini->prox;
	        free(nodo);
        }
    }
    
    free(f);
    return f;
}