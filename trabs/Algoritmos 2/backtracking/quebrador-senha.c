#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"
#include "quebrador-senha.h"
#define TAM 6
#define CHAR "uj2hi1d6nazmyt7vpesqr5x890wo4gb3klcf"

int quebra_senha_exaustivo(char *vetChar, int qtdeChar, char *senha, int tamSenha) {
	int i;
	/* caso base */
	if(tamSenha == TAM) {
		if(login(senha)) 
			return 1;
		return 0;
	}

	/* loop com recursao */
	for(i=0; i<=qtdeChar; i++) {
		senha[tamSenha]=vetChar[i];
		if(quebra_senha_exaustivo(vetChar,qtdeChar,senha,tamSenha+1) == 1)
			return 1;
	}
}

int quebra_senha_poda(char *vetChar, int qtdeChar, char *senha, int tamSenha, int letras, int numeros) {
	int i;
	/* caso base */
	if(tamSenha == TAM) {
		if(login(senha))
			return 1;
		return 0;
	}

	/* loop com recursao */
	for(i=0; i<=qtdeChar; i++) {
		if(vetChar[i] != '.') {

			/* adiciona caractere da senha */ 
			senha[tamSenha] = vetChar[i];
			vetChar[i]='.';
            
            /* caso seja letra e a quantidade de letras seja menor que 4 */
			if(senha[tamSenha] > 57) {
				if(letras < 4)
					if(quebra_senha_poda(vetChar,qtdeChar,senha,tamSenha+1,letras+1,numeros))
						return 1;
            /* caso seja numero e a quantidade de numeros seja menor que 4 */
			} else {
				if(numeros < 4)
					if(quebra_senha_poda(vetChar,qtdeChar,senha,tamSenha+1,letras,numeros+1))
						return 1;
			}
			/* remove caractere da senha */ 
			vetChar[i] = senha[tamSenha];
		}
	}
	return 0;
}

/* retorna 1 caso tenha encontrado a senha e 0 caso contrario */
int quebrador_senha_poda(void) {
	int qtdeChar;
	char vetChar[] = CHAR;
	qtdeChar = strlen(vetChar);
	/* preenche vetor com caracteres em ASCII (demora muito mais)
	int i, j = 0;
	for(i=48;i<=122;i++)
    {
        if(i==58)
            i=97;
        vetChar[j]=i;
        j++;
    }
	qtdeChar = j; 
	*/
	char senha[7];
	quebra_senha_poda(vetChar,qtdeChar,senha,0,0,0);
}

/* retorna 1 caso tenha encontrado a senha e 0 caso contrario */
int quebrador_senha_exaustivo(void) {
	int qtdeChar;
	char vetChar[] = CHAR;
	qtdeChar = strlen(vetChar);
	/* preenche vetor com caracteres em ASCII (demora muito mais)
	int i, j = 0;
	for(i=48;i<=122;i++)
    {
        if(i==58)
            i=97;
        vetChar[j]=i;
        j++;
    }
	qtdeChar = j; 
	*/
	char senha[7];
	quebra_senha_exaustivo(vetChar,qtdeChar,senha,0);
}
