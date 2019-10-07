/**
 * Compiler:
 * gcc -fopenmp -Wall -lm -O3 -o run main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <limits.h>
#include <math.h>

// MANUAL
#include "functionsix.c"
#include "functionsix_processor.c"
#include "output_generator.c"
// CLION
//#include "functionsix_processor.h"
//#include "output_generator.h"

#define LSIZE 1024//256 // LINHA
#define CSIZE 2048//512 // COLUNA
#define QPROCESS 50 // QUANTIDADE DE PROCESSAMENTO
#define GROW_MATRIX 1 // CRESCIMENTO DA MATRIZ << 2 (*4)
#define GROW_PROCESS 1 // DECRESCIMENTO DA QUANTIDADE DE PROCESSAMENTO >> 1 (/2)

int main( int argc, char** argv ) {
    /**
     * Variáveis:
     * tamMatriz = tamanho matriz
     * lsize = numero de linhas
     * csize = numero de colunas
     * numThreads = número de threads
     * qtProcess = quantidade de processamento
     * qtRecord = quantidade de registros
     * umax = maior valor unsigned
     * growMatrix = crescimento da matriz
     * growProcess = crescimento da quantidade de processamento
     * A = matriz entrada
     * r = Armazena os registros dos n threads
     * ptime = tempo de processamento
     * f_out = arquivo de saída
     */
    size_t tamMatriz;
    size_t lsize;
    size_t csize;
    size_t numThreads;
    size_t qtProcess;
    size_t qtRecord;
    size_t umax = UINT_MAX;
    size_t growMatrix = GROW_MATRIX;
    size_t growProcess = GROW_PROCESS;
    double *A;
    tRecord *r;
    tTime ptime;
    FILE *f_out;

    // Variáveis p/ saída
    time_t dTime = time(NULL);
    struct tm tm = *localtime(&dTime);
    char *n_file = (char*) malloc(35 * sizeof(char));

    // Definindo quantidade de linhas da matriz
    if(argc > 1) lsize = atoi(argv[1]);
    else         lsize = LSIZE;
    // Definindo quantidade de colunas da matriz
    if(argc > 2) csize = atoi(argv[2]);
    else         csize = CSIZE;
    // Definindo quantidade de threads que utilizadas para processamento paralelo
    if(argc > 3) numThreads = atoi(argv[3]);
    else         numThreads = omp_get_max_threads();
    // Definindo quantidade de repetições do processamento
    if(argc > 4) qtProcess = atoi(argv[4]);
    else         qtProcess = QPROCESS;

    // Alocando espaço para armazenar os registros dos threads multiplos de 2
    qtRecord = ((size_t)log2f(numThreads)) + 1;
    r = (tRecord *) malloc(qtRecord * sizeof(tRecord));

    // Gerando nome do arquivo de saída de acordo com a data e hora corrente
    sprintf(n_file, "registro_%d_%d_%d_%d_%d_%d.txt", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
            tm.tm_hour, tm.tm_min, tm.tm_sec);
    // Fluxo com arquivo de saída de registros
    if ((f_out = fopen(n_file, "a")) == NULL)
        printf("Erro ao gerar arquivo de saída\n");

    /**
     * Processamento da matriz e geração dos resultados p/ cada tamMatriz
     * t = índice p/ registrar dados thread (CACAU: 1 = 2t; 2 = 4t; 3 = 8t)
     * nt = número de threads utilizadas
     */
    for (size_t i = 0; i < qtRecord; i++)
    {
        // Alocando espaço para matriz de tamanho lxc
        tamMatriz = lsize * csize;
        A = (double *) malloc(tamMatriz * sizeof(double));

        // Preenchendo matriz com valores aleatórios
        srandom(123456789);
        for(size_t j = 0; j < tamMatriz; j++)
            A[j] = ((double)random() / RAND_MAX)*2.0 - 1.0;

        r[0].diff = 0.0;
        r[0].num_threads = 1;
        r[0].maior_tempo = 0.0;
        r[0].menor_tempo = umax;
        for (size_t t = 1, nt = 2; nt <= numThreads; nt *= 2, t++)
        {
            r[t].num_threads = nt;
            r[t].maior_tempo = 0.0;
            r[t].menor_tempo = umax;
            for (size_t j = qtProcess; j > 0; j--)
            {
                r[t].diff = processMatrix(A, lsize, csize, nt, &ptime);
                if (r[0].maior_tempo < ptime.tempo_sq) r[0].maior_tempo = ptime.tempo_sq;
                if (r[0].menor_tempo > ptime.tempo_sq) r[0].menor_tempo = ptime.tempo_sq;

                if (r[t].maior_tempo < ptime.tempo_pp) r[t].maior_tempo = ptime.tempo_pp;
                if (r[t].menor_tempo > ptime.tempo_pp) r[t].menor_tempo = ptime.tempo_pp;
            }
        }

        recordGenerator(r, qtRecord, lsize, csize, qtProcess, f_out);
        lsize <<= growMatrix; // *2
        csize <<= growMatrix; // *2
        if (qtProcess >= 6) qtProcess >>= growProcess; // /2

        free(A);
        fflush(f_out);
    }

    free(r);
    fclose(f_out);
    return 0;
}
