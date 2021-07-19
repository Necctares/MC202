#include "paciente.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void del_lista(ls_no p)
{
    while (p != NULL)
    {
        del_lista(p->prox);
        free(p);
    }
    return;
}

ls_no add_serv(ls_no p, int servico)
{
    ls_no aux = malloc(sizeof(Lista_servico));
    if (aux == NULL)
        exit(1);
    aux->servico = servico;
    aux->prox = p;
    return aux;
}

ls_no rem_serv(ls_no p)
{
    ls_no aux = p->prox;
    free(p);
    return aux;
}

ls_no inverter_lista(ls_no lista)
{
    ls_no atual, anterior, invertida = NULL;
    atual = lista;
    while (atual != NULL)
    {
        anterior = atual;
        atual = anterior->prox;
        anterior->prox = invertida;
        invertida = anterior;
    }
    return invertida;
}

pac add_paciente(char *nome, int ord, int prio)
{
    pac aux = malloc(sizeof(Paciente));
    if (aux == NULL)
        exit(1);
    strcpy(aux->nome, nome); //Copia o nome da entrada para o Novo Paciente.
    aux->ord_chegada = ord;
    aux->prioridade = prio;
    aux->horario = 480; // (480 / 60) = 8h.
    aux->servicos = NULL;
    return aux;
}

fp_no criar_fila()
{
    fp_no aux;
    aux = malloc(sizeof(Fila));
    if (aux == NULL)
        exit(1);
    aux->fim = NULL;
    aux->inicio = NULL;
    return aux;
}

void destruir_fila(fp_no fila)
{
    fila->fim = NULL;
    //Executa até a fila ficar vazia.
    while (fila->inicio != NULL)
    {
        //Guarda o nó do inicio da fila num auxiliar.
        p_no aux = fila->inicio;
        //Coloca a proxima posição da fila como a posição inicial.
        fila->inicio = fila->inicio->proximo;
        //Libera o nó que era a primeira posição da fila.
        free(aux);
    }
    free(fila);
    return;
}

void iniciar_Cecom(Cecom *c)
{
    //Inicializa as filas
    c->cg = criar_fila();    //Clinico Geral
    c->derm = criar_fila();  //Dermatologista
    c->enf = criar_fila();   //Enfermeiro
    c->neuro = criar_fila(); //Neurologista
    c->onc = criar_fila();   //Oncologista
    c->oto = criar_fila();   //Otorrinolaringologista
    c->pne = criar_fila();   //Pneumologista
    c->psi = criar_fila();   //Psiquiatra
    c->rad = criar_fila();   //Radiologista
    return;
}

void encerrar_Cecom(Cecom *c)
{
    //Destroi todas as filas do Cecom.
    destruir_fila(c->cg);
    destruir_fila(c->derm);
    destruir_fila(c->enf);
    destruir_fila(c->neuro);
    destruir_fila(c->onc);
    destruir_fila(c->oto);
    destruir_fila(c->pne);
    destruir_fila(c->psi);
    destruir_fila(c->rad);
    return;
}

//Função para criar um nó.
p_no criar_no(pac paciente)
{
    p_no aux = malloc(sizeof(No));
    aux->paciente = paciente;
    aux->anterior = NULL;
    aux->proximo = NULL;
    return aux;
}

void add_paciente_fim(fp_no fila, pac paciente)
{
    p_no aux = criar_no(paciente);
    if (aux == NULL)
        exit(1);
    //Checa se a fila está vazia.
    if (fila->fim == NULL)
    {
        fila->inicio = aux;
        fila->fim = aux;
    }
    else
    {
        //Adiciona paciente no fim.
        aux->anterior = fila->fim;
        fila->fim->proximo = aux;
        fila->fim = aux;
    }
    return;
}

void add_paciente_inicio(fp_no fila, pac paciente)
{
    p_no aux = criar_no(paciente);
    if (aux == NULL)
        exit(1);
    //Checa se a fila está vazia.
    if (fila->inicio == NULL)
    {
        fila->inicio = aux;
        fila->fim = aux;
    }
    else
    {
        //Adiciona paciente no inicio.
        aux->proximo = fila->inicio;
        fila->inicio->anterior = aux;
        fila->inicio = aux;
    }
    return;
}

void add_ordenado_fila(fp_no fila, pac paciente)
{
    p_no aux = criar_no(paciente);
    if (aux == NULL)
        exit(1);
    /*Checa se a fila está vazia, se a ordem do paciente é menor que o primeiro ou
    maior que o ultimo da fila. */
    if (fila->inicio == NULL)
    {
        fila->inicio = aux;
        fila->fim = aux;
    }
    else if (paciente->ord_chegada < fila->inicio->paciente->ord_chegada)
    {
        //Adiciona paciente no inicio.
        aux->proximo = fila->inicio;
        fila->inicio->anterior = aux;
        fila->inicio = aux;
    }
    else if (paciente->ord_chegada > fila->fim->paciente->ord_chegada)
    {
        //Adiciona paciente no final.
        aux->anterior = fila->fim;
        fila->fim->proximo = aux;
        fila->fim = aux;
    }
    else
    {
        //Procura por um paciente na fila que tenha ordem de chegada maior que o paciente a ser inserido.
        for (p_no atual = fila->inicio; atual != NULL; atual = atual->proximo)
        {
            if (paciente->ord_chegada < atual->paciente->ord_chegada)
            {
                //Adiciona o paciente na frente do paciente da posição "atual".
                p_no anterior = atual->anterior;
                aux->proximo = atual;
                aux->anterior = anterior;
                anterior->proximo = aux;
                atual->anterior = aux;
                return;
            }
        }
    }
    return;
}

