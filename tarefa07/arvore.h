#ifndef ARVORE_H
#define ARVORE_H

//Nó da arvore.
typedef struct  No
{
    unsigned long chave; //Chave para armazenar valor dos cartões.
    char *texto;
    struct No *esq, *dir;
} No;

typedef No* p_no;

//Cria uma nova arvore.
p_no criar_arvore();

//Destroi uma arvore.
void destruir_arvore(p_no raiz);

//Insere um nó na posição de acordo com a sua chave.
p_no inserir(p_no raiz, unsigned long chave, char *texto);

//Devolve o nó com o menor valor ligado a raiz.
p_no minimo(p_no raiz);

//Remove um nó que tenha a chave passada como parametro.
p_no remover(p_no raiz, unsigned long chave);

//Busca um elemento com a chave passada. Se não encontrar, retorna NULL.
p_no buscar(p_no raiz, unsigned long chave);

/**Procura um par de cartões da triade, caso encontre, adiciona o par na arvore da triade. 
 * Passando o nó raiz da arvore de mensagens, um nó que será iterado para busca,
 * e a soma buscada. Retorna 0 se não encontrado nenhum par, 1 se encontrado.
 * Só ira procurar a triade se encontrar != 0.*/
int procurar_triade(p_no arv_msg, p_no *triade, p_no no_procura, unsigned long soma_cartao, int *encontrar);

/**Função para pegar a triade de cartões.
Passe a raíz da arvore de mensagens, a raiz da triade, o nó inicial de iteração, a soma procurada
e uma chave encontrar. (Só irá procurar se encontrar != 0)*/
void pegar_triade(p_no arvore_msg, p_no *triade, p_no atual, unsigned long soma, int *encontrar);

//Imprime as mensagens do nó em ordem crescente referente as chaves.
void imprimir_ordem_crescente(p_no raiz);

//Junta os nós da triade em um unico cartão. Recebe a raíz da triade e a raíz da arvore de mensagem.
void triade_para_cartao(p_no *triade, p_no *arvore_msg);

#endif