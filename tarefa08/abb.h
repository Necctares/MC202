#ifndef ABB_H
#define ABB_H

enum Cor
{
    VERMELHO,
    PRETO
};

//Nó da arvore Rubro negra esquerdista.
typedef struct No
{
    enum Cor cor;
    double numero;
    int ocorrencia;
    struct No *esq, *dir;

} No;

typedef No *p_no;

//Cria uma arvore nova.
p_no criar_arvore();

//Destroi uma arvore existente.
void destruir_arvore(p_no raiz);

//Testa se o nó atual é Vermelho. Retorna 1 caso sim, 0 caso não.
int ehVermelho(p_no no_atual);

//Testa se o nó atual é Preto. Retorna 1 caso sim, 0 caso não.
int ehPreto(p_no no_atual);

//Rotaciona a arvore para a esquerda.
p_no rotacionar_esquerda(p_no raiz);

//Rotaciona a arvore para a direita.
p_no rotacionar_direita(p_no raiz);

//Sobe a cor vermelha (em relação a altura da arvore).
void subir_vermelho(p_no raiz);

//Insere um novo elemento(numero) na arvore rubro negra esquerdista.
p_no inserir(p_no raiz, double numero);

//Devolve o numero de vezes que o num_busca aparece na arvore.
int contar_ocorrencia(p_no raiz, double num_busca);

//Devolve a quantidade de numeros errados na lista legal.
int numeros_errados(p_no raiz);

#endif