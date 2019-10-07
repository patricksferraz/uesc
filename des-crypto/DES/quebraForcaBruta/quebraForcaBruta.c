/*
 *---------------------------------------------------------------------
 *
 *   File    : quebraForcaBruta.c
 *   Created : 2017-10-28
 *   Modified: 2017-10-28
 *
 *   Algoritmo de criptografia da rede de Feistel
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

#define MSB 0x80000000
#define LSB 0x1
//#define ROUNDS 15
#define TAM_MEIO_BLOCO 4
#define TAM_MEIO_BLOCO_H 8
#define QNT_LIN_SBOX 4
#define QNT_COL_SBOX 16

/**
 * --------------------------------------------------------------------
 * TIPOS
 * --------------------------------------------------------------------
 */

typedef struct {
    unsigned int b32;
    unsigned int b31;
    unsigned int b30;
    unsigned int b29;
    unsigned int b28;
    unsigned int b27;
    unsigned int b26;
    unsigned int b25;
    unsigned int b24;
    unsigned int b23;
    unsigned int b22;
    unsigned int b21;
    unsigned int b20;
    unsigned int b19;
    unsigned int b18;
    unsigned int b17;
    unsigned int b16;
    unsigned int b15;
    unsigned int b14;
    unsigned int b13;
    unsigned int b12;
    unsigned int b11;
    unsigned int b10;
    unsigned int b09;
    unsigned int b08;
    unsigned int b07;
    unsigned int b06;
    unsigned int b05;
    unsigned int b04;
    unsigned int b03;
    unsigned int b02;
    unsigned int b01;
} t32UBits;

typedef struct {
    unsigned int l;
    unsigned int r;
} tBloco8B;

typedef struct
{
    unsigned char byte_1;
    unsigned char byte_2;
    unsigned char byte_3;
    unsigned int  byte_4_7;
} tBloco7B;

typedef struct
{
    unsigned char byte_1;
    unsigned char byte_2;
    unsigned int  byte_3_6;
} tBloco6B;

typedef struct
{
    tBloco6B c1;
    tBloco6B c2;
    tBloco6B c3;
    tBloco6B c4;
    tBloco6B c5;
    tBloco6B c6;
    tBloco6B c7;
    tBloco6B c8;
    tBloco6B c9;
    tBloco6B c10;
    tBloco6B c11;
    tBloco6B c12;
    tBloco6B c13;
    tBloco6B c14;
    tBloco6B c15;
    tBloco6B c16;
} tChave;

/**
 * --------------------------------------------------------------------
 * VARIÁVEIS GLOBAIS
 * --------------------------------------------------------------------
 */

FILE *f_log_des;
FILE *f_log_key;

unsigned int s1[QNT_LIN_SBOX][QNT_COL_SBOX] = {
//    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
    {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7}, // 0
    { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8}, // 1
    { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0}, // 2
    {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}  // 3
};

unsigned int s2[QNT_LIN_SBOX][QNT_COL_SBOX] = {
//    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
    {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10}, // 0
    { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5}, // 1
    { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15}, // 2
    {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}  // 3
};

unsigned int s3[QNT_LIN_SBOX][QNT_COL_SBOX] = {
//    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
    {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8}, // 0
    {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1}, // 1
    {13,  6,  4,  9,  8, 15,  3,  0,  11, 1,  2, 12,  5, 10, 14,  7}, // 2
    { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}  // 3
};

unsigned int s4[QNT_LIN_SBOX][QNT_COL_SBOX] = {
//    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
    { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15}, // 0
    {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9}, // 1
    {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4}, // 2
    { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}  // 3
};

unsigned int s5[QNT_LIN_SBOX][QNT_COL_SBOX] = {
//    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
    { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9}, // 0
    {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6}, // 1
    { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14}, // 2
    {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}  // 3
};

unsigned int s6[QNT_LIN_SBOX][QNT_COL_SBOX] = {
//    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
    {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11}, // 0
    {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8}, // 1
    { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6}, // 2
    { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}  // 3
};

unsigned int s7[QNT_LIN_SBOX][QNT_COL_SBOX] = {
//    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
    { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1}, // 0
    {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6}, // 1
    { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2}, // 2
    { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}  // 3
};

unsigned int s8[QNT_LIN_SBOX][QNT_COL_SBOX] = {
//    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
    {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7}, // 0
    { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2}, // 1
    { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8}, // 2
    { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}  // 3
};

/**
 * --------------------------------------------------------------------
 * PROTÓTIPOS DE FUNÇÕES
 * --------------------------------------------------------------------
 */

void funcaoF 			 (unsigned int *bloco_4B, tBloco6B *chave, t32UBits *bit);
void ecb 		         (t32UBits *bit, FILE *f_in, FILE *f_out, tChave *chave);
void cbc        		 (t32UBits *bit, FILE *f_in, FILE *f_out, tChave *chave);
void pc1Bloco8B          (tBloco8B *chave_in, tBloco7B *chave_out, t32UBits *bit);
void pc2Bloco7B          (tBloco7B *chave_in, tBloco6B *chave_out, t32UBits *bit);
void fImprima4BBin       (unsigned int c, t32UBits *bit, FILE *f_out);
void leftShiftCircular7B (tBloco7B *bloco, t32UBits *bit);

/**
 * --------------------------------------------------------------------
 * FUNÇÃO PRINCIPAL MAIN
 * --------------------------------------------------------------------
 */

int main (int argc, char **argv)
{
    // Variáveis
    tBloco8B chave_8B;
    t32UBits bit;
    tChave   chave;
    FILE     *f_cipher;
    FILE     *f_plain;
    FILE     *f_out;
    
    // Verifica a quantidade de argumentos
    if (argc < 3 || argc > 5)
        printf("FORCA BRUTA 1.0 (10 Janeiro 2018)."
            "\n\nUSO: %s arquivoCifrado [-ação] [-operacao] [arquivoTextoClaro]"
            "\n\nONDE:"
            "\n\tarquivoCifrado\t\t:arquivo BINÁRIO cifrado para ser quebrado."
            "\n\tarquivoTextoClaro\t\t:arquivo TXT contendo texto claro para ser identificado."
            "\n\nPadrão da quebra é utilizando modo de operação Electronic Code Book."
            "\n\nAÇÃO:"
            "\n\t-pt\t\t:tentativa de quebra por texto claro."
            "\n\t-ct\t\t:tentativa de quebra por texto cifrado."
            "\n\nOPERAÇÃO:"
            "\n\t-cbc\t\t:defini modo de operação Cipher Block Chaining."
            "\n\nEXEMPLOS:"
            "\n\t%s arquivoCifrado.des -pt -cbc textoClaro.txt"
            "\n\t%s arquivoCifrado.des -ct -cbc\n\n", argv[0], argv[0], argv[0]);
    else
    {
        if ((f_cipher = fopen(argv[1], 'r') == NULL)
        {
            printf("Arquivo de entrada [%s] inválido.\n", argv[1]);
            exit(1);
        }
        
        if (strcmp(argv[2], '-ct') == 0)
        {
            /* quebra por texto cifrado busca por [ASCII] */
            if (argv[3] && (strcmp(argv[3], '-cbc') == 0))
            {
                /* quebra por texto cifrado cbc */
            }
            else
            {
                /* quebra por texto cifrado ecb */
            }
        }
        else if (strcmp(argv[2], '-pt') == 0)
        {
            if (argv[3])
            {
                if ((f_plain = fopen(argv[3], 'r')) == NULL)
                {
                    printf("Arguivo de entrada [%s] inválido.\n", argv[3]);
                    exit(1);
                }

                if (strcmp(argv[3], '-cbc') == 0)
                {

                    /* quebra por texto claro cbc */
                }
                else
                {

                    /* quebra por texto claro ecb */

                }

                fclose(f_plain);

            }
            else
            {
                printf("Faltam argumentos para operação.\n");
                exit(1);
            }
        }
        else
        {
            printf("Ação [%s] inválida.\n", argv[2]);
            exit(1);
        }

        // ------------------------------------------------------------------------------------------

        /**
         * inicializando32CasasBinarias
         */
        bit.b32 = 0x1;
        bit.b31 = 0x2;
        bit.b30 = 0x4;
        bit.b29 = 0x8;
        bit.b28 = 0x10;
        bit.b27 = 0x20;
        bit.b26 = 0x40;
        bit.b25 = 0x80;
        bit.b24 = 0x100;
        bit.b23 = 0x200;
        bit.b22 = 0x400;
        bit.b21 = 0x800;
        bit.b20 = 0x1000;
        bit.b19 = 0x2000;
        bit.b18 = 0x4000;
        bit.b17 = 0x8000;
        bit.b16 = 0x10000;
        bit.b15 = 0x20000;
        bit.b14 = 0x40000;
        bit.b13 = 0x80000;
        bit.b12 = 0x100000;
        bit.b11 = 0x200000;
        bit.b10 = 0x400000;
        bit.b09 = 0x800000;
        bit.b08 = 0x1000000;
        bit.b07 = 0x2000000;
        bit.b06 = 0x4000000;
        bit.b05 = 0x8000000;
        bit.b04 = 0x10000000;
        bit.b03 = 0x20000000;
        bit.b02 = 0x40000000;
        bit.b01 = 0x80000000;
        // end-inicializando32CasasBinarias

        fclose(f_cipher);
    }

	return 0;

} // end-main

/**
 * ----------------------------------------------------------------------
 * DEFINIÇÕES DE FUNÇÕES
 * ----------------------------------------------------------------------
 */

/**
 * Função gereChaves para gerar as 16 chaves a partir da chave de entrada
 * @param tBloco8B *chave_8B, tChave *chave, t32UBits *bit
 * @return void
 */

void gereChaves (tBloco8B *chave_8B, tChave *chave, t32UBits *bit)
{
    tBloco7B chave_7B;
    chave_7B.byte_1   = 0x0;
    chave_7B.byte_2   = 0x0;
    chave_7B.byte_3   = 0x0;
    chave_7B.byte_4_7 = 0x0;

    pc1Bloco8B(chave_8B, &chave_7B, bit);

    // Geração de c1
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &chave->c1, bit);

    // Geração de c2
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &chave->c2, bit);

    // Geração de c3
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &chave->c3, bit);

    // Geração de c4
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &chave->c4, bit);

    // Geração de c5
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &chave->c5, bit);

    // Geração de c6
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &chave->c6, bit);

    // Geração de c7
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &chave->c7, bit);

    // Geração de c8
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &chave->c8, bit);

    // Geração de c9
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &chave->c9, bit);

    // Geração de c10
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &chave->c10, bit);

    // Geração de c11
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &chave->c11, bit);

    // Geração de c12
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &chave->c12, bit);

    // Geração de c13
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &chave->c13, bit);

    // Geração de c14
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &chave->c14, bit);

    // Geração de c15
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &chave->c15, bit);

    // Geração de c16
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &chave->c16, bit);

} //end-gereChaves (tBloco8B *chave_8B, tChave *chave, t32UBits *bit)

