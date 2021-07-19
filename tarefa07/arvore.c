#include "arvore.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

p_no criar_arvore()
{
    return NULL;
}

//Destroi um nó.
void destruir_no(p_no no)
{
    if (no == NULL)
    {
        return;
    }
    destruir_no(no->esq);
    destruir_no(no->dir);
    free(no->texto);
    free(no);
    no = NULL;
    return;
}

void destruir_arvore(p_no raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    destruir_no(raiz);
    return;
}

p_no inserir(p_no raiz, unsigned long chave, char *texto)
{
    p_no aux;
    if (raiz == NULL)
    {
        aux = malloc(sizeof(No));
        aux->esq = aux->dir = NULL;
        aux->chave = chave;
        //Aloca espaço para o texto.
        aux->texto = malloc(sizeof(char) * (strlen(texto) + 1));
        //Copia o texto para o nó auxiliar.
        strcpy(aux->texto, texto);
        return aux;
    }
    //Checa onde irá colocar o novo nó.
    if (chave < raiz->chave)
    {
        raiz->esq = inserir(raiz->esq, chave, texto);
    }
    else
    {
        raiz->dir = inserir(raiz->dir, chave, texto);
    }
    return raiz;
}

p_no minimo(p_no raiz)
{
    if (raiz == NULL || raiz->esq == NULL)
    {
        return raiz;
    }
    return minimo(raiz->esq);
}

p_no remover(p_no raiz, unsigned long chave)
{
    if (raiz == NULL)
    {
        return raiz;
    }
    //Procura o nó com a chave correspondente.
    if (chave < raiz->chave)
    {
        raiz->esq = remover(raiz->esq, chave);
    }
    else if (chave > raiz->chave)
    {
        raiz->dir = remover(raiz->dir, chave);
    }
    else
    {
        //Checa se o nó tem no maximo 1 filho.
        if (raiz->esq == NULL)
        {
            p_no aux = raiz->dir;
            free(raiz->texto);
            free(raiz);
            return aux;
        }
        else if (raiz->dir == NULL)
        {
            p_no aux = raiz->esq;
            free(raiz->texto);
            free(raiz);
            return aux;
        }

        //Caso possua 2, precisamos pegar o menor a sua direita para substitui-lo.
        //Pega o menor nó a direita.
        p_no aux = minimo(raiz->dir);

        //Põe este nó na raiz.
        raiz->chave = aux->chave;
        free(raiz->texto);
        raiz->texto = malloc(sizeof(char) * (strlen(aux->texto) + 1));
        strcpy(raiz->texto, aux->texto);
        //Remove o nó na posição antiga.
        raiz->dir = remover(raiz->dir, aux->chave);
    }
    return raiz;
}

p_no buscar(p_no raiz, unsigned long chave)
{
    if (raiz == NULL || chave == raiz->chave)
    {
        return raiz;
    }
    if (chave < raiz->chave)
    {
        return buscar(raiz->esq, chave);
    }
    else
    {
        return buscar(raiz->dir, chave);
    }
}

int procurar_triade(p_no arv_msg, p_no *triade, p_no no_procura, unsigned long soma_cartao, int *encontrar)
{
    if (no_procura == NULL)
    {
        return 0;
    }
    //Busca um nó que complete a soma dos outros dois cartões.
    p_no aux = buscar(arv_msg, soma_cartao - no_procura->chave);
    //Caso ache, colocamos o par encontrado na triade.
    if (aux != NULL && *encontrar)
    {
        *triade = inserir(*triade, no_procura->chave, no_procura->texto);
        *triade = inserir(*triade, aux->chave, aux->texto);
        *encontrar = 0; //Seta a chave de procura para 0 (low).
        return 1;
    }
    return procurar_triade(arv_msg, triade, no_procura->dir, soma_cartao, encontrar) || procurar_triade(arv_msg, triade, no_procura->esq, soma_cartao, encontrar);
}

void pegar_triade(p_no arvore_msg, p_no *triade, p_no atual, unsigned long soma, int *encontrar)
{
    //Itera os nós da arvore de mensagem até encontrar um que satisfaça a soma da triade.
    if (atual->esq != NULL)
    {
        pegar_triade(arvore_msg, triade, atual->esq, soma, encontrar);
    }
    //Checa se o nó atual possui uma dupla que satisfaça a soma total.
    if (*encontrar && procurar_triade(arvore_msg, triade, arvore_msg, soma - atual->chave, encontrar))
    {
        //Caso encontre, insere o nó atual na triade. (O par restante já foi adicionado em procurar_triade).
        *triade = inserir(*triade, atual->chave, atual->texto);
        *encontrar = 0; //Seta a chave de busca para 0 (low).
        return;
    }

    if (atual->dir != NULL)
    {
        pegar_triade(arvore_msg, triade, atual->dir, soma, encontrar);
    }
    return;
}

//Concatena duas strings. s1 + s2 = s1s2;
char *concatenar(const char *s1, const char *s2)
{
    char *concat = malloc(strlen(s1) + strlen(s2) + 1);
    if (concat == NULL)
        exit(1);
    strcpy(concat, s1);
    strcat(concat, s2);
    return concat;
}

void triade_para_cartao(p_no *triade, p_no *arvore_msg)
{

    char *texto = ""; //Texto auxiliar para concatenar as mensagens da triade.
    char *free_temp = NULL; //Auxiliar para liberar memoria.
    unsigned long chave = 0; //UL para armazenar a soma das chaves da triade.
    p_no aux = minimo(*triade); //Pega o nó com menor chave.
    while (aux != NULL)
    {
        //Enquanto a triade não estiver vazia:
        chave += aux->chave;
        texto = concatenar(texto, aux->texto);
        free(free_temp); //Libera a posição antiga da variavel texto.
        free_temp = texto;
        *arvore_msg = remover(*arvore_msg, aux->chave); //Remove o nó atual da arvore de mensagem.
        *triade = remover(*triade, aux->chave); //Remove o nó atual da triade. 
        aux = minimo(*triade); //Busca novamente o menor nó.
    }
    //Insere um novo cartão criado apartir da triade na arvore de mensagem.
    *arvore_msg = inserir(*arvore_msg, chave, texto);
    free(texto);
    return;
}

void imprimir_ordem_crescente(p_no raiz)
{
    if (raiz != NULL)
    {
        imprimir_ordem_crescente(raiz->esq);
        printf("%s", raiz->texto);
        imprimir_ordem_crescente(raiz->dir);
    }
    return;
}