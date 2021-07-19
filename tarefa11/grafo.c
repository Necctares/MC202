#include "grafo.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>

Posicao novo_ponto(float x, float y)
{
    Posicao aux;
    aux.x = x;
    aux.y = y;
    return aux;
}

int distancia_min(Posicao p1, Posicao p2)
{
    double sum = pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2);
    return ceil(sqrt(sum));
}

p_grf criar_grafo(int num_vertices)
{
    p_grf aux = malloc(sizeof(Grafo));
    aux->num_vertices = num_vertices;
    aux->adjacencia = malloc(num_vertices * sizeof(int *));
    for (int i = 0; i < num_vertices; i++)
    {
        aux->adjacencia[i] = malloc(num_vertices * sizeof(int));
    }
    for (int i = 0; i < num_vertices; i++)
    {
        //Zera todas as relações de adjacencia do novo Grafo.
        for (int j = 0; j < num_vertices; j++)
        {
            aux->adjacencia[i][j] = 0;
        }
    }
    return aux;
}

void destruir_lista(p_no lista)
{
    if (lista != NULL)
    {
        destruir_lista(lista->prox);
        free(lista);
    }
    return;
}

void destruir_grafo(p_grf grafo)
{
    for (int i = 0; i < grafo->num_vertices; i++)
    {
        free(grafo->adjacencia[i]);
    }
    free(grafo->adjacencia);
    free(grafo);
    return;
}

p_no inserir(p_no lista, Posicao pos)
{
    p_no aux = malloc(sizeof(No));
    aux->pos = pos;
    aux->prox = lista;
    return aux;
}

void inserir_aresta(p_grf grafo, int v1, int v2, int peso)
{
    grafo->adjacencia[v1][v2] = peso;
    grafo->adjacencia[v2][v1] = peso;
    return;
}

//Função para auxiliar na busca do menor peso que não está na MST ainda.
int procurar_menor_peso(int *menor_peso, int *mst, int num_vertices)
{
    int vertice_minimo = -1, minimo = INT_MAX;
    //Encontra o vertice com o menor peso e que não esteja na MST.
    for (int vertice_atual = 0; vertice_atual < num_vertices; vertice_atual++)
    {
        if (mst[vertice_atual] == 0 && menor_peso[vertice_atual] < minimo)
        {
            vertice_minimo = vertice_atual;
            minimo = menor_peso[vertice_atual];
        }
    }
    //Retorna este vertice.
    return vertice_minimo;
}

//Função que retorna o maior peso entre as arestas do caminho V0 e V1 na MST.
int peso_maximo(int *pai, int **grafo, int v0, int v1)
{
    int maximo = -1;
    int aux = 0;
    while (v1 != v0)
    {
        aux = pai[v1];
        if (maximo < grafo[v1][aux])
        {
            maximo = grafo[v1][aux];
        }
        v1 = aux;
    }
    return maximo;
}

int menor_peso_max(p_grf grafo, int v0, int v1)
{
    //Vetor que armazena o pai de cada vertice contido na MST.
    int *pai = malloc(grafo->num_vertices * sizeof(int));
    //Armazena o menor peso de cada vertice.
    int *menor_peso = malloc(grafo->num_vertices * sizeof(int));
    //Armazena se o vertice está presente (1) ou não (0) na MST.
    int *mst = malloc(grafo->num_vertices * sizeof(int));

    //Checa se não houve erro na alocação.
    if (pai == NULL || menor_peso == NULL || mst == NULL)
    {
        exit(1);
    }

    //Zeramos a MST e colocamos um valor maximo para o campo menor peso.
    for (int i = 0; i < grafo->num_vertices; i++)
    {
        menor_peso[i] = INT_MAX;
        mst[i] = 0;
    }

    //Definimos o peso do Nó raiz (origem) como 0 e o pai como -1 (inexistente).
    menor_peso[0] = 0;
    pai[0] = -1;

    for (int i = 0; i < grafo->num_vertices - 1; i++)
    {
        //Pegamos o menor peso de um vertice que não está na MST.
        int aux = procurar_menor_peso(menor_peso, mst, grafo->num_vertices);
        //Colocamos este vertice na arvore (1).
        mst[aux] = 1;
        //Atualizamos os menores pesos e os pais com adjacencia ao novo vertice que ainda não estão na MST.
        for (int vertice_atual = 0; vertice_atual < grafo->num_vertices; vertice_atual++)
        {
            if (grafo->adjacencia[aux][vertice_atual] && grafo->adjacencia[aux][vertice_atual] < menor_peso[vertice_atual] && mst[vertice_atual] == 0)
            {
                pai[vertice_atual] = aux;
                menor_peso[vertice_atual] = grafo->adjacencia[aux][vertice_atual];
            }
        }
    }
    //Após construir a MST, encontramos o maior peso do caminho entre V0 e V1.
    int aux = peso_maximo(pai, grafo->adjacencia, v0, v1);
    //Libera memoria.
    free(pai);
    free(menor_peso);
    free(mst);
    return aux;
}
