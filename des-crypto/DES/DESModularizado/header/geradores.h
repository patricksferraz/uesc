/*
 *---------------------------------------------------------------------
 *
 *   File    : geradores.h
 *   Created : 2017-10-28
 *   Modified: 2017-10-28
 *
 *   Header com funções geradoras para aplicar na rede de Feistel 
 *
 *---------------------------------------------------------------------
 */

#ifndef _GERADORES_H
#define _GERADORES_H

/**
 * --------------------------------------------------------------------------
 * INCLUDES
 * --------------------------------------------------------------------------
 */

#include "permutadores.h"
#include "shiftCircular.h"
#include "valoresBinarios.h"

/**
 * --------------------------------------------------------------------------
 * TIPOS
 * --------------------------------------------------------------------------
 */

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
 * --------------------------------------------------------------------------
 * PROTÓTIPOS
 * --------------------------------------------------------------------------
 */

void gereChaves (tBloco8B *bloco, tChave *c);

/**
 * --------------------------------------------------------------------------
 * FUNÇÕES
 * --------------------------------------------------------------------------
 * 
 */

/**
 * Função para geração de chaves p/ rede de feistel
 * @param tBloco8B *chave_8B, tChave *chave, t32UBits *bit
 * @return void
 */

void gereChaves (tBloco8B *chave_8B, tChave *chave, t32UBits *bit)
{
    tBloco7B chave_7B;

    pc1Bloco8B(chave_8B, &chave_7B, &bit);

    // Geração de c1
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &c->c1, bit);

    // Geração de c2
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &c->c2, bit);

    // Geração de c3
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &c->c3, bit);

    // Geração de c4
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &c->c4, bit);

    // Geração de c5
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &c->c5, bit);

    // Geração de c6
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &c->c6, bit);

    // Geração de c7
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &c->c7, bit);

    // Geração de c8
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &c->c8, bit);

    // Geração de c9
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &c->c9, bit);

    // Geração de c10
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &c->c10, bit);

    // Geração de c11
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &c->c11, bit);

    // Geração de c12
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &c->c12, bit);

    // Geração de c13
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &c->c13, bit);

    // Geração de c14
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &c->c14, bit);

    // Geração de c15
    leftShiftCircular7B(&chave_7B, bit);
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &c->c15, bit);

    // Geração de c16
    leftShiftCircular7B(&chave_7B, bit);
    pc2Bloco7B(&chave_7B, &c->c16, bit);

}// end-gereChaves (tBloco8B *bloco, tChave *c)

#endif