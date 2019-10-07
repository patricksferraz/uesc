/*
 *---------------------------------------------------------------------
 *
 *   File    : geradorSaidas.h
 *   Created : 2017-10-28
 *   Modified: 2017-10-28
 *
 *   Header para manipulação das saídas do analisador léxico
 * 	 da linguagem Portugol
 *
 *---------------------------------------------------------------------
 */

#ifndef _GERADORSAIDAS_H
#define _GERADORSAIDAS_H

/**
 * ---------------------------------------------------
 * INCLUDES 
 * ---------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexema.h"
#include "tokens.h"
#include "tabSimbolos.h"
#include "errosLexicos.h"

/**
 * ---------------------------------------------------
 * PROTÓTIPOS DE FUNÇÕES
 * ---------------------------------------------------
 */

int gereArquivoErro       (FILE *f_in, char *nome_f_in, tTabErroLexIdentificado *tab_erro_lex);
int gereArquivoToken      (char *nome_f_in, tTabTkReconhecido *tab_token, tTabSimbolo tab_simbolo, int *maior_lex, int qnt_erros);
int gereArquivoTabSimbolo (char *nome_f_in, tTabSimbolo tab_token, int *maior_lex);

/**
 * ---------------------------------------------------
 * DECLARAÇÕES DE FUNÇÕES
 * ---------------------------------------------------
 */

/**
 * Função gera o arquivo contendo a entrada e seu erros
 * léxicos informados viasualmente a partir do arquivo
 * de entrada. Recebe por parametro o fluxo p/ arquivo
 * de entrada, o nome do arquivo e a tabela de erros
 * léxicos identificados pelo analisador léxico. Retorna
 * -1 para erro e 0 caso contrário.
 * @param FILE *f_in, char *nome_f_in, tTabErroLexIdentificado *tab_erro_lex
 * @return int
 */

int gereArquivoErro (FILE *f_in, char *nome_f_in, tTabErroLexIdentificado *tab_erro_lex)
{
    FILE *f_erro;
    char simbolo;
    char *nome_arq_erro;
    int  col;
    int  i = 0;
    int  linha = 1;
    size_t tam_linha = 0;

    nome_arq_erro = (char *) malloc (strlen(nome_f_in) * sizeof(char) + 5);
    sprintf(nome_arq_erro, "%s.err", nome_f_in);

    if ((f_erro = fopen(nome_arq_erro, "w")) == NULL)
	    return -1;
  
    rewind(f_in);
    fprintf(f_erro, "LISTA DE ERROS LEXICOS EM \"%s\"\n\n", nome_f_in);

    while (feof(f_in) == 0)
    {
        if ((simbolo = fgetc(f_in)) != EOF)
        {
            fprintf(f_erro, "[%5d] ", linha);
            tam_linha ++;

            while (simbolo != '\n' && simbolo != EOF)
            {
                fprintf(f_erro, "%c", simbolo);
                simbolo = fgetc(f_in);
                tam_linha ++;
            }

            if (tab_erro_lex->erro[i].lin == linha && i <= tab_erro_lex->indice_ult_registro)
            {
                
                fprintf(f_erro, "\n        ");
                for (col = 1; col < tab_erro_lex->erro[i].col; col++)
                    fprintf(f_erro, "-");
                fprintf(f_erro, "^\n");

                fprintf(f_erro, "        Erro lexico na linha %d coluna %d: %s '%c'",
                    tab_erro_lex->erro[i].lin,
                    tab_erro_lex->erro[i].col,
                    devolvaNomeErro(&tab_erro_lex->erro[i].id),
                    tab_erro_lex->erro[i].simbolo);
                
                i ++;
                if (tab_erro_lex->erro[i].lin == linha)
                {
                    fseek(f_in, -tam_linha, SEEK_CUR);
                    linha --;
                }

            }

            fprintf(f_erro, "\n");
            linha ++;
            tam_linha = 0;
        }
    }

    fprintf(f_erro, "\nTOTAL DE ERROS: %d\n", tab_erro_lex->indice_ult_registro + 1);

    free(nome_arq_erro);
    fclose(f_erro);

    return 0;

} // end-gereArquivoErro (FILE *f_in, char *nome_f_in, tTabErroLexIdentificado *tab_erro_lex)