/**
 * Função f p/ cifra do bloco Ri da rede de Feistel com as 8 S-Boxs
 * e a chave ki
 * @param unsigned int *bloco_4B, tBloco6B *bloco_6B, t32UBits *bit
 * @return void
 */

void funcaoF (unsigned int *bloco_4B, tBloco6B *chave, t32UBits *bit)
{
    tBloco6B bloco_6B;
    unsigned int lin = 0x0;
    unsigned int col = 0x0;
    unsigned int aux = 0x0;

    /**
     * Expansão em Ri
     */
    bloco_6B.byte_1   = 0x0;
    bloco_6B.byte_2   = 0x0;
    bloco_6B.byte_3_6 = 0x0;

    if (*bloco_4B & bit->b32) bloco_6B.byte_1 ^= bit->b25; // 32
    if (*bloco_4B & bit->b01) bloco_6B.byte_1 ^= bit->b26; //  1
    if (*bloco_4B & bit->b02) bloco_6B.byte_1 ^= bit->b27; //  2
    if (*bloco_4B & bit->b03) bloco_6B.byte_1 ^= bit->b28; //  3
    if (*bloco_4B & bit->b04) bloco_6B.byte_1 ^= bit->b29; //  4
    if (*bloco_4B & bit->b05) bloco_6B.byte_1 ^= bit->b30; //  5
    if (*bloco_4B & bit->b04) bloco_6B.byte_1 ^= bit->b31; //  4
    if (*bloco_4B & bit->b05) bloco_6B.byte_1 ^= bit->b32; //  5

    if (*bloco_4B & bit->b06) bloco_6B.byte_2 ^= bit->b25; //  6
    if (*bloco_4B & bit->b07) bloco_6B.byte_2 ^= bit->b26; //  7
    if (*bloco_4B & bit->b08) bloco_6B.byte_2 ^= bit->b27; //  8
    if (*bloco_4B & bit->b09) bloco_6B.byte_2 ^= bit->b28; //  9
    if (*bloco_4B & bit->b08) bloco_6B.byte_2 ^= bit->b29; //  8
    if (*bloco_4B & bit->b09) bloco_6B.byte_2 ^= bit->b30; //  9
    if (*bloco_4B & bit->b10) bloco_6B.byte_2 ^= bit->b31; // 10
    if (*bloco_4B & bit->b11) bloco_6B.byte_2 ^= bit->b32; // 11

    if (*bloco_4B & bit->b12) bloco_6B.byte_3_6 ^= bit->b01; // 12
    if (*bloco_4B & bit->b13) bloco_6B.byte_3_6 ^= bit->b02; // 13
    if (*bloco_4B & bit->b12) bloco_6B.byte_3_6 ^= bit->b03; // 12
    if (*bloco_4B & bit->b13) bloco_6B.byte_3_6 ^= bit->b04; // 13
    if (*bloco_4B & bit->b14) bloco_6B.byte_3_6 ^= bit->b05; // 14
    if (*bloco_4B & bit->b15) bloco_6B.byte_3_6 ^= bit->b06; // 15
    if (*bloco_4B & bit->b16) bloco_6B.byte_3_6 ^= bit->b07; // 16
    if (*bloco_4B & bit->b17) bloco_6B.byte_3_6 ^= bit->b08; // 17

    if (*bloco_4B & bit->b16) bloco_6B.byte_3_6 ^= bit->b09; // 16
    if (*bloco_4B & bit->b17) bloco_6B.byte_3_6 ^= bit->b10; // 17
    if (*bloco_4B & bit->b18) bloco_6B.byte_3_6 ^= bit->b11; // 18
    if (*bloco_4B & bit->b19) bloco_6B.byte_3_6 ^= bit->b12; // 19
    if (*bloco_4B & bit->b20) bloco_6B.byte_3_6 ^= bit->b13; // 20
    if (*bloco_4B & bit->b21) bloco_6B.byte_3_6 ^= bit->b14; // 21
    if (*bloco_4B & bit->b20) bloco_6B.byte_3_6 ^= bit->b15; // 20
    if (*bloco_4B & bit->b21) bloco_6B.byte_3_6 ^= bit->b16; // 21

    if (*bloco_4B & bit->b22) bloco_6B.byte_3_6 ^= bit->b17; // 22
    if (*bloco_4B & bit->b23) bloco_6B.byte_3_6 ^= bit->b18; // 23
    if (*bloco_4B & bit->b24) bloco_6B.byte_3_6 ^= bit->b19; // 24
    if (*bloco_4B & bit->b25) bloco_6B.byte_3_6 ^= bit->b20; // 25
    if (*bloco_4B & bit->b24) bloco_6B.byte_3_6 ^= bit->b21; // 24
    if (*bloco_4B & bit->b25) bloco_6B.byte_3_6 ^= bit->b22; // 25
    if (*bloco_4B & bit->b26) bloco_6B.byte_3_6 ^= bit->b23; // 26
    if (*bloco_4B & bit->b27) bloco_6B.byte_3_6 ^= bit->b24; // 27

    if (*bloco_4B & bit->b28) bloco_6B.byte_3_6 ^= bit->b25; // 28
    if (*bloco_4B & bit->b29) bloco_6B.byte_3_6 ^= bit->b26; // 29
    if (*bloco_4B & bit->b28) bloco_6B.byte_3_6 ^= bit->b27; // 28
    if (*bloco_4B & bit->b29) bloco_6B.byte_3_6 ^= bit->b28; // 29
    if (*bloco_4B & bit->b30) bloco_6B.byte_3_6 ^= bit->b29; // 30
    if (*bloco_4B & bit->b31) bloco_6B.byte_3_6 ^= bit->b30; // 31
    if (*bloco_4B & bit->b32) bloco_6B.byte_3_6 ^= bit->b31; // 32
    if (*bloco_4B & bit->b01) bloco_6B.byte_3_6 ^= bit->b32; //  1
    // end-expansaoRi

    // ------------------------------------------------------------------------------------------

    /**
     * Aplicação das S-Boxs
     -------------------
     * 32  1  2  3  4  5
     *  4  5  6  7  8  9
     *  8  9 10 11 12 13
     * 12 13 14 15 16 17
     * 16 17 18 19 20 21
     * 20 21 22 23 24 25
     * 24 25 26 27 28 29
     * 28 29 30 31 32  1
     ------------- tBloco6B -------------
     * 32  1  2  3  4  5  4  5 // 25 a 32
     *  6  7  8  9  8  9 10 11 // 25 a 32
     * 12 13 12 13 14 15 16 17 // 01 a 08
     * 16 17 18 19 20 21 20 21 // 09 a 16
     * 22 23 24 25 24 25 26 27 // 17 a 24
     * 28 29 28 29 30 31 32  1 // 25 a 32
     */

    bloco_6B.byte_1   ^= chave->byte_1;
    bloco_6B.byte_2   ^= chave->byte_2;
    bloco_6B.byte_3_6 ^= chave->byte_3_6;
    *bloco_4B = 0x0;

    // -------------- Aplicação de S1 --------------
    if (bloco_6B.byte_1 & bit->b25) lin ^= bit->b31; // 32
    if (bloco_6B.byte_1 & bit->b30) lin ^= bit->b32; //  5

    if (bloco_6B.byte_1 & bit->b26) col ^= bit->b29; //  1
    if (bloco_6B.byte_1 & bit->b27) col ^= bit->b30; //  2
    if (bloco_6B.byte_1 & bit->b28) col ^= bit->b31; //  3
    if (bloco_6B.byte_1 & bit->b29) col ^= bit->b32; //  4

    aux = s1[lin][col];

    if (aux & bit->b29) *bloco_4B ^= bit->b01;
    if (aux & bit->b30) *bloco_4B ^= bit->b02;
    if (aux & bit->b31) *bloco_4B ^= bit->b03;
    if (aux & bit->b32) *bloco_4B ^= bit->b04;

    lin = col = 0x0;

    // -------------- Aplicação de S2 --------------
    if (bloco_6B.byte_1 & bit->b31) lin ^= bit->b31; //  4
    if (bloco_6B.byte_2 & bit->b28) lin ^= bit->b32; //  9

    if (bloco_6B.byte_1 & bit->b32) col ^= bit->b29; //  5
    if (bloco_6B.byte_2 & bit->b25) col ^= bit->b30; //  6
    if (bloco_6B.byte_2 & bit->b26) col ^= bit->b31; //  7
    if (bloco_6B.byte_2 & bit->b27) col ^= bit->b32; //  8

    aux = s2[lin][col];

    if (aux & bit->b29) *bloco_4B ^= bit->b05;
    if (aux & bit->b30) *bloco_4B ^= bit->b06;
    if (aux & bit->b31) *bloco_4B ^= bit->b07;
    if (aux & bit->b32) *bloco_4B ^= bit->b08;

    lin = col = 0x0;

    // -------------- Aplicação de S3 --------------
    if (bloco_6B.byte_2   & bit->b29) lin ^= bit->b31; //  8
    if (bloco_6B.byte_3_6 & bit->b02) lin ^= bit->b32; //  13

    if (bloco_6B.byte_2   & bit->b30) col ^= bit->b29; //  9
    if (bloco_6B.byte_2   & bit->b31) col ^= bit->b30; // 10
    if (bloco_6B.byte_2   & bit->b32) col ^= bit->b31; // 11
    if (bloco_6B.byte_3_6 & bit->b01) col ^= bit->b32; // 12

    aux = s3[lin][col];

    if (aux & bit->b29) *bloco_4B ^= bit->b09;
    if (aux & bit->b30) *bloco_4B ^= bit->b10;
    if (aux & bit->b31) *bloco_4B ^= bit->b11;
    if (aux & bit->b32) *bloco_4B ^= bit->b12;

    lin = col = 0x0;

    // -------------- Aplicação de S4 --------------
    if (bloco_6B.byte_3_6 & bit->b03) lin ^= bit->b31; // 12
    if (bloco_6B.byte_3_6 & bit->b08) lin ^= bit->b32; // 17

    if (bloco_6B.byte_3_6 & bit->b04) col ^= bit->b29; // 13
    if (bloco_6B.byte_3_6 & bit->b05) col ^= bit->b30; // 14
    if (bloco_6B.byte_3_6 & bit->b06) col ^= bit->b31; // 15
    if (bloco_6B.byte_3_6 & bit->b07) col ^= bit->b32; // 16

    aux = s4[lin][col];

    if (aux & bit->b29) *bloco_4B ^= bit->b13;
    if (aux & bit->b30) *bloco_4B ^= bit->b14;
    if (aux & bit->b31) *bloco_4B ^= bit->b15;
    if (aux & bit->b32) *bloco_4B ^= bit->b16;

    lin = col = 0x0;

    // -------------- Aplicação de S5 --------------
    if (bloco_6B.byte_3_6 & bit->b09) lin ^= bit->b31; // 16
    if (bloco_6B.byte_3_6 & bit->b14) lin ^= bit->b32; // 21

    if (bloco_6B.byte_3_6 & bit->b10) col ^= bit->b29; // 17
    if (bloco_6B.byte_3_6 & bit->b11) col ^= bit->b30; // 18
    if (bloco_6B.byte_3_6 & bit->b12) col ^= bit->b31; // 19
    if (bloco_6B.byte_3_6 & bit->b13) col ^= bit->b32; // 20

    aux = s5[lin][col];

    if (aux & bit->b29) *bloco_4B ^= bit->b17;
    if (aux & bit->b30) *bloco_4B ^= bit->b18;
    if (aux & bit->b31) *bloco_4B ^= bit->b19;
    if (aux & bit->b32) *bloco_4B ^= bit->b20;

    lin = col = 0x0;

    // -------------- Aplicação de S6 --------------
    if (bloco_6B.byte_3_6 & bit->b15) lin ^= bit->b31; // 20
    if (bloco_6B.byte_3_6 & bit->b20) lin ^= bit->b32; // 25

    if (bloco_6B.byte_3_6 & bit->b16) col ^= bit->b29; // 21
    if (bloco_6B.byte_3_6 & bit->b17) col ^= bit->b30; // 22
    if (bloco_6B.byte_3_6 & bit->b18) col ^= bit->b31; // 23
    if (bloco_6B.byte_3_6 & bit->b19) col ^= bit->b32; // 24

    aux = s6[lin][col];

    if (aux & bit->b29) *bloco_4B ^= bit->b21;
    if (aux & bit->b30) *bloco_4B ^= bit->b22;
    if (aux & bit->b31) *bloco_4B ^= bit->b23;
    if (aux & bit->b32) *bloco_4B ^= bit->b24;

    lin = col = 0x0;

    // -------------- Aplicação de S7 --------------
    if (bloco_6B.byte_3_6 & bit->b21) lin ^= bit->b31; // 24
    if (bloco_6B.byte_3_6 & bit->b26) lin ^= bit->b32; // 29

    if (bloco_6B.byte_3_6 & bit->b22) col ^= bit->b29; // 25
    if (bloco_6B.byte_3_6 & bit->b23) col ^= bit->b30; // 26
    if (bloco_6B.byte_3_6 & bit->b24) col ^= bit->b31; // 27
    if (bloco_6B.byte_3_6 & bit->b25) col ^= bit->b32; // 28

    aux = s7[lin][col];

    if (aux & bit->b29) *bloco_4B ^= bit->b25;
    if (aux & bit->b30) *bloco_4B ^= bit->b26;
    if (aux & bit->b31) *bloco_4B ^= bit->b27;
    if (aux & bit->b32) *bloco_4B ^= bit->b28;

    lin = col = 0x0;

    // -------------- Aplicação de S8 --------------
    if (bloco_6B.byte_3_6 & bit->b27) lin ^= bit->b31; // 28
    if (bloco_6B.byte_3_6 & bit->b32) lin ^= bit->b32; //  1

    if (bloco_6B.byte_3_6 & bit->b28) col ^= bit->b29; // 29
    if (bloco_6B.byte_3_6 & bit->b29) col ^= bit->b30; // 30
    if (bloco_6B.byte_3_6 & bit->b30) col ^= bit->b31; // 31
    if (bloco_6B.byte_3_6 & bit->b31) col ^= bit->b32; // 32

    aux = s8[lin][col];

    if (aux & bit->b29) *bloco_4B ^= bit->b29;
    if (aux & bit->b30) *bloco_4B ^= bit->b30;
    if (aux & bit->b31) *bloco_4B ^= bit->b31;
    if (aux & bit->b32) *bloco_4B ^= bit->b32;

    // ------------------------------------------------------------------------------------------

    /**
     * Função de permutação P
     */
    aux = 0x0;

    if (*bloco_4B & bit->b16) aux ^= bit->b01; // 16
    if (*bloco_4B & bit->b07) aux ^= bit->b02; //  7
    if (*bloco_4B & bit->b20) aux ^= bit->b03; // 20
    if (*bloco_4B & bit->b21) aux ^= bit->b04; // 21
    if (*bloco_4B & bit->b29) aux ^= bit->b05; // 29
    if (*bloco_4B & bit->b12) aux ^= bit->b06; // 12
    if (*bloco_4B & bit->b28) aux ^= bit->b07; // 28
    if (*bloco_4B & bit->b17) aux ^= bit->b08; // 17

    if (*bloco_4B & bit->b01) aux ^= bit->b09; //  1
    if (*bloco_4B & bit->b15) aux ^= bit->b10; // 15
    if (*bloco_4B & bit->b23) aux ^= bit->b11; // 23
    if (*bloco_4B & bit->b26) aux ^= bit->b12; // 26
    if (*bloco_4B & bit->b05) aux ^= bit->b13; //  5
    if (*bloco_4B & bit->b18) aux ^= bit->b14; // 18
    if (*bloco_4B & bit->b31) aux ^= bit->b15; // 31
    if (*bloco_4B & bit->b10) aux ^= bit->b16; // 10

    if (*bloco_4B & bit->b02) aux ^= bit->b17; //  2
    if (*bloco_4B & bit->b08) aux ^= bit->b18; //  8
    if (*bloco_4B & bit->b24) aux ^= bit->b19; // 24
    if (*bloco_4B & bit->b14) aux ^= bit->b20; // 14
    if (*bloco_4B & bit->b32) aux ^= bit->b21; // 32
    if (*bloco_4B & bit->b27) aux ^= bit->b22; // 27
    if (*bloco_4B & bit->b03) aux ^= bit->b23; //  3
    if (*bloco_4B & bit->b09) aux ^= bit->b24; //  9

    if (*bloco_4B & bit->b19) aux ^= bit->b25; // 19
    if (*bloco_4B & bit->b13) aux ^= bit->b26; // 13
    if (*bloco_4B & bit->b30) aux ^= bit->b27; // 30
    if (*bloco_4B & bit->b06) aux ^= bit->b28; //  6
    if (*bloco_4B & bit->b22) aux ^= bit->b29; // 22
    if (*bloco_4B & bit->b11) aux ^= bit->b30; // 11
    if (*bloco_4B & bit->b04) aux ^= bit->b31; //  4
    if (*bloco_4B & bit->b25) aux ^= bit->b32; // 25

    *bloco_4B = aux;
    // end-permutacaoP

} // end-funcaoF (unsigned int *bloco_4B, tBloco6B *chave, t32UBits *bit)

