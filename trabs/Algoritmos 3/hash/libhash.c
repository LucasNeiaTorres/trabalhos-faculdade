#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libhash.h"
#define TAM 11

int h1(int k) {
    return k % TAM;
}

int h2(int k) {
    return floor(TAM * (k * 0.9 - floor(k * 0.9)));
}

int busca(int chave, hash_cell_t* T1, hash_cell_t* T2) {
    int posicao = h1(chave);
    if(T1[posicao].chave || T1[posicao].excluido){
        if(T1[posicao].chave == chave)
            return posicao;

        posicao = h2(chave);
        if(T2[posicao].chave == chave)
            return posicao;
    }
    return T1[posicao].chave;
}

void insere_hash(int chave, hash_cell_t* T1, hash_cell_t* T2) {
    int posicaoT1 = h1(chave);

    if(!T1[posicaoT1].chave || T1[posicaoT1].excluido) {
        T1[posicaoT1].chave = chave; 
        T1[posicaoT1].excluido = 0;
    }
    else {
       int posicaoT2 = h2(T1[posicaoT1].chave);
       T2[posicaoT2].chave = T1[posicaoT1].chave;
       T1[posicaoT1].chave = chave;
       T1[posicaoT1].excluido = 0;
    }
    
}

void remove_hash(int chave, hash_cell_t* T1, hash_cell_t* T2) {
    int posicaoT2 = h2(chave);
    if(T2[posicaoT2].chave == chave)
        T2[posicaoT2].chave = 0;
    else {
        int posicaoT1 = h1(chave);
        if(T1[posicaoT1].chave == chave) {
            T1[posicaoT1].chave = 0;
            T1[posicaoT1].excluido = 1;
        }
    }
}

void insere_tab_ordenada(hash_cell_t* tab, hash_cell_t* tabOrd) {
    int i, ord, anterior, aux;
    for(i=0; i<TAM; i++) {
        ord = 0;
        aux = tab[i].chave;

        while(tabOrd[ord].chave) {
            if(tabOrd[ord].chave >= aux) {
                anterior = tabOrd[ord].chave;
                tabOrd[ord].chave = aux;
                aux = anterior;
            }
            ord++;
        }
        // ultima posicao
        tabOrd[ord].chave = aux;
    }
}

void imprime_tabelas(hash_cell_t* T1, hash_cell_t* T2) {
    hash_cell_t* tabOrd = malloc(sizeof(hash_cell_t) * 2 * TAM);
    insere_tab_ordenada(T1, tabOrd);
    insere_tab_ordenada(T2, tabOrd);
    
    int i = 1;
    int posicao;
    while(tabOrd[i].chave) {
        posicao = busca(tabOrd[i].chave, T1, T2);
        if(T1[posicao].chave == tabOrd[i].chave) 
            printf("%d,T1,%d\n", tabOrd[i].chave, posicao);
        else 
            printf("%d,T2,%d\n", tabOrd[i].chave, posicao);
        
        i++;
    }
    free(tabOrd);
}