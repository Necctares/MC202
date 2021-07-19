#include <stdio.h>
#include "abb.h"
#include <stdlib.h>
#include <string.h>

#define TAM_MAX_ENTRADA 1024 * 700

void processar_entrada()
{
    int qntd_lista, num_op;
    char entrada[TAM_MAX_ENTRADA], *separar;
    p_no lista_legal = criar_arvore();

    //Pega a primeira linha com a quantidade de elementos e numero de operações.
    fgets(entrada, TAM_MAX_ENTRADA, stdin);

    //Separa as variaveis.
    separar = strtok(entrada, " ");
    qntd_lista = atoi(separar);
    separar = strtok(NULL, " ");
    num_op = atoi(separar);

    //Processa os numeros iniciais da lista.
    fgets(entrada, TAM_MAX_ENTRADA, stdin);
    int contador = 0;
    separar = strtok(entrada, " ");
    while (contador != qntd_lista)
    {
        if (separar != NULL)
        {
            lista_legal = inserir(lista_legal, atof(separar));
        }
        separar = strtok(NULL, " ");
        contador += 1;
    }

    //Processa as operações.
    contador = 0;
    while (contador != num_op)
    {
        //Pega o numero da operação.
        fgets(entrada, TAM_MAX_ENTRADA, stdin);
        separar = strtok(entrada, " ");

        //Realiza a operação requerida.
        switch (atoi(separar))
        {
        case 1:
            //Pega o numero necessario para realizar a operação.
            separar = strtok(NULL, " ");
            //Adiciona na arvore.
            lista_legal = inserir(lista_legal, atof(separar));
            qntd_lista += 1;
            break;
        case 2:
            //Pega o numero necessario para realizar a operação.
            separar = strtok(NULL, " ");
            //Devolve a quantidade de vezes que este numero aparece na lista legal.
            printf("%d\n", contar_ocorrencia(lista_legal, atof(separar)));
            break;
        case 3:
            /*Devolve a quantidade de numeros que precisam ser removidos para tornar a lista atual
            * em uma lista legal */
            printf("%d\n", numeros_errados(lista_legal));
            break;
        default:
            printf("Erro: operacao nao implementada.\n");
            break;
        }
        contador += 1;
    }
    //Limpa a memoria.
    destruir_arvore(lista_legal);
    return;
}

int main()
{
    processar_entrada();
    return 0;
}