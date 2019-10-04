//
// Created by ferraz on 07/05/18.
//

#include "functionsix.h"

double* mediaMatrizxColuna(double *A, size_t lsize, size_t csize)
{
    // Alocando espaço para vetor das médias
    double *media = (double*) malloc (lsize * sizeof(double));

    /**
     * Laço para percorrer linhas da matriz
     * somar os valores e calcular a média.
     * lsize = linha; csize = coluna
     */
    for (size_t i = 0; i < lsize; i++)
    {
        media[i] = 0.0;
        for (size_t j = 0; j < csize; j++)
            media[i] += A[i*csize + j];
        media[i] = media[i]/(double)csize;
    }

    // Retorna o endereço do vetor de médias
    return media;
}
