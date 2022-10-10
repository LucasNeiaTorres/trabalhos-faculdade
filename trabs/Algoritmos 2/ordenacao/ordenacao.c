#include "ordenacao.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

void getNome(char nome[]){
	//substitua por seu nome
	strncpy(nome, "Lucas Néia Torres", MAX_CHAR_NOME);
	nome[MAX_CHAR_NOME-1] = '\0';//adicionada terminação manual para caso de overflow
}

unsigned int getGRR(){
	return 20210570;
}

//a função a seguir deve retornar o seu número de GRR
unsigned int getGRR();

// funcoes para a busca sequencial

int buscaSequencial2(int vetor[], int valor, int a, int b, int* numComparacoes){
	if (a > b)
		return -1;
	
	(*numComparacoes)++;

	if (valor == vetor[b])
		return b;
	
	return buscaSequencial2(vetor, valor, a, b-1, numComparacoes);
}

int buscaSequencial(int vetor[], int tam, int valor, int* numComparacoes){
	*numComparacoes = 0;
	return buscaSequencial2(vetor, valor, 0, tam-1, numComparacoes);
}

// funcoes para a busca binaria

int buscaBinaria2(int vetor[], int valor, int a, int b, int* numComparacoes){
	int m;

	if (a > b)
		return -1;
	
	m = floor((a + b)/2);
	
	(*numComparacoes)++;
	if (valor == vetor[m])
		return m;

	(*numComparacoes)++;
	if (valor < vetor[m])
		return buscaBinaria2(vetor, valor, a, m-1, numComparacoes);
	
	return buscaBinaria2(vetor, valor, m+1, b, numComparacoes);
}

int buscaBinaria(int vetor[], int tam, int valor, int* numComparacoes){
	*numComparacoes = 0;
	return buscaBinaria2(vetor, valor, 0, tam-1, numComparacoes);
}

// funcoes para o insertion sort

void troca(int vetor[], int a, int b){
	int x;
	x = vetor[a];
	vetor[a] = vetor[b];
	vetor[b] = x;
}

int buscaOrdenado(int vetor[], int valor, int a, int b, int* numComparacoes){
	if (a > b)
		return a-1;

	(*numComparacoes)++;
	if (valor >= vetor[b])
		return b;

	return buscaOrdenado(vetor, valor, a, b-1, numComparacoes);
}

int insere(int vetor[], int a, int b, int* numComparacoes){
	int p, i;

	p = buscaOrdenado(vetor, vetor[b], a, b-1, numComparacoes);
	i = b;
	
	while (i > p + 1){
		troca(vetor, i, i-1);
		i--;
	}

	return *numComparacoes;
}

int insertionSort2(int vetor[], int a, int b){
        int numComparacoes = 0;

	if (a>=b)
		return 0;
      
	return insertionSort2(vetor, a, b-1) + insere(vetor, a, b, &numComparacoes);
}

int insertionSort(int vetor[], int tam){	
	return insertionSort2(vetor, 0, tam-1);
}

// funcoes para o selection sort

int minimo(int vetor[], int a, int b, int* numComparacoes){
	int i = a;
	int m = i;

	while (i < b){
		i++;
		(*numComparacoes)++;
		if (vetor[i] < vetor[m])
			m = i;
	}

	return m;
}

int selectionSort2(int vetor[], int a, int b){
    int numComparacoes = 0;

	if (a >= b)
		return 0;
	troca(vetor, a, minimo(vetor, a, b, &numComparacoes));
	
	return numComparacoes + selectionSort2(vetor, a+1, b);
}

int selectionSort(int vetor[], int tam){
	return selectionSort2(vetor, 0, tam-1);
}

// funcoes para o merge sort

void coloca_vetor(int va[], int vb[], int a, int b){
	int i, j;
	j = 0;
	for(i=a; i<=b; i++){
		va[i] = vb[j]; 
		j++;
	}
}

int intercala(int vetor[], int a, int m, int b){
	int i, j, k;
       	int numComparacoes = 0;
	int vetor2[b-a];

	if (a >= b)
		return 0;
	i = a;
	j = m + 1;
	for(k=0; k<=b-a; k++){
		numComparacoes++;
		if ((j>b) || (i<=m && vetor[i]<=vetor[j])){
			vetor2[k] = vetor[i];
			i++;
		} else {
			vetor2[k] = vetor[j];
			j++;
		}
	}	
	coloca_vetor(vetor, vetor2, a, b);

	return numComparacoes;
}

int mergeSort2(int vetor[], int a, int b){
	int m;

	if (a>=b)
		return 0;
	
	m = floor((a+b)/2);
	
	return mergeSort2(vetor, a, m) + mergeSort2(vetor, m+1, b) + intercala(vetor, a, m, b);
}

int mergeSort(int vetor[], int tam){
	return mergeSort2(vetor, 0, tam-1);
}

// funcoes para o quick sort

int particiona(int vetor[], int a, int b, int x, int* numComparacoes){
	int i;
	int m = a - 1;	

	for(i=a; i<=b; i++){
		(*numComparacoes)++;
		if (vetor[i] <= x){
			m++;
			troca(vetor, m, i);
		}
	}
	return m;
}

int quickSort2(int vetor[], int a, int b){
	int m;
	int numComparacoes = 0;

	if (a>=b)
		return 0;
	
	m = particiona(vetor, a, b, vetor[b], &numComparacoes);
	
	return numComparacoes + quickSort2(vetor, a, m-1) + quickSort2(vetor, m+1, b);
}

int quickSort(int vetor[], int tam){
	return quickSort2(vetor, 0, tam-1);
}

