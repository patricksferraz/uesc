/*
 *---------------------------------------------------------------------
 *
 *   File    : valoresBinarios.h
 *   Created : 2017-10-28
 *   Modified: 2017-10-28
 *
 *   Algoritmo que possui as representações de valores binários 
 *
 *---------------------------------------------------------------------
 */

#ifndef _VALORESBINARIOS_H
#define _VALORESBINARIOS_H

/**
 * --------------------------------------------------------------------------
 * TIPOS
 * --------------------------------------------------------------------------
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

/**
 * --------------------------------------------------------------------------
 * PROTÓTIPOS
 * --------------------------------------------------------------------------
 */

void inicialize32Ub (t32UBits *bit);

/**
 * --------------------------------------------------------------------------
 * FUNÇÕES
 * --------------------------------------------------------------------------
 * 
 */

/**
 * Função para inicializar 32 representações binárias
 *  1  2  3  4  5  6  7  8 * 33 34 35 36 37 38 39 40
 *  9 10 11 12 13 14 15 16 * 41 42 43 44 45 46 47 48
 * 17 18 19 20 21 22 23 24 * 49 50 51 52 53 54 55 56
 * 25 26 27 28 29 30 31 32 * 57 58 59 60 61 62 63 64
 * @param t32UBits *bit
 * @return void
 */

void inicialize32Ub (t32UBits *bit)
{    
    // 32 bits
    bit->b32 = 0x1;
    bit->b31 = 0x2;
    bit->b30 = 0x4;
    bit->b29 = 0x8;
    bit->b28 = 0x10;
    bit->b27 = 0x20;
    bit->b26 = 0x40;
    bit->b25 = 0x80;
    bit->b24 = 0x100;
    bit->b23 = 0x200;
    bit->b22 = 0x400;
    bit->b21 = 0x800;
    bit->b20 = 0x1000;
    bit->b19 = 0x2000;
    bit->b18 = 0x4000;
    bit->b17 = 0x8000;
    bit->b16 = 0x10000;
    bit->b15 = 0x20000;
    bit->b14 = 0x40000;
    bit->b13 = 0x80000;
    bit->b12 = 0x100000;
    bit->b11 = 0x200000;
    bit->b10 = 0x400000;
    bit->b09 = 0x800000;
    bit->b08 = 0x1000000;
    bit->b07 = 0x2000000;
    bit->b06 = 0x4000000;
    bit->b05 = 0x8000000;
    bit->b04 = 0x10000000;
    bit->b03 = 0x20000000;
    bit->b02 = 0x40000000;
    bit->b01 = 0x80000000;
}// end-inicialize32Ub (t32UBits *bit)

#endif