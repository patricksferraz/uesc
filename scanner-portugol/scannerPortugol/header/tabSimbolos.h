/*
 *---------------------------------------------------------------------
 *
 *   File    : tabSimbolos.h
 *   Created : 2017-10-28
 *   Modified: 2017-10-28
 *
 *   Header para manipulação da tabela de símbolos do analisador
 * 	 léxico da linguagem Portugol
 *
 *---------------------------------------------------------------------
 */

#ifndef _TABSIMBOLOS_H
#define _TABSIMBOLOS_H

/**
 * ---------------------------------------------------
 * INCLUDES 
 * ---------------------------------------------------
 */

#include <stdlib.h>
#include <string.h>
#include "tokens.h"

/**
 * ---------------------------------------------------
 * MACROS
 * ---------------------------------------------------
 */

#define TAM_TAB_SIMBOLOS 257
#define TAM_INICIAL_OCOR 10

/**
 * ---------------------------------------------------
 * TIPOS
 * ---------------------------------------------------
 */

typedef struct
{
	int lin;
	int col;
} tPos;

typedef struct tIdentificador
{
	char   *lex_char;
	tToken token;
	int    indice_ult_ocor;
	int    lex_int;
	float  lex_float;
	size_t tam_ocor;
	tPos   *ocor;
	struct tIdentificador *prox;
} tIdentificador;

typedef tIdentificador * tTabSimbolo[TAM_TAB_SIMBOLOS];

/**
 * ---------------------------------------------------
 * PROTÓTIPOS DE FUNÇÕES
 * ---------------------------------------------------
 */

int  instaleIdenTabSimbolo     	 (tTabSimbolo tab_simbolo, tIdentificador *iden);
int  instaleOcorIdentificador  	 (tIdentificador *iden_dest, tPos *ocor);
int  gereIdentificador 			 (tIdentificador *iden, char *lex, tToken *tk, tPos *ocor);
void finalizeTabSimbolo 		 (tTabSimbolo tab_simbolo);
unsigned int hash 			  	 (char *string);
tIdentificador * aloqueECopieIdentificador (tIdentificador *iden_src);

/**
 * ---------------------------------------------------
 * DECLARAÇÕES DE FUNÇÕES
 * ---------------------------------------------------
 */

/**
 * Função para instalar um identificador c/ lexema (tIdentificador)
 * na tabela de simbolos (tTabSimbolo), realocando espaço tPos *ocor
 * caso não exista. Retorna -1 caso ocorra erro durante alocação,
 * caso contrário retorna a posição em que o identificador foi
 * instalado na tabela de simbolos.
 * @param tTabSimbolo tab_simbolo, tIdentificador *iden
 * @return int
 */

int instaleIdenTabSimbolo (tTabSimbolo tab_simbolo, tIdentificador *iden)
{
	tIdentificador *iden_atual;
	tIdentificador *iden_anterior;
	unsigned int   cod_hash = hash(iden->lex_char);
	
	if ((tab_simbolo[cod_hash]) == NULL)
	{		
		if ((tab_simbolo[cod_hash] = aloqueECopieIdentificador(iden)) == NULL)
			return -1;
	}
	else
	{

		iden_atual = tab_simbolo[cod_hash];
		
		while(iden_atual != NULL)
		{
			if (iden_atual->token == iden->token && strcmp(iden_atual->lex_char, iden->lex_char) == 0)
				return instaleOcorIdentificador (iden_atual, iden->ocor);
		
			iden_anterior = iden_atual;
			iden_atual = iden_atual->prox;
		}

		if ((iden_atual = aloqueECopieIdentificador(iden)) == NULL)
			return -1;
		iden_anterior->prox = iden_atual;
		
	}

	return cod_hash;

} // end-instaleIdenTabSimbolo (tTabSimbolo tab_simbolo, tIdentificador *iden)

/**
 * Função para instalar uma nova ocorrência do identificador. Recebe
 * por parametro o identificador de destino (iden_dest) e a posição
 * da ocorrência. Retorna -1 se erro ou 0, caso contrário.
 * @param tIdentificador *iden_dest, tPos *ocor
 * @return int
 */

int instaleOcorIdentificador (tIdentificador *iden_dest, tPos *ocor)
{
	if ((iden_dest->indice_ult_ocor + 1) == iden_dest->tam_ocor)
	{
		iden_dest->tam_ocor <<= 1;

		iden_dest->ocor = (tPos *) realloc (iden_dest->ocor, (iden_dest->tam_ocor * sizeof(tPos)));
		if (iden_dest->ocor == NULL)
			return -1;
	}

	iden_dest->ocor[ ++ iden_dest->indice_ult_ocor ] = ocor[0];

	return 0;

} // end-instaleOcorIdentificador (tIdentificador *iden_dest, tPos *ocor)

