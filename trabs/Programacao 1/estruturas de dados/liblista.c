#include "liblista.h"
#include <stdio.h>
#include <stdlib.h>

lista_t* lista_cria() {
    /* aloca lista */
    lista_t* l = malloc(sizeof(lista_t));

    /* verifica falha de alocação */
    if (l == NULL)
        return NULL; 

    l->ini = NULL;
    l->tamanho = 0;

    return l;
}

int lista_vazia(lista_t* l) {
    if (l->tamanho == 0)
        return 1;
    return 0;
}

int lista_tamanho(lista_t* l) {
    return l->tamanho;
}

int lista_insere_inicio(lista_t* l, int elemento) {
    nodo_l_t* n;
    if( ! (n = malloc(sizeof(nodo_l_t))))
        return 0;
    n->elemento = elemento;
    n->prox = NULL;

    if (! (lista_vazia(l)))
        n->prox = l->ini;
    l->ini = n;
    l->tamanho++;

    return 1;
}

int lista_insere_fim (lista_t* l, int elemento) {
    nodo_l_t* n;
    nodo_l_t* aux;

    if (lista_vazia(l)) {
        lista_insere_inicio(l, elemento);
        return 1;
    }
    
    if (! (n = malloc(sizeof(nodo_l_t))))
        return 0;
    n->elemento = elemento;
    n->prox = NULL;

    l->tamanho++;
    aux = l->ini;
    /* encontra ultimo elemento e adiciona n a ele */
    while (aux->prox != NULL) 
        aux = aux->prox;

    aux->prox = n;   

    return 1;
}

int lista_insere_ordenado (lista_t* l, int elemento) {
    nodo_l_t* n;
    nodo_l_t* aux;

    aux = l->ini;
    if (lista_vazia(l) || (elemento <= l->ini->elemento)) {
        lista_insere_inicio(l, elemento);
        return 1;
    }
    if (! (n = malloc(sizeof(nodo_l_t))))
        return 0;
    n->elemento = elemento;

    aux = l->ini;
    /* encontra numero maior que o elemento ou o final da fila */
    /* para no nodo anterior ao elemento maior */
    while ((aux->prox != NULL) && (elemento > aux->prox->elemento))
        aux = aux->prox;

    n->prox = aux->prox;
    aux->prox = n;   
    l->tamanho++;

    return 1;
}

int lista_retira_inicio (lista_t* l, int* elemento) {
    nodo_l_t* n = l->ini;

    if (lista_vazia(l))
        return 0;

    l->ini = n->prox;
    n->prox = NULL;
    *elemento = n->elemento;
    free(n);
    l->tamanho--;
    
    return 1;
}

int lista_retira_fim (lista_t* l, int* elemento) {
    if (lista_vazia(l))
        return 0;

    nodo_l_t* aux = l->ini;
    
    /* verifica se a lista tem apenas um elemento */
    if (aux->prox) {
        nodo_l_t* ultimo;
        
        /* encontra ultimo elemento */
        while (aux->prox->prox) 
            aux = aux->prox;
        ultimo = aux->prox;
        *elemento = ultimo->elemento;
        aux->prox = NULL;
        aux = ultimo;
    } else {
        *elemento = aux->elemento;
        l->ini = NULL;
    }

    free(aux);
    l->tamanho--;

    return 1;
}

int lista_retira_elemento (lista_t* l, int* elemento) {
    if (lista_vazia(l))
        return 0;

    nodo_l_t* aux = l->ini;
    nodo_l_t* nodo_elem;

    if(l->ini->elemento == *elemento)
        return (lista_retira_inicio(l, elemento));
    
    /* procura elemento na lista e para no nodo anterior*/
    while (aux->prox) {
        if (aux->prox->elemento == *elemento) {
            if (! (aux->prox->prox))
                return (lista_retira_fim(l, elemento));
            nodo_elem = aux->prox;
            aux->prox = aux->prox->prox;
            aux = aux->prox;
                
            free(nodo_elem);
            l->tamanho--;
                
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

int lista_pertence (lista_t* l, int elemento) {
    if (lista_vazia(l))
        return 0;
    
    nodo_l_t* aux = l->ini;

    while (aux->prox){
        if (aux->elemento == elemento)
            return 1;
        aux = aux->prox;
    }
    return 0;
}


void lista_imprime (lista_t* l) {
    nodo_l_t* tmp = l->ini;
    
    if (tmp) {
        while(tmp->prox != NULL) {
            printf("%d ", tmp->elemento);
            tmp = tmp->prox;
        }
        printf("%d\n", tmp->elemento);
    }
}

lista_t* lista_destroi (lista_t* l) {
    nodo_l_t* nodo;
    
    if (! lista_vazia(l)) {
        while (l->ini != NULL) {
            nodo = l->ini;
	        l->ini = l->ini->prox;
	        free(nodo);
        }
    }
    
    free(l);
    return l;
}