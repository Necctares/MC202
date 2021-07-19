#include "professor_carlos.h"
#include <stdio.h>

void le_turmas(Turma[],int);
void menu(int,Turma[],int);

int main()
{
    int n_turmas, n_op;
    Turma geral[50];
    scanf("%d %d", &n_turmas, &n_op);
    le_turmas(geral, n_turmas);
    menu(n_op, geral, n_turmas);

    return 0;
}

void le_turmas(Turma t[], int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &t[i].qtd);
        for (int j = 0; j < t[i].qtd; j++)
        {
            scanf("%s %s %d %d %d", t[i].alunos[j].nome, t[i].alunos[j].sobrenome, &t[i].alunos[j].nascimento.dia, &t[i].alunos[j].nascimento.mes, &t[i].alunos[j].nascimento.ano);
        }
    }
    return;
}

void menu(int op, Turma t[], int n_turmas)
{
    int exe_op, op_aux;
    char s[6];
    Aluno aux_al;
    for (int i = 0; i < op; i++)
    {
        scanf("%d", &exe_op);
        switch (exe_op)
        {
        case 1:
            scanf(" %d", &op_aux);
            aux_al = procura_novo_na_turma(t, op_aux);
            printf("%s\n", aux_al.nome);
            break;

        case 2:
            scanf(" %d", &op_aux);
            aux_al = procura_velho_na_turma(t, op_aux);
            printf("%s\n", aux_al.sobrenome);
            break;

        case 3:
            aux_al = procura_velho_todas_turmas(t, n_turmas);
            printf("%s\n", aux_al.nome);
            break;

        case 4:
            aux_al = procura_novo_todas_turmas(t, n_turmas);
            printf("%s\n", aux_al.sobrenome);
            break;

        case 5:
            scanf(" %s", s);
            printf("%d\n", conta_substrings(t, n_turmas, s));
            break;

        case 6:
            scanf(" %d %s %s %d %d %d", &op_aux, aux_al.nome, aux_al.sobrenome, &aux_al.nascimento.dia, &aux_al.nascimento.mes, &aux_al.nascimento.ano);
            printf("%d\n", add_aluno(t, aux_al, op_aux));
            break;

        case 7:
            scanf(" %d", &op_aux);
            printf("%d\n", remove_aluno(t, op_aux));
            break;

        default:
            printf("error\n");
            break;
        }
    }
}