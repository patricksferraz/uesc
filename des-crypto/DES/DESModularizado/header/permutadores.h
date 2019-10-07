/*
 *---------------------------------------------------------------------
 *
 *   File    : permutadores.h
 *   Created : 2017-10-28
 *   Modified: 2017-10-28
 *
 *   Permutadores para aplicar na rede de Feistel 
 *
 *---------------------------------------------------------------------
 */

#ifndef _PERMUTADORES_H
#define _PERMUTADORES_H

/**
 * --------------------------------------------------------------------------
 * INCLUDES
 * --------------------------------------------------------------------------
 */

#include "valoresBinarios.h"

/**
 * --------------------------------------------------------------------------
 * TIPOS
 * --------------------------------------------------------------------------
 */

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

/**
 * --------------------------------------------------------------------------
 * PROTÓTIPOS
 * --------------------------------------------------------------------------
 */

void ipBloco8B        (tBloco8B *bloco_8B, t32UBits *bit);
void ipInversaBloco8B (tBloco8B *bloco_8B, t32UBits *bit);
void pc1Bloco8B       (tBloco8B *chave_in, tBloco7B *chave_out, t32UBits *bit);
void pc2Bloco7B       (tBloco7B *chave_in, tBloco6B *chave_out, t32UBits *bit);
void expansao4Bto6B   (unsigned int *bloco_4B, tBloco6B *bloco_6B, t32UBits *bit);
void funcaoF          (unsigned int *bloco_4B, tBloco6B *chave, t32UBits *bit);
void permutacaoP          (unsigned int *bloco_4B, t32UBits *bit);

/**
 * --------------------------------------------------------------------------
 * FUNÇÕES
 * --------------------------------------------------------------------------
 * 
 */

/**
 * Função para permutação de blocos de 8Bytes
 *  58 50 42 34 26 18 10 2
 *  60 52 44 36 28 20 12 4
 *  62 54 46 38 30 22 14 6
 *  64 56 48 40 32 24 16 8
 *  57 49 41 33 25 17 9  1
 *  59 51 43 35 27 19 11 3
 *  61 53 45 37 29 21 13 5
 *  63 55 47 39 31 23 15 7 
 * @param tBloco8B *bloco_8B, t32UBits *bit
 * @return void
 */

