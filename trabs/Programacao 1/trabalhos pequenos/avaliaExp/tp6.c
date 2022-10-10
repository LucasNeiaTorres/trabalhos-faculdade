#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "libpilha.h"
#define TAM 10

int eh_abertura(char c){
	if ((c == '(') || (c == '[') || (c == '{'))
		return 1;
	return 0;
}

/* se for expressão valida retorna 1, caso contrario retorna 0 */
int verifica_expressao (char* str, pilha_t* p)
{
	int i;

	/* percorre string */
	for (i = 0; str[i+1] != '\0'; i++)
	{
		/* caso seja abertura, insere na pilha */
		if (eh_abertura(str[i])){
			push(p, str[i]);
		}

		/* caso seja fechamento, remove da pilha */
		else if (str[i] == ')'){
			if (pop(p) != '(')
				return 0;
		}
		else if (str[i] == ']'){
			if (pop(p) != '[')
				return 0;
		}
		else if (str[i] == '}'){
			if (pop(p) != '{')
				return 0;
		}
		else
			return 0;
	}

	/* se percorreu toda string, retorna 1 */
	if (pilha_vazia(p))
		return 1;
	return 0;
}

int main(){
	/* aloca string e declara pilha */
    char* str = malloc(sizeof(char)*TAM);
    pilha_t* p;
	
	fgets (str, TAM, stdin);
	
	if (! (p = inicializa_pilha(TAM))){
		printf("Falha na alocação da pilha!");
		return 1;
	}

    printf("%d\n", verifica_expressao(str, p));

	free(str);
	destroi_pilha(p);

    return 0;
}

