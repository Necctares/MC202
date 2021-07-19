#ifndef UBER_H
#define UBER_H

#define TAM_MAX_NOME 15

//Struct para armazenar um par cartesiano (X,Y)
typedef struct Posicao
{
    int x, y;
} Posicao;

//Struct para armazenar os dados do cliente.
typedef struct Cliente
{
    char nome[TAM_MAX_NOME + 1];
    double avaliacao;
    Posicao origem;
    Posicao destino;
} Cliente;

//Struct para armazenar os dados do Uber.
typedef struct Uber
{
    Cliente c_atual;
    Posicao atual;
    int km_rodados, ocupado; //Caso o uber tenha cliente, Ocupado = 1, caso contrario, 0.
    double rendimento;
} Uber;

typedef Uber *p_ub;

typedef struct Fila_prioridade
{
    Cliente *cliente;
    int tam_atual, tam_total;
} FP;

typedef FP *p_fp;

//Inicializa um novo UBER.
p_ub novo_uber();

//Inicializa um novo CLIENTE.
Cliente novo_cliente(char *nome, double avaliacao, Posicao origem, Posicao destino);

//Cria uma nova FILA de prioridade com TAMANHO_MAX.
p_fp criar_fila(int tamanho_max);

//Destroi uma FILA.
void destruir_fila(p_fp fila);

/*Função para gerir um novo CLIENTE. Se o UBER estiver OCUPADO(1), insere CLIENTE na FILA.
Caso contrario, coloca como CLIENTE atual do UBER.*/
void inserir(p_fp fila, p_ub uber, Cliente cliente);

//Finaliza a corrida atual do UBER. Caso tenha cliente na FILA, encaminha o proximo cliente ao Uber.
void finalizar_corrida(p_fp fila, p_ub uber);

//Processa um pedido de cancelamento. Removendo o cliente com NOME da FILA.
void cancelar_solicitacao(p_fp fila, char *nome);

//Processa o encerramento das atividades do UBER.
void finalizar_jornada(p_ub uber);

#endif