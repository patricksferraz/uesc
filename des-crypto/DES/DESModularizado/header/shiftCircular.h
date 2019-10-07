/*
 *---------------------------------------------------------------------
 *
 *   File    : shiftCircular.h
 *   Created : 2017-10-28
 *   Modified: 2017-10-28
 *
 *   Deslocamento circular de blocos de 4 Bytes 
 *
 *---------------------------------------------------------------------
 */

#ifndef _SHIFTCIRCULAR_H
#define _SHIFTCIRCULAR_H

/**
 * --------------------------------------------------------------------------
 * INCLUDES
 * --------------------------------------------------------------------------
 * 
 */

#include "permutadores.h"
#include "valoresBinarios.h"

/**
 * --------------------------------------------------------------------------
 * MACROS
 * --------------------------------------------------------------------------
 * 
 */

#define MSB 0x80000000
#define LSB 0x1

/**
 * --------------------------------------------------------------------------
 * PROTÓTIPOS
 * --------------------------------------------------------------------------
 * 
 */

void leftShiftCircular4B (unsigned int *bloco, int qnt_shift);
void leftShiftCircular7B (tBloco7B *bloco);

/**
 * --------------------------------------------------------------------------
 * FUNÇÕES
 * --------------------------------------------------------------------------
 * 
 */

/**
 * Função realiza deslocamento circular a esquerda
 * no bloco de 4 Bytes.
 * @param unsigned int *bloco, int qnt_shift
 * @return void
 */

