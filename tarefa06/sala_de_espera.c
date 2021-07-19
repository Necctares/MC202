#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"

#define NUM_CLINICO_GERAL 10
#define NUM_RADIOLOGISTA 2
#define NUM_ENFERMEIRO 5
#define NUM_OTORRINOLARINGOLOGISTA 3
#define NUM_PNEUMOLOGISTA 4
#define NUM_DERMATOLOGISTA 7
#define NUM_NEUROLOGISTA 2
#define NUM_ONCOLOGISTA 1
#define NUM_PSIQUIATRA 4

void ler_entrada(Cecom *c)
{
    char linha[1024];
    int ordem_chegada = 0;
    //Pega a linha com os dados de cada paciente
    while (fgets(linha, 1024, stdin) != NULL)
    {
        char *nome, *separar;
        pac paciente;
        //Separa "Nome" do paciente
        nome = strtok(linha, "\"");
        //Separa prioridade, e depois seta se é normal(0) ou preferencial(1).
        separar = strtok(NULL, " ");
        if (strcmp(separar, "normal") == 0)
        {
            paciente = add_paciente(nome, ordem_chegada, 0);
        }
        else
        {
            paciente = add_paciente(nome, ordem_chegada, 1);
        }
        //Separa e adiciona os serviços requeridos ao paciente.
        separar = strtok(NULL, " ");
        while (separar != NULL)
        {
            paciente->servicos = add_serv(paciente->servicos, atoi(separar));
            separar = strtok(NULL, " ");
        }
        //Coloca os serviços na ordem certa.
        paciente->servicos = inverter_lista(paciente->servicos);
        //Coloca o paciente na fila do proximo serviço.
        encaminhar_paciente(c, paciente);
        ordem_chegada += 1;
    }
    return;
}

void iniciar_atendimento(Cecom *c)
{
    fp_no fila_espera = criar_fila();
    int em_funcionamento; //Checa se houve execução de serviço.
    int i;
    do
    {
        i = 0;
        em_funcionamento = 0;
        //Simula o atendimento em cada profissional.
        while (i < NUM_CLINICO_GERAL && c->cg->inicio != NULL)
        {
            //Adiciona 10 minutos ao paciente atual.
            c->cg->inicio->paciente->horario += 10;
            //Adiciona o paciente a fila de espera.
            add_ordenado_fila(fila_espera, c->cg->inicio->paciente);
            //Remove o paciente da fila de serviço atual.
            remove_inicio(c->cg);
            i += 1;
        }
        if (i > 0)
        {
            em_funcionamento = 1;
            //Adiciona 10 minutos a cada paciente não atendido da fila.
            gerir_horario(c->cg, 10);
        }
        i = 0;
        //Mesmo procedimento do Clinico Geral.
        while (i < NUM_RADIOLOGISTA && c->rad->inicio != NULL)
        {
            c->rad->inicio->paciente->horario += 10;
            add_ordenado_fila(fila_espera, c->rad->inicio->paciente);
            remove_inicio(c->rad);
            i += 1;
        }
        if (i > 0)
        {
            em_funcionamento = 1;
            gerir_horario(c->rad, 10);
        }
        i = 0;
        while (i < NUM_ENFERMEIRO && c->enf->inicio != NULL)
        {
            c->enf->inicio->paciente->horario += 10;
            add_ordenado_fila(fila_espera, c->enf->inicio->paciente);
            remove_inicio(c->enf);
            i += 1;
        }
        if (i > 0)
        {
            em_funcionamento = 1;
            gerir_horario(c->enf, 10);
        }
        i = 0;
        while (i < NUM_OTORRINOLARINGOLOGISTA && c->oto->inicio != NULL)
        {
            c->oto->inicio->paciente->horario += 10;
            add_ordenado_fila(fila_espera, c->oto->inicio->paciente);
            remove_inicio(c->oto);
            i += 1;
        }
        if (i > 0)
        {
            em_funcionamento = 1;
            gerir_horario(c->oto, 10);
        }
        i = 0;
        while (i < NUM_PNEUMOLOGISTA && c->pne->inicio != NULL)
        {
            c->pne->inicio->paciente->horario += 10;
            add_ordenado_fila(fila_espera, c->pne->inicio->paciente);
            remove_inicio(c->pne);
            i += 1;
        }
        if (i > 0)
        {
            em_funcionamento = 1;
            gerir_horario(c->pne, 10);
        }
        i = 0;
        while (i < NUM_DERMATOLOGISTA && c->derm->inicio != NULL)
        {
            c->derm->inicio->paciente->horario += 10;
            add_ordenado_fila(fila_espera, c->derm->inicio->paciente);
            remove_inicio(c->derm);
            i += 1;
        }
        if (i > 0)
        {
            em_funcionamento = 1;
            gerir_horario(c->derm, 10);
        }
        i = 0;
        while (i < NUM_NEUROLOGISTA && c->neuro->inicio != NULL)
        {
            c->neuro->inicio->paciente->horario += 10;
            add_ordenado_fila(fila_espera, c->neuro->inicio->paciente);
            remove_inicio(c->neuro);
            i += 1;
        }
        if (i > 0)
        {
            em_funcionamento = 1;
            gerir_horario(c->neuro, 10);
        }
        i = 0;
        while (i < NUM_ONCOLOGISTA && c->onc->inicio != NULL)
        {
            c->onc->inicio->paciente->horario += 10;
            add_ordenado_fila(fila_espera, c->onc->inicio->paciente);
            remove_inicio(c->onc);
            i += 1;
        }
        if (i > 0)
        {
            em_funcionamento = 1;
            gerir_horario(c->onc, 10);
        }
        i = 0;
        while (i < NUM_PSIQUIATRA && c->psi->inicio != NULL)
        {
            c->psi->inicio->paciente->horario += 10;
            add_ordenado_fila(fila_espera, c->psi->inicio->paciente);
            remove_inicio(c->psi);
            i += 1;
        }
        if (i > 0)
        {
            em_funcionamento = 1;
            gerir_horario(c->psi, 10);
        }
        //Encaminha os pacientes na fila de espera para o proximo atendimento.
        while (fila_espera->inicio != NULL)
        {
            encaminhar_paciente(c, fila_espera->inicio->paciente);
            remove_inicio(fila_espera);
        }
    } while (em_funcionamento);
    destruir_fila(fila_espera);
    encerrar_Cecom(c);
    return;
}

int main()
{
    Cecom hospital;
    //Inicializa as filas do Cecom.
    iniciar_Cecom(&hospital);
    ler_entrada(&hospital);
    iniciar_atendimento(&hospital);
    return 0;
}