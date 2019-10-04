/**
 * Compiler:
 * mpicc -Wall -lm -O3 -fopenmp -o runmpi main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>
#include <limits.h>
#include <math.h>

// MANUAL
#include "functionsix.c"
#include "functionsix_processor.c"
#include "output_generator.c"

#define LSIZE 1024 // LINHA
#define CSIZE 2048 // COLUNA
#define QPROCESS 50 // QUANTIDADE DE PROCESSAMENTO
#define QETAPA 4 // QUANTIDADE DE ETAPA
#define GROW_MATRIX 1 // CRESCIMENTO DA MATRIZ << 2 (*4)
#define GROW_PROCESS 1 // DECRESCIMENTO DA QUANTIDADE DE PROCESSAMENTO >> 1 (/2)

int main( int argc, char** argv ) {
    /**
     * Variáveis:
     * tamMatriz = tamanho matriz
     * lsize = numero de linhas
     * csize = numero de colunas
     * qtProcess = quantidade de processamento
     * umax = maior valor unsigned
     * growMatrix = crescimento da matriz
     * growProcess = crescimento da quantidade de processamento
     * rank = indetificador do processo
     * numProcessors = número de processos
     * A, A_1 = matrizes para calculo
     * start, stop = calculo do tempo de processamento
     * media, mediaP, mediaP_1 = vatores com as médias das matrizes seq, pp e pp/processor
     * r = Armazena os registros do processo
     * f_out = arquivo de saída
     * status = armazena o
     */
    size_t tamMatriz;
    size_t lsize;
    size_t csize;
    size_t bsize, lsize_1;
    size_t qtProcess;
    size_t umax = UINT_MAX;
    size_t growMatrix = GROW_MATRIX;
    size_t growProcess = GROW_PROCESS;
    int rank;
    int numProcessors;
    double *A = NULL, *A_1;
    double start, stop;
    double *media = NULL, *mediaP = NULL, *mediaP_1;
    tRecord r[2];
    tTime ptime;
    FILE *f_out = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcessors);

    // Definindo quantidade de linhas da matriz
    if(argc > 1) lsize = atoi(argv[1]);
    else         lsize = LSIZE;
    // Definindo quantidade de colunas da matriz
    if(argc > 2) csize = atoi(argv[2]);
    else         csize = CSIZE;
    // Definindo quantidade de repetições do processamento
    if(argc > 3) qtProcess = atoi(argv[3]);
    else         qtProcess = QPROCESS;

    if (rank == 0)
    {
        // Variáveis p/ saída
        time_t dTime = time(NULL);
        struct tm tm = *localtime(&dTime);
        char *n_file = (char*) malloc(35 * sizeof(char));

        // Gerando nome do arquivo de saída de acordo com a data e hora corrente
        sprintf(n_file, "registro_%d_%d_%d_%d_%d_%d.txt", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
        tm.tm_hour, tm.tm_min, tm.tm_sec);
        // Fluxo com arquivo de saída de registros
        if ((f_out = fopen(n_file, "a")) == NULL)
            printf("Erro ao gerar arquivo de saída\n");

        r[0].diff = 0.0;
        r[0].num_processors = 1;
    }

    /**
     * Processamento da matriz e geração dos resultados p/ cada tamMatriz
     */
    r[1].num_processors = numProcessors;

    // 4 para resultar em quantidade semelhante do projeto_1
    for (size_t i = 0; i < QETAPA; i++)
    {
        if (rank == 0)
        {
            r[0].maior_tempo = 0.0;
            r[0].menor_tempo = umax;
            
            // Alocando espaço para matriz de tamanho lxc
            tamMatriz = lsize * csize;
            A = (double *) malloc(tamMatriz * sizeof(double));

            // Preenchendo matriz com valores aleatórios
            srandom(123456789);
            for(size_t j = 0; j < tamMatriz; j++)
                A[j] = ((double)random() / RAND_MAX)*2.0 - 1.0;
        }

        // Calculando o tamanho da matrizes nos n processos para segmentação
        lsize_1 = lsize / numProcessors;
        bsize = lsize_1 * csize;
        A_1 = (double *) malloc(bsize * sizeof(double));

        r[1].maior_tempo = 0.0;
        r[1].menor_tempo = umax;
        for (size_t j = qtProcess; j > 0; j--)
        {
            r[1].diff = 0.0;
            ptime.tempo_sq = ptime.tempo_pp = 0.0;

            if (rank == 0)
            {
                // Executando sequencialmente e armazenando tempo
                start = omp_get_wtime();
                media = mediaMatrizxColuna(A, lsize, csize);
                stop = omp_get_wtime();
                ptime.tempo_sq = stop - start;

                // vetor para armazenar todas as médias
                mediaP = (double*) malloc (lsize * sizeof(double));
            }

            // Executando paralelamente e armazenando tempo
            start = omp_get_wtime();

            // Segmentando a matriz (A) em tamanho bsize (A_1) para os 'n' processos
            MPI_Scatter(A, bsize, MPI_DOUBLE, A_1, bsize, MPI_DOUBLE, 0, MPI_COMM_WORLD);

            mediaP_1 = mediaMatrizxColuna(A_1, lsize_1, csize);

            // Agrupando todas as médias (mediaP_1) no rank 0 (mediaP)
            MPI_Gather(mediaP_1, lsize_1, MPI_DOUBLE, mediaP, lsize_1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

            stop = omp_get_wtime();
            ptime.tempo_pp = stop - start;

            if (rank == 0)
            {
                // Armazenando a maior diferença das médias encontradas
                r[1].diff = bigDiff(media, mediaP, lsize);

                // Armazenando o tempo
                if (r[0].maior_tempo < ptime.tempo_sq) r[0].maior_tempo = ptime.tempo_sq;
                if (r[0].menor_tempo > ptime.tempo_sq) r[0].menor_tempo = ptime.tempo_sq;
                if (r[1].maior_tempo < ptime.tempo_pp) r[1].maior_tempo = ptime.tempo_pp;
                if (r[1].menor_tempo > ptime.tempo_pp) r[1].menor_tempo = ptime.tempo_pp;

                // Liberando espaço da memória
                free(media);
                free(mediaP);
            }

            free(mediaP_1);
        }

        if (rank == 0)
        {
            recordGenerator(r, 2, lsize, csize, qtProcess, f_out);
            fflush(f_out);
            free(A);
        }
        lsize <<= growMatrix; // *2
        csize <<= growMatrix; // *2
        if (qtProcess >= 6) qtProcess >>= growProcess; // /2

        free(A_1);
    }

    if (rank == 0) fclose(f_out);
    MPI_Finalize();
    return 0;
}
