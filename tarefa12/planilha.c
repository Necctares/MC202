#define _POSIX_C_SOURCE 200112L
#include "operacoes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_MAX_ENTRADA 1024

//Função para ler o arquivo csv e devolver uma matriz Planilha.
p_pl ler_planilha()
{
    //Armazena as variaveis de entrada.
    char entrada[TAM_MAX_ENTRADA], *separar;
    int num_linhas, num_colunas;

    //Pega o diretorio do arquivo csv, numero de linhas e colunas.
    fgets(entrada, 1024, stdin);

    separar = strtok(entrada, " \n");
    //Abre o arquivo csv.
    FILE *planilha = fopen(separar, "r");
    if (planilha == NULL)
    {
        printf("ERRO: Arquivo nao pode ser aberto.\n");
    }
    //Separa numero de colunas e linhas.
    separar = strtok(NULL, " \n");
    num_colunas = atoi(separar);

    separar = strtok(NULL, " \n");
    num_linhas = atoi(separar);

    //Cria uma nova planilha para receber o conteudo do arquivo csv.
    p_pl nv_plan = nova_planilha(num_linhas, num_colunas);
    //Variaveis auxiliares.
    int contador = 0; //Conta o numero de linhas.
    char *salvar_ptr; //Salva a posição atual do strtok_r
    char copia_separar[TAM_MAX_EXPRESSAO];
    //Lê todas as linhas do arquivo
    while (fgets(entrada, 1024, planilha) != NULL)
    {
        //Separa os dados do arquivo csv
        separar = strtok_r(entrada, ",\n", &salvar_ptr);
        //Caso apresente uma dependencia, adiciona na lista de dependencias
        if (separar[0] == '=')
        {
            strcpy(copia_separar, separar);
            nv_plan->lista_dependencia[contador * num_colunas] = extrair_dependencia(nv_plan->lista_dependencia[contador * num_colunas], copia_separar);
        }
        //Copia os dados para a matriz da planilha.
        strcpy(nv_plan->planilha[contador][0], separar);
        for (int i = 1; i < num_colunas; i++)
        {
            separar = strtok_r(NULL, ",\n", &salvar_ptr);
            if (separar[0] == '=')
            {
                strcpy(copia_separar, separar);
                nv_plan->lista_dependencia[(contador * num_colunas) + i] = extrair_dependencia(nv_plan->lista_dependencia[(contador * num_colunas) + i], copia_separar);
            }
            strcpy(nv_plan->planilha[contador][i], separar);
        }
        contador += 1;
    }
    //Fecha o arquivo csv.
    fclose(planilha);
    //Chama função para verificar se a planilha tem dependencia ciclica
    resolver_dependencia(nv_plan);
    return nv_plan;
}

//Função para executar as operações na planilha.
void executar_operacoes(p_pl planilha)
{
    char entrada[TAM_MAX_ENTRADA];
    char *op, *coordenada, *valor;

    //Lê as operações.
    while (fgets(entrada, 1024, stdin) != NULL)
    {
        //Verifica se é operação de leitura (G) ou de escrita (S) e executa a operação.
        op = strtok(entrada, " \n");
        if (op[0] == 'G')
        {
            coordenada = strtok(NULL, " \n");
            printf("%s:", coordenada);
            funcao_leitura(planilha, coordenada);
        }
        else
        {
            coordenada = strtok(NULL, " \n");
            valor = strtok(NULL, " \n");
            funcao_escrita(planilha, coordenada, atoi(valor));
        }
    }
    return;
}

int main()
{
    p_pl planilha = ler_planilha();
    executar_operacoes(planilha);
    destruir_planilha(planilha);
    return 0;
}