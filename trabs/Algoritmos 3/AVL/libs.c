#include <stdio.h>
#include <stdlib.h>
#include "libs.h"

int nivel (tNo_t* no)
{
    int alt_esq, alt_dir;
    if(no == NULL)
        return 0;
    alt_esq = nivel(no->esq);
    alt_dir = nivel(no->dir);
    if(alt_esq > alt_dir)
        return (alt_esq + 1);
    return (alt_dir + 1);
}

int altura(tNo_t* no)
{
    if(no == NULL)
        return 0;
    return no->altura;
}

int atualiza_ft(tNo_t* no) {
    if (! no)
        return 0;
    return (altura(no->esq) - altura(no->dir));
}

tNo_t* balanceia_insercao_arvore(tNo_t* no, int chave)
{   
    no->ft_balanceamento = atualiza_ft(no);
    if (no->ft_balanceamento > 1 && chave < no->esq->chave)
        return rot_dir(no);
 
    if (no->ft_balanceamento < -1 && chave > no->dir->chave)
        return rot_esq(no);
 
    if (no->ft_balanceamento > 1 && chave > no->esq->chave)
    {
        no->esq = rot_esq(no->esq);
        return rot_dir(no);
    }

    if (no->ft_balanceamento < -1 && chave < no->dir->chave)
    {
        no->dir = rot_dir(no->dir);
        return rot_esq(no);
    }
    return no;
}

tNo_t* balanceia_remocao_arvore(tNo_t* no)
{
    no->ft_balanceamento = atualiza_ft(no);
    
    if (no->ft_balanceamento > 1 && atualiza_ft(no->esq) >= 0)
        return rot_dir(no);
 
    if (no->ft_balanceamento > 1 && atualiza_ft(no->esq) < 0)
    {
        no->esq = rot_esq(no->esq);
        return rot_dir(no);
    }
 
    if (no->ft_balanceamento < -1 && atualiza_ft(no->dir) <= 0)
        return rot_esq(no);
 
    if (no->ft_balanceamento < -1 && atualiza_ft(no->dir) > 0)
    {
        no->dir = rot_dir(no->dir);
        return rot_esq(no);
    }

    return no;
}

tNo_t* cria_no(int nova_chave) {
    tNo_t *novo_no = malloc(sizeof(tNo_t));

    novo_no->chave = nova_chave;
    novo_no->dir = NULL;
    novo_no->esq = NULL;
    novo_no->altura = 1;
    return (novo_no);
}

int max(int a, int b) {
    printf("%d | %d\n", a, b);
    //if (a >= b)
        //return a;
    //return b;
    return 1;
}

tNo_t* insere_chave(int nova_chave, tNo_t *no) {
    if(no == NULL)
        return(cria_no(nova_chave));
    
    if(nova_chave > (no->chave))
        no->dir = insere_chave(nova_chave, no->dir);
    else if (nova_chave < (no->chave))
        no->esq = insere_chave(nova_chave, no->esq);
    else
        return no;

    //no->altura;
    max(altura(no->dir), altura(no->esq));

    no->ft_balanceamento = atualiza_ft(no);
    
    no = balanceia_insercao_arvore(no, nova_chave);

    return no;   
}

tNo_t* minimo(tNo_t* no) {
    while(no->esq != NULL)
        no = no->esq;
    return no;
}

tNo_t* rot_dir(tNo_t *p) {
    tNo_t *a = p->esq;
    tNo_t *b = a->dir;

    a->dir = p;
    p->esq = b;

    if(altura(b->esq) > altura(b->dir))
        p->altura = altura(b->esq) + 1;
    else
        p->altura = altura(b->dir) + 1;

    if(altura(a->esq)>altura(a->dir))
        a->altura = altura(a->esq) + 1;
    else
        a->altura = altura(a->dir) + 1;

    return a;
}

tNo_t* rot_esq(tNo_t *p) {
    tNo_t *a = p->dir;
    tNo_t *b = a->esq;

    a->esq = p;
    p->dir = b;

    p->altura = altura(p);
    a->altura = altura(a);

    return a;
}

tNo_t* remove_chave(int chave, tNo_t *no)
{
    tNo_t *no_aux;

    if (chave < no->chave)
        no->esq = remove_chave(chave, no->esq);
    else if(chave > no->chave)
        no->dir = remove_chave(chave, no->dir);

    //testa se eh folha
    else
    {   
        if((no->esq == NULL) || (no->dir == NULL)){
            no_aux = no->esq ? no->esq : no->dir;

            if(no_aux == NULL)
            {
                no_aux = no;
                no = NULL;
            }
            else
                *no = *no_aux;
            free(no_aux);
        }
        else
        {
            no_aux = minimo(no->dir);
            no->chave = no_aux->chave;
            no->dir = remove_chave(chave, no->dir);
        }

    }

    if(no == NULL)
        return no;

    no->altura = max(altura(no->dir), altura(no->esq)) + 1;

    no = balanceia_remocao_arvore(no);

    return no;
}

void em_ordem(tNo_t *no, int alt_total) {
    if (no != NULL)
    {
        em_ordem(no->esq, alt_total);
        printf("%d, ", no->chave);
        printf("%d \n", (alt_total - nivel(no)));
        em_ordem(no->dir, alt_total);
    }
}