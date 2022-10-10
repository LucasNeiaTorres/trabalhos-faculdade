#include "libpilha.h"
#include <stdio.h>
#include <stdlib.h>

pilha_t* inicializa_pilha(int nelem){
    /* aloca pilha */
    pilha_t* p = malloc(sizeof(pilha_t));

    /* verifica falha de alocação */
    if (p == NULL)
        return NULL; 

    /* aloca vetor */
    p->elems = malloc(nelem*sizeof(char));

    /* verifica falha de alocação */
    if (p->elems == NULL)
        return NULL; 

    p->topo = 0;
    p->nelem = nelem;

    return p;
}

int push(pilha_t* p, char elem){
    /* verifica se a pilha esta cheia */
    if(p->topo == p->nelem){
        return -1;
    }
    /* insere elemento no topo */
    p->elems[p->topo] = elem;
    p->topo++;

    return p->topo;
}

int pilha_vazia(pilha_t* p){
    if(p->topo == 0)
        return 1;
    return 0;
}

char pop(pilha_t* p){
    if(pilha_vazia(p))
        return 0;
    p->topo--;
    return p->elems[p->topo];
}

char topo(pilha_t* p){
    return p->elems[p->topo-1];
}

void destroi_pilha(pilha_t* p){
    free(p->elems);
    free(p);
}