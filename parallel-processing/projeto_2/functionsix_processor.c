//
// Created by ferraz on 07/05/18.
//

#include "functionsix_processor.h"

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