/**
 * Função gera o arquivo contendo os tokens reconhecidos
 * durante a analise léxica do arquivo de entrada. Recebe
 * por parametro o nome do arquivo, a tabela de tokens
 * reconhecidos pelo analisador léxico, a tabela de simbolos
 * geradas pelo analisado lexico e o tamanho do maior lexema.
 * Retorna -1 caso erro e 0 caso contrário.
 * @param char *nome_f_in, tTabTkReconhecido *tab_token, tTabSimbolo tab_simbolo, int *maior_lex, int qnt_erros
 * @return int
 */

int gereArquivoToken (char *nome_f_in, tTabTkReconhecido *tab_token, tTabSimbolo tab_simbolo, int *maior_lex, int qnt_erros)
{
    FILE *f_token;
    char *nome_arq_token;
    int  i;
    int  j;
    int  linha = 0;
    int  total_token = 0;
    int  qnt_token[QNT_TOKENS + 1] = {0};
    tToken token;
    tIdentificador *iden;

    nome_arq_token = (char *) malloc (strlen(nome_f_in) * sizeof(char) + 5);
    sprintf(nome_arq_token, "%s.tok", nome_f_in);

    if ((f_token = fopen(nome_arq_token, "w")) == NULL)
	    return -1;
    
    fprintf(f_token, "LISTA DE TOKENS RECONHECIDOS EM \"%s\"\n\n", nome_f_in);

    fprintf(f_token, "+-----+-----+-----+----------------+-");
    for (i = 0; i < *maior_lex; i++)
    	fprintf(f_token, "-");
    fprintf(f_token, "-+----------------+\n");

    fprintf(f_token, "| LIN | COL | COD | %-14s | %-*s |  POS TAB SIMB  |\n",
    	"TOKEN",
    	*maior_lex,
    	"LEXEMA");

    fprintf(f_token, "+-----+-----+-----+----------------+-");
    for (i = 0; i < *maior_lex; i++)
    	fprintf(f_token, "-");
    fprintf(f_token, "-+----------------+\n");

    for (i = 0; i <= tab_token->indice_ult_registro; i++)
    {
    	qnt_token[tab_token->token[i].id] ++;

    	if (tab_token->token[i].lin == linha)
			fprintf(f_token,"|     |");
		else
			fprintf(f_token,"| %3d |", tab_token->token[i].lin);

		fprintf(f_token," %3d | %3d | %-14s ", tab_token->token[i].col, tab_token->token[i].id,
            devolvaNomeToken(&tab_token->token[i].id));

		if (tab_token->token[i].pos_tab_simbolo == -1)
			fprintf(f_token, "| %-*s |                |\n", *maior_lex, " ");
        else
        {
            iden = tab_simbolo[tab_token->token[i].pos_tab_simbolo];

            while(iden != NULL)
            {
                if (tab_token->token[i].id == iden->token)
                {
                    for (j = 0; j <= iden->indice_ult_ocor; j++)
                    {
                        if (tab_token->token[i].lin == iden->ocor[j].lin
                            && tab_token->token[i].col == iden->ocor[j].col)
                        {
                            fprintf(f_token, "| %-*s |      %4d      |\n", *maior_lex,
                                iden->lex_char, tab_token->token[i].pos_tab_simbolo);
                        }
                    }
                }
                iden = iden->prox;
            }

        }

        if (tab_token->token[i].lin != linha)
            linha = tab_token->token[i].lin;
    }

    fprintf(f_token, "+-----+-----+-----+----------------+-");
    for (i = 0; i < *maior_lex; i++)
        fprintf(f_token, "-");
    fprintf(f_token, "-+----------------+\n");

    fprintf(f_token, "RESUMO\n\n");
    fprintf(f_token, "+-----+----------------+------+\n");
    fprintf(f_token, "| COD | TOKEN          | USOS |\n");
    fprintf(f_token, "+-----+----------------+------+\n");
    
    for (token = 1; token <= QNT_TOKENS; token++)
    {
        fprintf(f_token, "| %3d | %-14s | %4d |\n", token, devolvaNomeToken(&token), qnt_token[token]);
        total_token += qnt_token[token];
    }
    
    fprintf(f_token, "+-----+----------------+------+\n");
    fprintf(f_token, "|   0 | TOTAL          | %4d |\n", total_token);
    fprintf(f_token, "+-----+----------------+------+\n\n");

    fprintf(f_token, "TOTAL DE ERROS: %d\n\n", qnt_erros);

    free(nome_arq_token);
    fclose(f_token);

    return 0;

} // end-gereArquivoToken (char *nome_f_in, tTabTkReconhecido *tab_token, tTabSimbolo tab_simbolo, int *maior_lex, int qnt_erros)

