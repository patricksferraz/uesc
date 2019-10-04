/*
 *---------------------------------------------------------------------
 *
 *   File    : errosLexicos.h
 *   Created : 2017-10-28
 *   Modified: 2017-10-28
 *
 *   Header para manipulação dos Erros léxicos possíveis
 * 	 da linguagem Portugol
 *
 *---------------------------------------------------------------------
 */

#ifndef _ERROSLEXICOS_H
#define _ERROSLEXICOS_H

/**
 * ---------------------------------------------------
 * INCLUDES 
 * ---------------------------------------------------
 */


/**
 * ---------------------------------------------------
 * MACROS
 * ---------------------------------------------------
 */

#define QNT_ERROS_LEXICOS 5
#define TAM_INICIAL_TAB_ERRO 20

/**
 * ---------------------------------------------------
 * TIPOS
 * ---------------------------------------------------
 */

typedef enum
{
	tErro_ponto_isolado = 1,		  // 1
	tErro_caractere_invalido,		  // 2
	tErro_cadeia_nao_fechada,		  // 3
	tErro_delimitador_esperado,		  // 4
	tErro_comentario_bloco_nao_fechado// 5
} tErroLex;

typedef struct
{
	char simbolo;
	int  lin;
	int  col;
	tErroLex id;
} tErroLexIdentificado;

typedef struct
{
	int    indice_ult_registro;
	size_t tam_tabela;
	tErroLexIdentificado *erro;
} tTabErroLexIdentificado;

/**
 * ---------------------------------------------------
 * PROTÓTIPOS DE FUNÇÕES
 * ---------------------------------------------------
 */

char * devolvaNomeErro    (tErroLex *erro); 
int  inicializeTabErroLex (tTabErroLexIdentificado *tab_erro);
int  instaleErroLex 	  (tTabErroLexIdentificado *tab_erro, tErroLexIdentificado *erro);
void finalizeTabErroLex   (tTabErroLexIdentificado *tab_erro);

/**
 * ---------------------------------------------------
 * DECLARAÇÕES DE FUNÇÕES
 * ---------------------------------------------------
 */

/**
 * Função devolve o nome do erro ao seu respectivo tErroLex.
 * NULL caso não exista o erro informado.
 * @param tErroLex *erro
 * @return char *
 */

char * devolvaNomeErro (tErroLex *erro)
{
	switch (*erro)
	{
		case tErro_ponto_isolado:				 return "Ponto isolado";
		case tErro_caractere_invalido:			 return "Caractere invalido";
		case tErro_cadeia_nao_fechada:			 return "Cadeia nao fechada";
		case tErro_delimitador_esperado:		 return "Delimitador esperado";
		case tErro_comentario_bloco_nao_fechado: return "Comentario de bloco nao fechado";
	}

	return NULL;

} // end-devolvaNomeErro (tErroLex *erro)

/**
 * Função para inicializar tabela de erros identificados
 * com TAM_INICIAL_TAB_ERRO definido. Retorna 0 caso a 
 * inicialização ocorra com sucesso ou -1, caso contrário.
 * @param tTabErroLexIdentificado *tab_erro
 * @return int
 */

int inicializeTabErroLex (tTabErroLexIdentificado *tab_erro)
{
	tab_erro->indice_ult_registro = -1;
    tab_erro->tam_tabela = TAM_INICIAL_TAB_ERRO;

    tab_erro->erro = (tErroLexIdentificado *) malloc (tab_erro->tam_tabela * sizeof(tErroLexIdentificado));
    if (tab_erro->erro == NULL)
    	return -1;

    return 0;

} // end-inicializeTabErro (tTabErroLexIdentificado *tab_erro)

/**
 * Função para instalar um Erro léxico identificado
 * (tErroLexIdentificado) na tabela de erro identificado
 * (tTabErroLexIdentificado), realocando espaço na tabela
 * caso não exista. Retorna o índice onde o último erro
 * foi inserido na tabela ou -1 p/ erro durante a inserção
 * na tabela.
 * @param tTabErroLexIdentificado *tab_erro, tErroLexIdentificado *erro
 * @return int
 */

int instaleErroLex (tTabErroLexIdentificado *tab_erro, tErroLexIdentificado *erro)
{
	if ((tab_erro->indice_ult_registro + 1) == tab_erro->tam_tabela)
	{
		tab_erro->tam_tabela <<= 1;

		tab_erro->erro = (tErroLexIdentificado *) realloc (tab_erro->erro, (tab_erro->tam_tabela * sizeof(tErroLexIdentificado)));
		if (tab_erro->erro == NULL)
			return -1;
	}

	tab_erro->erro[ ++ tab_erro->indice_ult_registro ] = *erro;

	return tab_erro->indice_ult_registro;

} // end-instaleErroLex (tTabErroLexIdentificado *tab_erro, tErroLexIdentificado *erro)

/**
 * Função finaliza a tabela de erros identificados desalocando
 * o espaço de memória reservado para o mesmo.
 * @param tTabErroLexIdentificado *tab_erro
 * @return void
 */

void finalizeTabErroLex (tTabErroLexIdentificado *tab_erro)
{
	free(tab_erro->erro);

} // end-finalizeTabErroLex (tTabErroLexIdentificado *tab_erro)

#endif