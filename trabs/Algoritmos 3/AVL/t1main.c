#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs.h"
#define linesize 1024

int main()
{
    char linha[linesize];
    tNo_t *raiz;
    char operacao[1];
    char *pt;
    int chave;
    int alt_total;

    fgets(linha, linesize, stdin);
    printf("%s \n", linha);

    while (!(feof(stdin)))
    {
        pt = strtok(linha, " ");
        strcpy(operacao, pt);
        printf("operacao: %s \n", operacao);
        pt = strtok(NULL, " ");
        chave = atoi(pt);
        printf("nova chave: %d \n", chave);
        
        if (!(strcmp(operacao, "i")))
        {
            raiz = insere_chave(chave, raiz);         
        }
        if(!(strcmp(operacao, "r")))
        {
            raiz = remove_chave(chave, raiz);
        }

        alt_total = nivel(raiz);
        printf("imprimir em ordem: \n");
        em_ordem(raiz, alt_total);
        printf("altura da arvore: %d \n", nivel(raiz));

        fgets(linha, linesize, stdin);
        printf("%s \n", linha);
    }

    return 0;
}