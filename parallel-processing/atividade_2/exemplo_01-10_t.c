
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/* Como compilar
gcc -o run_01-10 -Wall -O3 -fopenmp exemplo_01-10.c
*/

//Patrick

double f(double x);

int main()
{
  double integral, a = 0.0, b = 1.0, h, temp = 0.0;
  int n = 512, i;

  #pragma omp parallel sections reduction(+:temp)
  {
    #pragma omp section
    h = (b - a) / n;
    #pragma omp section
    temp += f(a);
    #pragma omp section
    temp += f(b);
  }

  #pragma omp parallel sections
  {
    #pragma omp section
    integral = temp/2;
    #pragma omp section
    a += h;
  }

  #pragma omp parallel for reduction(+:integral)
  for(i = 1; i < n-1; i++)
    integral += f(a*i);

  integral *= h;

  printf("Integral = %lf\n", integral);
  return 0;
}

double f(double x)
{
  return x*x + 1.0;
}
