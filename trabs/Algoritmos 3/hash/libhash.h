#ifndef _LIBhash_t_H
#define _LIBhash_t_H

struct hash_cell {
    int chave;
    int excluido;
};
typedef struct hash_cell hash_cell_t;

int h1(int k);

int h2(int k);

int busca(int chave, hash_cell_t* T1, hash_cell_t* T2);

void insere_hash(int chave, hash_cell_t* T1, hash_cell_t* T2);

void remove_hash(int chave, hash_cell_t* T1, hash_cell_t* T2);

void insere_tab_ordenada(hash_cell_t* tab, hash_cell_t* TabOrd);

void imprime_tabelas(hash_cell_t* T1, hash_cell_t* T2);

#endif