#include <stdio.h>
#include "professor_carlos.h"

int compara_data(Data, Data);
int compara_nome(Aluno, Aluno);
int ocorre(char[], int, char[]);

Aluno procura_novo_na_turma(Turma t[], int j)
{
    Turma aux = t[j];
    int aluno_mnovo = 0;
    int cmp, cmp2;
    for (int i = 0; i < aux.qtd - 1; i++)
    {
        cmp = compara_data(aux.alunos[aluno_mnovo].nascimento, aux.alunos[i + 1].nascimento);
        if (cmp < 0)
        {
            aluno_mnovo = i + 1;
        }
        else if (cmp == 0)
        {
            cmp2 = compara_nome(aux.alunos[aluno_mnovo], aux.alunos[i + 1]);
            if (cmp2 > 0)
            {
                aluno_mnovo = i + 1;
            }
        }
    }
    return aux.alunos[aluno_mnovo];
}
//Retorna 0 se a1=a2, 1 se a1>a2 e -1 se a1<a2.
int compara_data(Data a1, Data a2)
{
    if (a1.ano > a2.ano)
    {
        return 1;
    }
    else if (a1.ano < a2.ano)
    {
        return -1;
    }
    else
    {
        if (a1.mes > a2.mes)
        {
            return 1;
        }
        else if (a1.mes < a2.mes)
        {
            return -1;
        }
        else
        {
            if (a1.dia > a2.dia)
            {
                return 1;
            }
            else if (a1.dia < a2.dia)
            {
                return -1;
            }
            else
            {
                return 0;
            }
        }
    }
}
//Retorna 0 se a1=a2, 1 se a1>a2 e -1 se a1<a2.
int compara_nome(Aluno a1, Aluno a2)
{
    int i;
    for (i = 0; a1.nome[i] != '\0'; i++)
    {
        if (a1.nome[i] > a2.nome[i])
        {
            return 1;
        }
        else if (a1.nome[i] < a2.nome[i])
        {
            return -1;
        }
    }
    if (a1.nome[i] == a2.nome[i])
    {
        for (i = 0; a1.sobrenome[i] != '\0'; i++)
        {
            if (a1.sobrenome[i] > a2.sobrenome[i])
            {
                return 1;
            }
            else if (a1.sobrenome[i] < a2.sobrenome[i])
            {
                return -1;
            }
        }
    }
    return 0;
}

Aluno procura_velho_na_turma(Turma t[], int j)
{
    Turma aux = t[j];
    int aluno_mvelho = 0;
    int cmp;
    for (int i = 0; i < aux.qtd - 1; i++)
    {
        cmp = compara_data(aux.alunos[aluno_mvelho].nascimento, aux.alunos[i + 1].nascimento);
        if (cmp > 0)
        {
            aluno_mvelho = i + 1;
        }
        else if (cmp == 0)
        {
            if (compara_nome(aux.alunos[aluno_mvelho], aux.alunos[i + 1]) > 0)
            {
                aluno_mvelho = i + 1;
            }
        }
    }
    return aux.alunos[aluno_mvelho];
}

Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas)
{
    Aluno cmp, aluno_mvelho;
    aluno_mvelho = procura_velho_na_turma(t, 0);
    for (int i = 0; i < qtd_turmas - 1; i++)
    {
        cmp = procura_velho_na_turma(t, i + 1);
        if (compara_data(aluno_mvelho.nascimento, cmp.nascimento) > 0)
        {
            aluno_mvelho = cmp;
        }
        else if (compara_data(aluno_mvelho.nascimento, cmp.nascimento) == 0)
        {
            if (compara_nome(aluno_mvelho, cmp) > 0)
            {
                aluno_mvelho = cmp;
            }
        }
    }
    return aluno_mvelho;
}

Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas)
{
    Aluno cmp, aluno_mnovo;
    aluno_mnovo = procura_novo_na_turma(t, 0);
    for (int i = 0; i < qtd_turmas - 1; i++)
    {
        cmp = procura_novo_na_turma(t, i + 1);
        if (compara_data(aluno_mnovo.nascimento, cmp.nascimento) < 0)
        {
            aluno_mnovo = cmp;
        }
        else if (compara_data(aluno_mnovo.nascimento, cmp.nascimento) == 0)
        {
            if (compara_nome(aluno_mnovo, cmp) > 0)
            {
                aluno_mnovo = cmp;
            }
        }
    }
    return aluno_mnovo;
}
//Retorna 0 se não encontrado padrão, 1 caso contrario.
int ocorre(char texto[], int pos, char padrao[])
{
    int j;
    for (j = 0; padrao[j] != '\0'; j++)
        if (texto[pos + j] == '\0' || (texto[pos + j] != padrao[j] && padrao[j] != '*'))
            return 0;
    return 1;
}

int conta_substrings(Turma t[], int qtd_turmas, char *padrao)
{
    int contador = 0, chave;
    for (int i = 0; i < qtd_turmas; i++)
    {
        for (int j = 0; j < t[i].qtd; j++)
        {
            chave = 0;
            for (int a = 0; t[i].alunos[j].nome[a] != '\0' && chave == 0; a++)
            {
                if (ocorre(t[i].alunos[j].nome, a, padrao))
                {
                    contador += 1;
                    chave = 1;
                }
            }
        }
    }
    return contador;
}

int add_aluno(Turma t[], Aluno A, int j){
    t[j].alunos[t[j].qtd]=A;
    t[j].qtd += 1;
    return t[j].qtd;
}

int remove_aluno(Turma t[], int j){
    t[j].qtd -= 1;
    return t[j].qtd;
}