#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define TAM_MAX_STR 1024

typedef struct {
  char palavra[TAM_MAX_STR];
} palavras_t; 

int contaLinhas(char *nomeArquivo) {
    int qtde = 0;
    char linha[TAM_MAX_STR];
    FILE* arquivo;

    arquivo = fopen(nomeArquivo, "r");

    if (!arquivo)
    {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    while (!feof(arquivo)) {
        fgets(linha, TAM_MAX_STR, arquivo);
        qtde++;
    }
    fclose(arquivo);
    return qtde;
}

palavras_t* lePalavras(char *nomeArquivo) {
    palavras_t* palavras = malloc(sizeof(palavras_t) * contaLinhas(nomeArquivo));
    FILE* arquivo;
    int index = 0;

    arquivo = fopen(nomeArquivo, "r");

    if (!arquivo)
    {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    while(! feof(arquivo)) {
        fgets(palavras[index].palavra, TAM_MAX_STR, arquivo);
        palavras[index].palavra[strlen(palavras[index].palavra)-1] = '\0';
        printf("%s\n", palavras[index].palavra);
        index++;
    }
    palavras[index].palavra[strlen(palavras[index].palavra)] = '\0';

    fclose(arquivo);
    return palavras;
}

int main(int argc, char* argv[]) {
    palavras_t* palavras = lePalavras(argv[1]);
    int indice;
    char letra[2];
    int i = 0;
    int tentativas = 0;
    int tam_palavra = 0;

    srand(clock());
    indice = random() % contaLinhas(argv[1]);
    char* palavraEscolhida = palavras[indice].palavra;
    char palavraAtual[strlen(palavraEscolhida)];

    printf("%s - %ld letras\n", palavras[indice].palavra, strlen(palavras[indice].palavra));

    tam_palavra = strlen(palavraEscolhida);
    while(i < tam_palavra) {
        palavraAtual[i] = '_';
        i++;
    }
    palavraAtual[i] = '\0'; 
    printf("%s - %ld letras\n", palavraAtual, strlen(palavraAtual));

    while(strcmp(palavraAtual, palavraEscolhida)) {
        printf("\nDigite uma letra: ");
        scanf ("%s", letra);
        int pos;
        
        for(pos=0; pos<strlen(palavraEscolhida); pos++) {
            if((palavraEscolhida[pos] == letra[0]) || (palavraEscolhida[pos] == toupper(letra[0]))) {
                palavraAtual[pos] = letra[0];
            }
        }

        printf("Palavra: ");
        int a = 0;
        while(a < strlen(palavraEscolhida)) {
            printf("%c", palavraAtual[a]);
            a++;
        }
        printf("\n");
        tentativas++;
    }
    printf("\nVocê acertou com %d tentativas\n\n", tentativas);

    free(palavras);
    return 0;
}