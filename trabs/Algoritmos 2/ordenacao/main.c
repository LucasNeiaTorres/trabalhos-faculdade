#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ordenacao.h"

void preenche_vetor(int vetor[], int tam){
    int i;
    for (i=0; i<tam; i++)
       vetor[i] = rand()%10000;
}

void imprime_vetor(int vetor[], int tam){
    int i;
    for (i=0; i<tam; i++)
       printf("%d ",vetor[i]);
    printf("\n");
}

int verifica_ordenacao(int vetor[], int tam){
    int i;
    for (i=0; i<tam-1; i++){
        if (vetor[i] > vetor[i+1]){
            return 0;
        }
    }
    return 1;
}

double tempoInsertionSort(int vetor[], int tamVetor, int* numComp, int qtTeste){
	clock_t start, end;
	double total = 0;
	int i;
	*numComp = 0;

	for(i=0; i<qtTeste; i++){
		preenche_vetor(vetor, tamVetor);
		start = clock();
		*numComp += insertionSort(vetor, tamVetor);
		end = clock();
		total += ((double)end - start)/CLOCKS_PER_SEC;
	}
	*numComp = *numComp / qtTeste; 
	total = total / qtTeste;
	return total;
}

double tempoSelectionSort(int vetor[], int tamVetor, int* numComp, int qtTeste){
	clock_t start, end;
	double total = 0;
	int i;
	*numComp = 0;

	for(i=0; i<qtTeste; i++){
		preenche_vetor(vetor, tamVetor);
		start = clock();
		*numComp += selectionSort(vetor, tamVetor);
		end = clock();
		total += ((double)end - start)/CLOCKS_PER_SEC;
	}
	*numComp = *numComp / qtTeste; 
	total = total / qtTeste;
	return total;
}

double tempoMergeSort(int vetor[], int tamVetor, int* numComp, int qtTeste){
	clock_t start, end;
	double total = 0;
	int i;
	*numComp = 0;

	for(i=0; i<qtTeste; i++){
		preenche_vetor(vetor, tamVetor);
		start = clock();
		*numComp += mergeSort(vetor, tamVetor);
		end = clock();
		total += ((double)end - start)/CLOCKS_PER_SEC;
	}
	*numComp = *numComp / qtTeste; 
	total = total / qtTeste;
	return total;
}

double tempoQuickSort(int vetor[], int tamVetor, int* numComp, int qtTeste){
	clock_t start, end;
	double total = 0;
	int i;
	*numComp = 0;

	for(i=0; i<qtTeste; i++){
		preenche_vetor(vetor, tamVetor);
		start = clock();
		*numComp += quickSort(vetor, tamVetor);
		end = clock();
		total += ((double)end - start)/CLOCKS_PER_SEC;
	}
	*numComp = *numComp / qtTeste; 
	total = total / qtTeste;
	return total;
}

int main(){
	char nome[MAX_CHAR_NOME];
	int idxBusca;
	int numComp;
	double totalSec;

	//Dica: somente ?? pos??ivel criar vetores grandes utilizando aloca????o din??mica de mem??ria
	//Veja um exemplo de aloca????o din??mica a seguir
	int tamVetor = 10000;
	int qtTeste = 1;
	int* vetor = malloc(tamVetor * sizeof(int));
	if(vetor == NULL){
		printf("Falha fatal. Imposs??vel alocar memoria.");
		return 1;
	}
	//Depois de alocado, o vetor pode ser utilizado normalmente
	//N??o esque??a de desalocar no final do programa via free

	getNome(nome);
	printf("Trabalho de %s\n", nome);
	printf("GRR %u\n", getGRR());

	printf("\n-------------------------SORTS-------------------------\n");

	totalSec = tempoInsertionSort(vetor, tamVetor, &numComp, qtTeste);

	printf("Insertion Sort: %f segundos | %d compara????es\n", totalSec, numComp);
	
	totalSec = tempoSelectionSort(vetor, tamVetor, &numComp, qtTeste);

	printf("Selection Sort: %f segundos | %d compara????es\n", totalSec, numComp);

	totalSec = tempoMergeSort(vetor, tamVetor, &numComp, qtTeste);

	printf("Merge Sort: %f segundos | %d compara????es\n", totalSec, numComp);

	totalSec = tempoQuickSort(vetor, tamVetor, &numComp, qtTeste);

	printf("Quick Sort: %f segundos | %d compara????es\n", totalSec, numComp);

	printf("\n-------------------------BUSCAS-------------------------\n");

	clock_t start, end;
    double total = 0;
    numComp = 0;

    preenche_vetor(vetor, tamVetor);
    quickSort(vetor, tamVetor);

    start = clock();
    idxBusca = buscaSequencial(vetor, tamVetor, vetor[tamVetor*4/5], &numComp);
    end = clock();
    total = ((double)end - start)/CLOCKS_PER_SEC;

    printf("Busca Sequencial - Resultado: %d?? posi????o | %d compara????es | %f segundos", idxBusca, numComp, total);

    numComp = 0;
    total = 0;

    start = clock();
    idxBusca = buscaBinaria(vetor, tamVetor, vetor[tamVetor*4/5], &numComp);
    end = clock();
    total = ((double)end - start)/CLOCKS_PER_SEC;

    printf("\nBusca Binaria - Resultado: %d?? posi????o | %d compara????es | %f segundos\n", idxBusca, numComp, total);

	//?? obrigat??rio que voc?? libere a mem??ria alocada din??micamente via free
	free(vetor);

	return 0;
}