/**
 * Função decifra a mensagem contida em um arquivo s/log
 * Modo de operação ECB - Electronic Code Book Mode
 * @param t32UBits *bit, FILE *f_in, FILE *f_out, tChave *chave
 * @return void
 */

void ecb (t32UBits *bit, FILE *f_in, FILE *f_out, tChave *chave)
{
	// Variáveis
    tBloco8B bloco;
    tBloco8B permutacao;
    size_t tam_bloco_lido;
    size_t tam_1byte = sizeof(char);
    size_t tam_meio_bloco = TAM_MEIO_BLOCO;
    unsigned int fun;
    unsigned int left;
    unsigned int right;
	unsigned int byte1 = 0xff000000;
    unsigned int byte2 = 0xff0000;
    unsigned int byte3 = 0xff00;
    unsigned int byte4 = 0xff;
    unsigned int flagL, flagR;
    int msb = MSB;

    while (feof(f_in) == 0)
    {

        /**
    	 * leProximoBloco
    	 */
	    fread(&bloco.l, tam_1byte, tam_meio_bloco, f_in);

	    if (feof(f_in) == 0)
	    {
		    fread(&bloco.r, tam_1byte, tam_meio_bloco, f_in);
		    // end-leProximoBloco

		    // ----------------------------------------------
	        
	        /**
	         * aplicaPermutacaoInicial
	         *  58 50 42 34 26 18 10 2
			 *  60 52 44 36 28 20 12 4
			 *  62 54 46 38 30 22 14 6
			 *  64 56 48 40 32 24 16 8
			 *  57 49 41 33 25 17 9  1
			 *  59 51 43 35 27 19 11 3
			 *  61 53 45 37 29 21 13 5
			 *  63 55 47 39 31 23 15 7 
	         */
		    permutacao.l = 0x0;
	    	permutacao.r = 0x0;
	        
	        if (bloco.r & bit->b26) permutacao.l ^= bit->b01; // 58
		    if (bloco.r & bit->b18) permutacao.l ^= bit->b02; // 50
		    if (bloco.r & bit->b10) permutacao.l ^= bit->b03; // 42
		    if (bloco.r & bit->b02) permutacao.l ^= bit->b04; // 34
		    if (bloco.l & bit->b26) permutacao.l ^= bit->b05; // 26
		    if (bloco.l & bit->b18) permutacao.l ^= bit->b06; // 18
		    if (bloco.l & bit->b10) permutacao.l ^= bit->b07; // 10
		    if (bloco.l & bit->b02) permutacao.l ^= bit->b08; // 2
		    
		    if (bloco.r & bit->b28) permutacao.l ^= bit->b09; // 60
		    if (bloco.r & bit->b20) permutacao.l ^= bit->b10; // 52
		    if (bloco.r & bit->b12) permutacao.l ^= bit->b11; // 44
		    if (bloco.r & bit->b04) permutacao.l ^= bit->b12; // 36
		    if (bloco.l & bit->b28) permutacao.l ^= bit->b13; // 28
		    if (bloco.l & bit->b20) permutacao.l ^= bit->b14; // 20
		    if (bloco.l & bit->b12) permutacao.l ^= bit->b15; // 12
		    if (bloco.l & bit->b04) permutacao.l ^= bit->b16; // 4
		    
		    if (bloco.r & bit->b30) permutacao.l ^= bit->b17; // 62
		    if (bloco.r & bit->b22) permutacao.l ^= bit->b18; // 54
		    if (bloco.r & bit->b14) permutacao.l ^= bit->b19; // 46
		    if (bloco.r & bit->b06) permutacao.l ^= bit->b20; // 38
		    if (bloco.l & bit->b30) permutacao.l ^= bit->b21; // 30
		    if (bloco.l & bit->b22) permutacao.l ^= bit->b22; // 22
		    if (bloco.l & bit->b14) permutacao.l ^= bit->b23; // 14
		    if (bloco.l & bit->b06) permutacao.l ^= bit->b24; // 6
		    
		    if (bloco.r & bit->b32) permutacao.l ^= bit->b25; // 64
		    if (bloco.r & bit->b24) permutacao.l ^= bit->b26; // 56
		    if (bloco.r & bit->b16) permutacao.l ^= bit->b27; // 48
		    if (bloco.r & bit->b08) permutacao.l ^= bit->b28; // 40
		    if (bloco.l & bit->b32) permutacao.l ^= bit->b29; // 32
		    if (bloco.l & bit->b24) permutacao.l ^= bit->b30; // 24
		    if (bloco.l & bit->b16) permutacao.l ^= bit->b31; // 16
		    if (bloco.l & bit->b08) permutacao.l ^= bit->b32; // 8
		    
		    if (bloco.r & bit->b25) permutacao.r ^= bit->b01; // 57
		    if (bloco.r & bit->b17) permutacao.r ^= bit->b02; // 49
		    if (bloco.r & bit->b09) permutacao.r ^= bit->b03; // 41
		    if (bloco.r & bit->b01) permutacao.r ^= bit->b04; // 33
		    if (bloco.l & bit->b25) permutacao.r ^= bit->b05; // 25
		    if (bloco.l & bit->b17) permutacao.r ^= bit->b06; // 17
		    if (bloco.l & bit->b09) permutacao.r ^= bit->b07; // 9
		    if (bloco.l & bit->b01) permutacao.r ^= bit->b08; // 1
		    
		    if (bloco.r & bit->b27) permutacao.r ^= bit->b09; // 59
		    if (bloco.r & bit->b19) permutacao.r ^= bit->b10; // 51
		    if (bloco.r & bit->b11) permutacao.r ^= bit->b11; // 43
		    if (bloco.r & bit->b03) permutacao.r ^= bit->b12; // 35
		    if (bloco.l & bit->b27) permutacao.r ^= bit->b13; // 27
		    if (bloco.l & bit->b19) permutacao.r ^= bit->b14; // 19
		    if (bloco.l & bit->b11) permutacao.r ^= bit->b15; // 11
		    if (bloco.l & bit->b03) permutacao.r ^= bit->b16; // 3
		    
		    if (bloco.r & bit->b29) permutacao.r ^= bit->b17; // 61
		    if (bloco.r & bit->b21) permutacao.r ^= bit->b18; // 53
		    if (bloco.r & bit->b13) permutacao.r ^= bit->b19; // 45
		    if (bloco.r & bit->b05) permutacao.r ^= bit->b20; // 37
		    if (bloco.l & bit->b29) permutacao.r ^= bit->b21; // 29
		    if (bloco.l & bit->b21) permutacao.r ^= bit->b22; // 21
		    if (bloco.l & bit->b13) permutacao.r ^= bit->b23; // 13
		    if (bloco.l & bit->b05) permutacao.r ^= bit->b24; // 5
		    
		    if (bloco.r & bit->b31) permutacao.r ^= bit->b25; // 63
		    if (bloco.r & bit->b23) permutacao.r ^= bit->b26; // 55
		    if (bloco.r & bit->b15) permutacao.r ^= bit->b27; // 47
		    if (bloco.r & bit->b07) permutacao.r ^= bit->b28; // 39
		    if (bloco.l & bit->b31) permutacao.r ^= bit->b29; // 31
		    if (bloco.l & bit->b23) permutacao.r ^= bit->b30; // 23
		    if (bloco.l & bit->b15) permutacao.r ^= bit->b31; // 15
		    if (bloco.l & bit->b07) permutacao.r ^= bit->b32; // 7

		    bloco = permutacao;
		    // end-aplicaPermutacaoInicial

		    // ----------------------------------------------

	        /**
	    	 * aplicaFeistel
	    	 */

		    // ----------------- ROUND 01 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c16, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
	   	    // ----------------- ROUND 02 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c15, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
		    // ----------------- ROUND 03 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c14, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
		    // ----------------- ROUND 04 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c13, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
		    // ----------------- ROUND 05 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c12, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
		    // ----------------- ROUND 06 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c11, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
		    // ----------------- ROUND 07 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c10, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
		    // ----------------- ROUND 08 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c9, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
		    // ----------------- ROUND 09 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c8, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
		    // ----------------- ROUND 10 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c7, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
		    // ----------------- ROUND 11 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c6, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
		    // ----------------- ROUND 12 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c5, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
		    // ----------------- ROUND 13 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c4, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
		    // ----------------- ROUND 14 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c3, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
		    // ----------------- ROUND 15 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c2, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
		    // ----------------- ROUND 16 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c1, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        // Swap para saida
		    bloco.r = left;
		    bloco.l = right;
		    // end-aplicaFeistel

		    // ----------------------------------------------

	        /**
	    	 * aplicaPermutacaoInversa
	    	 *  40 8 48 16 56 24 64 32
			 *  39 7 47 15 55 23 63 31
			 *  38 6 46 14 54 22 62 30
			 *  37 5 45 13 53 21 61 29
			 *  36 4 44 12 52 20 60 28
			 *  35 3 43 11 51 19 59 27
			 *  34 2 42 10 50 18 58 26
			 *  33 1 41 9  49 17 57 25 
	    	 */
		    permutacao.l = 0x0;
	    	permutacao.r = 0x0;
	        
	        if (bloco.r & bit->b08) permutacao.l ^= bit->b01; // 40
		    if (bloco.l & bit->b08) permutacao.l ^= bit->b02; // 8
		    
		    if (bloco.r & bit->b16) permutacao.l ^= bit->b03; // 48
		    if (bloco.l & bit->b16) permutacao.l ^= bit->b04; // 16
		    
		    if (bloco.r & bit->b24) permutacao.l ^= bit->b05; // 56
		    if (bloco.l & bit->b24) permutacao.l ^= bit->b06; // 24
		    
		    if (bloco.r & bit->b32) permutacao.l ^= bit->b07; // 64
		    if (bloco.l & bit->b32) permutacao.l ^= bit->b08; // 32
		    
		    if (bloco.r & bit->b07) permutacao.l ^= bit->b09; // 39
		    if (bloco.l & bit->b07) permutacao.l ^= bit->b10; // 7
		    
		    if (bloco.r & bit->b15) permutacao.l ^= bit->b11; // 47
		    if (bloco.l & bit->b15) permutacao.l ^= bit->b12; // 15
		    
		    if (bloco.r & bit->b23) permutacao.l ^= bit->b13; // 55
		    if (bloco.l & bit->b23) permutacao.l ^= bit->b14; // 23
		    
		    if (bloco.r & bit->b31) permutacao.l ^= bit->b15; // 63
		    if (bloco.l & bit->b31) permutacao.l ^= bit->b16; // 31
		    
		    if (bloco.r & bit->b06) permutacao.l ^= bit->b17; // 38
		    if (bloco.l & bit->b06) permutacao.l ^= bit->b18; // 6
		    
		    if (bloco.r & bit->b14) permutacao.l ^= bit->b19; // 46
		    if (bloco.l & bit->b14) permutacao.l ^= bit->b20; // 14
		    
		    if (bloco.r & bit->b22) permutacao.l ^= bit->b21; // 54
		    if (bloco.l & bit->b22) permutacao.l ^= bit->b22; // 22
		    
		    if (bloco.r & bit->b30) permutacao.l ^= bit->b23; // 62
		    if (bloco.l & bit->b30) permutacao.l ^= bit->b24; // 30
		    
		    if (bloco.r & bit->b05) permutacao.l ^= bit->b25; // 37
		    if (bloco.l & bit->b05) permutacao.l ^= bit->b26; // 5
		    
		    if (bloco.r & bit->b13) permutacao.l ^= bit->b27; // 45
		    if (bloco.l & bit->b13) permutacao.l ^= bit->b28; // 13
		    
		    if (bloco.r & bit->b21) permutacao.l ^= bit->b29; // 53
		    if (bloco.l & bit->b21) permutacao.l ^= bit->b30; // 21
		    
		    if (bloco.r & bit->b29) permutacao.l ^= bit->b31; // 61
		    if (bloco.l & bit->b29) permutacao.l ^= bit->b32; // 29
		    
		    if (bloco.r & bit->b04) permutacao.r ^= bit->b01; // 36
		    if (bloco.l & bit->b04) permutacao.r ^= bit->b02; // 4
		    
		    if (bloco.r & bit->b12) permutacao.r ^= bit->b03; // 44
		    if (bloco.l & bit->b12) permutacao.r ^= bit->b04; // 12
		    
		    if (bloco.r & bit->b20) permutacao.r ^= bit->b05; // 52
		    if (bloco.l & bit->b20) permutacao.r ^= bit->b06; // 20
		    
		    if (bloco.r & bit->b28) permutacao.r ^= bit->b07; // 60
		    if (bloco.l & bit->b28) permutacao.r ^= bit->b08; // 28
		    
		    if (bloco.r & bit->b03) permutacao.r ^= bit->b09; // 35
		    if (bloco.l & bit->b03) permutacao.r ^= bit->b10; // 3
		    
		    if (bloco.r & bit->b11) permutacao.r ^= bit->b11; // 43
		    if (bloco.l & bit->b11) permutacao.r ^= bit->b12; // 11
		    
		    if (bloco.r & bit->b19) permutacao.r ^= bit->b13; // 51
		    if (bloco.l & bit->b19) permutacao.r ^= bit->b14; // 19
		    
		    if (bloco.r & bit->b27) permutacao.r ^= bit->b15; // 59
		    if (bloco.l & bit->b27) permutacao.r ^= bit->b16; // 27
		    
		    if (bloco.r & bit->b02) permutacao.r ^= bit->b17; // 34
		    if (bloco.l & bit->b02) permutacao.r ^= bit->b18; // 2
		    
		    if (bloco.r & bit->b10) permutacao.r ^= bit->b19; // 42
		    if (bloco.l & bit->b10) permutacao.r ^= bit->b20; // 10
		    
		    if (bloco.r & bit->b18) permutacao.r ^= bit->b21; // 50
		    if (bloco.l & bit->b18) permutacao.r ^= bit->b22; // 18
		    
		    if (bloco.r & bit->b26) permutacao.r ^= bit->b23; // 58
		    if (bloco.l & bit->b26) permutacao.r ^= bit->b24; // 26
		    
		    if (bloco.r & bit->b01) permutacao.r ^= bit->b25; // 33
		    if (bloco.l & bit->b01) permutacao.r ^= bit->b26; // 1
		    
		    if (bloco.r & bit->b09) permutacao.r ^= bit->b27; // 41
		    if (bloco.l & bit->b09) permutacao.r ^= bit->b28; // 9
		    
		    if (bloco.r & bit->b17) permutacao.r ^= bit->b29; // 49
		    if (bloco.l & bit->b17) permutacao.r ^= bit->b30; // 17
		    
		    if (bloco.r & bit->b25) permutacao.r ^= bit->b31; // 57
		    if (bloco.l & bit->b25) permutacao.r ^= bit->b32; // 25
		    
		    bloco = permutacao;
	        // end-aplicaPermutacaoInversa

		    // ----------------------------------------------

	        /**
	         * escreveBlocoSaida
	         */
	        flagL = 4;
	        flagR = 4;
	        if ((bloco.l & byte1) == byte1) flagL--;
	        if ((bloco.l & byte2) == byte2) flagL--;
	        if ((bloco.l & byte3) == byte3) flagL--;
	        if ((bloco.l & byte4) == byte4) flagL--;

	        if ((bloco.r & byte1) == byte1) flagR--;
	        if ((bloco.r & byte2) == byte2) flagR--;
	        if ((bloco.r & byte3) == byte3) flagR--;
	        if ((bloco.r & byte4) == byte4) flagR--;

	        // Escreve saida no arquivo
	        fwrite(&bloco.l, tam_1byte, flagL, f_out);
	        fwrite(&bloco.r, tam_1byte, flagR, f_out);
	        
	        if (flagL < 4 || flagR < 4) break;
	        // end-escreveBlocoSaida
    	}
    }
    
} // end-ecb (t32UBits *bit, FILE *f_in, FILE *f_out, tChave *chave)

