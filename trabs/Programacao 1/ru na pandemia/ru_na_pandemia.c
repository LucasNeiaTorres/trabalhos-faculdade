#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libpilha.h"
#include "libfila.h"
#include "liblista.h"
#define N_PESSOAS 1000

/* lista motivos
*
* 1: nao vacinado
* 2: sem mascara e sem dinheiro
* 3: sem mascara e acabaram
* 4: sem refeicao
*/

int aleat(int a, int b) {
    return (rand()%(b-a+1))+a;
}

typedef struct {
    double dinheiro_total;
    double renda_refeicoes;
    double renda_mascaras;
} balanco;

typedef struct {
    int ticket;
    int vacinado;
    int mascara;
    double dinheiro;
    int motivo;
} pessoas_t;

void popula(pessoas_t* pessoas, int* n_vacinados, int* n_mascaras) {
    int i;

    for(i=0; i<N_PESSOAS; i++) {
        pessoas[i].ticket = i+1;
        pessoas[i].vacinado = aleat(0,100)<96 ?  1 : 0;
        pessoas[i].mascara = aleat(0,100)<93 ?  1 : 0;
        pessoas[i].dinheiro = aleat(0,100)<60 ?  1.3 : 3.8;
        pessoas[i].motivo = 4;

        *n_vacinados += pessoas[i].vacinado;
        *n_mascaras += pessoas[i].mascara;
    }
}

void povoa_fila(fila_t* atendimentos, pessoas_t* pessoas) {
    int i;
    for(i=0; i<N_PESSOAS; i++){
        queue(atendimentos, pessoas[i].ticket);
    }
}
 
void preenche_pilha(pilha_t* pilha) {
    int i;
    for(i=1; i<=pilha->nelem; i++)
        push(pilha, i);
}

int posicao_pessoa(pessoas_t* pessoas, int ticket){
    int i;
    for(i=0; i<N_PESSOAS; i++)
        if(pessoas[i].ticket == ticket)
            return i;
    return -1;
}

int fiscal(fila_t* atendimentos, lista_t* nao_atendidos, pessoas_t* pessoas, pilha_t* mascaras, pilha_t* refeicoes, balanco* balanco_diario) {
    int elemento;
    dequeue(atendimentos, &elemento);

    if(refeicoes->topo == 0) {
        printf("Acabaram as refeicoes e todas as pessoas foram dispensadas \n");
        pessoas[elemento-1].motivo = 4;
        return 1;
    }

    printf("ticket: %d | vacinado: %d | mascara: %d | dinheiro: %f | ", pessoas[elemento-1].ticket, pessoas[elemento-1].vacinado, pessoas[elemento-1].mascara, pessoas[elemento-1].dinheiro);

    /* caso primeiro da fila nao estiver vacinado */
    if(! (pessoas[elemento-1].vacinado)) {
        printf("Nao esta vacinado \n");
        lista_insere_ordenado(nao_atendidos, elemento);
        pessoas[elemento-1].motivo = 1;
        return 0;

    /* caso primeiro da fila nao estiver de mascara */
    } else if(! (pessoas[elemento-1].mascara)) {

        /* caso esse tenha dinheiro para comprar mascara e tenha mascaras ele compra uma mascara e volta a fila*/
        if(pessoas[elemento-1].dinheiro == 3.8) {
            /* caso nao tenha mais mascaras */
            if(mascaras->topo == 0) {
                printf("Sem mascara e acabaram as mascaras \n");
                lista_insere_ordenado(nao_atendidos, elemento);
                pessoas[elemento-1].motivo = 3;
                return 0;
            }
            /* caso tenha mascara diponivel */
            printf("Sem mascara, comprou uma e retornou a fila \n");
            pessoas[elemento-1].dinheiro -= 2.5;
            pessoas[elemento-1].mascara = 1;
            pop(mascaras);
            queue(atendimentos, elemento);
            
            balanco_diario->dinheiro_total += 2.5;
            balanco_diario->renda_mascaras += 2.5;
            return 0;
        }
        /* caso esse nao tenha dinheiro ele vai a fila de nao atendidos */
        printf("Sem mascara e nao tem dinheiro para uma \n");
        lista_insere_ordenado(nao_atendidos, elemento);
        pessoas[elemento-1].motivo = 2;
        return 0;

    /* caso tenha dinheiro para a refeicao, compra, caso nao, vai para fila de nao atendidos */
    } else if(pessoas[elemento-1].dinheiro >= 1.3) {
        printf("Conseguiu comer \n");
        pessoas[elemento-1].dinheiro -= 1.3;
        pop(refeicoes);

        balanco_diario->dinheiro_total += 1.3;
        balanco_diario->renda_refeicoes += 1.3;
        pessoas[elemento-1].motivo = 0;
        return 0;
    }
    printf("Nao tem dinheiro para refeicao \n");
    lista_insere_ordenado(nao_atendidos, elemento);
    return 0;
}

