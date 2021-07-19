#include <stdio.h>

int main()
{
    int apostas[1000][16] = {}, apostadores, aux_num, aux_cont, sorteio[6] = {},
        gan_6 = 0, gan_5 = 0, gan_4 = 0;
    float premio;
    scanf("%d %f ", &apostadores, &premio);
    //Lê as apostas
    for (int i = 0; i < apostadores; i++)
    {
        aux_cont = 0;
        for (int j = 0; j < 60; j++)
        {
            scanf("%d ", &aux_num);
            if (aux_num == 1)
            {
                apostas[i][aux_cont] = j + 1;
                aux_cont += 1;
            }
        }
        apostas[i][aux_cont] = -1;
    }
    for (int i = 0; i < 6; i++)
    {
        scanf("%d ", &sorteio[i]);
    }
    //Confere numero de ganhadores
    for (int i = 0; i < apostadores; i++)
    {
        aux_cont = 0;
        aux_num = 0;
        while (apostas[i][aux_cont] != -1)
        {
            for (int j = 0; j < 6; j++)
            {
                if (sorteio[j] == apostas[i][aux_cont])
                {
                    aux_num += 1;
                }
            }
            aux_cont += 1;
        }
        if (aux_num == 4)
        {
            apostas[i][15] = 4;
            gan_4 += 1;
        }
        else if (aux_num == 6)
        {
            apostas[i][15] = 6;
            gan_6 += 1;
        }
        else if (aux_num == 5)
        {
            apostas[i][15] = 5;
            gan_5 += 1;
        }
    }
    //Mostra os premios
    for (int i = 0; i < apostadores; i++)
    {
        if (apostas[i][15] == 4)
        {
            printf("%.2f\n", (premio * 0.19) / gan_4);
        }
        else if (apostas[i][15] == 5)
        {
            printf("%.2f\n", (premio * 0.19) / gan_5);
        }
        else if (apostas[i][15] == 6)
        {
            printf("%.2f\n", (premio * 0.62) / gan_6);
        }
        else
        {
            printf("0.00\n");
        }
    }

    return 0;
}