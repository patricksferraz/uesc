/*
 *---------------------------------------------------------------------
 *
 *   File    : conversores.h
 *   Created : 2017-10-28
 *   Modified: 2017-10-28
 *
 *   Conversores de tipo
 *
 *---------------------------------------------------------------------
 */

#ifndef _CONVERSORES_H
#define _CONVERSORES_H

/**
 * --------------------------------------------------------------------------
 * INCLUDES
 * --------------------------------------------------------------------------
 * 
 */

#include "valoresBinarios.h"
#include "permutadores.h"

/**
 * --------------------------------------------------------------------------
 * PROTÓTIPOS
 * --------------------------------------------------------------------------
 * 
 */

void imprima1BBin  (unsigned char c, t32UBits *bit);
void imprima4BBin  (unsigned int c, t32UBits *bit);
void fImprima1BBin (unsigned char c, t32UBits *bit, FILE *f_out);
void fImprima4BBin (unsigned int c, t32UBits *bit, FILE *f_out);
void fImprima6BBin (tBloco6B *bloco, t32UBits *bit, FILE *f_out);
void fImprima7BBin (tBloco7B *bloco, t32UBits *bit, FILE *f_out);

/**
 * --------------------------------------------------------------------------
 * FUNÇÕES
 * --------------------------------------------------------------------------
 * 
 */

/**
 * Função imprime unsigned int em binário
 * @param unsigned int c, t32UBits *bit
 * @return void
 */

void imprima4BBin (unsigned int c, t32UBits *bit)
{

    // 01 - 08
    (c & bit->b01)? printf("1"): printf("0");
    (c & bit->b02)? printf("1"): printf("0");
    (c & bit->b03)? printf("1"): printf("0");
    (c & bit->b04)? printf("1"): printf("0");
    (c & bit->b05)? printf("1"): printf("0");
    (c & bit->b06)? printf("1"): printf("0");
    (c & bit->b07)? printf("1"): printf("0");
    (c & bit->b08)? printf("1"): printf("0");

    // 09 - 16
    (c & bit->b09)? printf("1"): printf("0");
    (c & bit->b10)? printf("1"): printf("0");
    (c & bit->b11)? printf("1"): printf("0");
    (c & bit->b12)? printf("1"): printf("0");
    (c & bit->b13)? printf("1"): printf("0");
    (c & bit->b14)? printf("1"): printf("0");
    (c & bit->b15)? printf("1"): printf("0");
    (c & bit->b16)? printf("1"): printf("0");

    // 17 - 24
    (c & bit->b17)? printf("1"): printf("0");
    (c & bit->b18)? printf("1"): printf("0");
    (c & bit->b19)? printf("1"): printf("0");
    (c & bit->b20)? printf("1"): printf("0");
    (c & bit->b21)? printf("1"): printf("0");
    (c & bit->b22)? printf("1"): printf("0");
    (c & bit->b23)? printf("1"): printf("0");
    (c & bit->b24)? printf("1"): printf("0");
    
    // 25 - 32
    (c & bit->b25)? printf("1"): printf("0");
    (c & bit->b26)? printf("1"): printf("0");
    (c & bit->b27)? printf("1"): printf("0");
    (c & bit->b28)? printf("1"): printf("0");
    (c & bit->b29)? printf("1"): printf("0");
    (c & bit->b30)? printf("1"): printf("0");
    (c & bit->b31)? printf("1"): printf("0");
    (c & bit->b32)? printf("1"): printf("0");

}// end-imprima4BBin (unsigned int c, t32UBits *bit)

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
 * Função imprime unsigned char em binário
 * @param unsigned int c, t32UBits *bit
 * @return void
 */

void imprima1BBin (unsigned char c, t32UBits *bit)
{
    
    // 01 - 08
    (c & bit->b25)? printf("1"): printf("0");
    (c & bit->b26)? printf("1"): printf("0");
    (c & bit->b27)? printf("1"): printf("0");
    (c & bit->b28)? printf("1"): printf("0");
    (c & bit->b29)? printf("1"): printf("0");
    (c & bit->b30)? printf("1"): printf("0");
    (c & bit->b31)? printf("1"): printf("0");
    (c & bit->b32)? printf("1"): printf("0");

}// end-imprima4BBin (unsigned char c, t32UBits *bit)

/**
 * Função imprime unsigned char em binário no arquivo
 * @param unsigned int c, t32UBits *bit, FILE *f_out
 * @return void
 */

void fImprima1BBin (unsigned char c, t32UBits *bit, FILE *f_out)
{

    // 01 - 08
    (c & bit->b25)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b26)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b27)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b28)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b29)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b30)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b31)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');
    (c & bit->b32)? fprintf(f_out, "%c", '1'): fprintf(f_out, "%c", '0');

}// end-fImprima1BBin (unsigned char c, t32UBits *bit, FILE *f_out)

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

    fprintf(f_out, " |");

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

    fprintf(f_out, " |");

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
    
    fprintf(f_out, " |");
    
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

    fprintf(f_out, " |");

} // end-fImprima7BBin (tBloco7B *bloco, t32UBits *bit, FILE *f_out)

#endif
