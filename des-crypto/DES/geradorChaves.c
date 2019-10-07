/*
 *---------------------------------------------------------------------
 *
 *   File    : redeFeistelCP8B.c
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

#define TAM_MEIO_BLOCO 4

/**
 * --------------------------------------------------------------------------
 * TIPOS
 * --------------------------------------------------------------------------
 */

typedef struct
{
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
 * PROTÒTIPOS DE FUNÇÔES
 * --------------------------------------------------------------------
 */

void pc1Bloco8B          (tBloco8B *chave_in, tBloco7B *chave_out, t32UBits *bit);
void pc2Bloco7B          (tBloco7B *chave_in, tBloco6B *chave_out, t32UBits *bit);
void fImprima4BBin       (unsigned int c, t32UBits *bit, FILE *f_out);
void fImprima6BBin       (tBloco6B *bloco, t32UBits *bit, FILE *f_out);
void fImprima7BBin       (tBloco7B *bloco, t32UBits *bit, FILE *f_out);
void leftShiftCircular7B (tBloco7B *bloco, t32UBits *bit);

/**
 * --------------------------------------------------------------------
 * VARIÁVEIS GLOBAIS
 * --------------------------------------------------------------------
 */

FILE *f_log;

/**
 * --------------------------------------------------------------------
 * FUNÇÃO PRINCIPAL MAIN
 * --------------------------------------------------------------------
 */

int main (int argc, char **argv)
{
    // Variáveis
    tBloco7B chave_7B;
    tBloco8B chave_8B;
    t32UBits bit;
    tChave   c;
    int      i, j;
    size_t tam_meio_bloco = TAM_MEIO_BLOCO;
    char * nome_arq_log = (char *) malloc(21 * sizeof(char));
    
    // Verifica a quantidade de argumentos
    if (argc != 2)
        printf("uso:\n"
            "\tGerar chaves:\t ./geradorChaves k\n"
            "\tonde:\n"
            "\tk\teh uma chave de oito bytes\n");
    else
    {
        // armazenandoChave
        if (strlen(argv[1]) != 8)
        {
            printf("Erro, favor digitar uma chave de oito bytes\n");
            exit(1);
        }
        else
            for (i = 0, j = tam_meio_bloco; i < tam_meio_bloco; i++, j++)
            {
                chave_8B.l = (chave_8B.l << 8) | argv[1][i];
                chave_8B.r = (chave_8B.r << 8) | argv[1][j];
            }
        // end-armazenandoChave
        
        // inicializando32CasasBinarias
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

        strcpy(nome_arq_log, "keysched-");
        if ((f_log = fopen(strcat( strcat(nome_arq_log, argv[1]) , ".txt" ), "w")) == NULL)
        {
            printf("Erro ao criar arquivo de log\n");
            exit(1);
        }

        fprintf(f_log, "Chave eh: %s\n", argv[1]);
        fprintf(f_log, "Binario: ");
        fImprima4BBin(chave_8B.l, &bit, f_log);
        fImprima4BBin(chave_8B.r, &bit, f_log);
        fprintf(f_log, "\n\n");

        fprintf(f_log, "+------");
        fprintf(f_log, "+------------------------------");
        fprintf(f_log, "+------------------------------");
        fprintf(f_log, "+-------------------------------------------------------------");
        fprintf(f_log, "+--------------------------------------------------+\n");
        fprintf(f_log, "| %4s | %-28s | %-28s | %-59s | %-48s |\n", "i", "Ci", "Di", "Li", "Ki");
        fprintf(f_log, "+------");
        fprintf(f_log, "+------------------------------");
        fprintf(f_log, "+------------------------------");
        fprintf(f_log, "+-------------------------------------------------------------");
        fprintf(f_log, "+--------------------------------------------------+\n");
        fprintf(f_log, "| %4d | ", 1);

        // gereChaves
        pc1Bloco8B(&chave_8B, &chave_7B, &bit);
        fImprima7BBin(&chave_7B, &bit, f_log);

        // Geração de c1
        leftShiftCircular7B(&chave_7B, &bit);
        fImprima7BBin(&chave_7B, &bit, f_log);
        pc2Bloco7B(&chave_7B, &c.c1, &bit);
        fImprima6BBin(&c.c1, &bit, f_log);

        // Geração de c2
        fprintf(f_log, "\n| %4d | ", 2);
        fImprima7BBin(&chave_7B, &bit, f_log);
        leftShiftCircular7B(&chave_7B, &bit);
        fImprima7BBin(&chave_7B, &bit, f_log);
        pc2Bloco7B(&chave_7B, &c.c2, &bit);
        fImprima6BBin(&c.c2, &bit, f_log);

        // Geração de c3
        fprintf(f_log, "\n| %4d | ", 3);
        fImprima7BBin(&chave_7B, &bit, f_log);
        leftShiftCircular7B(&chave_7B, &bit);
        leftShiftCircular7B(&chave_7B, &bit);
        fImprima7BBin(&chave_7B, &bit, f_log);
        pc2Bloco7B(&chave_7B, &c.c3, &bit);
        fImprima6BBin(&c.c3, &bit, f_log);

        // Geração de c4
        fprintf(f_log, "\n| %4d | ", 4);
        fImprima7BBin(&chave_7B, &bit, f_log);
        leftShiftCircular7B(&chave_7B, &bit);
        leftShiftCircular7B(&chave_7B, &bit);
        fImprima7BBin(&chave_7B, &bit, f_log);
        pc2Bloco7B(&chave_7B, &c.c4, &bit);
        fImprima6BBin(&c.c4, &bit, f_log);

        // Geração de c5
        fprintf(f_log, "\n| %4d | ", 5);
        fImprima7BBin(&chave_7B, &bit, f_log);
        leftShiftCircular7B(&chave_7B, &bit);
        leftShiftCircular7B(&chave_7B, &bit);
        fImprima7BBin(&chave_7B, &bit, f_log);
        pc2Bloco7B(&chave_7B, &c.c5, &bit);
        fImprima6BBin(&c.c5, &bit, f_log);

        // Geração de c6
        fprintf(f_log, "\n| %4d | ", 6);
        fImprima7BBin(&chave_7B, &bit, f_log);
        leftShiftCircular7B(&chave_7B, &bit);
        leftShiftCircular7B(&chave_7B, &bit);
        fImprima7BBin(&chave_7B, &bit, f_log);
        pc2Bloco7B(&chave_7B, &c.c6, &bit);
        fImprima6BBin(&c.c6, &bit, f_log);

        // Geração de c7
        fprintf(f_log, "\n| %4d | ", 7);
        fImprima7BBin(&chave_7B, &bit, f_log);
        leftShiftCircular7B(&chave_7B, &bit);
        leftShiftCircular7B(&chave_7B, &bit);
        fImprima7BBin(&chave_7B, &bit, f_log);
        pc2Bloco7B(&chave_7B, &c.c7, &bit);
        fImprima6BBin(&c.c7, &bit, f_log);

        // Geração de c8
        fprintf(f_log, "\n| %4d | ", 8);
        fImprima7BBin(&chave_7B, &bit, f_log);
        leftShiftCircular7B(&chave_7B, &bit);
        leftShiftCircular7B(&chave_7B, &bit);
        fImprima7BBin(&chave_7B, &bit, f_log);
        pc2Bloco7B(&chave_7B, &c.c8, &bit);
        fImprima6BBin(&c.c8, &bit, f_log);

        // Geração de c9
        fprintf(f_log, "\n| %4d | ", 9);
        fImprima7BBin(&chave_7B, &bit, f_log);
        leftShiftCircular7B(&chave_7B, &bit);
        fImprima7BBin(&chave_7B, &bit, f_log);
        pc2Bloco7B(&chave_7B, &c.c9, &bit);
        fImprima6BBin(&c.c9, &bit, f_log);

        // Geração de c10
        fprintf(f_log, "\n| %4d | ", 10);
        fImprima7BBin(&chave_7B, &bit, f_log);
        leftShiftCircular7B(&chave_7B, &bit);
        leftShiftCircular7B(&chave_7B, &bit);
        fImprima7BBin(&chave_7B, &bit, f_log);
        pc2Bloco7B(&chave_7B, &c.c10, &bit);
        fImprima6BBin(&c.c10, &bit, f_log);

        // Geração de c11
        fprintf(f_log, "\n| %4d | ", 11);
        fImprima7BBin(&chave_7B, &bit, f_log);
        leftShiftCircular7B(&chave_7B, &bit);
        leftShiftCircular7B(&chave_7B, &bit);
        fImprima7BBin(&chave_7B, &bit, f_log);
        pc2Bloco7B(&chave_7B, &c.c11, &bit);
        fImprima6BBin(&c.c11, &bit, f_log);

        // Geração de c12
        fprintf(f_log, "\n| %4d | ", 12);
        fImprima7BBin(&chave_7B, &bit, f_log);
        leftShiftCircular7B(&chave_7B, &bit);
        leftShiftCircular7B(&chave_7B, &bit);
        fImprima7BBin(&chave_7B, &bit, f_log);
        pc2Bloco7B(&chave_7B, &c.c12, &bit);
        fImprima6BBin(&c.c12, &bit, f_log);

        // Geração de c13
        fprintf(f_log, "\n| %4d | ", 13);
        fImprima7BBin(&chave_7B, &bit, f_log);
        leftShiftCircular7B(&chave_7B, &bit);
        leftShiftCircular7B(&chave_7B, &bit);
        fImprima7BBin(&chave_7B, &bit, f_log);
        pc2Bloco7B(&chave_7B, &c.c13, &bit);
        fImprima6BBin(&c.c13, &bit, f_log);

        // Geração de c14
        fprintf(f_log, "\n| %4d | ", 14);
        fImprima7BBin(&chave_7B, &bit, f_log);
        leftShiftCircular7B(&chave_7B, &bit);
        leftShiftCircular7B(&chave_7B, &bit);
        fImprima7BBin(&chave_7B, &bit, f_log);
        pc2Bloco7B(&chave_7B, &c.c14, &bit);
        fImprima6BBin(&c.c14, &bit, f_log);

        // Geração de c15
        fprintf(f_log, "\n| %4d | ", 15);
        fImprima7BBin(&chave_7B, &bit, f_log);
        leftShiftCircular7B(&chave_7B, &bit);
        leftShiftCircular7B(&chave_7B, &bit);
        fImprima7BBin(&chave_7B, &bit, f_log);
        pc2Bloco7B(&chave_7B, &c.c15, &bit);
        fImprima6BBin(&c.c15, &bit, f_log);

        // Geração de c16
        fprintf(f_log, "\n| %4d | ", 16);
        fImprima7BBin(&chave_7B, &bit, f_log);
        leftShiftCircular7B(&chave_7B, &bit);
        fImprima7BBin(&chave_7B, &bit, f_log);
        pc2Bloco7B(&chave_7B, &c.c16, &bit);
        fImprima6BBin(&c.c16, &bit, f_log);
        // end-gereChaves

        fprintf(f_log, "\n+------");
        fprintf(f_log, "+------------------------------");
        fprintf(f_log, "+------------------------------");
        fprintf(f_log, "+-------------------------------------------------------------");
        fprintf(f_log, "+--------------------------------------------------+\n");
        fprintf(f_log, "| %4s | %-14s%14s | %-14s%14s | %-29s%30s | %-24s%24s |\n",
                       "-", "b01", "b28", "b29", "b56", "b01", "b56", "b01", "b48");
        fprintf(f_log, "+------");
        fprintf(f_log, "+------------------------------");
        fprintf(f_log, "+------------------------------");
        fprintf(f_log, "+-------------------------------------------------------------");
        fprintf(f_log, "+--------------------------------------------------+\n\n");

        // Fecha fluxo com arquivos
        fclose(f_log);
    }

    return 0;
    
} // end-main (int argc, char **argv)

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

}// end-fImprima4BBin (unsigned int c, t32UBits *bit)

