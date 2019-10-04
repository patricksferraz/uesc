#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define VSIZE 128

double maximo(double *x, int size);
double minimo(double *x, int size);
double soma  (double *x, int size);
double media (double *x, int size);

int main( int argc, char** argv )
{
  int vSize;
  double *x, max, min, som, med;
  double start, stop;

  start = omp_get_wtime();

  if(argc > 1)
		vSize = atoi(argv[1]);
	else
    vSize = VSIZE;

  x = (double *) malloc(vSize * sizeof(double));
  srandom(123456789);

  for(size_t i = 0; i < vSize; i++)
    x[i] = ((double)random() / RAND_MAX)*2.0 - 1.0;

  max = maximo(x, vSize);
  min = minimo(x, vSize);
  som = soma  (x, vSize);
  med = media (x, vSize);

  printf("Máximo: %f\nMínimo: %f\nSoma: %f\nMedia: %f\n", max, min, som, med);

  free(x);

  stop = omp_get_wtime();
  printf("time: %f\n", stop-start);
  return 0;
}

double maximo(double *x, int size)
{
  double max = x[0];

  for (size_t i = 1; i < size; i++)
    if (x[i] > max)
      max = x[i];

  return max;
}

double minimo(double *x, int size)
{
  double min = x[0];

  for (size_t i = 1; i < size; i++)
    if (x[i] < min)
      min = x[i];

  return min;
}

double soma(double *x, int size)
{
  double soma = 0;

  for (size_t i = 0; i < size; i++)
    soma += x[i];

  return soma;
}

double media(double *x, int size)
{
  double media, som = soma(x, size);

  media = som/size;

  return media;
}
