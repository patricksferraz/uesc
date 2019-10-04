#include <stdio.h>
#include <stdlib.h>

#define N 10

int lerPrimos (int *listaPrimos, int n, char *n_arq);
int retornaDuplas (int *listaPrimos, int qtPrimo, int n);

int main(int argc, char **argv)
{
    int n;
    int * listaPrimos;
    int qtPrimo;
    int duplas;

    if (argc > 1) n = atoi(argv[1]);
    else n = N;

    qtPrimo = n >> 1;
    listaPrimos = (int *) malloc (qtPrimo * sizeof(int));

    if (lerPrimos(listaPrimos, n, "primos.txt") == 0)
    {
        printf("Erro ao realizar leitura dos numeros primos.\nConfira se o arquivo 'primos.txt' encontra-se na pasta.");
    }
    else
    {
        duplas = retornaDuplas(listaPrimos, qtPrimo, n);
        printf("A quantidade de duplas de primos para o numero %d são: %d\n", n, duplas);
    }

    free(listaPrimos);
    return 0;
}

int lerPrimos (int *listaPrimos, int n, char *n_arq)
{
    FILE *f_primos;
    int i = 0;
    int val;

    if ((f_primos = fopen(n_arq, "r")) == NULL)
    {
        return 0;
    }
    else
    {
        while ((fscanf(f_primos, "%d", &val)) != EOF)
        {
            if (val < n)
            {
                listaPrimos[i] = val;
                i++;
            }
            else
                break;
        }

        fclose(f_primos);
        return 1;
    }

}

int retornaDuplas (int *listaPrimos, int qtPrimo, int n)
{
    int duplas = 0;

    for (int i = 0; i < qtPrimo; i++)
    {
        if (!listaPrimos[i]) break;
        for (int j = i; j < qtPrimo; j++)
        {
            if (!listaPrimos[j]) break;
            if ((listaPrimos[i] + listaPrimos[j]) == n)
            {
                duplas ++;
                break;
            }
        }
    }

    return duplas;
}
