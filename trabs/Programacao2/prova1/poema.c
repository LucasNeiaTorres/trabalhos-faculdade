#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#define MAX 102400
#define LINHA 5

int main(int argc, char *argv[]) {
    FILE *arquivo;
    char linha[LINHA];
    char *pt = "";
    int posicao;
    char caractere;
    char *token = " ";

    char *poema = malloc(MAX * sizeof(char));
    if(! poema) {
        perror("Erro na alocação");
        exit(1);
    }

    arquivo = fopen(argv[1], "r");
    if (! arquivo) {
        perror ("Erro ao abrir arquivo");
        exit (1);
    }
  
    while(! feof(arquivo)) {
        fread(&posicao, 3, 1, arquivo);
        fgetc (arquivo);
        caractere = fgetc (arquivo);
        poema[posicao] = caractere;
    }
    int i;
    for(i=0; i<MAX; i++) {
        if (poema[posicao])
            printf("%c", poema[i]);
    }
    printf("\n");
    fclose(arquivo);
    return 0;
}