void imprime_motivo(int motivo) {
    switch(motivo) {
        case 1:
            printf("nao vacinado\n");
            break;
        case 2:
            printf("sem  mascara e sem dinheiro\n");
            break;
        case 3:
            printf("sem  mascara e acabaram-as\n");
            break;
        case 4:
            printf("acabaram as refeicoes\n");
            break;
        default:
            printf("ERRO");
    }
}

void insere_sobra(lista_t* nao_atendidos, fila_t* atendimentos) {
    int elemento = 0;
    while(! fila_vazia(atendimentos)) {
        dequeue(atendimentos, &elemento);
        lista_insere_ordenado(nao_atendidos, elemento);

    }
}

void contabilidade(lista_t* nao_atendidos, pessoas_t* pessoas, balanco* balanco_diario) {
    printf("Dinheiro arrecadado no total: %f\n", balanco_diario->dinheiro_total);
    printf("Dinheiro arrecadado com as refeicoes: %f\n", balanco_diario->renda_refeicoes);
    printf("Dinheiro arrecadado com as mascaras: %f\n", balanco_diario->renda_mascaras);
    int i = 0;
    int elemento = 0;

    while(nao_atendidos->ini) {
        if(nao_atendidos->ini->elemento == pessoas[i].ticket) {
            printf("ticket %d: ", pessoas[i].ticket);
            imprime_motivo(pessoas[i].motivo);
            lista_retira_inicio(nao_atendidos, &elemento);
        }
        i++;
    }
}

int main() {
    srand(time(NULL));

    int n_vacinados = 0;
    int n_mascaras = 0;

    /* cria e inicializa o balanco diario */
    balanco* balanco_diario = malloc(sizeof(balanco));
    if(balanco_diario == NULL)
        return 1;
    balanco_diario->dinheiro_total = 0.0;
    balanco_diario->renda_refeicoes = 0.0;
    balanco_diario->renda_mascaras = 0.0;

    /* cria e preenche pilha de mascaras */
    pilha_t* mascaras = pilha_cria(aleat(1,100));
    preenche_pilha(mascaras);
    printf("Número de máscaras: %d\n", mascaras->nelem);
    
     /* cria e preenche pilha de refeicoes */
    pilha_t* refeicoes = pilha_cria(aleat(500,1000));
    preenche_pilha(refeicoes);
    printf("Número de refeições: %d\n", refeicoes->nelem);

    /* cria e preenche vetor de pessoas */
    pessoas_t* pessoas = malloc(sizeof(pessoas_t)*N_PESSOAS);
    if(pessoas == NULL)
        return 1;
    popula(pessoas, &n_vacinados, &n_mascaras);
    
    printf("Número de vacinados: %d\n", n_vacinados);
    printf("Número de pessoas com mascara: %d\n", n_mascaras);

    /* cria e preenche fila de atendimentos */
    fila_t* atendimentos = fila_cria();
    povoa_fila(atendimentos, pessoas);
    
    /* cria lista de tickets nao-atendidos */
    lista_t* nao_atendidos = lista_cria();

    while(! fila_vazia(atendimentos))
        if(fiscal(atendimentos, nao_atendidos, pessoas, mascaras, refeicoes, balanco_diario))
            break;
    insere_sobra(nao_atendidos, atendimentos);
    contabilidade(nao_atendidos, pessoas, balanco_diario);

    free(balanco_diario);
    pilha_destroi(mascaras);
    pilha_destroi(refeicoes);
    free(pessoas);
    fila_destroi(atendimentos);
    lista_destroi(nao_atendidos);
    return 0;
}