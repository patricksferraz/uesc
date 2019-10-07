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
    int num_processors;
} tRecord;
//

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
