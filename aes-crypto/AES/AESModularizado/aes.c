/*
 *---------------------------------------------------------------------
 *
 *   File    : aes.c
 *   Created : 2018-01-01
 *   Modified: 2018-01-01
 *
 *   Algoritmo de criptografia do AES
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
#include <string.h>

/**
 * --------------------------------------------------------------------
 * MACROS
 * --------------------------------------------------------------------
 */

#define TAM_CHAVE 4 // bytes Nk
#define TAM_BLOCO 4 // bytes Nb
#define ROUNDS 10   // Nr

/**
 * --------------------------------------------------------------------
 * TIPOS
 * --------------------------------------------------------------------
 */

typedef char tByte;

/**
 * --------------------------------------------------------------------
 * VARIÁVEIS GLOBAIS
 * --------------------------------------------------------------------
 */


/**
 * --------------------------------------------------------------------
 * PROTÓTIPOS DE FUNÇÕES
 * --------------------------------------------------------------------
 */

void Cipher (tByte in[TAM_BLOCO << 2], tByte out[TAM_BLOCO << 2], tByte w[TAM_BLOCO * (ROUNDS + 1)]);

/**
 * --------------------------------------------------------------------
 * FUNÇÃO PRINCIPAL MAIN
 * --------------------------------------------------------------------
 */

int main (int argc, char **argv)
{
    // Verifica a quantidade de argumentos
    if (argc != 4)
        printf("AES 1.0 (01 Janeiro 2018)."
            "\n\nUSO: %s arquivo [-ação] k"
            "\n\nONDE:"
            "\n\tarquivo\t\t:arquivo TEXTO para ser criptografado."
            "\n\t\t\t|arquivo BINÁRIO para ser descriptografado."
            "\n\tk\t\t:chave de dezesseis-caracteres (ASCII)."
            "\n\nAÇÃO:"
            "\n\t-c\t\t:criptografar entrada."
            "\n\t-d\t\t:descriptografar entrada."
            "\n\nEXEMPLOS:"
            "\n\t%s mensagem.txt -c abcdefghabcdefgh"
            "\n\t%s mensagem-txt.des -d abcdefghabcdefgh\n\n", argv[0], argv[0], argv[0]);
    else
    {                 //0    1    2    3    4    5    6    7    8    9   10    11
        char vm[12] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
        char *v = vm;
        char x = v[0][1];

        printf("%c\n", x);
    }

	return 0;

} // end-main

/**
 * --------------------------------------------------------------------
 * DECLARAÇÕES DE FUNÇÕES
 * --------------------------------------------------------------------
 */

void Cipher (tByte in[TAM_BLOCO << 2], tByte out[TAM_BLOCO << 2], tByte w[TAM_BLOCO * (ROUNDS + 1)])
{
    tByte state;
}