void ipBloco8B (tBloco8B *bloco_8B, t32UBits *bit)
{
    tBloco8B aux;
    aux.l = 0x0;
    aux.r = 0x0;
    
    if (bloco_8B->r & bit->b26) aux.l ^= bit->b01; // 58
    if (bloco_8B->r & bit->b18) aux.l ^= bit->b02; // 50
    if (bloco_8B->r & bit->b10) aux.l ^= bit->b03; // 42
    if (bloco_8B->r & bit->b02) aux.l ^= bit->b04; // 34
    if (bloco_8B->l & bit->b26) aux.l ^= bit->b05; // 26
    if (bloco_8B->l & bit->b18) aux.l ^= bit->b06; // 18
    if (bloco_8B->l & bit->b10) aux.l ^= bit->b07; // 10
    if (bloco_8B->l & bit->b02) aux.l ^= bit->b08; // 2
    
    if (bloco_8B->r & bit->b28) aux.l ^= bit->b09; // 60
    if (bloco_8B->r & bit->b20) aux.l ^= bit->b10; // 52
    if (bloco_8B->r & bit->b12) aux.l ^= bit->b11; // 44
    if (bloco_8B->r & bit->b04) aux.l ^= bit->b12; // 36
    if (bloco_8B->l & bit->b28) aux.l ^= bit->b13; // 28
    if (bloco_8B->l & bit->b20) aux.l ^= bit->b14; // 20
    if (bloco_8B->l & bit->b12) aux.l ^= bit->b15; // 12
    if (bloco_8B->l & bit->b04) aux.l ^= bit->b16; // 4
    
    if (bloco_8B->r & bit->b30) aux.l ^= bit->b17; // 62
    if (bloco_8B->r & bit->b22) aux.l ^= bit->b18; // 54
    if (bloco_8B->r & bit->b14) aux.l ^= bit->b19; // 46
    if (bloco_8B->r & bit->b06) aux.l ^= bit->b20; // 38
    if (bloco_8B->l & bit->b30) aux.l ^= bit->b21; // 30
    if (bloco_8B->l & bit->b22) aux.l ^= bit->b22; // 22
    if (bloco_8B->l & bit->b14) aux.l ^= bit->b23; // 14
    if (bloco_8B->l & bit->b06) aux.l ^= bit->b24; // 6
    
    if (bloco_8B->r & bit->b32) aux.l ^= bit->b25; // 64
    if (bloco_8B->r & bit->b24) aux.l ^= bit->b26; // 56
    if (bloco_8B->r & bit->b16) aux.l ^= bit->b27; // 48
    if (bloco_8B->r & bit->b08) aux.l ^= bit->b28; // 40
    if (bloco_8B->l & bit->b32) aux.l ^= bit->b29; // 32
    if (bloco_8B->l & bit->b24) aux.l ^= bit->b30; // 24
    if (bloco_8B->l & bit->b16) aux.l ^= bit->b31; // 16
    if (bloco_8B->l & bit->b08) aux.l ^= bit->b32; // 8
    
    if (bloco_8B->r & bit->b25) aux.r ^= bit->b01; // 57
    if (bloco_8B->r & bit->b17) aux.r ^= bit->b02; // 49
    if (bloco_8B->r & bit->b09) aux.r ^= bit->b03; // 41
    if (bloco_8B->r & bit->b01) aux.r ^= bit->b04; // 33
    if (bloco_8B->l & bit->b25) aux.r ^= bit->b05; // 25
    if (bloco_8B->l & bit->b17) aux.r ^= bit->b06; // 17
    if (bloco_8B->l & bit->b09) aux.r ^= bit->b07; // 9
    if (bloco_8B->l & bit->b01) aux.r ^= bit->b08; // 1
    
    if (bloco_8B->r & bit->b27) aux.r ^= bit->b09; // 59
    if (bloco_8B->r & bit->b19) aux.r ^= bit->b10; // 51
    if (bloco_8B->r & bit->b11) aux.r ^= bit->b11; // 43
    if (bloco_8B->r & bit->b03) aux.r ^= bit->b12; // 35
    if (bloco_8B->l & bit->b27) aux.r ^= bit->b13; // 27
    if (bloco_8B->l & bit->b19) aux.r ^= bit->b14; // 19
    if (bloco_8B->l & bit->b11) aux.r ^= bit->b15; // 11
    if (bloco_8B->l & bit->b03) aux.r ^= bit->b16; // 3
    
    if (bloco_8B->r & bit->b29) aux.r ^= bit->b17; // 61
    if (bloco_8B->r & bit->b21) aux.r ^= bit->b18; // 53
    if (bloco_8B->r & bit->b13) aux.r ^= bit->b19; // 45
    if (bloco_8B->r & bit->b05) aux.r ^= bit->b20; // 37
    if (bloco_8B->l & bit->b29) aux.r ^= bit->b21; // 29
    if (bloco_8B->l & bit->b21) aux.r ^= bit->b22; // 21
    if (bloco_8B->l & bit->b13) aux.r ^= bit->b23; // 13
    if (bloco_8B->l & bit->b05) aux.r ^= bit->b24; // 5
    
    if (bloco_8B->r & bit->b31) aux.r ^= bit->b25; // 63
    if (bloco_8B->r & bit->b23) aux.r ^= bit->b26; // 55
    if (bloco_8B->r & bit->b15) aux.r ^= bit->b27; // 47
    if (bloco_8B->r & bit->b07) aux.r ^= bit->b28; // 39
    if (bloco_8B->l & bit->b31) aux.r ^= bit->b29; // 31
    if (bloco_8B->l & bit->b23) aux.r ^= bit->b30; // 23
    if (bloco_8B->l & bit->b15) aux.r ^= bit->b31; // 15
    if (bloco_8B->l & bit->b07) aux.r ^= bit->b32; // 7

    *bloco_8B = aux;
}// end-ipBloco8B (tBloco8B *bloco_8B, t32UBits *bit)

