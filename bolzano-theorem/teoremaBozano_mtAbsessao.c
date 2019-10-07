/*
 *---------------------------------------------------------------------
 *
 *   File    : teoremaBozano.c
 *   Created : 2018-09-03
 *   Modified: 2018-09-03
 *   Compiler: gcc teoremaBozano_mtAbsessao.c -lm -O3 -o teoremaBozano
 *
 *   Algoritmo para aplicação do teorema de Bozano
 *
 *---------------------------------------------------------------------
 */

/**
 * --------------------------------------------------------------------
 * INCLUDES
 * --------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/**
 * --------------------------------------------------------------------
 * MACROS
 * --------------------------------------------------------------------
 */

 #define A 2
 #define B 3
 #define ITERACOES 50

/**
 * --------------------------------------------------------------------
 * PROTÓTIPOS DE FUNÇÕES
 * --------------------------------------------------------------------
 */

double  f               (double x);
int     satisfaz        (double x, double y);
void    escreveArquivo  (FILE *f_out, int i, double a, double b, double xi, double fa, double fxi, double result);

/**
 * --------------------------------------------------------------------
 * FUNÇÃO PRINCIPAL MAIN
 * --------------------------------------------------------------------
 */

int main(int argc, char const *argv[]) {

  // Variáveis
  FILE *f_out;
  double a, b, xi, fa, fb, fxi, result;
  int iteracoes;
  char *nArq;

  // Verificação da entrada
  if (argc > 1 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
    printf("TEOREMA DE BOZANO 1.0 (03 Setembro 2018)."
      "\n\nUSO: %s [a] [b] [i] [-opcao]"
      "\n\nONDE:"
      "\n\ta\t\t:valor de a (double)."
      "\n\tb\t\t:valor de b (double)."
      "\n\ti\t\t:numero de iteracoes (inteiro)."
      "\n\nOPÇÕES:"
      "\n\t--help|-h\t:exibi este manual de uso"
      "\n\nEXEMPLOS:"
      "\n\t%s 2"
      "\n\t%s 2 3"
      "\n\t%s 2 3 1000"
      "\n\t%s 2.4 4.5 30\n\n", argv[0], argv[0], argv[0], argv[0], argv[0]);

    return 0;
  }
  //

  // Init default
  if (argc > 1) a = atof(argv[1]);
  else a = A;
  if (argc > 2) b = atof(argv[2]);
  else b = B;
  if (argc > 3) iteracoes = atoi(argv[3]);
  else iteracoes = ITERACOES;

  // Alocando tamanho p/Arquivo de saída
  if ((nArq = malloc (sizeof(char) << 6)) == NULL) {
    printf("Erro de alocacao\n");
    exit(1);
  }
  // Nome do arquivo de saída
  sprintf(nArq, "teoremaBozano[%f_%f_%d].txt", a, b, iteracoes);

  // Abrindo fluxo com arquivo de saída
  if ((f_out = fopen(nArq, "w")) == NULL) {
    printf("Erro ao gerar arquivo de saida\n");
    exit(1);
  }

  // Verificação do teoremaBozano
  fa = f(a);
  fb = f(b);
  result = fa * fb;

  // Escrita inicial
  fprintf(f_out, "A:%f B:%f\n"
    "Teorema Bozano: f(a):%f * f(b):%f = %f [%s]\n\n", a, b, fa, fb, result, result < 0 ? "Satisfaz" : "Nao Satisfaz");
  fprintf(f_out, "+------------+------------+------------+------------+------------+------------+------------+\n");
  fprintf(f_out, "| %*s | %*s | %*s | %*s | %*s | %*s | %*s |\n",
    10, "i", 10, "a", 10, "b", 10, "xi", 10, "f(a)", 10, "f(xi)", 10, "f(a)*f(xi)"); // i, a, b, xi, fa, fxi, fafxi
  fprintf(f_out, "+------------+------------+------------+------------+------------+------------+------------+\n");
  //

  // Geração e escrita das iterações
  for (int i = 0; i < iteracoes; i++) {
    xi = (a+b) / 2;
    fa = f(a);
    fxi = f(xi);

    result = fa * fxi;
    escreveArquivo (f_out, (i + 1), a, b, xi, fa, fxi, result);

    if (result > 0) a = xi;
    else b = xi;
  }
  //

  // Escrita final
  fprintf(f_out, "+------------+------------+------------+------------+------------+------------+------------+\n");

  // Desalocando memória e fechando fluxo c/ arquivo
  free(nArq);
  fclose(f_out);
  return 0;
}

/**
 * --------------------------------------------------------------------
 * DECLARAÇÃO DAS FUNÇÕES
 * --------------------------------------------------------------------
 */

/**
 * Função para cálculo de fx
 * @param double valor x
 * @return double (x*log(x))-1
 */
double f (double x) {
  return (x * log10(x)) - 1;
}

/**
 * Função para verificar se os valores satisfazem o teoremaBozano
 * @param double valor a
 * @param double valor b
 * @return int 1 satisfaz; 0 não satisfaz
 */
int satisfaz (double x, double y) {
  if (x * y < 0) return 1;
  else return 0;
}

/**
 * Função para escrita no arquivo de saída
 * @param FILE * arquivo de saída
 * @param int número da iteração
 * @param double valor a
 * @param double valor b
 * @param double valor xi
 * @param double valor f(a)
 * @param double valor f(xi)
 * @param double valor f(a) * f(xi)
 * @return void
 */
void escreveArquivo (FILE *f_out, int i, double a, double b, double xi, double fa, double fxi, double result) {
  fprintf(f_out, "| %*d | %*f | %*f | %*f | %*f | %*f | %*f |\n",
    10, i, 10, a, 10, b, 10, xi, 10, fa, 10, fxi, 10, result);
}
