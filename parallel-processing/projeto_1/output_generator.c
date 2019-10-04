//
// Created by ferraz on 12/05/18.
//

#include "output_generator.h"

int recordGenerator (tRecord *r, size_t qtRecord, size_t lsize, size_t csize, size_t qtProcess, FILE *f_out)
{
    double t_sq = r[0].menor_tempo;
    double speedup;
    size_t tamMatriz = lsize * csize;

    fprintf(f_out, "\nTamanho matriz: %zu x %zu (%zu)\n", lsize, csize, tamMatriz);
    fprintf(f_out, "Quantidade de processamento: %zu\n\n", qtProcess);
    fprintf(f_out, "+-------------+-------------------------+------------+------------+------------+\n");
    fprintf(f_out, "| %-*s | %*sTempo%*s | %-*s | %-*s | %-*s |\n", 11, "", 9, "", 9, "", 10, "", 10, "", 10, "");
    fprintf(f_out, "| N Thread(s) | %*s%*s | %*s%*s | Maior Diff |   Speedup  | Eficiencia |\n",
            7, "min", 3, " ", 7, "max", 3, " ");
    fprintf(f_out, "+-------------+------------+------------+------------+------------+------------+\n");
    for (int i = 0; i < qtRecord; i++)
    {
        speedup = t_sq/r[i].menor_tempo;
        fprintf(f_out, "| %11zu | %*f | %*f | %*f | %*f | %*f |\n", r[i].num_threads, 10, r[i].menor_tempo,
                10, r[i].maior_tempo, 10 ,r[i].diff, 10, speedup, 10, speedup/r[i].num_threads);
    }
    fprintf(f_out, "+-------------+------------+------------+------------+------------+------------+\n");

    return 0;
}