/**
 * Função para permutação inversa de blocos de 8Bytes
 *  40 8 48 16 56 24 64 32
 *  39 7 47 15 55 23 63 31
 *  38 6 46 14 54 22 62 30
 *  37 5 45 13 53 21 61 29
 *  36 4 44 12 52 20 60 28
 *  35 3 43 11 51 19 59 27
 *  34 2 42 10 50 18 58 26
 *  33 1 41 9  49 17 57 25 
 * @param tBloco8B *bloco_8B, t32UBits *bit
 * @return void
 */

void ipInversaBloco8B (tBloco8B *bloco_8B, t32UBits *bit)
{
    tBloco8B aux;
    aux.l = 0x0;
    aux.r = 0x0;
    
    if (bloco_8B->r & bit->b08) aux.l ^= bit->b01; // 40
    if (bloco_8B->l & bit->b08) aux.l ^= bit->b02; // 8
    
    if (bloco_8B->r & bit->b16) aux.l ^= bit->b03; // 48
    if (bloco_8B->l & bit->b16) aux.l ^= bit->b04; // 16
    
    if (bloco_8B->r & bit->b24) aux.l ^= bit->b05; // 56
    if (bloco_8B->l & bit->b24) aux.l ^= bit->b06; // 24
    
    if (bloco_8B->r & bit->b32) aux.l ^= bit->b07; // 64
    if (bloco_8B->l & bit->b32) aux.l ^= bit->b08; // 32
    
    if (bloco_8B->r & bit->b07) aux.l ^= bit->b09; // 39
    if (bloco_8B->l & bit->b07) aux.l ^= bit->b10; // 7
    
    if (bloco_8B->r & bit->b15) aux.l ^= bit->b11; // 47
    if (bloco_8B->l & bit->b15) aux.l ^= bit->b12; // 15
    
    if (bloco_8B->r & bit->b23) aux.l ^= bit->b13; // 55
    if (bloco_8B->l & bit->b23) aux.l ^= bit->b14; // 23
    
    if (bloco_8B->r & bit->b31) aux.l ^= bit->b15; // 63
    if (bloco_8B->l & bit->b31) aux.l ^= bit->b16; // 31
    
    if (bloco_8B->r & bit->b06) aux.l ^= bit->b17; // 38
    if (bloco_8B->l & bit->b06) aux.l ^= bit->b18; // 6
    
    if (bloco_8B->r & bit->b14) aux.l ^= bit->b19; // 46
    if (bloco_8B->l & bit->b14) aux.l ^= bit->b20; // 14
    
    if (bloco_8B->r & bit->b22) aux.l ^= bit->b21; // 54
    if (bloco_8B->l & bit->b22) aux.l ^= bit->b22; // 22
    
    if (bloco_8B->r & bit->b30) aux.l ^= bit->b23; // 62
    if (bloco_8B->l & bit->b30) aux.l ^= bit->b24; // 30
    
    if (bloco_8B->r & bit->b05) aux.l ^= bit->b25; // 37
    if (bloco_8B->l & bit->b05) aux.l ^= bit->b26; // 5
    
    if (bloco_8B->r & bit->b13) aux.l ^= bit->b27; // 45
    if (bloco_8B->l & bit->b13) aux.l ^= bit->b28; // 13
    
    if (bloco_8B->r & bit->b21) aux.l ^= bit->b29; // 53
    if (bloco_8B->l & bit->b21) aux.l ^= bit->b30; // 21
    
    if (bloco_8B->r & bit->b29) aux.l ^= bit->b31; // 61
    if (bloco_8B->l & bit->b29) aux.l ^= bit->b32; // 29
    
    if (bloco_8B->r & bit->b04) aux.r ^= bit->b01; // 36
    if (bloco_8B->l & bit->b04) aux.r ^= bit->b02; // 4
    
    if (bloco_8B->r & bit->b12) aux.r ^= bit->b03; // 44
    if (bloco_8B->l & bit->b12) aux.r ^= bit->b04; // 12
    
    if (bloco_8B->r & bit->b20) aux.r ^= bit->b05; // 52
    if (bloco_8B->l & bit->b20) aux.r ^= bit->b06; // 20
    
    if (bloco_8B->r & bit->b28) aux.r ^= bit->b07; // 60
    if (bloco_8B->l & bit->b28) aux.r ^= bit->b08; // 28
    
    if (bloco_8B->r & bit->b03) aux.r ^= bit->b09; // 35
    if (bloco_8B->l & bit->b03) aux.r ^= bit->b10; // 3
    
    if (bloco_8B->r & bit->b11) aux.r ^= bit->b11; // 43
    if (bloco_8B->l & bit->b11) aux.r ^= bit->b12; // 11
    
    if (bloco_8B->r & bit->b19) aux.r ^= bit->b13; // 51
    if (bloco_8B->l & bit->b19) aux.r ^= bit->b14; // 19
    
    if (bloco_8B->r & bit->b27) aux.r ^= bit->b15; // 59
    if (bloco_8B->l & bit->b27) aux.r ^= bit->b16; // 27
    
    if (bloco_8B->r & bit->b02) aux.r ^= bit->b17; // 34
    if (bloco_8B->l & bit->b02) aux.r ^= bit->b18; // 2
    
    if (bloco_8B->r & bit->b10) aux.r ^= bit->b19; // 42
    if (bloco_8B->l & bit->b10) aux.r ^= bit->b20; // 10
    
    if (bloco_8B->r & bit->b18) aux.r ^= bit->b21; // 50
    if (bloco_8B->l & bit->b18) aux.r ^= bit->b22; // 18
    
    if (bloco_8B->r & bit->b26) aux.r ^= bit->b23; // 58
    if (bloco_8B->l & bit->b26) aux.r ^= bit->b24; // 26
    
    if (bloco_8B->r & bit->b01) aux.r ^= bit->b25; // 33
    if (bloco_8B->l & bit->b01) aux.r ^= bit->b26; // 1
    
    if (bloco_8B->r & bit->b09) aux.r ^= bit->b27; // 41
    if (bloco_8B->l & bit->b09) aux.r ^= bit->b28; // 9
    
    if (bloco_8B->r & bit->b17) aux.r ^= bit->b29; // 49
    if (bloco_8B->l & bit->b17) aux.r ^= bit->b30; // 17
    
    if (bloco_8B->r & bit->b25) aux.r ^= bit->b31; // 57
    if (bloco_8B->l & bit->b25) aux.r ^= bit->b32; // 25
    
    *bloco_8B = aux;
}// end-ipInversaBloco8B (tBloco8B *bloco_8B, t32UBits *bit)

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

} // end-pc1Bloco8B (tBloco8B *chave_in, tBloco7B *chave_out, t32UBits *bit)

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
 * byte_3_6 = 17 18 19 20 21 22 23 24 // 01 a 08
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
 * Função para expansão do bloco de 4 Bytes p/ 6 Bytes
 * 32  1  2  3  4  5 * 32  1  2  3  4  5  4  5
 *  4  5  6  7  8  9 *  6  7  8  9  8  9 10 11
 *  8  9 10 11 12 13 * 12 13 12 13 14 15 16 17
 * 12 13 14 15 16 17 * 16 17 18 19 20 21 20 21
 * 16 17 18 19 20 21 * 22 23 24 25 24 25 26 27
 * 20 21 22 23 24 25 * 28 29 28 29 30 31 32  1
 * 24 25 26 27 28 29 *
 * 28 29 30 31 32  1 *
 ------------------ Bloco6B --------------------
 * byte_1 =    1  2  3  4  5  6  7  8 // 25 a 32
 * byte_2 =    9 10 11 12 13 14 15 16 // 25 a 32
 * byte_3_6 = 17 18 19 20 21 22 23 24 // 01 a 08
 *            25 26 27 28 29 30 31 32 // 09 a 16
 *            33 34 35 36 37 38 39 40 // 17 a 24
 *            41 42 43 44 45 46 47 48 // 25 a 32
 * @param unsigned int *bloco_4B, tBloco6B *bloco_6B, t32UBits *bit
 * @return void
 */

