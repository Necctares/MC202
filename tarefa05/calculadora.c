#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 24

typedef struct No
{
    int numero;
    struct No *prox;
} No;

typedef struct No *p_no;

p_no criar_lista()
{
    return NULL;
}

void destruir_lista(p_no lista)
{
    if (lista != NULL)
    {
        destruir_lista(lista->prox);
        free(lista);
    }
    return;
}

p_no adicionar_elemento(p_no lista, int num)
{
    p_no aux;
    aux = malloc(sizeof(No));
    if (aux == NULL)
    {
        exit(1);
    }
    aux->numero = num;
    aux->prox = lista;
    return aux;
}

p_no remover_elemento(p_no lista)
{
    p_no aux;
    aux = lista->prox;
    free(lista);
    return aux;
}

void imprimir_lista(p_no lista)
{
    p_no atual;
    for (atual = lista; atual != NULL; atual = atual->prox)
    {
        printf("%d", atual->numero);
    }
    printf("\n");
}

p_no inverter_lista(p_no lista)
{
    p_no atual, anterior, invertida = criar_lista();
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

//Retorna 1 se num1 > num2, 0 se num1 == num2 e -1 se num2 > num1.
int compara_string_numero(char *num1, char *num2)
{
    if (strlen(num1) > strlen(num2))
    {
        return 1;
    }
    else if (strlen(num1) < strlen(num2))
    {
        return -1;
    }
    else
    {
        for (int i = 0; i < strlen(num1); i++)
        {
            if ((int)num1[i] > (int)num2[i])
            {
                return 1;
            }
            if ((int)num1[i] < (int)num2[i])
            {
                return -1;
            }
        }
    }
    return 0;
}

p_no calcular_soma(p_no n1, p_no n2)
{
    p_no aux, num1 = n1, num2 = n2;
    aux = criar_lista();
    int carry = 0, soma;
    while (num1 != NULL || num2 != NULL)
    {
        soma = carry;
        if (num1 != NULL)
        {
            soma += num1->numero;
        }
        if (num2 != NULL)
        {
            soma += num2->numero;
        }
        carry = soma / 10;
        soma %= 10;
        aux = adicionar_elemento(aux, soma);
        if (num1 != NULL)
        {
            num1 = num1->prox;
        }
        if (num2 != NULL)
        {
            num2 = num2->prox;
        }
    }
    if (carry != 0)
    {
        aux = adicionar_elemento(aux, carry);
    }
    return aux;
}

//Calcula o valor de n1 - n2, sendo OBRIGATORIAMENTE n1 >= n2.
p_no calcular_sub(p_no n1, p_no n2)
{
    p_no aux, num1 = n1, num2 = n2;
    aux = criar_lista();
    int carry = 0, sub = 0;
    while (num2 != NULL)
    {
        sub = num1->numero - num2->numero - carry;
        if (sub < 0)
        {
            sub += 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        num2 = num2->prox;
        num1 = num1->prox;
        aux = adicionar_elemento(aux, sub);
    }

    //Adiciona o carry extra se houver.
    if (carry != 0)
    {
        sub = num1->numero - carry;
        aux = adicionar_elemento(aux, sub);
        num1 = num1->prox;
    }

    //Adiciona o resto de num1 que equivaleria a parte da subtração num1 - 0xxx.
    while (num1 != NULL)
    {
        aux = adicionar_elemento(aux, num1->numero);
        num1 = num1->prox;
    }

    //Remove todos os 0 da frente. e.g. 000xxxxx -> xxxxxx.
    while (aux->numero == 0 && aux->prox != NULL)
    {
        aux = remover_elemento(aux);
    }

    return aux;
}

p_no calcular_mult(p_no n1, p_no n2)
{
    p_no aux_soma = criar_lista();
    aux_soma = adicionar_elemento(aux_soma, 0);
    //checa se não está multiplicando por 0.
    if ((n1->numero == 0 && n1->prox == NULL) || (n2->numero == 0 && n2->prox == NULL))
    {
        return aux_soma;
    }

    //Multiplica os dois numeros.
    int mult, carry, contador = 0;
    for (p_no num2 = n2; num2 != NULL; num2 = num2->prox)
    {
        p_no aux_mult = criar_lista();
        carry = 0;
        for (p_no num1 = n1; num1 != NULL; num1 = num1->prox)
        {
            mult = (num1->numero * num2->numero) + carry;
            carry = mult / 10;
            aux_mult = adicionar_elemento(aux_mult, mult % 10);
        }

        if (carry != 0)
        {
            aux_mult = adicionar_elemento(aux_mult, carry);
        }
        aux_mult = inverter_lista(aux_mult);

        for (int i = 0; i < contador; i++)
        {
            aux_mult = adicionar_elemento(aux_mult, 0);
        }

        p_no temp = aux_soma;
        aux_soma = calcular_soma(aux_soma, aux_mult);
        destruir_lista(temp);
        destruir_lista(aux_mult);
        contador += 1;
        aux_soma = inverter_lista(aux_soma);
    }

    aux_soma = inverter_lista(aux_soma);
    return aux_soma;
}

int main()
{
    int num_op;
    char num_1[TAM_MAX + 1], num_2[TAM_MAX + 1], op;
    scanf("%d", &num_op);
    for (int i = 0; i < num_op; i++)
    {
        //Lê os numeros.
        scanf(" %c", &op);
        scanf(" %s %s", num_1, num_2);
        p_no n1, n2, result;
        n1 = criar_lista();
        n2 = criar_lista();

        //Converte os numeros lidos de string para inteiro armazenando numa lista ligada.
        for (int i = 0; i < strlen(num_1); i++)
        {
            n1 = adicionar_elemento(n1, (int)num_1[i] - 48);
        }

        for (int i = 0; i < strlen(num_2); i++)
        {
            n2 = adicionar_elemento(n2, (int)num_2[i] - 48);
        }

        //Processa a opção escolhida.
        switch (op)
        {
        case '+':
            result = calcular_soma(n1, n2);
            imprimir_lista(result);
            break;
        case '-':
            if (compara_string_numero(num_1, num_2) > 0)
            {
                result = calcular_sub(n1, n2);
                imprimir_lista(result);
            }
            else if (compara_string_numero(num_1, num_2) < 0)
            {
                result = calcular_sub(n2, n1);
                imprimir_lista(result);
            }
            else
            {
                result = NULL;
                printf("0\n");
            }
            break;
        case '*':
            result = calcular_mult(n1, n2);
            imprimir_lista(result);
            break;

        default:
            printf("Ainda nao implementada.\n");
            break;
        }
        destruir_lista(result);
        destruir_lista(n1);
        destruir_lista(n2);
    }
    return 0;
}