/**
 * Função gera o arquivo contendo a tabela de simbolos criada
 * durante a analise léxica do arquivo de entrada. Recebe por
 * parametro o nome do arquivo, e a tabela de simbolos.
 * Retorna -1 caso erro e 0 caso contrário.
 * @param char *nome_f_in, tTabSimbolo tab_simbolo
 * @return int
 */

int gereArquivoTabSimbolo (char *nome_f_in, tTabSimbolo tab_simbolo, int *maior_lex)
{
    FILE *f_simbolo;
    char *nome_arq_simbolo;
    int  i;
    int  j;
    int  maior_ocor = 0;
    tIdentificador *iden;
    tToken token;

    nome_arq_simbolo = (char *) malloc (strlen(nome_f_in) * sizeof(char) + 5);
    sprintf(nome_arq_simbolo, "%s.tbl", nome_f_in);

    if ((f_simbolo = fopen(nome_arq_simbolo, "w")) == NULL)
	    return -1;
    
    // Verifica qual maior ocorrência
    for (i = 0; i < TAM_TAB_SIMBOLOS; i++)
        if (tab_simbolo[i])
            if (tab_simbolo[i]->indice_ult_ocor > maior_ocor)
                maior_ocor = tab_simbolo[i]->indice_ult_ocor;
    maior_ocor ++; // conta o indice 0
    maior_ocor *= 10; // tam que (lin,col) ocupa na tabela de simbolos

    fprintf(f_simbolo, "TABELA DE SIMBOLOS - \"%s\"\n\n", nome_f_in);

    fprintf(f_simbolo, "+-----+----------------+-");
    for (i = 0; i < *maior_lex; i++)
        fprintf(f_simbolo, "-");
    fprintf(f_simbolo, "-+-");
    for (i = 0; i < maior_ocor; i++)
        fprintf(f_simbolo, "-");
    fprintf(f_simbolo, "+\n");
        
    fprintf(f_simbolo,"| POS | %-14s | %-*s | %-*s|\n", "TOKEN", *maior_lex,
        "LEXEMA", maior_ocor, "POS NA ENTRADA (linha,coluna)");

    fprintf(f_simbolo, "+-----+----------------+-");
    for (i = 0; i < *maior_lex; i++)
        fprintf(f_simbolo, "-");
    fprintf(f_simbolo, "-+-");
    for (i = 0; i < maior_ocor; i++)
        fprintf(f_simbolo, "-");
    fprintf(f_simbolo, "+\n");


    for (i = 0; i < TAM_TAB_SIMBOLOS; i++)
    {
        iden = tab_simbolo[i];

        while(iden != NULL)
        {
            token = iden->token;
            fprintf(f_simbolo, "| %3d | %-14s | %-*s | ", i, devolvaNomeToken(&token), *maior_lex,
                iden->lex_char);
            for (j = 0; j <= iden->indice_ult_ocor; j++)
                fprintf(f_simbolo, "(%3d,%3d) ", iden->ocor[j].lin, iden->ocor[j].col);
            fprintf(f_simbolo, "%*s|\n", maior_ocor - ((iden->indice_ult_ocor + 1)* 10), "");
            iden = iden->prox;
        }

    }

    fprintf(f_simbolo, "+-----+----------------+-");
    for (i = 0; i < *maior_lex; i++)
        fprintf(f_simbolo, "-");
    fprintf(f_simbolo, "-+-");
    for (i = 0; i < maior_ocor; i++)
        fprintf(f_simbolo, "-");
    fprintf(f_simbolo, "+\n");

    free(nome_arq_simbolo);
    fclose(f_simbolo);

    return 0;

} // end-gereArquivoTabSimbolo (char *nome_f_in, tTabSimbolo tab_simbolo)

#endif