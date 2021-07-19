#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"

#define NUM_MAX_LUGIA 30
#define TAM_MAX_ENTRADA 128

void processar_entrada()
{
    //Variaveis para armazenar temporariamente a entrada.
    char entrada[TAM_MAX_ENTRADA], *separar;
    float x, y;
    //Armazena o numero de paradas totais e o numero de paradas com lugia.
    int num_paradas = 0, num_paradas_lugia = 0;
    //Vetor para armazenar os vertices que contem paradas com lugia.
    int lugia[NUM_MAX_LUGIA];
    //Fila para armazenar as posicoes.
    p_no posicao_paradas = NULL;

    //Pega o ponto de origem.
    fgets(entrada, TAM_MAX_ENTRADA, stdin);
    separar = strtok(entrada, " \n");
    x = atof(separar);
    separar = strtok(NULL, " \n");
    y = atof(separar);

    //Insere na fila.
    posicao_paradas = inserir(posicao_paradas, novo_ponto(x, y));

    //Processa o restante dos pontos de parada.
    while (fgets(entrada, TAM_MAX_ENTRADA, stdin) != NULL)
    {
        num_paradas += 1;

        //Separa as coordenadas.
        separar = strtok(entrada, " \n");
        x = atof(separar);
        separar = strtok(NULL, " \n");
        y = atof(separar);

        //Checa se é pokestop ou lugia.
        separar = strtok(NULL, " \n");

        if (strcmp("Lugia", separar) == 0)
        {
            //Se for lugia, guardamos a posição do vertice.
            lugia[num_paradas_lugia] = num_paradas;
            num_paradas_lugia += 1;
        }
        //Insere o ponto na fila.
        posicao_paradas = inserir(posicao_paradas, novo_ponto(x, y));
    }

    //Grafo para armazenar as posições contidas na lista.
    p_grf grafo = criar_grafo(num_paradas + 1);
    //Variavel para auxiliar na construção do grafo.
    int paradas_restantes = num_paradas;

    for (p_no atual = posicao_paradas; atual != NULL; atual = atual->prox)
    {
        //Percorremos a lista inserindo as arestas com seu respectivo peso no grafo.
        int loopi = num_paradas;
        for (p_no loop = posicao_paradas; loop != atual; loop = loop->prox)
        {
            inserir_aresta(grafo, loopi, paradas_restantes, distancia_min(loop->pos, atual->pos));
            loopi -= 1;
        }
        paradas_restantes -= 1;
    }

    //Libera a lista da memoria após seu uso.
    destruir_lista(posicao_paradas);
    //Variavel para auxiliar na busca da aresta com menor peso possivel.
    int menor_peso = INT_MAX;

    for (int i = 0; i < num_paradas_lugia; i++)
    {
        //Checamos o caminho com menor peso entre a origem (0) e todos os vertices de Lugia com uma MST.
        int aux = menor_peso_max(grafo, 0, lugia[i]);
        if (aux < menor_peso)
        {
            menor_peso = aux;
        }
    }
    //Printa o menor peso e libera o grafo da memoria.
    printf("%d\n", menor_peso);
    destruir_grafo(grafo);
    return;
}

int main()
{
    processar_entrada();
    return 0;
}