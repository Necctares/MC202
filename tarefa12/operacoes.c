#include "operacoes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Função para criar uma nova pilha.
p_pilha nova_pilha()
{
    p_pilha aux = malloc(sizeof(Pilha));
    aux->num_elementos = 0;
    aux->pilha = malloc(sizeof(char *) * TAM_MAX_EXPRESSAO);
    for (int i = 0; i < TAM_MAX_EXPRESSAO; i++)
    {
        aux->pilha[i] = malloc(sizeof(char) * TAM_MAX_CELULA_DEPENDENTE);
    }
    return aux;
}

//Função para destruir uma pilha.
void destruir_pilha(p_pilha pilha)
{
    for (int i = 0; i < TAM_MAX_EXPRESSAO; i++)
    {
        free(pilha->pilha[i]);
    }
    free(pilha->pilha);
    free(pilha);
    return;
}

//Função para remover o elemento do topo da pilha. Retorna este elemento.
char *remover_topo(p_pilha pilha)
{
    pilha->num_elementos -= 1;
    return pilha->pilha[pilha->num_elementos];
}

//Função para adicionar um DADO ao topo da PILHA.
void adicionar_topo(p_pilha pilha, char *dado)
{
    strcpy(pilha->pilha[pilha->num_elementos], dado);
    pilha->num_elementos += 1;
    return;
}

//Mesmas funções para a pilha versão de numeros inteiros.
int remover_tpint(p_pint pilha)
{
    pilha->num_elementos -= 1;
    return pilha->pilha[pilha->num_elementos];
}

void adicionar_tpint(p_pint pilha, int dado)
{
    pilha->pilha[pilha->num_elementos] = dado;
    pilha->num_elementos += 1;
    return;
}

p_pint nova_pint()
{
    p_pint aux = malloc(sizeof(Pilha));
    aux->num_elementos = 0;
    aux->pilha = malloc(sizeof(int) * TAM_MAX_EXPRESSAO);
    return aux;
}

void destruir_pint(p_pint pilha)
{
    free(pilha->pilha);
    free(pilha);
    return;
}

p_pl nova_planilha(int num_linhas, int num_colunas)
{
    p_pl aux = malloc(sizeof(Planilha));
    aux->planilha = malloc(sizeof(char *) * num_linhas);
    for (int i = 0; i < num_linhas; i++)
    {
        aux->planilha[i] = malloc(sizeof(char *) * num_colunas);
        for (int j = 0; j < num_colunas; j++)
        {
            aux->planilha[i][j] = malloc(sizeof(char) * TAM_MAX_EXPRESSAO);
        }
    }
    aux->lista_dependencia = malloc(sizeof(No) * (num_colunas * num_linhas));
    for (int i = 0; i < num_colunas * num_linhas; i++)
    {
        aux->lista_dependencia[i] = NULL;
    }
    aux->num_colunas = num_colunas;
    aux->num_linhas = num_linhas;
    return aux;
}

//Função para destruir a lista passada.
void destruir_lista(p_no lista)
{
    if (lista != NULL)
    {
        destruir_lista(lista->proximo);
        free(lista);
    }
    lista = NULL;
    return;
}

p_no inserir_lista(p_no lista, char *celula)
{
    p_no aux = malloc(sizeof(No));
    aux->proximo = lista;
    strcpy(aux->celula, celula);
    return aux;
}

//Função que devolve a lista passada invertida. A lista original é destruida.
p_no inverter_lista(p_no lista)
{
    p_no aux = NULL;
    for (p_no atual = lista; atual != NULL; atual = atual->proximo)
    {
        aux = inserir_lista(aux, atual->celula);
    }
    destruir_lista(lista);
    return aux;
}

void destruir_planilha(p_pl planilha)
{
    for (int i = 0; i < planilha->num_linhas * planilha->num_colunas; i++)
    {
        destruir_lista(planilha->lista_dependencia[i]);
    }
    free(planilha->lista_dependencia);
    for (int i = 0; i < planilha->num_linhas; i++)
    {
        for (int j = 0; j < planilha->num_colunas; j++)
        {
            free(planilha->planilha[i][j]);
        }
        free(planilha->planilha[i]);
    }
    free(planilha->planilha);
    free(planilha);
    return;
}