void expansao4Bto6B (unsigned int *bloco_4B, tBloco6B *bloco_6B, t32UBits *bit)
{
    bloco_6B->byte_1   = 0x0;
    bloco_6B->byte_2   = 0x0;
    bloco_6B->byte_3_6 = 0x0;

    if (*bloco_4B & bit->b32) bloco_6B->byte_1 ^= bit->b25; // 32
    if (*bloco_4B & bit->b01) bloco_6B->byte_1 ^= bit->b26; //  1
    if (*bloco_4B & bit->b02) bloco_6B->byte_1 ^= bit->b27; //  2
    if (*bloco_4B & bit->b03) bloco_6B->byte_1 ^= bit->b28; //  3
    if (*bloco_4B & bit->b04) bloco_6B->byte_1 ^= bit->b29; //  4
    if (*bloco_4B & bit->b05) bloco_6B->byte_1 ^= bit->b30; //  5
    if (*bloco_4B & bit->b04) bloco_6B->byte_1 ^= bit->b31; //  4
    if (*bloco_4B & bit->b05) bloco_6B->byte_1 ^= bit->b32; //  5

    if (*bloco_4B & bit->b06) bloco_6B->byte_2 ^= bit->b25; //  6
    if (*bloco_4B & bit->b07) bloco_6B->byte_2 ^= bit->b26; //  7
    if (*bloco_4B & bit->b08) bloco_6B->byte_2 ^= bit->b27; //  8
    if (*bloco_4B & bit->b09) bloco_6B->byte_2 ^= bit->b28; //  9
    if (*bloco_4B & bit->b08) bloco_6B->byte_2 ^= bit->b29; //  8
    if (*bloco_4B & bit->b09) bloco_6B->byte_2 ^= bit->b30; //  9
    if (*bloco_4B & bit->b10) bloco_6B->byte_2 ^= bit->b31; // 10
    if (*bloco_4B & bit->b11) bloco_6B->byte_2 ^= bit->b32; // 11

    if (*bloco_4B & bit->b12) bloco_6B->byte_3_6 ^= bit->b01; // 12
    if (*bloco_4B & bit->b13) bloco_6B->byte_3_6 ^= bit->b02; // 13
    if (*bloco_4B & bit->b12) bloco_6B->byte_3_6 ^= bit->b03; // 12
    if (*bloco_4B & bit->b13) bloco_6B->byte_3_6 ^= bit->b04; // 13
    if (*bloco_4B & bit->b14) bloco_6B->byte_3_6 ^= bit->b05; // 14
    if (*bloco_4B & bit->b15) bloco_6B->byte_3_6 ^= bit->b06; // 15
    if (*bloco_4B & bit->b16) bloco_6B->byte_3_6 ^= bit->b07; // 16
    if (*bloco_4B & bit->b17) bloco_6B->byte_3_6 ^= bit->b08; // 17

    if (*bloco_4B & bit->b16) bloco_6B->byte_3_6 ^= bit->b09; // 16
    if (*bloco_4B & bit->b17) bloco_6B->byte_3_6 ^= bit->b10; // 17
    if (*bloco_4B & bit->b18) bloco_6B->byte_3_6 ^= bit->b11; // 18
    if (*bloco_4B & bit->b19) bloco_6B->byte_3_6 ^= bit->b12; // 19
    if (*bloco_4B & bit->b20) bloco_6B->byte_3_6 ^= bit->b13; // 20
    if (*bloco_4B & bit->b21) bloco_6B->byte_3_6 ^= bit->b14; // 21
    if (*bloco_4B & bit->b20) bloco_6B->byte_3_6 ^= bit->b15; // 20
    if (*bloco_4B & bit->b21) bloco_6B->byte_3_6 ^= bit->b16; // 21

    if (*bloco_4B & bit->b22) bloco_6B->byte_3_6 ^= bit->b17; // 22
    if (*bloco_4B & bit->b23) bloco_6B->byte_3_6 ^= bit->b18; // 23
    if (*bloco_4B & bit->b24) bloco_6B->byte_3_6 ^= bit->b19; // 24
    if (*bloco_4B & bit->b25) bloco_6B->byte_3_6 ^= bit->b20; // 25
    if (*bloco_4B & bit->b24) bloco_6B->byte_3_6 ^= bit->b21; // 24
    if (*bloco_4B & bit->b25) bloco_6B->byte_3_6 ^= bit->b22; // 25
    if (*bloco_4B & bit->b26) bloco_6B->byte_3_6 ^= bit->b23; // 26
    if (*bloco_4B & bit->b27) bloco_6B->byte_3_6 ^= bit->b24; // 27

    if (*bloco_4B & bit->b28) bloco_6B->byte_3_6 ^= bit->b25; // 28
    if (*bloco_4B & bit->b29) bloco_6B->byte_3_6 ^= bit->b26; // 29
    if (*bloco_4B & bit->b28) bloco_6B->byte_3_6 ^= bit->b27; // 28
    if (*bloco_4B & bit->b29) bloco_6B->byte_3_6 ^= bit->b28; // 29
    if (*bloco_4B & bit->b30) bloco_6B->byte_3_6 ^= bit->b29; // 30
    if (*bloco_4B & bit->b31) bloco_6B->byte_3_6 ^= bit->b30; // 31
    if (*bloco_4B & bit->b32) bloco_6B->byte_3_6 ^= bit->b31; // 32
    if (*bloco_4B & bit->b01) bloco_6B->byte_3_6 ^= bit->b32; //  1

} // end-expansao4Bto6B (unsigned int *bloco_4B, tBloco6B *bloco_6B, t32UBits *bit)

