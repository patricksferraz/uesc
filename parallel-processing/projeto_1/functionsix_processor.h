//
// Created by ferraz on 07/05/18.
//

#ifndef PROJETO_1_FUNCTIONSIX_PROCESSOR_H
#define PROJETO_1_FUNCTIONSIX_PROCESSOR_H

#include <stdlib.h>
#include <omp.h>
#include "functionsix.h"

// Novos tipos de dados
typedef struct time
{
    double tempo_sq;
    double tempo_pp;
} tTime;

typedef struct registro
{
    double diff;
    double maior_tempo;
    double menor_tempo;
    size_t num_threads;
} tRecord;
//

/**
 * Função processa a matriz para calculo das médias das linhas de forma sequencial
 * e paralelo armazenando o tempo de cada uma, a maior diferença entre as média
 * encontradas, número de threads utilizados no processamento paralelo e o tamanho
 * da matriz
 * @param A matriz para processar
 * @param lsize número de colunas da matriz
 * @param csize número de linhas da matriz
 * @param num_threads número de threads p/ processamente paralelo
 * @param time struct para armazenar os tempos do sequencial e paralelo
 * @return diferença entre os maiores médias encontradas
 */
double processMatrix(double *A, size_t lsize, size_t csize, size_t num_threads, tTime *time);

/**
 * Função retorna a maior diferença entre os índices de dois vetores
 * de tamanho lsize
 * @param media vetor de média 1
 * @param mediaP vetor de médias 2
 * @param lsize tamanho dos vetores
 * @return maior diferença encontrada
 */
double bigDiff(double *media, double *mediaP, size_t lsize);

#endif //PROJETO_1_FUNCTIONSIX_PROCESSOR_H
