/*
 *---------------------------------------------------------------------
 *
 *   File    : tokens.h
 *   Created : 2017-10-28
 *   Modified: 2017-10-28
 *
 *   Header para manipulação de Tokens do analisador léxico
 *	 da linguagem Portugol
 *
 *---------------------------------------------------------------------
 */

#ifndef _TOKENS_H
#define _TOKENS_H

/**
 * ---------------------------------------------------
 * INCLUDES 
 * ---------------------------------------------------
 */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/**
 * ---------------------------------------------------
 * MACROS
 * ---------------------------------------------------
 */

#define QNT_TOKENS 41
#define TAM_INICIAL_TAB_TOKEN 100
//#define QNT_PALAVRAS_RESERVADAS 18

/**
 * ---------------------------------------------------
 * TIPOS
 * ---------------------------------------------------
 */

typedef enum
{
	tk_EOF = 1,	   // 1
	tk_IDEN,	   // 2
	tk_INTEIRO,	   // 3
	tk_DECIMAL,	   // 4
	tk_CADEIA,	   // 5
	tk_inicio,	   // 6
	tk_fim,		   // 7
	tk_int,		   // 8
	tk_dec,		   // 9
	tk_leia,	   // 10
	tk_imprima,	   // 11
	tk_para,	   // 12
	tk_de,		   // 13
	tk_ate,		   // 14
	tk_passo,	   // 15
	tk_fim_para,   // 16
	tk_se,		   // 17
	tk_entao,	   // 18
	tk_senao,	   // 19
	tk_fim_se,	   // 20
	tk_e,		   // 21
	tk_ou,		   // 22
	tk_nao,		   // 23
	tk_virg,	   // 24
	tk_pt_virg,	   // 25
	tk_dois_pts,   // 26
	tk_abre_par,   // 27
	tk_fecha_par,  // 28
	tk_menor,	   // 29
	tk_menor_igual,// 30
	tk_maior,	   // 31
	tk_maior_igual,// 32
	tk_diferente,  // 33
	tk_igual,	   // 34
	tk_incr,	   // 35
	tk_decr,	   // 36
	tk_atrib,	   // 37
	tk_mais,	   // 38
	tk_menos,	   // 39
	tk_vezes,	   // 40
	tk_dividido	   // 41
} tToken;

typedef struct
{
    int    lin;
    int    col;
    int    pos_tab_simbolo;
    tToken id;
} tTkReconhecido;

typedef struct
{
	int    indice_ult_registro;
    size_t tam_tabela;
    tTkReconhecido *token;
} tTabTkReconhecido;

/**
 * ---------------------------------------------------
 * PROTÓTIPOS DE FUNÇÕES
 * ---------------------------------------------------
 */

char   * devolvaNomeToken 	      (tToken *token);
int    inicializeTabTkReconhecido (tTabTkReconhecido *tab_token);
int    instaleToken 			  (tTabTkReconhecido *tab_token, tTkReconhecido *token);
void   finalizeTabTKReconhecido   (tTabTkReconhecido *tab_token);
tToken palavraReservadaOuIden     (char *lexema);

/**
 * ---------------------------------------------------
 * DECLARAÇÕES DE FUNÇÕES
 * ---------------------------------------------------
 */

/**
 * Função devolve o nome do seu respectivo tToken.
 * Retorna NULL caso não exista o token informado.
 * @param tToken *token
 * @return char *
 */

char * devolvaNomeToken (tToken *token)
{
	char *tk [] = {
		NULL,
		"tk_EOF",
		"tk_IDEN",
		"tk_INTEIRO",
		"tk_DECIMAL",
		"tk_CADEIA",
		"tk_inicio",
		"tk_fim",
		"tk_int",
		"tk_dec",
		"tk_leia",
		"tk_imprima",
		"tk_para",
		"tk_de",
		"tk_ate",
		"tk_passo",
		"tk_fim_para",
		"tk_se",
		"tk_entao",
		"tk_senao",
		"tk_fim_se",
		"tk_e",
		"tk_ou",
		"tk_nao",
		"tk_virg",
		"tk_pt_virg",
		"tk_dois_pts",
		"tk_abre_par",
		"tk_fecha_par",
		"tk_menor",
		"tk_menor_igual",
		"tk_maior",
		"tk_maior_igual",
		"tk_diferente",
		"tk_igual",
		"tk_incr",
		"tk_decr",
		"tk_atrib",
		"tk_mais",
		"tk_menos",
		"tk_vezes",
		"tk_dividido"
	};
	
	return tk[*token];

} // end-devolvaNomeToken (tToken *token)