/**
 * Função imprime bloco de 6 Bytes em binário no arquivo
 ------------------ Bloco6B --------------------
 * byte_1 =    1  2  3  4  5  6  7  8 // 25 a 32
 * byte_2 =    9 10 11 12 13 14 15 16 // 25 a 32
 * byte_3_6 = 17 18 19 20 21 22 23 24 // 01 a 08
 *            25 26 27 28 29 30 31 32 // 09 a 16
 *            33 34 35 36 37 38 39 40 // 17 a 24
 *            41 42 43 44 45 46 47 48 // 25 a 32
 * @param tBloco6B *bloco, t32UBits *bit, FILE *f_out
 * @return void
 */

void fImprima6BBin (tBloco6B *bloco, t32UBits *bit, FILE *f_out)
{

    // 01 - 08
    (bloco->byte_1 & bit->b25)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_1 & bit->b26)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_1 & bit->b27)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_1 & bit->b28)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_1 & bit->b29)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_1 & bit->b30)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_1 & bit->b31)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_1 & bit->b32)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');

    // 09 - 16
    (bloco->byte_2 & bit->b25)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_2 & bit->b26)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_2 & bit->b27)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_2 & bit->b28)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_2 & bit->b29)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_2 & bit->b30)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_2 & bit->b31)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_2 & bit->b32)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');

    // 17 - 24
    (bloco->byte_3_6 & bit->b01)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b02)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b03)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b04)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b05)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b06)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b07)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b08)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');

    //fprintf(f_out, " | ");

    // 25 - 32
    (bloco->byte_3_6 & bit->b09)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b10)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b11)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b12)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b13)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b14)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b15)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b16)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');

    // 33 - 40
    (bloco->byte_3_6 & bit->b17)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b18)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b19)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b20)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b21)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b22)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b23)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b24)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');

    // 41 - 48
    (bloco->byte_3_6 & bit->b25)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b26)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b27)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b28)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b29)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b30)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b31)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3_6 & bit->b32)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');

    fprintf(f_out, " | ");

} // end-fImprima6BBin (tBloco6B *bloco, t32UBits *bit, FILE *f_out)

