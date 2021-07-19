#include <stdio.h>
#include <stdlib.h>
#include "uber.h"
#include <string.h>

#define TAM_ENTRADA 1024
#define TAM_MAX_FILA 500

void processar_entrada()
{
    char entrada[TAM_ENTRADA], *separar;
    p_fp fila_uber = criar_fila(TAM_MAX_FILA);
    p_ub uber = novo_uber();

    //Pega a proxima entrada.
    while (fgets(entrada, TAM_ENTRADA, stdin) != NULL)
    {
        char menu;
        //Pega a proxima ação a ser executada.
        separar = strtok(entrada, " ");
        menu = separar[0];

        //Processa a ação.
        switch (menu)
        {
        case 'A':
        {
            //Processa o pedido de um novo cliente.
            Posicao origem;
            Posicao destino;
            double avaliacao;
            char *nome;

            //Separa os dados do cliente a ser adicionado.
            nome = strtok(NULL, " ");
            separar = strtok(NULL, " ");
            avaliacao = atof(separar);
            separar = strtok(NULL, " ");
            origem.x = atoi(separar);
            separar = strtok(NULL, " ");
            origem.y = atoi(separar);
            separar = strtok(NULL, " ");
            destino.x = atoi(separar);
            separar = strtok(NULL, " ");
            destino.y = atoi(separar);

            //Insere o novo cliente na fila de espera.
            inserir(fila_uber, uber, novo_cliente(nome, avaliacao, origem, destino));
            break;
        }
        case 'F':
            //Processa o fim de uma corrida.
            finalizar_corrida(fila_uber, uber);
            break;

        case 'C':
            //Processa o cancelamento de um pedido.
            separar = strtok(NULL, " \n");
            uber->rendimento += 7;
            cancelar_solicitacao(fila_uber, separar);
            break;

        case 'T':
            //Encerra o dia de trabalho do uber.
            finalizar_jornada(uber);
            break;

        default:
            printf("ERRO: FUNCAO NAO IMPLEMENTADA.\n");
            break;
        }
    }
    //Libera memoria.
    free(uber);
    destruir_fila(fila_uber);
    return;
}

int main()
{
    processar_entrada();
    return 0;
}