#ifndef OPERACOES_H
#define OPERACOES_H

#define TAM_MAX_EXPRESSAO 80
#define TAM_MAX_CELULA_DEPENDENTE 12

//Nó da lista de dependencias.
typedef struct No
{
    char celula[TAM_MAX_CELULA_DEPENDENTE];
    struct No *proximo;
} No;

typedef No *p_no;

typedef struct Planilha
{
    char ***planilha;
    p_no *lista_dependencia;
    int num_linhas;
    int num_colunas;
} Planilha;

typedef Planilha *p_pl;

//Pilha para armazenar os sinais de operação +,- das equações.
typedef struct Pilha
{
    char **pilha;
    int num_elementos;
} Pilha;

typedef Pilha *p_pilha;

//Pilha para armazenar os numeros das equações.
typedef struct Pilha_int
{
    int *pilha;
    int num_elementos;
} Pilha_int;

typedef Pilha_int *p_pint;

//Função que cria uma nova planilha com o NUM_LINHAS e o NUM_COLUNAS passados.
p_pl nova_planilha(int num_linhas, int num_colunas);

//Função para destruir uma planilha.
void destruir_planilha(p_pl planilha);

//Função para ler o conteudo de uma CELULA da PLANILHA.
void funcao_leitura(p_pl planilha, char *celula);

//Função para editar um VALOR na CELULA da PLANILHA.
void funcao_escrita(p_pl planilha, char *celula, int valor);

/*Função para resolver as dependencias presentes na PLANILHA. Caso encontre
dependencia ciclia, edita o valor das celulas com tal dependencia para #ERRO#.*/
void resolver_dependencia(p_pl planilha);

//Função para inserir uma CELULA na LISTA de dependencias.
p_no inserir_lista(p_no lista, char *celula);

//Função para pegar todas as dependencias de uma celula que contem equação.
p_no extrair_dependencia(p_no lista, char *celula);

#endif