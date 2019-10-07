//
// Created by ferraz on 07/05/18.
//

#include "functionsix_processor.h"

double processMatrix(double *A, size_t lsize, size_t csize, size_t num_threads, tTime *time)
{
    double start, stop;
    double diff;

    // Executando sequencialmente e armazenando tempo
    start = omp_get_wtime();
    double *media = mediaMatrizxColuna(A, lsize, csize);
    stop = omp_get_wtime();
    time->tempo_sq = stop - start;

    // Executando paralelamente e armazenando tempo
    start = omp_get_wtime();
    double *mediaP = mediaMatrizxColunap(A, lsize, csize, num_threads);
    stop = omp_get_wtime();
    time->tempo_pp = stop - start;

    // Armazenando a maior diferença das médias encontradas
    diff = bigDiff(media, mediaP, lsize);

    // Liberando espaço da memória
    free(media);
    free(mediaP);
    // Retornando os valores da diferença
    return diff;
}

double bigDiff(double *media, double *mediaP, size_t lsize)
{
    double diff = 0.0;
    double tmp;

    for (size_t i = 0; i < lsize; i++)
    {
        tmp = media[i] - mediaP[i];
        if (tmp < 0.0)  tmp  =-tmp; // converte valor para positivo
        if (tmp > diff) diff = tmp;
    }

    return diff;
}
