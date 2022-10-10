#include <stdio.h>
#include <stdlib.h>

#define TAM 200

/* calcula tamanho do vetor */
int tam_vetores (int vet[])
{
   int len = 0;
   while (vet[len]!=-1) 
	   len++;
   return len;
}

int *une_vetores (int vet1[], int vet2[])
{
    int *vetor, i;
    int tam1=0, tam2=0;
    int tam;
    
    /* recebe tamanho dos vetores e calcula o do vetor final  */
    tam1 = tam_vetores(vet1);
    tam2 = tam_vetores(vet2);
    tam = tam1+tam2+1;

    /* alocando e verificando */
    if ( !(vetor = malloc (sizeof(int)*tam)) )
        return vetor;

    /* inserindo vetor 1 e vetor 2 no vetor final  */
    for (i=0; i<tam1; i++)
        *(vetor+i) = vet1[i];

    for (i=tam1; i<tam; i++)
        *(vetor+i) = vet2[i-tam1];

    return vetor;
}

void imprime_vetor (int *vetor)
{
    int i=0;
    while (vetor[i] != -1){
        printf("%d ", vetor[i]);
	i++;
    }
    printf("\n");
}

void libera_vetor(int **vet)
{
    free(*vet);
    *vet = NULL;
}

int ler_vetor(int *vetor)
{
    int i = 0;

    while ((scanf("%d", &vetor[i])) && (i < TAM) && (vetor[i] != -1))
        i++;

    return *vetor;
}

int main ()
{
    int vet1[TAM];
    int vet2[TAM];    
    int *vetor_final;

    ler_vetor(vet1);
    ler_vetor(vet2);
   
    vetor_final = une_vetores(vet1, vet2); 
    imprime_vetor(vetor_final);
    
    libera_vetor(&vetor_final);
    
    return 0;
}

