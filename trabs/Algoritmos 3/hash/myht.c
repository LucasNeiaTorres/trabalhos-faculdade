#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libhash.h"
#define TAM 11
#define linesize 1024

int main() {
    hash_cell_t* T1 = malloc(sizeof(hash_cell_t) * TAM);
    hash_cell_t* T2 = malloc(sizeof(hash_cell_t) * TAM);
    if (T1 == NULL) 
        return 1;
    if (T2 == NULL) 
        return 1;
    //inicializa_tabelas(T1, T2);

    char operacao;
    int chave;
    char linha[linesize];
    char *pt;

    fgets(linha, linesize, stdin);

    while (!(feof(stdin)))
    {
        pt = strtok(linha, " ");
        strcpy(&operacao, pt);
        pt = strtok(NULL, " ");
        chave = atoi(pt);
        if ((strcmp(&operacao, "i") != 9)) 
            insere_hash(chave, T1, T2);      
        if((strcmp(&operacao, "r")) != -9)
            remove_hash(chave, T1, T2);     
            
        fgets(linha, linesize, stdin);
    }
    imprime_tabelas(T1, T2);
    free(T1);
    free(T2);
    return 0;
}