/**
 * Função decifra a mensagem contida em um arquivo s/log
 * Modo de operação CBC - Cipher Block Chaining
 * @param t32UBits *bit, FILE *f_in, FILE *f_out, tChave *chave
 * @return void
 */

void cbc (t32UBits *bit, FILE *f_in, FILE *f_out, tChave *chave)
{
	// Variáveis
	tBloco8B vi;
    tBloco8B aux;
    tBloco8B bloco;
    tBloco8B permutacao;
    size_t tam_bloco_lido;
    size_t tam_1byte = sizeof(char);
    size_t tam_meio_bloco = TAM_MEIO_BLOCO;
    unsigned int fun;
    unsigned int left;
    unsigned int right;
	unsigned int byte1 = 0xff000000;
    unsigned int byte2 = 0xff0000;
    unsigned int byte3 = 0xff00;
    unsigned int byte4 = 0xff;
    unsigned int flagL, flagR;
    int msb = MSB;

    // inicializaVI
	vi.l = 0x55555555;
	vi.r = 0x55555555;

    while (feof(f_in) == 0)
    {

        /**
    	 * leProximoBloco
    	 */
	    fread(&bloco.l, tam_1byte, tam_meio_bloco, f_in);

	    if (feof(f_in) == 0)
	    {
		    fread(&bloco.r, tam_1byte, tam_meio_bloco, f_in);
		    // end-leProximoBloco

		    // ----------------------------------------------

		    // armazena bloco p/ prox VI
		    aux.l = bloco.l;
		    aux.r = bloco.r;

		    // ----------------------------------------------
	        
	        /**
	         * aplicaPermutacaoInicial
	         *  58 50 42 34 26 18 10 2
			 *  60 52 44 36 28 20 12 4
			 *  62 54 46 38 30 22 14 6
			 *  64 56 48 40 32 24 16 8
			 *  57 49 41 33 25 17 9  1
			 *  59 51 43 35 27 19 11 3
			 *  61 53 45 37 29 21 13 5
			 *  63 55 47 39 31 23 15 7 
	         */
		    permutacao.l = 0x0;
	    	permutacao.r = 0x0;
	        
	        if (bloco.r & bit->b26) permutacao.l ^= bit->b01; // 58
		    if (bloco.r & bit->b18) permutacao.l ^= bit->b02; // 50
		    if (bloco.r & bit->b10) permutacao.l ^= bit->b03; // 42
		    if (bloco.r & bit->b02) permutacao.l ^= bit->b04; // 34
		    if (bloco.l & bit->b26) permutacao.l ^= bit->b05; // 26
		    if (bloco.l & bit->b18) permutacao.l ^= bit->b06; // 18
		    if (bloco.l & bit->b10) permutacao.l ^= bit->b07; // 10
		    if (bloco.l & bit->b02) permutacao.l ^= bit->b08; // 2
		    
		    if (bloco.r & bit->b28) permutacao.l ^= bit->b09; // 60
		    if (bloco.r & bit->b20) permutacao.l ^= bit->b10; // 52
		    if (bloco.r & bit->b12) permutacao.l ^= bit->b11; // 44
		    if (bloco.r & bit->b04) permutacao.l ^= bit->b12; // 36
		    if (bloco.l & bit->b28) permutacao.l ^= bit->b13; // 28
		    if (bloco.l & bit->b20) permutacao.l ^= bit->b14; // 20
		    if (bloco.l & bit->b12) permutacao.l ^= bit->b15; // 12
		    if (bloco.l & bit->b04) permutacao.l ^= bit->b16; // 4
		    
		    if (bloco.r & bit->b30) permutacao.l ^= bit->b17; // 62
		    if (bloco.r & bit->b22) permutacao.l ^= bit->b18; // 54
		    if (bloco.r & bit->b14) permutacao.l ^= bit->b19; // 46
		    if (bloco.r & bit->b06) permutacao.l ^= bit->b20; // 38
		    if (bloco.l & bit->b30) permutacao.l ^= bit->b21; // 30
		    if (bloco.l & bit->b22) permutacao.l ^= bit->b22; // 22
		    if (bloco.l & bit->b14) permutacao.l ^= bit->b23; // 14
		    if (bloco.l & bit->b06) permutacao.l ^= bit->b24; // 6
		    
		    if (bloco.r & bit->b32) permutacao.l ^= bit->b25; // 64
		    if (bloco.r & bit->b24) permutacao.l ^= bit->b26; // 56
		    if (bloco.r & bit->b16) permutacao.l ^= bit->b27; // 48
		    if (bloco.r & bit->b08) permutacao.l ^= bit->b28; // 40
		    if (bloco.l & bit->b32) permutacao.l ^= bit->b29; // 32
		    if (bloco.l & bit->b24) permutacao.l ^= bit->b30; // 24
		    if (bloco.l & bit->b16) permutacao.l ^= bit->b31; // 16
		    if (bloco.l & bit->b08) permutacao.l ^= bit->b32; // 8
		    
		    if (bloco.r & bit->b25) permutacao.r ^= bit->b01; // 57
		    if (bloco.r & bit->b17) permutacao.r ^= bit->b02; // 49
		    if (bloco.r & bit->b09) permutacao.r ^= bit->b03; // 41
		    if (bloco.r & bit->b01) permutacao.r ^= bit->b04; // 33
		    if (bloco.l & bit->b25) permutacao.r ^= bit->b05; // 25
		    if (bloco.l & bit->b17) permutacao.r ^= bit->b06; // 17
		    if (bloco.l & bit->b09) permutacao.r ^= bit->b07; // 9
		    if (bloco.l & bit->b01) permutacao.r ^= bit->b08; // 1
		    
		    if (bloco.r & bit->b27) permutacao.r ^= bit->b09; // 59
		    if (bloco.r & bit->b19) permutacao.r ^= bit->b10; // 51
		    if (bloco.r & bit->b11) permutacao.r ^= bit->b11; // 43
		    if (bloco.r & bit->b03) permutacao.r ^= bit->b12; // 35
		    if (bloco.l & bit->b27) permutacao.r ^= bit->b13; // 27
		    if (bloco.l & bit->b19) permutacao.r ^= bit->b14; // 19
		    if (bloco.l & bit->b11) permutacao.r ^= bit->b15; // 11
		    if (bloco.l & bit->b03) permutacao.r ^= bit->b16; // 3
		    
		    if (bloco.r & bit->b29) permutacao.r ^= bit->b17; // 61
		    if (bloco.r & bit->b21) permutacao.r ^= bit->b18; // 53
		    if (bloco.r & bit->b13) permutacao.r ^= bit->b19; // 45
		    if (bloco.r & bit->b05) permutacao.r ^= bit->b20; // 37
		    if (bloco.l & bit->b29) permutacao.r ^= bit->b21; // 29
		    if (bloco.l & bit->b21) permutacao.r ^= bit->b22; // 21
		    if (bloco.l & bit->b13) permutacao.r ^= bit->b23; // 13
		    if (bloco.l & bit->b05) permutacao.r ^= bit->b24; // 5
		    
		    if (bloco.r & bit->b31) permutacao.r ^= bit->b25; // 63
		    if (bloco.r & bit->b23) permutacao.r ^= bit->b26; // 55
		    if (bloco.r & bit->b15) permutacao.r ^= bit->b27; // 47
		    if (bloco.r & bit->b07) permutacao.r ^= bit->b28; // 39
		    if (bloco.l & bit->b31) permutacao.r ^= bit->b29; // 31
		    if (bloco.l & bit->b23) permutacao.r ^= bit->b30; // 23
		    if (bloco.l & bit->b15) permutacao.r ^= bit->b31; // 15
		    if (bloco.l & bit->b07) permutacao.r ^= bit->b32; // 7

		    bloco = permutacao;
		    // end-aplicaPermutacaoInicial

		    // ----------------------------------------------

	        /**
	         * aplicaFeistel
	         */

	        // ----------------- ROUND 01 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c16, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
	        // ----------------- ROUND 02 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c15, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
	        // ----------------- ROUND 03 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c14, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
	        // ----------------- ROUND 04 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c13, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
	        // ----------------- ROUND 05 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c12, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
	        // ----------------- ROUND 06 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c11, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
	        // ----------------- ROUND 07 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c10, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
	        // ----------------- ROUND 08 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c9, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
	        // ----------------- ROUND 09 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c8, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
	        // ----------------- ROUND 10 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c7, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
	        // ----------------- ROUND 11 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c6, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
	        // ----------------- ROUND 12 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c5, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
	        // ----------------- ROUND 13 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c4, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
	        // ----------------- ROUND 14 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c3, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
	        // ----------------- ROUND 15 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c2, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        //Swap para próximo round
	        bloco.r = right;
	        bloco.l = left;
	        // ----------------- ROUND 16 -------------------
	        // Aplica função F
	        fun = bloco.r;
	        funcaoF(&fun, &chave->c1, bit);
	        // XOR Li
	        right = fun ^ bloco.l;
	        left = bloco.r;
	        // Swap para saida
	        bloco.r = left;
	        bloco.l = right;
	        // end-aplicaFeistel

		    // ----------------------------------------------

	        /**
	    	 * aplicaPermutacaoInversa
	    	 *  40 8 48 16 56 24 64 32
			 *  39 7 47 15 55 23 63 31
			 *  38 6 46 14 54 22 62 30
			 *  37 5 45 13 53 21 61 29
			 *  36 4 44 12 52 20 60 28
			 *  35 3 43 11 51 19 59 27
			 *  34 2 42 10 50 18 58 26
			 *  33 1 41 9  49 17 57 25 
	    	 */
		    permutacao.l = 0x0;
	    	permutacao.r = 0x0;
	        
	        if (bloco.r & bit->b08) permutacao.l ^= bit->b01; // 40
		    if (bloco.l & bit->b08) permutacao.l ^= bit->b02; // 8
		    
		    if (bloco.r & bit->b16) permutacao.l ^= bit->b03; // 48
		    if (bloco.l & bit->b16) permutacao.l ^= bit->b04; // 16
		    
		    if (bloco.r & bit->b24) permutacao.l ^= bit->b05; // 56
		    if (bloco.l & bit->b24) permutacao.l ^= bit->b06; // 24
		    
		    if (bloco.r & bit->b32) permutacao.l ^= bit->b07; // 64
		    if (bloco.l & bit->b32) permutacao.l ^= bit->b08; // 32
		    
		    if (bloco.r & bit->b07) permutacao.l ^= bit->b09; // 39
		    if (bloco.l & bit->b07) permutacao.l ^= bit->b10; // 7
		    
		    if (bloco.r & bit->b15) permutacao.l ^= bit->b11; // 47
		    if (bloco.l & bit->b15) permutacao.l ^= bit->b12; // 15
		    
		    if (bloco.r & bit->b23) permutacao.l ^= bit->b13; // 55
		    if (bloco.l & bit->b23) permutacao.l ^= bit->b14; // 23
		    
		    if (bloco.r & bit->b31) permutacao.l ^= bit->b15; // 63
		    if (bloco.l & bit->b31) permutacao.l ^= bit->b16; // 31
		    
		    if (bloco.r & bit->b06) permutacao.l ^= bit->b17; // 38
		    if (bloco.l & bit->b06) permutacao.l ^= bit->b18; // 6
		    
		    if (bloco.r & bit->b14) permutacao.l ^= bit->b19; // 46
		    if (bloco.l & bit->b14) permutacao.l ^= bit->b20; // 14
		    
		    if (bloco.r & bit->b22) permutacao.l ^= bit->b21; // 54
		    if (bloco.l & bit->b22) permutacao.l ^= bit->b22; // 22
		    
		    if (bloco.r & bit->b30) permutacao.l ^= bit->b23; // 62
		    if (bloco.l & bit->b30) permutacao.l ^= bit->b24; // 30
		    
		    if (bloco.r & bit->b05) permutacao.l ^= bit->b25; // 37
		    if (bloco.l & bit->b05) permutacao.l ^= bit->b26; // 5
		    
		    if (bloco.r & bit->b13) permutacao.l ^= bit->b27; // 45
		    if (bloco.l & bit->b13) permutacao.l ^= bit->b28; // 13
		    
		    if (bloco.r & bit->b21) permutacao.l ^= bit->b29; // 53
		    if (bloco.l & bit->b21) permutacao.l ^= bit->b30; // 21
		    
		    if (bloco.r & bit->b29) permutacao.l ^= bit->b31; // 61
		    if (bloco.l & bit->b29) permutacao.l ^= bit->b32; // 29
		    
		    if (bloco.r & bit->b04) permutacao.r ^= bit->b01; // 36
		    if (bloco.l & bit->b04) permutacao.r ^= bit->b02; // 4
		    
		    if (bloco.r & bit->b12) permutacao.r ^= bit->b03; // 44
		    if (bloco.l & bit->b12) permutacao.r ^= bit->b04; // 12
		    
		    if (bloco.r & bit->b20) permutacao.r ^= bit->b05; // 52
		    if (bloco.l & bit->b20) permutacao.r ^= bit->b06; // 20
		    
		    if (bloco.r & bit->b28) permutacao.r ^= bit->b07; // 60
		    if (bloco.l & bit->b28) permutacao.r ^= bit->b08; // 28
		    
		    if (bloco.r & bit->b03) permutacao.r ^= bit->b09; // 35
		    if (bloco.l & bit->b03) permutacao.r ^= bit->b10; // 3
		    
		    if (bloco.r & bit->b11) permutacao.r ^= bit->b11; // 43
		    if (bloco.l & bit->b11) permutacao.r ^= bit->b12; // 11
		    
		    if (bloco.r & bit->b19) permutacao.r ^= bit->b13; // 51
		    if (bloco.l & bit->b19) permutacao.r ^= bit->b14; // 19
		    
		    if (bloco.r & bit->b27) permutacao.r ^= bit->b15; // 59
		    if (bloco.l & bit->b27) permutacao.r ^= bit->b16; // 27
		    
		    if (bloco.r & bit->b02) permutacao.r ^= bit->b17; // 34
		    if (bloco.l & bit->b02) permutacao.r ^= bit->b18; // 2
		    
		    if (bloco.r & bit->b10) permutacao.r ^= bit->b19; // 42
		    if (bloco.l & bit->b10) permutacao.r ^= bit->b20; // 10
		    
		    if (bloco.r & bit->b18) permutacao.r ^= bit->b21; // 50
		    if (bloco.l & bit->b18) permutacao.r ^= bit->b22; // 18
		    
		    if (bloco.r & bit->b26) permutacao.r ^= bit->b23; // 58
		    if (bloco.l & bit->b26) permutacao.r ^= bit->b24; // 26
		    
		    if (bloco.r & bit->b01) permutacao.r ^= bit->b25; // 33
		    if (bloco.l & bit->b01) permutacao.r ^= bit->b26; // 1
		    
		    if (bloco.r & bit->b09) permutacao.r ^= bit->b27; // 41
		    if (bloco.l & bit->b09) permutacao.r ^= bit->b28; // 9
		    
		    if (bloco.r & bit->b17) permutacao.r ^= bit->b29; // 49
		    if (bloco.l & bit->b17) permutacao.r ^= bit->b30; // 17
		    
		    if (bloco.r & bit->b25) permutacao.r ^= bit->b31; // 57
		    if (bloco.l & bit->b25) permutacao.r ^= bit->b32; // 25
		    
		    bloco = permutacao;
	        // end-aplicaPermutacaoInversa

	        // ----------------------------------------------

	        // aplicaVI
		    bloco.l ^= vi.l;
		    bloco.r ^= vi.r;
		    // Swap VI para proximo bloco
		    vi.l = aux.l;
		    vi.r = aux.r;

		    // ----------------------------------------------

	        /**
	    	 * escreveBlocoSaida
	    	 */
	        flagL = 4;
	        flagR = 4;
	        if ((bloco.l & byte1) == byte1) flagL--;
	        if ((bloco.l & byte2) == byte2) flagL--;
	        if ((bloco.l & byte3) == byte3) flagL--;
	        if ((bloco.l & byte4) == byte4) flagL--;

	        if ((bloco.r & byte1) == byte1) flagR--;
	        if ((bloco.r & byte2) == byte2) flagR--;
	        if ((bloco.r & byte3) == byte3) flagR--;
	        if ((bloco.r & byte4) == byte4) flagR--;

	        // Escreve saida no arquivo
	        fwrite(&bloco.l, tam_1byte, flagL, f_out);
	        fwrite(&bloco.r, tam_1byte, flagR, f_out);

	        if (flagL < 4 || flagR < 4) break;
		    // end-escreveBlocoSaida
    	}
    }
    
} // end-cbc (t32UBits *bit, FILE *f_in, FILE *f_out, tChave *chave)