/**
 * Função para gerar um tIdentificador *iden a partir dos
 * dados passados por parâmetro. Retorna -1 caso erro ou 0,
 * caso contrário.
 * @param tIdentificador *iden, char *lex, tToken *tk, tPos *ocor
 * @return int
 */

int gereIdentificador (tIdentificador *iden, char *lex, tToken *tk, tPos *ocor)
{
	size_t tam_lex = strlen(lex);
	
	iden->lex_char = (char *) malloc (tam_lex * sizeof(char) + 1);
	if (iden->lex_char == NULL)
		return -1;
	
	iden->ocor = (tPos *) malloc (sizeof(tPos));
	if (iden->ocor == NULL)	
		return -1;

	if (*tk == tk_INTEIRO)
	{
		iden->lex_int   = atoi(lex);
		iden->lex_float = -1;
	}
	else if (*tk == tk_DECIMAL)
	{
		iden->lex_float = atof(lex);
		iden->lex_int   = -1;
	}

	strcpy(iden->lex_char, lex);
	iden->token 		  = *tk;
	iden->tam_ocor 		  = TAM_INICIAL_OCOR;
	iden->indice_ult_ocor = 0;
	iden->ocor[0] 		  = ocor[0];

	return 0;

} // end-gereIdentificador (tIdentificador *iden, char *lex, tToken *tk, tPos *ocor)

/**
 * Função finaliza a tabela de simbolos desalocando
 * o espaço de memória reservado para o mesmo.
 * @param tTabSimbolo tab_simbolo
 * @return void
 */

void finalizeTabSimbolo (tTabSimbolo tab_simbolo)
{
	tIdentificador *anterior;
	tIdentificador *atual;
	int i;

    for (i = 0; i < TAM_TAB_SIMBOLOS; i++)
	{
		anterior = atual = tab_simbolo[i];
		while (atual != NULL)
		{
			atual = atual->prox;
			free(anterior->lex_char);
			free(anterior->ocor);
			free(anterior);
			anterior = atual;
		}
	}

} // end-finalizeTabSimbolo (tTabSimbolo tab_simbolo)

/**
 * Função para hash c/ shift e compressão multiplique,
 * adicione e divida (MAD), em uma string recebida por
 * parametro, retornando o código hash (unsigned int).
 * @param char *string
 * @return unsigned int
 */

unsigned int hash (char *string)
{
	unsigned int i;
	unsigned int h = 0;
	size_t tam = strlen(string);

    for (i = 0; i < tam; i++)
    	h = (h << 3) + string[i];

    return (((7*h) + 5) % TAM_TAB_SIMBOLOS);

} // end-hash (char *string)

/**
 * Função para alocar memória e copiar dados de um identificador a outro.
 * Recebe por parametro o identificador de origem (iden_src), que possui
 * os dados. Retorna NULL se ocorrer erro na alocação ou retorna o endereço
 * inicial do tIdentificador alocado, caso contrário.
 * @param tIdentificador *iden_src
 * @return tIdentificador *
 */

tIdentificador * aloqueECopieIdentificador (tIdentificador *iden_src)
{
	tIdentificador * iden;
	size_t tam_inicial_ocor = TAM_INICIAL_OCOR;
	size_t tam_lexema       = strlen(iden_src->lex_char);

	iden = (tIdentificador *) malloc (sizeof(tIdentificador));
	if (iden == NULL)
		return NULL;

	iden->lex_char = (char *) malloc (tam_lexema * sizeof(char) + 1);
	if (iden->lex_char == NULL)
		return NULL;

	iden->ocor = (tPos *) malloc (tam_inicial_ocor * sizeof(tPos));
	if (iden->ocor == NULL)
		return NULL;

	strcpy(iden->lex_char, iden_src->lex_char);
	iden->token 		  = iden_src->token;
	iden->tam_ocor 	      = iden_src->tam_ocor;
	iden->indice_ult_ocor = iden_src->indice_ult_ocor;
	iden->lex_int 		  = iden_src->lex_int;
	iden->lex_float 	  = iden_src->lex_float;
	iden->ocor[0] 		  = iden_src->ocor[0];
	iden->prox 			  = NULL;

	return iden;

} // end-aloqueECopieIdentificador (tIdentificador *iden_src)

#endif