//Função para extrair a coluna referente da string da celula. Ex: A2 --> 0
int converter_coluna(char *celula)
{
    char *separar = strtok(celula, "= ");
    return separar[0] - 'A';
}

//Função para extrair a linha referente da string da celula. Ex: A2 --> 1
int converter_linha(char *celula)
{
    char *separar = strtok(celula, "= QWERTYUIOPASDFGHJKLZXCVBNM");
    return atoi(separar) - 1;
}

//Função para calcular o valor de uma CELULA que contem uma equação. Devolve o resultado.
char *calcular_equacao(p_pl planilha, char *celula)
{
    char *separar;
    char *resposta = malloc(sizeof(char) * TAM_MAX_EXPRESSAO);
    p_no lista_string = NULL;
    //Separa todos os caracteres validos da equação.
    separar = strtok(celula, " =");
    if (separar != NULL)
    {
        lista_string = inserir_lista(lista_string, separar);
    }
    while (separar != NULL)
    {
        separar = strtok(NULL, " =");
        if (separar != NULL)
        {
            lista_string = inserir_lista(lista_string, separar);
        }
    }
    lista_string = inverter_lista(lista_string);
    p_pint p_int = nova_pint();
    p_pilha p_operador = nova_pilha();

    //Percorre todos os caracteres da equação.
    for (p_no atual = lista_string; atual != NULL; atual = atual->proximo)
    {
        //Caso a celula seja um operador, adiciona na pilha de operações.
        if (atual->celula[0] == '+' || atual->celula[0] == '-')
        {
            adicionar_topo(p_operador, atual->celula);
        }
        else if (atual->celula[0] == ')' || atual->celula[0] == '(')
        {
            //Caso seja um parenteses ), remove os dois ultimos numeros da pilha e executa a operação do topo da pilha.
            if (atual->celula[0] == ')')
            {
                int aux_b = remover_tpint(p_int);
                int aux_a = remover_tpint(p_int);
                int resultado = 0;
                char *op = remover_topo(p_operador);
                switch (op[0])
                {
                case '+':
                    resultado = aux_a + aux_b;
                    adicionar_tpint(p_int, resultado);
                    break;
                case '-':
                    resultado = aux_a - aux_b;
                    adicionar_tpint(p_int, resultado);
                    break;
                default:
                    printf("Operacao nao encontrada.\n");
                    break;
                }
            }
        }
        else
        {
            //Caso contrario, é uma celula de referencia ou numero.
            char celula_aux[TAM_MAX_EXPRESSAO];
            strcpy(celula_aux, planilha->planilha[converter_linha(atual->celula)][converter_coluna(atual->celula)]);
            if (celula_aux[0] == '=' && celula_aux[2] == '(')
            {
                //Caso a celula referencie outra celula com equação, chama novamente a função.
                char *aux = calcular_equacao(planilha, celula_aux);
                adicionar_tpint(p_int, atoi(aux));
                free(aux);
            }
            else if (celula_aux[0] == '=')
            {
                //Caso ela referencie outra celula com referencia, checa qual proximo dado.
                while (celula_aux[0] == '=' && celula_aux[2] != '(')
                {
                    strcpy(celula_aux, planilha->planilha[converter_linha(celula_aux)][converter_coluna(celula_aux)]);
                }
                if (celula_aux[0] == '=' && celula_aux[2] == '(')
                {
                    //Se o proximo for uma equação, chama a função novamente.
                    char *aux = calcular_equacao(planilha, celula_aux);
                    adicionar_tpint(p_int, atoi(aux));
                    free(aux);
                }
                else
                {
                    //Caso contrario, adiciona o numero a pilha.
                    adicionar_tpint(p_int, atoi(celula_aux));
                }
            }
            else if (celula_aux[1] == '#')
            {
                //Se a celula acessada tiver uma dependencia ciclia, retorna #ERRO#.
                strcpy(resposta, " #ERRO# ");
                return resposta;
            }
            else
            {
                //Caso contrario, é um numero e será adicionado a pilha.
                adicionar_tpint(p_int, atoi(celula_aux));
            }
        }
    }
    //Remove o resultado da pilha e salva na variavel resposta.
    int aux = remover_tpint(p_int);
    sprintf(resposta, " %d ", aux);
    //Libera memoria.
    destruir_pilha(p_operador);
    destruir_pint(p_int);
    destruir_lista(lista_string);
    return resposta;
}