/**
 * Função para permutação de blocos de 8 p/ 7Bytes
 * 57 49 41 33 25 17  9 * 57 49 41 33 25 17  9  1
 *  1 58 50 42 34 26 18 * 58 50 42 34 26 18 10  2
 * 10  2 59 51 43 35 27 * 59 51 43 35 27 19 11  3
 * 19 11  3 60 52 44 36 *
 * -------------------- * -----------------------
 * 63 55 47 39 31 23 15 * 60 52 44 36 63 55 47 39
 *  7 62 54 46 38 30 22 * 31 23 15  7 62 54 46 38
 * 14  6 61 53 45 37 29 * 30 22 14  6 61 53 45 37
 * 21 13  5 28 20 12  4 * 29 21 13  5 28 20 12  4
 ---------------------------------------------------
 *  1  2  3  4  5  6  7  8 * 33 34 35 36 37 38 39 40
 *  9 10 11 12 13 14 15 16 * 41 42 43 44 45 46 47 48
 * 17 18 19 20 21 22 23 24 * 49 50 51 52 53 54 55 56
 * 25 26 27 28 29 30 31 32 * 57 58 59 60 61 62 63 64
 * @param tBloco8B *chave_in, tBloco7B *chave_out, t32UBits *bit
 * @return void
 */

