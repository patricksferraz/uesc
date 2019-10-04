/**
* Teste de região paralela dentro de paralela:
* Obs.:
* Uma região paralela dentro de outra região paralela resulta na criação de um novo grupo de
* “threads” de apenas uma “thread”, por “default”. É possível definir um número maior de
* “threads”, utilizando um dos dois métodos disponíveis:
* 1. Utilização da função omp_set_nested() no código Fortran ou C/C++;
* 2. Definindo a variável de ambiente OMP_NESTED, antes da execução.
*/

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

  #pragma omp parallel for schedule(dynamic)
  for(size_t i = 0; i < vSize; i++)
    x[i] = ((double)random() / RAND_MAX)*2.0 - 1.0;

  #pragma omp parallel sections
  {
    omp_set_nested(1);
    #pragma omp section
    {
      printf("Max threads parallel: %d\n", omp_get_max_threads());
      printf("Threads parallel: %d\n", omp_get_num_threads());
      printf("In parallel-parallel: %d\n\n", omp_in_parallel());
      max = maximo(x, vSize);
    }
    #pragma omp section
    min = minimo(x, vSize);
    #pragma omp section
    som = soma  (x, vSize);
    #pragma omp section
    med = media (x, vSize);
  }

  printf("Máximo: %f\nMínimo: %f\nSoma: %f\nMedia: %f\n", max, min, som, med);

  free(x);

  stop = omp_get_wtime();
  printf("time: %f\n", stop-start);
  return 0;
}

double maximo(double *x, int size)
{
  double max = x[0];

  #pragma omp parallel shared(max)
  {
    #pragma omp single
    {
      printf("Max threads parallel-parallel: %d\n", omp_get_max_threads());
      printf("Threads parallel-parallel: %d\n", omp_get_num_threads());
      printf("In parallel-parallel: %d\n\n", omp_in_parallel());
    }

    #pragma omp for schedule(dynamic)
    for (size_t i = 1; i < size; i++)
      if (x[i] > max)
        max = x[i];
  }

  return max;
}

double minimo(double *x, int size)
{
  double min = x[0];

  #pragma omp parallel for schedule(dynamic) shared(min)
  for (size_t i = 1; i < size; i++)
    if (x[i] < min)
      min = x[i];

  return min;
}

double soma(double *x, int size)
{
  double soma = 0;

  #pragma omp parallel for schedule(dynamic) reduction(+:soma)
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