void remove_inicio(fp_no fila)
{
    //Checa se a fila não está vazia.
    if (fila->inicio == NULL)
        printf("Erro: Fila vazia.\n");
    else
    {
        p_no aux = fila->inicio;
        fila->inicio = fila->inicio->proximo;
        //Checa se a fila está vazia depois da remoção.
        if (fila->inicio == NULL)
        {
            fila->fim = NULL;
        }
        else
        {
            fila->inicio->anterior = NULL;
        }
        //Libera o elemento a ser removido.
        free(aux);
    }
    return;
}

void remove_fim(fp_no fila)
{
    if (fila->fim == NULL)
        printf("Erro: Fila vazia.\n");
    else
    {
        p_no aux = fila->fim;
        fila->fim = fila->fim->anterior;
        if (fila->fim == NULL)
        {
            fila->inicio = NULL;
        }
        else
        {
            fila->fim->proximo = NULL;
        }
        free(aux);
    }
    return;
}

void encaminhar_paciente(Cecom *cecom, pac paciente)
{
    /*Checa se o paciente tem serviços pendentes.
    Se tiver, encaminha para proxima fila, caso contrario, executa sua saida do hospital.*/
    if (paciente->servicos != NULL)
    {
        switch (paciente->servicos->servico) //Identifica o proximo serviço requerido pelo paciente.
        {
        case 1:
            if (paciente->prioridade) //Checa se é prioritario.
            {
                //Caso seja, adiciona no inicio da fila do proximo serviço requerido.
                add_paciente_inicio(cecom->cg, paciente);
                //Remove o serviço requerido da sua lista de serviços.
                paciente->servicos = rem_serv(paciente->servicos);
            }
            else
            {
                //Caso contrario, adiciona no fim da fila do proximo serviço requerido.
                add_paciente_fim(cecom->cg, paciente);
                paciente->servicos = rem_serv(paciente->servicos);
            }
            break;

        case 2:
            if (paciente->prioridade)
            {
                add_paciente_inicio(cecom->rad, paciente);
                paciente->servicos = rem_serv(paciente->servicos);
            }
            else
            {
                add_paciente_fim(cecom->rad, paciente);
                paciente->servicos = rem_serv(paciente->servicos);
            }
            break;
        case 3:
            if (paciente->prioridade)
            {
                add_paciente_inicio(cecom->enf, paciente);
                paciente->servicos = rem_serv(paciente->servicos);
            }
            else
            {
                add_paciente_fim(cecom->enf, paciente);
                paciente->servicos = rem_serv(paciente->servicos);
            }
            break;
        case 4:
            if (paciente->prioridade)
            {
                add_paciente_inicio(cecom->oto, paciente);
                paciente->servicos = rem_serv(paciente->servicos);
            }
            else
            {
                add_paciente_fim(cecom->oto, paciente);
                paciente->servicos = rem_serv(paciente->servicos);
            }
            break;
        case 5:
            if (paciente->prioridade)
            {
                add_paciente_inicio(cecom->pne, paciente);
                paciente->servicos = rem_serv(paciente->servicos);
            }
            else
            {
                add_paciente_fim(cecom->pne, paciente);
                paciente->servicos = rem_serv(paciente->servicos);
            }
            break;
        case 6:
            if (paciente->prioridade)
            {
                add_paciente_inicio(cecom->derm, paciente);
                paciente->servicos = rem_serv(paciente->servicos);
            }
            else
            {
                add_paciente_fim(cecom->derm, paciente);
                paciente->servicos = rem_serv(paciente->servicos);
            }
            break;
        case 7:
            if (paciente->prioridade)
            {
                add_paciente_inicio(cecom->neuro, paciente);
                paciente->servicos = rem_serv(paciente->servicos);
            }
            else
            {
                add_paciente_fim(cecom->neuro, paciente);
                paciente->servicos = rem_serv(paciente->servicos);
            }
            break;
        case 8:
            if (paciente->prioridade)
            {
                add_paciente_inicio(cecom->onc, paciente);
                paciente->servicos = rem_serv(paciente->servicos);
            }
            else
            {
                add_paciente_fim(cecom->onc, paciente);
                paciente->servicos = rem_serv(paciente->servicos);
            }
            break;
        case 9:
            if (paciente->prioridade)
            {
                add_paciente_inicio(cecom->psi, paciente);
                paciente->servicos = rem_serv(paciente->servicos);
            }
            else
            {
                add_paciente_fim(cecom->psi, paciente);
                paciente->servicos = rem_serv(paciente->servicos);
            }
            break;
        default:
            printf("Erro: Servico nao encontrado.\n");
            break;
        }
    }
    else
    {
        //Saída do hospital.
        //Imprime horario e nome do paciente.
        imprimir_saida(paciente);
        //Certifica que a lista do paciente esteja totalmente liberada.
        del_lista(paciente->servicos);
        //Libera paciente da memoria.
        free(paciente);
    }
    return;
}

void gerir_horario(fp_no fila, int x)
{
    //Percorre a fila adicionando um valor x ao horario de cada paciente na fila.
    for (p_no atual = fila->inicio; atual != NULL; atual = atual->proximo)
    {
        atual->paciente->horario += x;
    }
    return;
}

void imprimir_saida(pac paciente)
{
    //Imprime hh:mm "Nome do Paciente".
    printf("%.2d:%.2d %s\n", paciente->horario / 60, paciente->horario % 60, paciente->nome);
    return;
}