void pc1Bloco8B (tBloco8B *chave_in, tBloco7B *chave_out, t32UBits *bit)
{
    chave_out->byte_1   = 0x0;
    chave_out->byte_2   = 0x0;
    chave_out->byte_3   = 0x0;
    chave_out->byte_4_7 = 0x0;
    
    if (chave_in->r & bit->b25) chave_out->byte_1 ^= bit->b25; // 57
    if (chave_in->r & bit->b17) chave_out->byte_1 ^= bit->b26; // 49
    if (chave_in->r & bit->b09) chave_out->byte_1 ^= bit->b27; // 41
    if (chave_in->r & bit->b01) chave_out->byte_1 ^= bit->b28; // 33

    if (chave_in->l & bit->b25) chave_out->byte_1 ^= bit->b29; // 25
    if (chave_in->l & bit->b17) chave_out->byte_1 ^= bit->b30; // 17
    if (chave_in->l & bit->b09) chave_out->byte_1 ^= bit->b31; //  9
    if (chave_in->l & bit->b01) chave_out->byte_1 ^= bit->b32; //  1

    if (chave_in->r & bit->b26) chave_out->byte_2 ^= bit->b25; // 58
    if (chave_in->r & bit->b18) chave_out->byte_2 ^= bit->b26; // 50
    if (chave_in->r & bit->b10) chave_out->byte_2 ^= bit->b27; // 42
    if (chave_in->r & bit->b02) chave_out->byte_2 ^= bit->b28; // 34

    if (chave_in->l & bit->b26) chave_out->byte_2 ^= bit->b29; // 26
    if (chave_in->l & bit->b18) chave_out->byte_2 ^= bit->b30; // 18
    if (chave_in->l & bit->b10) chave_out->byte_2 ^= bit->b31; // 10
    if (chave_in->l & bit->b02) chave_out->byte_2 ^= bit->b32; //  2

    if (chave_in->r & bit->b27) chave_out->byte_3 ^= bit->b25; // 59
    if (chave_in->r & bit->b19) chave_out->byte_3 ^= bit->b26; // 51
    if (chave_in->r & bit->b11) chave_out->byte_3 ^= bit->b27; // 43
    if (chave_in->r & bit->b03) chave_out->byte_3 ^= bit->b28; // 35

    if (chave_in->l & bit->b27) chave_out->byte_3 ^= bit->b29; // 27
    if (chave_in->l & bit->b19) chave_out->byte_3 ^= bit->b30; // 19
    if (chave_in->l & bit->b11) chave_out->byte_3 ^= bit->b31; // 11
    if (chave_in->l & bit->b03) chave_out->byte_3 ^= bit->b32; //  3

    if (chave_in->r & bit->b28) chave_out->byte_4_7 ^= bit->b01; // 60
    if (chave_in->r & bit->b20) chave_out->byte_4_7 ^= bit->b02; // 52
    if (chave_in->r & bit->b12) chave_out->byte_4_7 ^= bit->b03; // 44
    if (chave_in->r & bit->b04) chave_out->byte_4_7 ^= bit->b04; // 36

    if (chave_in->l & bit->b31) chave_out->byte_4_7 ^= bit->b05; // 63
    if (chave_in->l & bit->b23) chave_out->byte_4_7 ^= bit->b06; // 55
    if (chave_in->l & bit->b15) chave_out->byte_4_7 ^= bit->b07; // 47
    if (chave_in->l & bit->b07) chave_out->byte_4_7 ^= bit->b08; // 39

    if (chave_in->r & bit->b31) chave_out->byte_4_7 ^= bit->b09; // 31
    if (chave_in->r & bit->b23) chave_out->byte_4_7 ^= bit->b10; // 23
    if (chave_in->r & bit->b15) chave_out->byte_4_7 ^= bit->b11; // 15
    if (chave_in->r & bit->b07) chave_out->byte_4_7 ^= bit->b12; //  7

    if (chave_in->l & bit->b30) chave_out->byte_4_7 ^= bit->b13; // 62
    if (chave_in->l & bit->b22) chave_out->byte_4_7 ^= bit->b14; // 54
    if (chave_in->l & bit->b14) chave_out->byte_4_7 ^= bit->b15; // 46
    if (chave_in->l & bit->b06) chave_out->byte_4_7 ^= bit->b16; // 38

    if (chave_in->r & bit->b30) chave_out->byte_4_7 ^= bit->b17; // 30
    if (chave_in->r & bit->b22) chave_out->byte_4_7 ^= bit->b18; // 22
    if (chave_in->r & bit->b14) chave_out->byte_4_7 ^= bit->b19; // 14
    if (chave_in->r & bit->b06) chave_out->byte_4_7 ^= bit->b20; //  6

    if (chave_in->l & bit->b29) chave_out->byte_4_7 ^= bit->b21; // 61
    if (chave_in->l & bit->b21) chave_out->byte_4_7 ^= bit->b22; // 53
    if (chave_in->l & bit->b13) chave_out->byte_4_7 ^= bit->b23; // 45
    if (chave_in->l & bit->b05) chave_out->byte_4_7 ^= bit->b24; // 37

    if (chave_in->r & bit->b29) chave_out->byte_4_7 ^= bit->b25; // 29
    if (chave_in->r & bit->b21) chave_out->byte_4_7 ^= bit->b26; // 21
    if (chave_in->r & bit->b13) chave_out->byte_4_7 ^= bit->b27; // 13
    if (chave_in->r & bit->b05) chave_out->byte_4_7 ^= bit->b28; //  5

    if (chave_in->l & bit->b28) chave_out->byte_4_7 ^= bit->b29; // 28
    if (chave_in->l & bit->b20) chave_out->byte_4_7 ^= bit->b30; // 20
    if (chave_in->l & bit->b12) chave_out->byte_4_7 ^= bit->b31; // 12
    if (chave_in->l & bit->b04) chave_out->byte_4_7 ^= bit->b32; //  4

} // end-pc1Bloco8B (tBloco8B *chave_in, tBloco7B *chave_out, t32UBits *&bit)

