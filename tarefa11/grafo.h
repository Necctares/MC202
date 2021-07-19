#ifndef GRAFO_H
#define GRAFO_H

//Struct para armazenar uma posicao (X,Y).
typedef struct Posicao
{
    float x, y;
} Posicao;

//Struct para armazenar um nó da lista de Posições.
typedef struct No
{
    Posicao pos;
    struct No *prox;
} No;

typedef No *p_no;

typedef struct Grafo
{
    int **adjacencia;
    int num_vertices;
} Grafo;

typedef Grafo *p_grf;

//Devolve um par cartesiano de entrada (x,y).
Posicao novo_ponto(float x, float y);

//Calcula a distancia euclidiana entre a posicao p1 e p2 e retorna seu resultado para o maior inteiro proximo.
int distancia_min(Posicao p1, Posicao p2);

//Cria um GRAFO contendo NUM_VERTICES.
p_grf criar_grafo(int num_vertices);

//Destroi o Grafo passado.
void destruir_grafo(p_grf grafo);

//Insere uma aresta no GRAFO, entre V1 e V2 com o PESO determinado.
void inserir_aresta(p_grf grafo, int v1, int v2, int peso);

//Função para inserir uma POSICAO na lista.
p_no inserir(p_no lista, Posicao pos);

//Destroi a lista passada.
void destruir_lista(p_no lista);

//Função que retorna o peso da maior aresta no caminho com os menores pesos possiveis entre V0 e V1.
int menor_peso_max(p_grf grafo, int v0, int v1);

#endif