/**
 * Função f p/ cifra do bloco Ri da rede de Feistel com as 8 S-Boxs
 * @param unsigned int *bloco_4B, tBloco6B *bloco_6B, t32UBits *bit
 * @return void
 */
void funcaoF (unsigned int *bloco_4B, tBloco6B *chave, t32UBits *bit)
{
    tBloco6B bloco_6B;
    unsigned int lin = 0x0;
    unsigned int col = 0x0;
    unsigned int aux = 0x0;

    unsigned int s1[][] = {
    //    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
        {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7} // 0
        { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8} // 1
        { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0} // 2
        {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13} // 3
    }

    unsigned int s2[][] = {
    //    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
        {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10} // 0
        { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5} // 1
        { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15} // 2
        {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9} // 3
    }

    unsigned int s3[][] = {
    //    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
        {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8} // 0
        {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1} // 1
        {13,  6,  4,  9,  8, 15,  3,  0,  11, 1,  2, 12,  5, 10, 14,  7} // 2
        { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12} // 3
    }

    unsigned int s4[][] = {
    //    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
        { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15} // 0
        {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9} // 1
        {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4} // 2
        { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14} // 3
    }

    unsigned int s5[][] = {
    //    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
        { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9} // 0
        {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6} // 1
        { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14} // 2
        {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3} // 3
    }

    unsigned int s6[][] = {
    //    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
        {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11} // 0
        {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8} // 1
        { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6} // 2
        { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13} // 3
    }

    unsigned int s7[][] = {
    //    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
        { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1} // 0
        {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6} // 1
        { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2} // 2
        { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12} // 3
    }

    unsigned int s8[][] = {
    //    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
        {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7} // 0
        { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2} // 1
        { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8} // 2
        { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11} // 3
    }

    // Expansão em Ri
    expansao4Bto6B(bloco_4B, *bloco_6B, bit);
    
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

    *bloco_6B ^= *chave;    
    *bloco_4B = 0x0;

    // -------------- Aplicação de S1 --------------
    if (bloco_6B->byte_1 & bit->b25) lin ^= bit->b31; // 32
    if (bloco_6B->byte_1 & bit->b30) lin ^= bit->b32; //  5

    if (bloco_6B->byte_1 & bit->b26) col ^= bit->b29; //  1
    if (bloco_6B->byte_1 & bit->b27) col ^= bit->b30; //  2
    if (bloco_6B->byte_1 & bit->b28) col ^= bit->b31; //  3
    if (bloco_6B->byte_1 & bit->b29) col ^= bit->b32; //  4

    aux = s1[lin][col];

    if (aux & bit->b29) *bloco_4B ^= bit->b01;
    if (aux & bit->b30) *bloco_4B ^= bit->b02;
    if (aux & bit->b31) *bloco_4B ^= bit->b03;
    if (aux & bit->b32) *bloco_4B ^= bit->b04;

    lin = col = 0x0;

    // -------------- Aplicação de S2 --------------
    if (bloco_6B->byte_1 & bit->b31) lin ^= bit->b31; //  4
    if (bloco_6B->byte_2 & bit->b28) lin ^= bit->b32; //  9

    if (bloco_6B->byte_1 & bit->b32) col ^= bit->b29; //  5
    if (bloco_6B->byte_2 & bit->b25) col ^= bit->b30; //  6
    if (bloco_6B->byte_2 & bit->b26) col ^= bit->b31; //  7
    if (bloco_6B->byte_2 & bit->b27) col ^= bit->b32; //  8

    aux = s2[lin][col];

    if (aux & bit->b29) *bloco_4B ^= bit->b05;
    if (aux & bit->b30) *bloco_4B ^= bit->b06;
    if (aux & bit->b31) *bloco_4B ^= bit->b07;
    if (aux & bit->b32) *bloco_4B ^= bit->b08;

    lin = col = 0x0;

    // -------------- Aplicação de S3 --------------
    if (bloco_6B->byte_2   & bit->b29) lin ^= bit->b31; //  8
    if (bloco_6B->byte_3_6 & bit->b02) lin ^= bit->b32; //  13

    if (bloco_6B->byte_2   & bit->b30) col ^= bit->b29; //  9
    if (bloco_6B->byte_2   & bit->b31) col ^= bit->b30; // 10
    if (bloco_6B->byte_2   & bit->b32) col ^= bit->b31; // 11
    if (bloco_6B->byte_3_6 & bit->b01) col ^= bit->b32; // 12

    aux = s3[lin][col];

    if (aux & bit->b29) *bloco_4B ^= bit->b09;
    if (aux & bit->b30) *bloco_4B ^= bit->b10;
    if (aux & bit->b31) *bloco_4B ^= bit->b11;
    if (aux & bit->b32) *bloco_4B ^= bit->b12;

    lin = col = 0x0;

    // -------------- Aplicação de S4 --------------
    if (bloco_6B->byte_3_6 & bit->b03) lin ^= bit->b31; // 12
    if (bloco_6B->byte_3_6 & bit->b08) lin ^= bit->b32; // 17

    if (bloco_6B->byte_3_6 & bit->b04) col ^= bit->b29; // 13
    if (bloco_6B->byte_3_6 & bit->b05) col ^= bit->b30; // 14
    if (bloco_6B->byte_3_6 & bit->b06) col ^= bit->b31; // 15
    if (bloco_6B->byte_3_6 & bit->b07) col ^= bit->b32; // 16

    aux = s4[lin][col];

    if (aux & bit->b29) *bloco_4B ^= bit->b13;
    if (aux & bit->b30) *bloco_4B ^= bit->b14;
    if (aux & bit->b31) *bloco_4B ^= bit->b15;
    if (aux & bit->b32) *bloco_4B ^= bit->b16;

    lin = col = 0x0;

    // -------------- Aplicação de S5 --------------
    if (bloco_6B->byte_3_6 & bit->b09) lin ^= bit->b31; // 16
    if (bloco_6B->byte_3_6 & bit->b14) lin ^= bit->b32; // 21

    if (bloco_6B->byte_3_6 & bit->b10) col ^= bit->b29; // 17
    if (bloco_6B->byte_3_6 & bit->b11) col ^= bit->b30; // 18
    if (bloco_6B->byte_3_6 & bit->b12) col ^= bit->b31; // 19
    if (bloco_6B->byte_3_6 & bit->b13) col ^= bit->b32; // 20

    aux = s5[lin][col];

    if (aux & bit->b29) *bloco_4B ^= bit->b17;
    if (aux & bit->b30) *bloco_4B ^= bit->b18;
    if (aux & bit->b31) *bloco_4B ^= bit->b19;
    if (aux & bit->b32) *bloco_4B ^= bit->b20;

    lin = col = 0x0;

    // -------------- Aplicação de S6 --------------
    if (bloco_6B->byte_3_6 & bit->b15) lin ^= bit->b31; // 20
    if (bloco_6B->byte_3_6 & bit->b20) lin ^= bit->b32; // 25

    if (bloco_6B->byte_3_6 & bit->b16) col ^= bit->b29; // 21
    if (bloco_6B->byte_3_6 & bit->b17) col ^= bit->b30; // 22
    if (bloco_6B->byte_3_6 & bit->b18) col ^= bit->b31; // 23
    if (bloco_6B->byte_3_6 & bit->b19) col ^= bit->b32; // 24

    aux = s6[lin][col];

    if (aux & bit->b29) *bloco_4B ^= bit->b21;
    if (aux & bit->b30) *bloco_4B ^= bit->b22;
    if (aux & bit->b31) *bloco_4B ^= bit->b23;
    if (aux & bit->b32) *bloco_4B ^= bit->b24;

    lin = col = 0x0;

    // -------------- Aplicação de S7 --------------
    if (bloco_6B->byte_3_6 & bit->b21) lin ^= bit->b31; // 24
    if (bloco_6B->byte_3_6 & bit->b26) lin ^= bit->b32; // 29

    if (bloco_6B->byte_3_6 & bit->b22) col ^= bit->b29; // 25
    if (bloco_6B->byte_3_6 & bit->b23) col ^= bit->b30; // 26
    if (bloco_6B->byte_3_6 & bit->b24) col ^= bit->b31; // 27
    if (bloco_6B->byte_3_6 & bit->b25) col ^= bit->b32; // 28

    aux = s7[lin][col];

    if (aux & bit->b29) *bloco_4B ^= bit->b25;
    if (aux & bit->b30) *bloco_4B ^= bit->b26;
    if (aux & bit->b31) *bloco_4B ^= bit->b27;
    if (aux & bit->b32) *bloco_4B ^= bit->b28;

    lin = col = 0x0;

    // -------------- Aplicação de S8 --------------
    if (bloco_6B->byte_3_6 & bit->b27) lin ^= bit->b31; // 28
    if (bloco_6B->byte_3_6 & bit->b32) lin ^= bit->b32; //  1

    if (bloco_6B->byte_3_6 & bit->b28) col ^= bit->b29; // 29
    if (bloco_6B->byte_3_6 & bit->b29) col ^= bit->b30; // 30
    if (bloco_6B->byte_3_6 & bit->b30) col ^= bit->b31; // 31
    if (bloco_6B->byte_3_6 & bit->b31) col ^= bit->b32; // 32

    aux = s8[lin][col];

    if (aux & bit->b29) *bloco_4B ^= bit->b29;
    if (aux & bit->b30) *bloco_4B ^= bit->b30;
    if (aux & bit->b31) *bloco_4B ^= bit->b31;
    if (aux & bit->b32) *bloco_4B ^= bit->b32;

    permutacaoP(bloco_4B, bit);

} // end-funcaoF (unsigned int *bloco_4B, tBloco6B *chave, t32UBits *bit)

/**
 * Função p para aplicação na função F da rede de Feistel
 * após as S-Boxs
 * 16  7 20 21 * 16  7 20 21 29 12 28 17
 * 29 12 28 17 *  1 15 23 26  5 18 31 10
 *  1 15 23 26 *  2  8 24 14 32 27  3  9
 *  5 18 31 10 * 19 13 30  6 22 11  4 25
 *  2  8 24 14 * 
 * 32 27  3  9 * 
 * 19 13 30  6 *
 * 22 11  4 25 *
 * @param unsigned int *bloco_4B, t32UBits *bit
 * @return void
 */

void permutacaoP (unsigned int *bloco_4B, t32UBits *bit)
{
    unsigned int aux = 0x0;

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

} // end-permutacaoP (unsigned int *bloco_4B, t32UBits *bit)

#endif