/**
 * Função para permutação de blocos de 7 p/ 6Bytes
 * 14 17 11 24  1  5 * 14 17 11 24  1  5  3 28
 *  3 28 15  6 21 10 * 15  6 21 10 23 19 12  4
 * 23 19 12  4 26  8 *
 * 16  7 27 20 13  2 *
 * ----------------- * -----------------------
 * 41 52 31 37 47 55 * 26  8 16  7 27 20 13  2
 * 30 40 51 45 33 48 * 41 52 31 37 47 55 30 40
 * 44 49 39 56 34 53 * 51 45 33 48 44 49 39 56
 * 46 42 50 36 29 32 * 34 53 46 42 50 36 29 32
 ------------------ Bloco7B --------------------
 * byte_1 =    1  2  3  4  5  6  7  8 // 25 a 32
 * byte_2 =    9 10 11 12 13 14 15 16 // 25 a 32
 * byte_3 =   17 18 19 20 21 22 23 24 // 25 a 32
 * byte_4_7 = 25 26 27 28 29 30 31 32 // 01 a 08
 *            33 34 35 36 37 38 39 40 // 09 a 16
 *            41 42 43 44 45 46 47 48 // 17 a 24
 *            49 50 51 52 53 54 55 56 // 25 a 32
 ------------------ Bloco6B --------------------
 * byte_1 =    1  2  3  4  5  6  7  8 // 25 a 32
 * byte_2 =    9 10 11 12 13 14 15 16 // 25 a 32
 * byte_3_7 = 17 18 19 20 21 22 23 24 // 01 a 08
 *            25 26 27 28 29 30 31 32 // 09 a 16
 *            33 34 35 36 37 38 39 40 // 17 a 24
 *            41 42 43 44 45 46 47 48 // 25 a 32
 * @param tBloco7B *chave_in, tBloco6B *chave_out, t32UBits *bit
 * @return void
 */

void pc2Bloco7B (tBloco7B *chave_in, tBloco6B *chave_out, t32UBits *bit)
{
    chave_out->byte_1   = 0x0;
    chave_out->byte_2   = 0x0;
    chave_out->byte_3_6 = 0x0;

    if (chave_in->byte_2 & bit->b30)   chave_out->byte_1 ^= bit->b25; // 14
    if (chave_in->byte_3 & bit->b25)   chave_out->byte_1 ^= bit->b26; // 17
    if (chave_in->byte_2 & bit->b27)   chave_out->byte_1 ^= bit->b27; // 11
    if (chave_in->byte_3 & bit->b32)   chave_out->byte_1 ^= bit->b28; // 24

    if (chave_in->byte_1 & bit->b25)   chave_out->byte_1 ^= bit->b29; //  1
    if (chave_in->byte_1 & bit->b29)   chave_out->byte_1 ^= bit->b30; //  5
    if (chave_in->byte_1 & bit->b27)   chave_out->byte_1 ^= bit->b31; //  3
    if (chave_in->byte_4_7 & bit->b04) chave_out->byte_1 ^= bit->b32; // 28

    if (chave_in->byte_2 & bit->b31)   chave_out->byte_2 ^= bit->b25; // 15
    if (chave_in->byte_1 & bit->b30)   chave_out->byte_2 ^= bit->b26; //  6
    if (chave_in->byte_3 & bit->b29)   chave_out->byte_2 ^= bit->b27; // 21
    if (chave_in->byte_2 & bit->b26)   chave_out->byte_2 ^= bit->b28; // 10

    if (chave_in->byte_3 & bit->b31)   chave_out->byte_2 ^= bit->b29; // 23
    if (chave_in->byte_3 & bit->b27)   chave_out->byte_2 ^= bit->b30; // 19
    if (chave_in->byte_2 & bit->b28)   chave_out->byte_2 ^= bit->b31; // 12
    if (chave_in->byte_1 & bit->b28)   chave_out->byte_2 ^= bit->b32; //  4

    if (chave_in->byte_4_7 & bit->b02) chave_out->byte_3_6 ^= bit->b01; // 26
    if (chave_in->byte_1 & bit->b32)   chave_out->byte_3_6 ^= bit->b02; //  8
    if (chave_in->byte_2 & bit->b32)   chave_out->byte_3_6 ^= bit->b03; // 16
    if (chave_in->byte_1 & bit->b31)   chave_out->byte_3_6 ^= bit->b04; //  7

    if (chave_in->byte_4_7 & bit->b03) chave_out->byte_3_6 ^= bit->b05; // 27
    if (chave_in->byte_3 & bit->b28)   chave_out->byte_3_6 ^= bit->b06; // 20
    if (chave_in->byte_2 & bit->b29)   chave_out->byte_3_6 ^= bit->b07; // 13
    if (chave_in->byte_1 & bit->b26)   chave_out->byte_3_6 ^= bit->b08; //  2

    if (chave_in->byte_4_7 & bit->b17) chave_out->byte_3_6 ^= bit->b09; // 41
    if (chave_in->byte_4_7 & bit->b28) chave_out->byte_3_6 ^= bit->b10; // 52
    if (chave_in->byte_4_7 & bit->b07) chave_out->byte_3_6 ^= bit->b11; // 31
    if (chave_in->byte_4_7 & bit->b13) chave_out->byte_3_6 ^= bit->b12; // 37

    if (chave_in->byte_4_7 & bit->b23) chave_out->byte_3_6 ^= bit->b13; // 47
    if (chave_in->byte_4_7 & bit->b31) chave_out->byte_3_6 ^= bit->b14; // 55
    if (chave_in->byte_4_7 & bit->b06) chave_out->byte_3_6 ^= bit->b15; // 30
    if (chave_in->byte_4_7 & bit->b16) chave_out->byte_3_6 ^= bit->b16; // 40

    if (chave_in->byte_4_7 & bit->b27) chave_out->byte_3_6 ^= bit->b17; // 51
    if (chave_in->byte_4_7 & bit->b21) chave_out->byte_3_6 ^= bit->b18; // 45
    if (chave_in->byte_4_7 & bit->b09) chave_out->byte_3_6 ^= bit->b19; // 33
    if (chave_in->byte_4_7 & bit->b24) chave_out->byte_3_6 ^= bit->b20; // 48

    if (chave_in->byte_4_7 & bit->b20) chave_out->byte_3_6 ^= bit->b21; // 44
    if (chave_in->byte_4_7 & bit->b25) chave_out->byte_3_6 ^= bit->b22; // 49
    if (chave_in->byte_4_7 & bit->b15) chave_out->byte_3_6 ^= bit->b23; // 39
    if (chave_in->byte_4_7 & bit->b32) chave_out->byte_3_6 ^= bit->b24; // 56

    if (chave_in->byte_4_7 & bit->b10) chave_out->byte_3_6 ^= bit->b25; // 34
    if (chave_in->byte_4_7 & bit->b29) chave_out->byte_3_6 ^= bit->b26; // 53
    if (chave_in->byte_4_7 & bit->b22) chave_out->byte_3_6 ^= bit->b27; // 46
    if (chave_in->byte_4_7 & bit->b18) chave_out->byte_3_6 ^= bit->b28; // 42

    if (chave_in->byte_4_7 & bit->b26) chave_out->byte_3_6 ^= bit->b29; // 50
    if (chave_in->byte_4_7 & bit->b12) chave_out->byte_3_6 ^= bit->b30; // 36
    if (chave_in->byte_4_7 & bit->b05) chave_out->byte_3_6 ^= bit->b31; // 29
    if (chave_in->byte_4_7 & bit->b08) chave_out->byte_3_6 ^= bit->b32; // 32

} // end-pc2Bloco7B (tBloco7B *chave_in, tBloco6B *chave_out, t32UBits *bit)

