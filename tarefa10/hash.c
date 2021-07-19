#include "hash.h"
#include <string.h>
#include <stdlib.h>

p_hash criar_hash()
{
    p_hash aux = malloc(sizeof(Hash));
    if (aux == NULL)
    {
        exit(1);
    }
    for (int i = 0; i < TAM_MAX_DIC; i++)
    {
        aux->vetor[i] = NULL;
    }
    return aux;
}

//Função para destruir uma lista ligada.
void destruir_lista(p_no lista)
{
    if (lista == NULL)
    {
        return;
    }
    destruir_lista(lista->proximo);
    free(lista);
    return;
}

void destruir_hash(p_hash h)
{
    for (int i = 0; i < TAM_MAX_DIC; i++)
    {
        destruir_lista(h->vetor[i]);
    }
    free(h);
    return;
}

//Função para calcular o hash da chave. Retorna seu valor.
int hash(char *chave)
{
    int i, n = 0;
    for (i = 0; i < strlen(chave); i++)
    {
        n = ((256 * n) + chave[i]) % TAM_MAX_DIC;
    }
    return n;
}

//Função que insere uma palavra na lista ligada correspondente ao hash.
p_no inserir_lista(p_no lista, char *chave)
{
    p_no aux = malloc(sizeof(No));
    if (aux == NULL)
    {
        exit(1);
    }
    //Copia chave para o nó auxiliar.
    strcpy(aux->palavra, chave);
    aux->proximo = lista;
    return aux;
}

void inserir(p_hash h, char *palavra)
{
    int num_hash = hash(palavra);
    h->vetor[num_hash] = inserir_lista(h->vetor[num_hash], palavra);
    return;
}

//Retorna o nó que contem a PALAVRA buscada. Caso não encontre, retorna NULL.
p_no buscar(p_hash h, char *palavra)
{
    int num_hash = hash(palavra);
    p_no atual;
    //Percorre a lista ligada armazenada no vetor com hash correspondente.
    for (atual = h->vetor[num_hash]; atual != NULL; atual = atual->proximo)
    {
        //Compara as palavras.
        if (strcmp(palavra, atual->palavra) == 0)
        {
            //Caso encontre, retorna o nó atual.
            return atual;
        }
    }
    //Caso contrario, retorna NULL.
    return NULL;
}

//Função para checar a diferença entre duas palavras.
int checar_palavra(char *a, char *b)
{
    //Checa se a diferença de tamanho das duas palavras é maior que 1.
    if (abs((int)strlen(a) - (int)strlen(b)) >= 2)
    {
        //Caso sim, retorna 2 (vermelho).
        return 2;
    }
    else
    {
        //Caso contrario, precisaremos comparar as duas palavras letra por letra.
        int contador = 0, contador_rem = 0;
        if (strlen(a) > strlen(b))
        {
            //Percorre as letras das duas palavras até a ultima da menor.
            for (int i = 0; i < strlen(b); i++)
            {
                if (a[i] != b[i])
                {
                    contador += 1;
                    //Checa se não é um caso de remoção de letra.
                    if (a[i + 1] == b[i])
                    {
                        contador_rem += 1;
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < strlen(a); i++)
            {
                if (a[i] != b[i])
                {
                    contador += 1;
                    if (a[i] == b[i + 1])
                    {
                        contador_rem += 1;
                    }
                }
            }
        }
        /**Caso contador seja 0, então a diferença é 1 letra.
         * Se (contador - contador_rem) == 0, então ocorreu erro de digitação de uma letra a menos.
         * Para ambos os casos precisamos retornar 1 (amarelo).*/
        if (contador == 0 || (contador - contador_rem) == 0)
        {
            return 1;
        }
        else
        {
            //Caso contrario, retornaremos o valor normal encontrado.
            return contador;
        }
    }
}

//Retorna a quantidade de erros minima da PALAVRA buscada. 1 (Amarelo), 2 (Vermelho).
int conferir_erros(p_hash h, char *palavra)
{
    p_no atual = NULL;
    //Percorre o dicionario em busca de uma palavra que contenha numero de erros 1 (Amarelo).
    for (int i = 0; i < TAM_MAX_DIC; i++)
    {
        for (atual = h->vetor[i]; atual != NULL; atual = atual->proximo)
        {
            //Caso ache, retorna 1. (Amarelo)
            if (checar_palavra(atual->palavra, palavra) < 2)
            {
                return 1;
            }
        }
    }
    //Caso contrario, retorna 2. (Vermelho)
    return 2;
}
