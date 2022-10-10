#include "libpilha.h"
#include <stdio.h>
#include <stdlib.h>

pilha_t* pilha_cria (int nelem) {
    /* aloca pilha */
    pilha_t* p = malloc(sizeof(pilha_t));

    /* verifica falha de alocação */
    if (p == NULL)
        return NULL; 

    /* aloca vetor */
    p->elems = malloc(nelem*sizeof(int));

    /* verifica falha de alocação */
    if (p->elems == NULL)
        return NULL; 

    p->topo = 0;
    p->nelem = nelem;

    return p;
}

int push (pilha_t* p, int elem) {
    /* verifica se a pilha esta cheia */
    if (p->topo == p->nelem) {
        return -1;
    }
    /* insere elemento no topo */
    p->elems[p->topo] = elem;
    p->topo++;

    return p->topo;
}

int pilha_vazia (pilha_t* p) {
    if (p->topo == 0)
        return 1;
    return 0;
}

int pop (pilha_t* p) {
    if (pilha_vazia(p))
        return 0;
    p->topo--;
    return p->elems[p->topo];
}

int pilha_topo (pilha_t* p) {
    return p->elems[p->topo-1];
}

int pilha_tamanho (pilha_t* p) {
    return p->topo;
}

pilha_t* pilha_destroi (pilha_t* p) {
    free(p->elems);
    free(p);

    return p;
}

void pilha_imprime (pilha_t* p) {
    if(pilha_vazia(p))
        return;
    
    int i;
    
    for(i=0; i<(p->topo)-1; i++)
    	printf("%d ", p->elems[i]);
    printf("%d\n", p->elems[i]);
}
