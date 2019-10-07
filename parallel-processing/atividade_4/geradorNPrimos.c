#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int ehPrimo (unsigned int x);

int main()
{
    FILE *f_out = fopen("primos.txt", "w");
    unsigned int max = 4294967295;

    for (unsigned int i = 2; i <= max; i++)
        if (ehPrimo(i))
            fprintf(f_out, "%d\n", i);

    fclose(f_out);
    return 0;
}

int ehPrimo (unsigned int x)
{
    unsigned int limite = (unsigned int) sqrt(x);

    for (unsigned int i = 2; i <= limite; i++)
        if ((x % i) == 0)
            return 0;

    return 1;
}