/**
 * Função realiza deslocamento circular a esquerda
 * no bloco de 7 Bytes.
 ------------------ Bloco7B --------------------
 * byte_1 =    1  2  3  4  5  6  7  8 // 25 a 32
 * byte_2 =    9 10 11 12 13 14 15 16 // 25 a 32
 * byte_3 =   17 18 19 20 21 22 23 24 // 25 a 32
 * byte_4_7 = 25 26 27 28|29 30 31 32 // 01 a 08
 *            33 34 35 36 37 38 39 40 // 09 a 16
 *            41 42 43 44 45 46 47 48 // 17 a 24
 *            49 50 51 52 53 54 55 56 // 25 a 32
 ------------------ Bloco7B p ------------------
 * byte_1 =    2  3  4  5  6  7  8  9 // 25 a 32
 * byte_2 =   10 11 12 13 14 15 16 17 // 25 a 32
 * byte_3 =   18 19 20 21 22 23 24 25 // 25 a 32
 * byte_4_7 = 26 27 28  1|30 31 32 33 // 01 a 08
 *            34 35 36 37 38 39 40 41 // 09 a 16
 *            42 43 44 45 46 47 48 49 // 17 a 24
 *            50 51 52 53 54 55 56 29 // 25 a 32
 * @param tBloco7B *bloco, t32UBits *bit
 * @return void
 */

void leftShiftCircular7B(tBloco7B *bloco, t32UBits *bit)
{
    tBloco7B aux;
    aux.byte_1   = 0x0;
    aux.byte_2   = 0x0;
    aux.byte_3   = 0x0;
    aux.byte_4_7 = 0x0;

    // Permutação nos primeiros 28bits
    if (bloco->byte_1 & bit->b26) aux.byte_1 ^= bit->b25; // 02
    if (bloco->byte_1 & bit->b27) aux.byte_1 ^= bit->b26; // 03
    if (bloco->byte_1 & bit->b28) aux.byte_1 ^= bit->b27; // 04
    if (bloco->byte_1 & bit->b29) aux.byte_1 ^= bit->b28; // 05
    if (bloco->byte_1 & bit->b30) aux.byte_1 ^= bit->b29; // 06
    if (bloco->byte_1 & bit->b31) aux.byte_1 ^= bit->b30; // 07
    if (bloco->byte_1 & bit->b32) aux.byte_1 ^= bit->b31; // 08
    if (bloco->byte_2 & bit->b25) aux.byte_1 ^= bit->b32; // 09
    
    if (bloco->byte_2 & bit->b26) aux.byte_2 ^= bit->b25; // 10
    if (bloco->byte_2 & bit->b27) aux.byte_2 ^= bit->b26; // 11
    if (bloco->byte_2 & bit->b28) aux.byte_2 ^= bit->b27; // 12
    if (bloco->byte_2 & bit->b29) aux.byte_2 ^= bit->b28; // 13
    if (bloco->byte_2 & bit->b30) aux.byte_2 ^= bit->b29; // 14
    if (bloco->byte_2 & bit->b31) aux.byte_2 ^= bit->b30; // 15
    if (bloco->byte_2 & bit->b32) aux.byte_2 ^= bit->b31; // 16
    if (bloco->byte_3 & bit->b25) aux.byte_2 ^= bit->b32; // 17
    
    if (bloco->byte_3   & bit->b26) aux.byte_3 ^= bit->b25; // 18
    if (bloco->byte_3   & bit->b27) aux.byte_3 ^= bit->b26; // 19
    if (bloco->byte_3   & bit->b28) aux.byte_3 ^= bit->b27; // 20
    if (bloco->byte_3   & bit->b29) aux.byte_3 ^= bit->b28; // 21
    if (bloco->byte_3   & bit->b30) aux.byte_3 ^= bit->b29; // 22
    if (bloco->byte_3   & bit->b31) aux.byte_3 ^= bit->b30; // 23
    if (bloco->byte_3   & bit->b32) aux.byte_3 ^= bit->b31; // 24
    if (bloco->byte_4_7 & bit->b01) aux.byte_3 ^= bit->b32; // 25
    
    if (bloco->byte_4_7 & bit->b02) aux.byte_4_7 ^= bit->b01; // 26
    if (bloco->byte_4_7 & bit->b03) aux.byte_4_7 ^= bit->b02; // 27
    if (bloco->byte_4_7 & bit->b04) aux.byte_4_7 ^= bit->b03; // 28
    if (bloco->byte_1   & bit->b25) aux.byte_4_7 ^= bit->b04; // 29

    // Permutação nos ultimos 28bits
    if (bloco->byte_4_7 & bit->b06) aux.byte_4_7 ^= bit->b05; // 30
    if (bloco->byte_4_7 & bit->b07) aux.byte_4_7 ^= bit->b06; // 31
    if (bloco->byte_4_7 & bit->b08) aux.byte_4_7 ^= bit->b07; // 32
    if (bloco->byte_4_7 & bit->b09) aux.byte_4_7 ^= bit->b08; // 33

    if (bloco->byte_4_7 & bit->b10) aux.byte_4_7 ^= bit->b09; // 34
    if (bloco->byte_4_7 & bit->b11) aux.byte_4_7 ^= bit->b10; // 35
    if (bloco->byte_4_7 & bit->b12) aux.byte_4_7 ^= bit->b11; // 36
    if (bloco->byte_4_7 & bit->b13) aux.byte_4_7 ^= bit->b12; // 37
    if (bloco->byte_4_7 & bit->b14) aux.byte_4_7 ^= bit->b13; // 38
    if (bloco->byte_4_7 & bit->b15) aux.byte_4_7 ^= bit->b14; // 39
    if (bloco->byte_4_7 & bit->b16) aux.byte_4_7 ^= bit->b15; // 40
    if (bloco->byte_4_7 & bit->b17) aux.byte_4_7 ^= bit->b16; // 41

    if (bloco->byte_4_7 & bit->b18) aux.byte_4_7 ^= bit->b17; // 42
    if (bloco->byte_4_7 & bit->b19) aux.byte_4_7 ^= bit->b18; // 43
    if (bloco->byte_4_7 & bit->b20) aux.byte_4_7 ^= bit->b19; // 44
    if (bloco->byte_4_7 & bit->b21) aux.byte_4_7 ^= bit->b20; // 45
    if (bloco->byte_4_7 & bit->b22) aux.byte_4_7 ^= bit->b21; // 46
    if (bloco->byte_4_7 & bit->b23) aux.byte_4_7 ^= bit->b22; // 47
    if (bloco->byte_4_7 & bit->b24) aux.byte_4_7 ^= bit->b23; // 48
    if (bloco->byte_4_7 & bit->b25) aux.byte_4_7 ^= bit->b24; // 49

    if (bloco->byte_4_7 & bit->b26) aux.byte_4_7 ^= bit->b25; // 50
    if (bloco->byte_4_7 & bit->b27) aux.byte_4_7 ^= bit->b26; // 51
    if (bloco->byte_4_7 & bit->b28) aux.byte_4_7 ^= bit->b27; // 52
    if (bloco->byte_4_7 & bit->b29) aux.byte_4_7 ^= bit->b28; // 53
    if (bloco->byte_4_7 & bit->b30) aux.byte_4_7 ^= bit->b29; // 54
    if (bloco->byte_4_7 & bit->b31) aux.byte_4_7 ^= bit->b30; // 55
    if (bloco->byte_4_7 & bit->b32) aux.byte_4_7 ^= bit->b31; // 56
    if (bloco->byte_4_7 & bit->b05) aux.byte_4_7 ^= bit->b32; // 57
    
    *bloco = aux;

}// end-leftShiftCircular4B (unsigned int *bloco, int qnt_shift)

/**
 * Função imprime unsigned int em binário no arquivo
 * @param unsigned int c, t32UBits *bit, FILE *f_out
 * @return void
 */

void fImprima4BBin (unsigned int c, t32UBits *bit, FILE *f_out)
{

    // 01 - 08
    (c & bit->b01)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b02)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b03)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b04)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b05)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b06)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b07)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b08)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');

    // 09 - 16
    (c & bit->b09)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b10)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b11)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b12)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b13)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b14)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b15)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b16)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');

    // 17 - 24
    (c & bit->b17)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b18)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b19)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b20)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b21)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b22)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b23)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b24)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    
    // 25 - 32
    (c & bit->b25)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b26)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b27)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b28)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b29)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b30)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b31)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b32)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');

    fprintf(f_out, " | ");

}// end-fImprima4BBin (unsigned int c, t32UBits *bit)