void leftShiftCircular4B(unsigned int *bloco, int qnt_shift)
{
    unsigned int msb = MSB;
    unsigned int lsb = LSB;
    
    for ( ; qnt_shift > 0; qnt_shift--)
    {
        if (*bloco & msb)
            *bloco = (*bloco << 1) | lsb;
        else
            *bloco <<= 1;
    }

}// end-leftShiftCircular4B (unsigned int *bloco, int qnt_shift)

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
	if (bloco->byte_1 & bit->b26) aux.byte_1 ^= bit->b25; // 
    if (bloco->byte_1 & bit->b27) aux.byte_1 ^= bit->b26; // 
    if (bloco->byte_1 & bit->b28) aux.byte_1 ^= bit->b27; // 
    if (bloco->byte_1 & bit->b29) aux.byte_1 ^= bit->b28; // 
    if (bloco->byte_1 & bit->b30) aux.byte_1 ^= bit->b29; // 
    if (bloco->byte_1 & bit->b31) aux.byte_1 ^= bit->b30; // 
    if (bloco->byte_1 & bit->b32) aux.byte_1 ^= bit->b31; // 
    if (bloco->byte_2 & bit->b25) aux.byte_1 ^= bit->b32; // 
    
    if (bloco->byte_2 & bit->b26) aux.byte_2 ^= bit->b25; // 
    if (bloco->byte_2 & bit->b27) aux.byte_2 ^= bit->b26; // 
    if (bloco->byte_2 & bit->b28) aux.byte_2 ^= bit->b27; // 
    if (bloco->byte_2 & bit->b29) aux.byte_2 ^= bit->b28; // 
    if (bloco->byte_2 & bit->b30) aux.byte_2 ^= bit->b29; // 
    if (bloco->byte_2 & bit->b31) aux.byte_2 ^= bit->b30; // 
    if (bloco->byte_2 & bit->b32) aux.byte_2 ^= bit->b31; // 
    if (bloco->byte_3 & bit->b25) aux.byte_2 ^= bit->b32; // 
    
    if (bloco->byte_3   & bit->b26) aux.byte_3 ^= bit->b25; // 
    if (bloco->byte_3   & bit->b27) aux.byte_3 ^= bit->b26; // 
    if (bloco->byte_3   & bit->b28) aux.byte_3 ^= bit->b27; // 
    if (bloco->byte_3   & bit->b29) aux.byte_3 ^= bit->b28; // 
    if (bloco->byte_3   & bit->b30) aux.byte_3 ^= bit->b29; // 
    if (bloco->byte_3   & bit->b31) aux.byte_3 ^= bit->b30; // 
    if (bloco->byte_3   & bit->b32) aux.byte_3 ^= bit->b31; // 
    if (bloco->byte_4_7 & bit->b01) aux.byte_3 ^= bit->b32; // 
    
    if (bloco->byte_4_7 & bit->b02) aux.byte_4_7 ^= bit->b01; // 
    if (bloco->byte_4_7 & bit->b03) aux.byte_4_7 ^= bit->b02; // 
    if (bloco->byte_4_7 & bit->b04) aux.byte_4_7 ^= bit->b03; // 
    if (bloco->byte_1   & bit->b25) aux.byte_4_7 ^= bit->b04; // 

	// Permutação nos ultimos 28bits
    if (bloco->byte_4_7 & bit->b06) aux.byte_4_7 ^= bit->b05; // 
    if (bloco->byte_4_7 & bit->b07) aux.byte_4_7 ^= bit->b06; // 
    if (bloco->byte_4_7 & bit->b08) aux.byte_4_7 ^= bit->b07; // 
    if (bloco->byte_4_7 & bit->b09) aux.byte_4_7 ^= bit->b08; // 
    
    if (bloco->byte_4_7 & bit->b10) aux.byte_4_7 ^= bit->b09; // 
    if (bloco->byte_4_7 & bit->b11) aux.byte_4_7 ^= bit->b10; // 
    if (bloco->byte_4_7 & bit->b12) aux.byte_4_7 ^= bit->b11; // 
    if (bloco->byte_4_7 & bit->b13) aux.byte_4_7 ^= bit->b12; // 
    if (bloco->byte_4_7 & bit->b14) aux.byte_4_7 ^= bit->b13; // 
    if (bloco->byte_4_7 & bit->b15) aux.byte_4_7 ^= bit->b14; // 
    if (bloco->byte_4_7 & bit->b16) aux.byte_4_7 ^= bit->b15; // 
    if (bloco->byte_4_7 & bit->b17) aux.byte_4_7 ^= bit->b16; // 
    
    if (bloco->byte_4_7 & bit->b18) aux.byte_4_7 ^= bit->b17; // 
    if (bloco->byte_4_7 & bit->b19) aux.byte_4_7 ^= bit->b18; // 
    if (bloco->byte_4_7 & bit->b20) aux.byte_4_7 ^= bit->b19; // 
    if (bloco->byte_4_7 & bit->b21) aux.byte_4_7 ^= bit->b20; // 
    if (bloco->byte_4_7 & bit->b22) aux.byte_4_7 ^= bit->b21; // 
    if (bloco->byte_4_7 & bit->b23) aux.byte_4_7 ^= bit->b22; // 
    if (bloco->byte_4_7 & bit->b24) aux.byte_4_7 ^= bit->b23; // 
    if (bloco->byte_4_7 & bit->b25) aux.byte_4_7 ^= bit->b24; // 

    if (bloco->byte_4_7 & bit->b26) aux.byte_4_7 ^= bit->b25; // 
    if (bloco->byte_4_7 & bit->b27) aux.byte_4_7 ^= bit->b26; // 
    if (bloco->byte_4_7 & bit->b28) aux.byte_4_7 ^= bit->b27; // 
    if (bloco->byte_4_7 & bit->b29) aux.byte_4_7 ^= bit->b28; // 
    if (bloco->byte_4_7 & bit->b30) aux.byte_4_7 ^= bit->b29; // 
    if (bloco->byte_4_7 & bit->b31) aux.byte_4_7 ^= bit->b30; // 
    if (bloco->byte_4_7 & bit->b32) aux.byte_4_7 ^= bit->b31; // 
    if (bloco->byte_4_7 & bit->b05) aux.byte_4_7 ^= bit->b32; // 
    
	*bloco = aux;

}// end-leftShiftCircular4B (unsigned int *bloco, int qnt_shift)

#endif
