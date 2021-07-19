#include <stdio.h>
#include <string.h>

#define MAX_COLUNA 100
#define MAX_LINHA 100
#define MAX_PALAVRA 10
#define MAX_TAM_PALAVRA 20

int procura_palavra(char texto[][100], char *palavra, int pos_pal, int pos_lin, int pos_col, int num_linhas, int num_colunas)
{
    if (texto[pos_lin][pos_col] != palavra[pos_pal])
    {
        return 0;
    }
    if (pos_pal == strlen(palavra) - 1)
    {
        return 1;
    }
    char aux = texto[pos_lin][pos_col];
    texto[pos_lin][pos_col] = '0';
    if (pos_lin > 1)
    {
        if (procura_palavra(texto, palavra, pos_pal + 1, pos_lin - 1, pos_col, num_linhas, num_colunas))
        {
            return 1;
        }
    }
    if (pos_lin < num_linhas - 1)
    {
        if (procura_palavra(texto, palavra, pos_pal + 1, pos_lin + 1, pos_col, num_linhas, num_colunas))
        {
            return 1;
        }
    }
    if (pos_col > 0)
    {
        if (procura_palavra(texto, palavra, pos_pal + 1, pos_lin, pos_col - 1, num_linhas, num_colunas))
        {
            return 1;
        }
    }
    if (pos_col < num_colunas - 1)
    {
        if (procura_palavra(texto, palavra, pos_pal + 1, pos_lin, pos_col + 1, num_linhas, num_colunas))
        {
            return 1;
        }
    }
    texto[pos_lin][pos_col] = aux;
    return 0;
}

void procura_texto(char texto[][100], char *palavra, int num_linhas, int num_colunas)
{
    for (int i = 0; i < num_linhas; i++)
    {
        for (int j = 0; j < num_colunas; j++)
        {
            if (procura_palavra(texto, palavra, 0, i, j, num_linhas, num_colunas)){
                printf("sim\n");
                return;
            }
        }
    }
    printf("nao\n");
    return;
}

void copia_matriz(char matriz_ori[][100], char matriz_cop[][100], int num_lin, int num_col)
{
    for (int i = 0; i < num_lin; i++)
    {
        for (int j = 0; j < num_col; j++)
        {
            matriz_cop[i][j] = matriz_ori[i][j];
        }
    }
    return;
}

int main()
{
    char texto[MAX_LINHA][MAX_COLUNA], aux_t[MAX_LINHA][MAX_COLUNA], palavra[MAX_PALAVRA][MAX_TAM_PALAVRA];
    int num_linhas, num_colunas, num_palavras;
    scanf("%d %d %d", &num_linhas, &num_colunas, &num_palavras);
    //Lê o texto
    for (int i = 0; i < num_linhas; i++)
    {
        for (int j = 0; j < num_colunas; j++)
        {
            scanf(" %c", &texto[i][j]);
        }
    }
    //Lê as palavras
    for (int i = 0; i < num_palavras; i++)
    {
        scanf(" %s", palavra[i]);
    }
    //Busca as palavras no texto
    for (int i = 0; i < num_palavras; i++)
    {
        copia_matriz(texto, aux_t, num_linhas, num_colunas);
        procura_texto(aux_t, palavra[i], num_linhas, num_colunas);
    }
    return 0;
}