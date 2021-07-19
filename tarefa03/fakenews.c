#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct termos
{
    char termo[26];
    double *h_relevancia;
    double max;
    double min;
    double med;
    double des_pad;
    int class; //Classifica o termo em Bot(0), Evento: Surpreendente(1), Normal(2), Local(3), Irrelevante(4).
} Termo;

void le_dados(Termo *, int, int);
void calcula_dados(Termo *, int, int);
double calcula_max(double *, int);
double calcula_media(double *, int);
double calcula_min(double *, int);
double calcula_desv_padrao(double *, double, int);
void calcula_class(Termo *);
void conta_class(Termo *, int, int *, int *, int *, int *, int *);
void imprime(Termo *, int, int, int, int, int, int);
void limpa_dados(Termo *, int);

int main()
{
    int n_termos, q_dias, bot = 0, eve_nor = 0, eve_irr = 0, eve_sur = 0, eve_loc = 0;
    Termo *fakenews;
    scanf("%d %d", &n_termos, &q_dias);
    fakenews = malloc(sizeof(Termo) * n_termos);
    if (fakenews == NULL)
    {
        exit(1);
    }
    le_dados(fakenews, n_termos, q_dias);
    for(int i=0;i<n_termos;i++){
        calcula_dados(&fakenews[i], n_termos, q_dias);
    }    
    conta_class(fakenews, n_termos, &bot, &eve_sur, &eve_nor, &eve_loc, &eve_irr);
    imprime(fakenews, n_termos, bot, eve_sur, eve_nor, eve_loc, eve_irr);
    limpa_dados(fakenews, n_termos);

    return 0;
}

void limpa_dados(Termo *d, int termos)
{
    for (int i = 0; i < termos; i++)
    {
        free(d[i].h_relevancia);
    }
    free(d);
    return;
}

void imprime(Termo *d, int termos, int bot, int eve_sur, int eve_nor, int eve_loc, int eve_irr)
{
    for (int i = 0; i < termos; i++)
    {
        printf("%s %.2lf %.2lf %.2lf %.2lf\n", d[i].termo, d[i].max, d[i].min, d[i].med, d[i].des_pad);
    }
    printf("\nRESULTADO:\n");
    printf("Bot (%d):", bot);
    for (int i = 0; i < termos; i++)
    {
        if (d[i].class == 0)
        {
            printf(" %s", d[i].termo);
        }
    }
    printf("\n");
    printf("Surpreendente (%d):", eve_sur);
    for (int i = 0; i < termos; i++)
    {
        if (d[i].class == 1)
        {
            printf(" %s", d[i].termo);
        }
    }
    printf("\n");
    printf("Normal (%d):", eve_nor);
    for (int i = 0; i < termos; i++)
    {
        if (d[i].class == 2)
        {
            printf(" %s", d[i].termo);
        }
    }
    printf("\n");
    printf("Local (%d):", eve_loc);
    for (int i = 0; i < termos; i++)
    {
        if (d[i].class == 3)
        {
            printf(" %s", d[i].termo);
        }
    }
    printf("\n");
    printf("Irrelevante (%d):", eve_irr);
    for (int i = 0; i < termos; i++)
    {
        if (d[i].class == 4)
        {
            printf(" %s", d[i].termo);
        }
    }
    return;
}

void conta_class(Termo *d, int termos, int *bot, int *eve_sur, int *eve_nor, int *eve_loc, int *eve_irr)
{
    for (int i = 0; i < termos; i++)
    {
        switch (d[i].class)
        {
        case 0:
            *bot += 1;
            break;
        case 1:
            *eve_sur += 1;
            break;
        case 2:
            *eve_nor += 1;
            break;
        case 3:
            *eve_loc += 1;
            break;

        default:
            *eve_irr += 1;
            break;
        }
    }
    return;
}

void le_dados(Termo *d, int termos, int dias)
{
    for (int i = 0; i < termos; i++)
    {
        d[i].h_relevancia = malloc(sizeof(double) * dias);
        if (d[i].h_relevancia == NULL)
        {
            exit(1);
        }
        scanf("%s", d[i].termo);
        for (int j = 0; j < dias; j++)
        {
            scanf("%lf ", &d[i].h_relevancia[j]);
        }
    }
    return;
}

void calcula_dados(Termo *d, int termos, int dias)
{
    d->max = calcula_max(d->h_relevancia, dias);
    d->med = calcula_media(d->h_relevancia, dias);
    d->min = calcula_min(d->h_relevancia, dias);
    d->des_pad = calcula_desv_padrao(d->h_relevancia, d->med, dias);
    calcula_class(d);
    return;
}

double calcula_max(double *numeros, int dias)
{
    double max = numeros[0];
    for (int i = 1; i < dias; i++)
    {
        if (max < numeros[i])
        {
            max = numeros[i];
        }
    }
    return max;
}

double calcula_min(double *numeros, int dias)
{
    double min = numeros[0];
    for (int i = 1; i < dias; i++)
    {
        if (min > numeros[i])
        {
            min = numeros[i];
        }
    }
    return min;
}

double calcula_media(double *numeros, int dias)
{
    double soma = 0;
    for (int i = 0; i < dias; i++)
    {
        soma += numeros[i];
    }
    return soma / dias;
}

double calcula_desv_padrao(double *numeros, double media, int dias)
{
    double soma = 0;
    for (int i = 0; i < dias; i++)
    {
        soma += pow(numeros[i] - media, 2);
    }
    soma /= dias;
    return sqrt(soma);
}

void calcula_class(Termo *d)
{
    if (d->med >= 60 && d->des_pad > 15)
    {
        d->class = 0;
    }
    else if (d->med >= 60 && d->des_pad <= 15)
    {
        d->class = 1;
    }
    else if (d->med < 60 && d->max >= 80 && d->min > 20)
    {
        d->class = 2;
    }
    else if (d->med < 60 && d->max >= 80 && d->min <= 20)
    {
        d->class = 3;
    }
    else
    {
        d->class = 4;
    }
    return;
}
