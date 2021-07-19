#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

#define TAM_MAX_ENTRADA 1024 * 4

void processar_mensagens()
{
    char linha[TAM_MAX_ENTRADA];
    //Pega os dados do Nº de cartões/autoridades.
    while (fgets(linha, TAM_MAX_ENTRADA, stdin) != NULL)
    {
        p_no arvore_msg = criar_arvore();
        char *separar;
        unsigned long num_cartoes, num_autoridades, num_do_cartao;

        //Separa o Numero de cartões.
        separar = strtok(linha, " ");
        num_cartoes = atol(separar);
        //Separa o Numero de Autoridades.
        separar = strtok(NULL, " ");
        num_autoridades = atol(separar);

        //Pega os dados dos cartões.
        fgets(linha, TAM_MAX_ENTRADA, stdin);
        //Separa o primeiro numero de cartão.
        separar = strtok(linha, " ");
        int contador = 0;
        while (num_cartoes != contador)
        {
            num_do_cartao = atol(separar);
            //Separa o proximo texto do cartão.
            separar = strtok(NULL, "\"");

            //Insere um nó contendo o numero e o texto do cartão.
            arvore_msg = inserir(arvore_msg, num_do_cartao, separar);

            //Pega o proximo numero do cartão.
            separar = strtok(NULL, " ");
            contador += 1;
        }
        unsigned long autoridade;
        contador = 0;
        //Pega o numero das autoridades.
        fgets(linha, TAM_MAX_ENTRADA, stdin);
        separar = strtok(linha, " ");
        autoridade = atol(separar);
        while (contador != num_autoridades && num_cartoes > 3)
        {
            int encontrar = 1; //Seta a variavel de busca para 1 (high).
            p_no triade = criar_arvore();
            pegar_triade(arvore_msg, &triade, arvore_msg, autoridade, &encontrar);
            triade_para_cartao(&triade, &arvore_msg);
            destruir_arvore(triade);
            //Pega o numero da proxima autoridade.
            separar = strtok(NULL, " ");
            if (separar != NULL)
            {
                autoridade = atol(separar);
            }
            contador += 1;
        }
        imprimir_ordem_crescente(arvore_msg);
        printf("\n");
        destruir_arvore(arvore_msg);
    }
    return;
}

int main()
{
    processar_mensagens();
    return 0;
}