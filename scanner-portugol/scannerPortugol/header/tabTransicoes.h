/*
 *---------------------------------------------------------------------
 *
 *   File    : tabTransicoes.h
 *   Created : 2017-10-28
 *   Modified: 2017-10-28
 *
 *   Header para manipulação da tabela de transições dos estados para
 *   analisador léxico de Portugol
 *
 *---------------------------------------------------------------------
 */

#ifndef _TABTRANSICOES_H
#define _TABTRANSICOES_H

/**
 * ---------------------------------------------------
 * INCLUDES
 * ---------------------------------------------------
 */

#include <ctype.h>

/**
 * ---------------------------------------------------
 * MACROS
 * ---------------------------------------------------
 */

#define QNT_ESTADOS  44
#define QNT_SIMBOLOS 21

/**
 * ---------------------------------------------------
 * TIPOS
 * ---------------------------------------------------
 */

typedef enum
{
    s_digito,   // 0
    s_pt,       // 1
    s_letra,    // 2
    s_under,    // 3
    s_aspas,    // 4
    s_menor,    // 5
    s_maior,    // 6
    s_menos,    // 7
    s_mais,     // 8
    s_igual,    // 9
    s_vezes,    // 10
    s_pt_virg,  // 11
    s_virg,     // 12
    s_dois_pts, // 13
    s_fecha_par,// 14
    s_abre_par, // 15
    s_dividido, // 16
    s_EOF,      // 17
    s_barra_n,  // 18
    s_branco,   // 19
    s_outro     // 20
} tSimbolo;

/**
 * ---------------------------------------------------
 * VARIÁVEIS GLOBAIS
 * ---------------------------------------------------
 */

unsigned int transicao[QNT_ESTADOS][QNT_SIMBOLOS] = {
//   \D | . |\L | _ | " | < | > | - | + | = | * | ; | , | : | ) | ( | / |EOF|\n |\b |outro 
    { 1,  7,  9, 43, 11, 14, 19, 22, 25, 28, 29, 30, 31, 32, 33, 34, 39, 42,  0,  0, 43}, // estado  0
    { 1,  4,  3,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2}, // estado  1
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado  2
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado  3
    { 4,  6,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6}, // estado  4
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado  5
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado  6
    { 4,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8}, // estado  7
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado  8
    { 9, 10,  9,  9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, // estado  9
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 10
    {11, 11, 11, 11, 13, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 11, 11}, // estado 11
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 12
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 13
    {18, 18, 18, 18, 18, 18, 17, 16, 18, 15, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18}, // estado 14
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 15
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 16
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 17
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 18
    {21, 21, 21, 21, 21, 21, 21, 21, 21, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21}, // estado 19
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 20
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 21
    {24, 24, 24, 24, 24, 24, 24, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24}, // estado 22
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 23
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 24
    {27, 27, 27, 27, 27, 27, 27, 27, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27}, // estado 25
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 26
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 27
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 28
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 29
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 30
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 31
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 32
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 33
    {35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35}, // estado 34
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 35
    {36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 36, 36, 36, 36, 36, 36, 38, 36, 36, 36}, // estado 36
    {36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 36, 36, 36,  0, 36, 36, 38, 36, 36, 36}, // estado 37
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 38
    {40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 41, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40}, // estado 39
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 40
    {41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 42,  0, 41, 41}, // estado 41
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 42
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // estado 43
};

/**
 * ---------------------------------------------------
 * PROTÓTIPOS DE FUNÇÕES
 * ---------------------------------------------------
 */

tSimbolo char2Simbolo (char *caractere);

/**
 * ---------------------------------------------------
 * DECLARAÇÕES DE FUNÇÕES
 * ---------------------------------------------------
 */

/**
 * Função retorna o simbolo da tabela de transições
 * correspondente ao caractere de entrada.
 * @param char *caractere
 * @return tSimbolo
 */

tSimbolo char2Simbolo (char *caractere)
{
    switch (*caractere)
    {
        case '.' :  return s_pt;
        case '_' :  return s_under;
        case '"' :  return s_aspas;
        case '<' :  return s_menor;
        case '>' :  return s_maior;
        case '-' :  return s_menos;
        case '+' :  return s_mais;
        case '=' :  return s_igual;
        case '*' :  return s_vezes;
        case ';' :  return s_pt_virg;
        case ',' :  return s_virg;
        case ':' :  return s_dois_pts;
        case ')' :  return s_fecha_par;
        case '(' :  return s_abre_par;
        case '/' :  return s_dividido;
        case EOF :  return s_EOF;
        case '\n':  return s_barra_n;
        default:
            if (isalpha(*caractere)) return s_letra;
            if (isdigit(*caractere)) return s_digito;
            if (isspace(*caractere)) return s_branco;
            return s_outro;
    }

} // end-char2Simbolo (char *caractere)

#endif