/**
 * Função para inicializar tabela de tokens reconhecido
 * com TAM_INICIAL_TAB_TOKEN definido. Retorna 0 caso a
 * inicialização ocorra com sucesso ou -1 caso contrário.
 * @param tTabTkReconhecido *tab_token
 * @return int
 */

int inicializeTabTkReconhecido (tTabTkReconhecido *tab_token)
{
	tab_token->indice_ult_registro = -1;
    tab_token->tam_tabela = TAM_INICIAL_TAB_TOKEN;
    tab_token->token = (tTkReconhecido *) malloc (tab_token->tam_tabela * sizeof(tTkReconhecido));

    if (tab_token->token == NULL)
    	return -1;

    return 0;

} // end-inicializeTabTkReconhecido (tTabTkReconhecido *tab_token)

/**
 * Função para instalar um token reconhecido (tTkReconhecido) na
 * tabela de token reconhecido (tTabTkReconhecido), realocando
 * espaço na tabela caso não exista. Retorna o índice onde o 
 * último token foi inserido na tabela ou -1 se erro durante a
 * inserção na tabela.
 * @param tTabTkReconhecido *tab_token, tTkReconhecido *token
 * @return int
 */

int instaleToken (tTabTkReconhecido *tab_token, tTkReconhecido *token)
{
	if ((tab_token->indice_ult_registro + 1) == tab_token->tam_tabela)
	{
		tab_token->tam_tabela <<= 1;

		tab_token->token = (tTkReconhecido *) realloc (tab_token->token, (tab_token->tam_tabela * sizeof(tTkReconhecido)));
		if (tab_token->token == NULL)
			return -1;
	}

	tab_token->token[ ++ tab_token->indice_ult_registro ] = *token;

	return tab_token->indice_ult_registro;

} // end-instaleToken (tTabTkReconhecido *tab_token, tTkReconhecido *token)

/**
 * Função finaliza a tabela de tokens reconhecidos desalocando
 * o espaço de memória reservado para o mesmo.
 * @param tTabTkReconhecido *tab_token
 * @return void
 */

void finalizeTabTKReconhecido (tTabTkReconhecido *tab_token)
{
	free(tab_token->token);

} // end-finalizeTabTKReconhecido (tTabTkReconhecido *tab_token)

/**
 * Função verifica se o identificador é uma palavra reservada através
 * do lexema de entrada e retorna o token respectivo.
 * @param char *lexema
 * @return tToken
 */

tToken palavraReservadaOuIden (char *lexema)
{
	tToken token;
	int    i;
	size_t tam_lexema = strlen(lexema);
	// Variável auxiliar p/ ignorar caixa alta/baixa em palavras reservadas
	char   *aux = (char *) malloc (tam_lexema * sizeof(char) + 1);

	if (aux == NULL)
		return -1;

	for (i = 0; i <= tam_lexema; i++)
		aux[i] = tolower(lexema[i]);

	// Verifica se eh palavra reservada ou identificador
	if 		(strcmp(aux,   "inicio") == 0)	token = tk_inicio;
	else if (strcmp(aux,	  "fim") == 0)	token = tk_fim;
	else if (strcmp(aux,	  "int") == 0)	token = tk_int;
	else if (strcmp(aux,	  "dec") == 0)	token = tk_dec;
	else if (strcmp(aux,	 "leia") == 0)	token = tk_leia;
	else if (strcmp(aux,  "imprima") == 0)	token = tk_imprima;
	else if (strcmp(aux,	 "para") == 0)	token = tk_para;
	else if (strcmp(aux, 	   "de") == 0)	token = tk_de;
	else if (strcmp(aux,	  "ate") == 0)	token = tk_ate;
	else if (strcmp(aux,    "passo") == 0)	token = tk_passo;
	else if (strcmp(aux, "fim_para") == 0)	token = tk_fim_para;
	else if (strcmp(aux, 	   "se") == 0)	token = tk_se;
	else if (strcmp(aux,    "entao") == 0)	token = tk_entao;
	else if (strcmp(aux,    "senao") == 0)	token = tk_senao;
	else if (strcmp(aux,   "fim_se") == 0)	token = tk_fim_se;
	else if (strcmp(aux,    	"e") == 0)	token = tk_e;
	else if (strcmp(aux, 	   "ou") == 0)	token = tk_ou;
	else if (strcmp(aux, 	  "nao") == 0)	token = tk_nao;
	else token = tk_IDEN;

	free(aux);
	return token;

} // end-palavraReservadaOuIden (char *lexema)

#endif