
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


/* Como compilar
gcc -o run_01-10 -Wall -O3 -fopenmp exemplo_01-10.c
*/

double f(double x);

int main()
{

  double integral, a = 0.0, b = 1.0, h, x;
  int n = 4096, i;
  h = (b - a) / n;

  integral = (f(a) + f(b))/2;
  x = a;
  for(i = 1; i < n-1; i++){
    x += h;
    integral += f(x);
  }

  integral *= h;

  printf("Integral = %lf\n", integral);
  return 0;
}

double f(double x)
{
  return x*x + 1.0;
}
