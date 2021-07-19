#ifndef HASH_H
#define HASH_H

#define TAM_MAX_DIC 197 //Tamanho maximo do dicionario. (Como NUM_PALAVRAS < 100 -> TAM_MAX = 197 para o load factor ser sempre menor que 75%)
#define TAM_MAX_PALAVRA 25

//Nó para implementar a lista ligada do hash.
typedef struct No
{
    char palavra[TAM_MAX_PALAVRA + 1];
    struct No *proximo;
} No;

typedef No *p_no;

//Struct do Hash com um vetor para armazenar as listas ligadas.
typedef struct Hash
{
    p_no vetor[TAM_MAX_DIC];
} Hash;

typedef Hash *p_hash;

//Função para criar hash com um vetor de TAM_MAX_DIC (197).
p_hash criar_hash();

//Função para destruir o hash H.
void destruir_hash(p_hash h);

//Função que insere uma PALAVRA no hash H.
void inserir(p_hash h, char *palavra);

//Função para buscar a PALAVRA no hash H.
p_no buscar(p_hash h, char *palavra);

//Função para conferir a quantidade de erros de uma PALAVRA usando o hash H como "dicionario" base.
int conferir_erros(p_hash h, char *palavra);

#endif