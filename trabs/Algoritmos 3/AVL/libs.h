#ifndef _LIBS_t_H
#define _LIBS_t_H

struct tNo
{
    int chave;
    struct tNo *esq, *dir, *pai;
    int ft_balanceamento;
    int altura;
};
typedef struct tNo tNo_t;

tNo_t* cria_no(int nova_chave);

tNo_t* insere_chave(int nova_chave, tNo_t *no);

tNo_t* remove_chave(int chave, tNo_t* no);

tNo_t* minimo(tNo_t *no);

tNo_t* rot_esq(tNo_t *p);

tNo_t* rot_dir(tNo_t *p);

void em_ordem(tNo_t *no, int alt_total);

int nivel(tNo_t *no);

int altura(tNo_t *no);

tNo_t *balanceia_insercao_arvore(tNo_t *no, int chave);

tNo_t *balanceia_remocao_arvore(tNo_t *no);

int atualiza_ft(tNo_t *no);

#endif