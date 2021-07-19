#include <stdio.h>
#include "hash.h"
#include "string.h"
#include <stdlib.h>

#define TAM_MAX_ENTRADA 32

void processar_entrada()
{
    char entrada[TAM_MAX_ENTRADA], *separar;
    int num_dic, num_texto;

    //Pega o numero de palavras no dicionario e texto.
    fgets(entrada, 32, stdin);
    //Separa as duas variaveis.
    separar = strtok(entrada, " \n");
    num_dic = atoi(separar);
    separar = strtok(NULL, " \n");
    num_texto = atoi(separar);

    p_hash dicionario = criar_hash();
    //Insere as palavras no dicionario.
    for (int i = 0; i < num_dic; i++)
    {
        fgets(entrada, 32, stdin);
        separar = strtok(entrada, " \n");
        inserir(dicionario, separar);
    }
    //Faz a busca pelas palavras passadas se estão corretas em relação ao dicionario.
    for (int i = 0; i < num_texto; i++)
    {
        fgets(entrada, 32, stdin);
        separar = strtok(entrada, " \n");
        //Busca a palavra da entrada no dicionario.
        if (buscar(dicionario, separar) != NULL)
        {
            //Caso ache, imprime verde (correto).
            printf("verde\n");
        }
        else
        {
            //Caso contrario, faz a checagem de erros.
            if (conferir_erros(dicionario, separar) < 2)
            {
                //Se o erro for menor que 2 letras, imprime amarelo.
                printf("amarelo\n");
            }
            else
            {
                //Caso contrario, vermelho.
                printf("vermelho\n");
            }
        }
    }
    //Libera memoria.
    destruir_hash(dicionario);
    return;
}

int main()
{
    processar_entrada();
    return 0;
}