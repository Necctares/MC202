#include "abb.h"
#include <stdlib.h>

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

int ehVermelho(p_no no_atual)
{
    if (no_atual == NULL)
    {
        return 0;
    }
    return no_atual->cor == VERMELHO;
}

int ehPreto(p_no no_atual)
{
    if (no_atual == NULL)
    {
        return 1;
    }
    return no_atual->cor == PRETO;
}

p_no rotacionar_esquerda(p_no raiz)
{
    p_no aux = raiz->dir;
    raiz->dir = aux->esq;
    aux->esq = raiz;
    aux->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return aux;
}

p_no rotacionar_direita(p_no raiz)
{
    p_no aux = raiz->esq;
    raiz->esq = aux->dir;
    aux->dir = raiz;
    aux->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return aux;
}

void subir_vermelho(p_no raiz)
{
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
    return;
}

//Insere o elemento com o numero passado na arvore.
p_no inserir_elemento(p_no raiz, double numero)
{
    p_no novo;
    if (raiz == NULL)
    {
        novo = malloc(sizeof(No));
        novo->esq = novo->dir = NULL;
        novo->numero = numero;
        novo->ocorrencia = 1;
        novo->cor = VERMELHO;
        return novo;
    }
    if (numero < raiz->numero)
    {
        raiz->esq = inserir_elemento(raiz->esq, numero);
    }
    else
    {
        raiz->dir = inserir_elemento(raiz->dir, numero);
    }
    //Correção da arvore rubro negra esquerdista para que se mantenha suas propriedades.
    if (ehVermelho(raiz->dir) && ehPreto(raiz->esq))
    {
        raiz = rotacionar_esquerda(raiz);
    }
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->esq->esq))
    {
        raiz = rotacionar_direita(raiz);
    }
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->dir))
    {
        subir_vermelho(raiz);
    }
    return raiz;
}

//Busca se o numero está na arvore. Retorna NULL caso não encontre nada.
p_no buscar_numero(p_no raiz, double numero)
{
    if (raiz == NULL || numero == raiz->numero)
    {
        return raiz;
    }
    if (numero < raiz->numero)
    {
        return buscar_numero(raiz->esq, numero);
    }
    else
    {
        return buscar_numero(raiz->dir, numero);
    }
}

p_no inserir(p_no raiz, double elemento)
{
    //Checa se o numero a ser inserido já não está presente na arvore.
    p_no aux = buscar_numero(raiz, elemento);
    if (aux != NULL)
    {
        //Se sim, só acrescentamos sua ocorrencia em 1.
        aux->ocorrencia += 1;
    }
    else
    {
        //Caso contrario, inserimos em um novo nó.
        raiz = inserir_elemento(raiz, elemento);
        raiz->cor = PRETO;
    }
    return raiz;
}

int contar_ocorrencia(p_no raiz, double num_busca)
{
    p_no aux = buscar_numero(raiz, num_busca);
    if (aux != NULL)
    {
        return aux->ocorrencia;
    }
    else
    {
        return 0;
    }
}

//Função para a contagem de todos os elementos que não seguem a regra da lista legal.
void contador(p_no raiz, int *contagem)
{
    //Percorre toda a arvore.
    if (raiz->esq != NULL)
    {
        contador(raiz->esq, contagem);
    }
    if (raiz->numero != raiz->ocorrencia)
    {
        /*Caso o numero do nó atual não esteja de acordo com o criterio da lista legal,
        adicionamos a contagem de remoção.
        Checa se a ocorrencia do numero é maior que o mesmo.*/
        if (raiz->ocorrencia > raiz->numero)
        {
            //Caso sim, apenas precisaremos remover o excedente.
            *contagem += (raiz->ocorrencia - raiz->numero);
        }
        else
        {
            //Caso não, precisaremos remover todas as suas ocorrencias.
            *contagem += raiz->ocorrencia;
        }
    }
    if (raiz->dir != NULL)
    {
        contador(raiz->dir, contagem);
    }
    return;
}

int numeros_errados(p_no raiz)
{
    int contagem = 0;
    contador(raiz, &contagem);
    return contagem;
}
