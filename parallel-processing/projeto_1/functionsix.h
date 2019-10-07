//
// Created by ferraz on 07/05/18.
//

#ifndef PROJETO_1_FUNCTIONSIX_H
#define PROJETO_1_FUNCTIONSIX_H

#include <stdlib.h>
#include <omp.h>

// Projeto6: Retorna a media dos elementos de cada linha de uma matriz

/**
 * Função calcula a média dos valores de cada linha da matriz
 * @param A matriz
 * @param lsize quantidade de linhas
 * @param csize quantidade de colunas
 * @return vetor contendo a média de cada linha
 */
double* mediaMatrizxColuna(double *A, size_t lsize, size_t csize); // Sequencial

/**
 * Função calcula a média dos valores de cada linha da matriz
 * utilizando multithread
 * @param A matriz
 * @param lsize quantidade de linhas
 * @param csize quantidade de colunas
 * @param num_threads número de threads
 * @return vetor contendo a média de cada linha
 */
double* mediaMatrizxColunap(double *A, size_t lsize, size_t csize, size_t num_threads); // Parallel

#endif //PROJETO_1_FUNCTIONSIX_H
