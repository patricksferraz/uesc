/*
 *---------------------------------------------------------------------
 *
 *   File    : lexema.h
 *   Created : 2017-10-28
 *   Modified: 2017-10-28
 *
 *   Header para manipulação dos lexemas p/ o analisador léxico de
 *   Portugol
 *
 *---------------------------------------------------------------------
 */

#ifndef _LEXEMA_H
#define _LEXEMA_H

/**
 * ---------------------------------------------------
 * INCLUDES 
 * ---------------------------------------------------
 */

#include <stdlib.h>
#include <string.h>

/**
 * ---------------------------------------------------
 * MACROS
 * ---------------------------------------------------
 */

#define TAM_INICIAL_LEXEMA 25

/**
 * ---------------------------------------------------
 * TIPOS
 * ---------------------------------------------------
 */

typedef struct
{
    char   *nome;
    int    indice_ult_registro;
    int    maior_lex;
    size_t tam_lexema;
} tLexema;

/**
 * ---------------------------------------------------
 * PROTÓTIPOS DE FUNÇÕES
 * ---------------------------------------------------
 */

char * inicializeLexema     (tLexema *lexema);
int  concateneSimboloLexema (tLexema *lexema, char *simbolo);
void reinicieLexema 		(tLexema *lexema);
void finalizeLexema		    (tLexema *lexema);

/**
 * ---------------------------------------------------
 * DECLARAÇÕES DE FUNÇÕES
 * ---------------------------------------------------
 */

/**
 * Função para inicializar lexema com TAM_INICIAL_LEXEMA
 * definido e retorna o ponteiro p/ lexema.nome (endereço
 * do primeiro indice do nome), ou seja, NULL caso não
 * exista memória suficiente.
 * @param tLexema *lexema
 * @return char *
 */

char * inicializeLexema (tLexema *lexema)
{
    lexema->maior_lex  = 0;
    lexema->indice_ult_registro = -1;
    lexema->tam_lexema = TAM_INICIAL_LEXEMA;
    lexema->nome = (char *) malloc (lexema->tam_lexema * sizeof(char) + 1);

    return lexema->nome;

} // end-inicializeLexema (tLexema *lexema)

/**
 * Função para cocatenar um caractere ao nome de um tLexema
 * realocando espaço caso não exista. Retorna o novo espaço
 * disponível para armazenar o nome do lexema ou -1 caso
 * ocorra erro ao cocatenar.
 * @param tLexema *lexema, char *simbolo
 * @return int
 */

int concateneSimboloLexema (tLexema *lexema, char *simbolo)
{
	if ((lexema->indice_ult_registro + 1) == lexema->tam_lexema)
	{
		lexema->tam_lexema <<= 1;

		lexema->nome = (char *) realloc (lexema->nome, (lexema->tam_lexema * sizeof(char) + 1));
		if (lexema->nome == NULL)
			return -1;
	}

	lexema->nome[ ++ lexema->indice_ult_registro ] = *simbolo;
	lexema->nome[ lexema->indice_ult_registro + 1] = '\0';

	return lexema->tam_lexema;

} // end-concateneSimboloLexema (tLexema *lexema, char *simbolo)

/**
 * Função reinicia o lexema, alterando o indice do ultimo
 * registro para -1.
 * @param tLexema *lexema
 * @return void
 */

void reinicieLexema (tLexema *lexema)
{
	size_t tam_lex = strlen(lexema->nome);

    lexema->indice_ult_registro = -1;

    if (tam_lex > lexema->maior_lex)
    	lexema->maior_lex = tam_lex;

} // end-reinicieLexema (tLexema *lexema)

/**
 * Função finaliza o lexema desalocando o espaço de memória
 * reservado para o mesmo.
 * @param tLexema *lexema
 * @return void
 */

void finalizeLexema (tLexema *lexema)
{
	free(lexema->nome);

} // end-finalizeLexema (tLexema *lexema)

#endif