/**
 * Função imprime bloco de 7 Bytes em binário no arquivo
 ------------------ Bloco7B --------------------
 * byte_1 =    1  2  3  4  5  6  7  8 // 25 a 32
 * byte_2 =    9 10 11 12 13 14 15 16 // 25 a 32
 * byte_3 =   17 18 19 20 21 22 23 24 // 25 a 32
 * byte_4_7 = 25 26 27 28 29 30 31 32 // 01 a 08
 *            33 34 35 36 37 38 39 40 // 09 a 16
 *            41 42 43 44 45 46 47 48 // 17 a 24
 *            49 50 51 52 53 54 55 56 // 25 a 32
 * @param tBloco7B *bloco, t32UBits *bit, FILE *f_out
 * @return void
 */

void fImprima7BBin (tBloco7B *bloco, t32UBits *bit, FILE *f_out)
{

    // 01 - 08
    (bloco->byte_1 & bit->b25)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_1 & bit->b26)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_1 & bit->b27)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_1 & bit->b28)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_1 & bit->b29)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_1 & bit->b30)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_1 & bit->b31)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_1 & bit->b32)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');

    // 09 - 16
    (bloco->byte_2 & bit->b25)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_2 & bit->b26)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_2 & bit->b27)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_2 & bit->b28)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_2 & bit->b29)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_2 & bit->b30)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_2 & bit->b31)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_2 & bit->b32)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');

    // 17 - 24
    (bloco->byte_3 & bit->b25)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3 & bit->b26)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3 & bit->b27)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3 & bit->b28)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3 & bit->b29)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3 & bit->b30)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3 & bit->b31)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_3 & bit->b32)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    
    // 25 - 28
    (bloco->byte_4_7 & bit->b01)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b02)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b03)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b04)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    
    fprintf(f_out, " | ");
    
    // 29 - 32
    (bloco->byte_4_7 & bit->b05)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b06)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b07)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b08)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');

    // 33 - 40
    (bloco->byte_4_7 & bit->b09)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b10)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b11)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b12)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b13)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b14)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b15)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b16)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');

    // 41 - 48
    (bloco->byte_4_7 & bit->b17)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b18)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b19)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b20)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b21)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b22)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b23)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b24)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');

    // 49 - 56
    (bloco->byte_4_7 & bit->b25)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b26)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b27)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b28)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b29)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b30)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b31)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (bloco->byte_4_7 & bit->b32)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');

    fprintf(f_out, " | ");

} // end-fImprima7BBin (tBloco7B *bloco, t32UBits *bit, FILE *f_out)