void funcao_leitura(p_pl planilha, char *celula)
{
    char *extrair_celula = malloc(sizeof(char) * TAM_MAX_EXPRESSAO);
    strcpy(extrair_celula, planilha->planilha[converter_linha(celula)][converter_coluna(celula)]);
    //Checa qual o conteudo da celula a ser lida.
    if (extrair_celula[0] == '=' && extrair_celula[2] == '(')
    {
        //Se for uma equação, chamamos a função para calcular seu valor.
        char *aux = calcular_equacao(planilha, extrair_celula);
        printf("%s\n", aux);
        free(aux);
    }
    else if (extrair_celula[0] == '=')
    {
        //Se for uma celula de referencia, chamamos novamente a função.
        funcao_leitura(planilha, extrair_celula);
    }
    else
    {
        //Caso contrario, é um numero e printamos seu valor.
        printf("%s\n", extrair_celula);
    }
    free(extrair_celula);
    return;
}

void funcao_escrita(p_pl planilha, char *celula, int valor)
{
    printf("%s:%s-> %d \n", celula, planilha->planilha[converter_linha(celula)][converter_coluna(celula)], valor);
    sprintf(planilha->planilha[converter_linha(celula)][converter_coluna(celula)], " %d ", valor);
    return;
}

p_no extrair_dependencia(p_no lista, char *celula)
{
    char *separar;
    separar = strtok(celula, "=()+- ");
    while (separar != NULL)
    {
        lista = inserir_lista(lista, separar);
        separar = strtok(NULL, "=()+- ");
    }
    return lista;
}

//Função para checar se o VERTICE(celula) contem dependencia ciclica ou não. Retorna 1 caso sim, 0 caso não.
int checar_dependencia(p_pl planilha, int vertice, int *visitado, int *pilha_rec)
{
    if (!visitado[vertice])
    {
        //Se o vertice não foi visitado, marca como visitado e adiciona na pilha recursiva.
        visitado[vertice] = 1;
        pilha_rec[vertice] = 1;
        //Percorre a lista de dependencia do vertice em questão.
        for (p_no atual = planilha->lista_dependencia[vertice]; atual != NULL; atual = atual->proximo)
        {
            //Checa se há dependencia, caso sim, retorna 1.
            int aux = ((converter_linha(atual->celula) * planilha->num_colunas) + converter_coluna(atual->celula));
            if (!visitado[aux] && checar_dependencia(planilha, aux, visitado, pilha_rec))
            {
                return 1;
            }
            else if (pilha_rec[aux])
            {
                return 1;
            }
        }
    }
    //Caso não tenha dependencia, removemos o vertice da pilha recursiva e retornamos 0.
    pilha_rec[vertice] = 0;
    return 0;
}

void resolver_dependencia(p_pl planilha)
{
    int *visitado = malloc(sizeof(int) * (planilha->num_colunas * planilha->num_linhas));
    int *pilha_rec = malloc(sizeof(int) * (planilha->num_colunas * planilha->num_linhas));
    //Checa todas as celulas presente na planilha.
    for (int k = 0; k < planilha->num_colunas * planilha->num_linhas; k++)
    {
        for (int i = 0; i < planilha->num_colunas * planilha->num_linhas; i++)
        {
            visitado[i] = 0;
            pilha_rec[i] = 0;
        }
        if (checar_dependencia(planilha, k, visitado, pilha_rec))
        {
            //Se houver dependencia, colocamos o valor da celula com a mensagem de #ERRO#.
            sprintf(planilha->planilha[k / planilha->num_colunas][k % planilha->num_colunas], " #ERRO# ");
        }
    }
    free(visitado);
    free(pilha_rec);
    return;
}
