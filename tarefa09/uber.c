#include "uber.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PAI(n) ((n - 1) / 2)
#define FILHO_ESQ(n) ((2 * n) + 1)
#define FILHO_DIR(n) ((2 * n) + 2)

p_ub novo_uber()
{
    //Aloca espaço na memoria e zera as variaveis iniciais.
    p_ub aux = malloc(sizeof(Uber));
    aux->atual.x = aux->atual.y = 0;
    aux->km_rodados = 0;
    aux->rendimento = 0;
    aux->ocupado = 0;
    return aux;
}

Cliente novo_cliente(char *nome, double avaliacao, Posicao origem, Posicao destino)
{
    Cliente novo;
    //Copia o nome para o cliente.
    strcpy(novo.nome, nome);
    novo.avaliacao = avaliacao;
    novo.origem = origem;
    novo.destino = destino;
    return novo;
}

void destruir_fila(p_fp fila)
{
    free(fila->cliente);
    free(fila);
    fila = NULL;
    return;
}

p_fp criar_fila(int tam_max)
{
    p_fp novo = malloc(sizeof(FP));
    novo->cliente = malloc(tam_max * sizeof(Cliente));
    novo->tam_atual = 0;
    novo->tam_total = tam_max;
    return novo;
}

//Função para checar se deve subir a prioridade do elemento na posição POS na FILA de prioridade.
void subir_heap(p_fp fila, int pos)
{
    //Checa se POS não é a primeira da fila e se sua Chave é maior que o do elemento pai.
    if (pos > 0 && fila->cliente[PAI(pos)].avaliacao < fila->cliente[pos].avaliacao)
    {
        //Caso seja, trocamos suas posições.
        Cliente aux = fila->cliente[PAI(pos)];

        fila->cliente[PAI(pos)] = fila->cliente[pos];
        fila->cliente[pos] = aux;

        //Chama novamente a função para checar se irá subir novamente.
        subir_heap(fila, PAI(pos));
    }
    return;
}

void inserir(p_fp fila, p_ub uber, Cliente cliente)
{
    printf("Cliente %s foi adicionado(a)\n", cliente.nome);
    //Checa se o UBER está ocupado.
    if (uber->ocupado)
    {
        //Caso sim, insere CLIENTE na FILA.
        fila->cliente[fila->tam_atual] = cliente;
        fila->tam_atual++;
        subir_heap(fila, fila->tam_atual - 1);
    }
    else
    {
        //Caso não, atribui CLIENTE para cliente atual do UBER.
        uber->c_atual = cliente;
        uber->ocupado = 1;
    }
    return;
}

//Função para checar se deve diminuir a prioridade do elemento na posição POS na FILA.
void descer_heap(p_fp fila, int pos)
{
    int maior_filho;
    //Checa se existe um filho esquerdo.
    if (FILHO_ESQ(pos) < fila->tam_atual)
    {
        maior_filho = FILHO_ESQ(pos);
        //Checa se existe um filho direito e se a chave do filho direito é maior do que o do esquerdo.
        if (FILHO_DIR(pos) < fila->tam_atual && fila->cliente[FILHO_ESQ(pos)].avaliacao < fila->cliente[FILHO_DIR(pos)].avaliacao)
        {
            maior_filho = FILHO_DIR(pos);
        }
        //Checa se o filho com a maior chave é maior do que a chave do elemento em POS.
        if (fila->cliente[pos].avaliacao < fila->cliente[maior_filho].avaliacao)
        {
            //Caso seja, trocamos as posições.
            Cliente aux = fila->cliente[maior_filho];
            fila->cliente[maior_filho] = fila->cliente[pos];
            fila->cliente[pos] = aux;
            //E chamamos novamente a função para checar se devemos descer novamente.
            descer_heap(fila, maior_filho);
        }
    }
    return;
}

//Função que retornar o elemento de maior chave da FILA, removendo-o no procedimento.
Cliente pegar_maximo(p_fp fila)
{
    //Pega o cliente com valor maximo.
    Cliente cliente = fila->cliente[0];

    //Troca sua posição com o ultimo cliente da fila.
    Cliente aux = fila->cliente[fila->tam_atual - 1];
    fila->cliente[fila->tam_atual - 1] = fila->cliente[0];
    fila->cliente[0] = aux;
    //Decrementa o tamanho atual, "excluindo" assim o cliente da fila.
    fila->tam_atual--;

    //Chama a função de descer na FILA para colocar o cliente que estava em ultimo no lugar correto.
    descer_heap(fila, 0);
    return cliente;
}

//Função para calcular a distancia (Distancia de Manhattan) entre a coordenada inicial e a final.
int calcular_distancia(Posicao inicial, Posicao final)
{
    return (abs(inicial.x - final.x) + abs(inicial.y - final.y));
}

void finalizar_corrida(p_fp fila, p_ub uber)
{
    printf("A corrida de %s foi finalizada\n", uber->c_atual.nome);

    //Atualiza os dados do UBER com a corrida finalizada.
    uber->km_rodados += calcular_distancia(uber->atual, uber->c_atual.origem);
    int km_viagem = calcular_distancia(uber->c_atual.origem, uber->c_atual.destino);
    uber->rendimento += km_viagem * 1.4;
    uber->km_rodados += km_viagem;

    //Seta a posição atual do UBER para o destino final do cliente que finalizou a corrida.
    uber->atual.x = uber->c_atual.destino.x;
    uber->atual.y = uber->c_atual.destino.y;

    //Checa se a FILA de prioridade não está vazia.
    if (fila->tam_atual)
    {
        //Caso não esteja, atribui o proximo cliente para o UBER.
        Cliente atual = pegar_maximo(fila);
        uber->c_atual = atual;
    }
    else
    {
        //Caso esteja, coloca o UBER como desocupado.
        uber->ocupado = 0;
    }
    return;
}

void cancelar_solicitacao(p_fp fila, char *nome)
{
    //Percorre a FILA em busca do cliente com NOME.
    for (int i = 0; i < fila->tam_atual; i++)
    {
        //Caso ache, remove-o da fila.
        if (strcmp(fila->cliente[i].nome, nome) == 0)
        {
            Cliente aux = fila->cliente[fila->tam_atual - 1];
            printf("%s cancelou a corrida\n", fila->cliente[i].nome);
            fila->cliente[fila->tam_atual - 1] = fila->cliente[i];
            fila->cliente[i] = aux;
            fila->tam_atual--;

            descer_heap(fila, i);
            break;
        }
    }
    return;
}

void finalizar_jornada(p_ub uber)
{
    //Calcula as despesas: Aluguel do carro -> 57.00 + Gasolina gasta.
    double despesas = 57.00 + ((uber->km_rodados / 10.00) * 4.104);
    //Calcula o rendimento liquido: Rendimento das corridas - despesas - taxa sobre o rendimento da Uber.
    double rendimento_liquido = uber->rendimento - (despesas + (uber->rendimento * 0.25));
    //Imprime os resultados.
    printf("\nJornada finalizada. Aqui esta o seu rendimento de hoje\n");
    printf("Km total: %d\n", uber->km_rodados);
    printf("Rendimento bruto: %.2lf\n", uber->rendimento);
    printf("Despesas: %.2lf\n", despesas);
    printf("Rendimento liquido: %.2lf\n", rendimento_liquido);
    return;
}
