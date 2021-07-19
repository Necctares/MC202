#ifndef PACIENTE_H
#define PACIENTE_H

#define TAM_MAX_NOME 51

//Armazena os serviços requeridos de um paciente.
typedef struct lista_servico
{
    int servico;
    struct lista_servico *prox;
} Lista_servico;

typedef struct lista_servico *ls_no;

//Armazena dados de um paciente.
typedef struct paciente
{
    char nome[TAM_MAX_NOME];
    int horario; //Armazena horario em minutos.
    int ord_chegada;
    int prioridade;
    ls_no servicos;
} Paciente;

typedef struct paciente *pac;

//Nó para armazenar dados da struct Paciente.
typedef struct no
{
    pac paciente;
    struct no *anterior, *proximo;
} No;

typedef struct no* p_no;

typedef struct fila
{
    p_no inicio, fim;
} Fila;

typedef struct fila *fp_no;

//Struct com as filas necessarias para o CECOM, com cada serviço possuindo uma fila.
typedef struct cecom
{
    fp_no cg;
    fp_no rad;
    fp_no enf;
    fp_no oto;
    fp_no pne;
    fp_no derm;
    fp_no neuro;
    fp_no onc;
    fp_no psi;
} Cecom;

//Remove Lista.
void del_lista(ls_no servicos);

//Adiciona um serviço na lista de serviços do paciente.
ls_no add_serv(ls_no servicos, int id_servico);

//Remove um serviço da lista de serviços do paciente.
ls_no rem_serv(ls_no servicos);

//Inverte a lista de serviço.
ls_no inverter_lista(ls_no lista);

//Cria um paciente com seus respectivos dados, Nome, Ordem de Chegada e Prioridade.
pac add_paciente(char *nome, int ordem, int prioridade);

//Inicializa uma struct representando o CECOM.
void iniciar_Cecom(Cecom *c);

//Destroi todas as filas do CECOM.
void encerrar_Cecom(Cecom *c);

//Inicializa fila.
fp_no criar_fila();

//Destroi fila.
void destruir_fila(fp_no fila);

//Adiciona um paciente ao fim (Fundo) da fila.
void add_paciente_fim(fp_no fila, pac paciente);

//Adiciona um paciente no inicio (Frente) da fila.
void add_paciente_inicio(fp_no fila, pac paciente);

//Adiciona um paciente na fila pela ordem de chegada.
void add_ordenado_fila(fp_no fila, pac paciente);

//Remove um paciente no inicio (Frente) da fila.
void remove_inicio(fp_no fila);

//Remove um paciente no fim (Fundo) da fila.
void remove_fim(fp_no fila);

//Adiciona um paciente a uma das filas do Cecom.
void encaminhar_paciente(Cecom* cecom, pac paciente);

//Adiciona x minutos no horario dos pacientes que estão na fila.
void gerir_horario(fp_no fila, int x);

//Imprime a saida do paciente com Horario hh:mm + Nome.
void imprimir_saida(pac Paciente);

#endif