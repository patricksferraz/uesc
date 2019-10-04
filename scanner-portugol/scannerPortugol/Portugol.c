/*
 *---------------------------------------------------------------------
 *
 *   File    : analisadorLexico.h
 *   Created : 2017-10-28
 *   Modified: 2017-10-28
 *
 *   Analisador Léxico da linguagem Portugol
 *
 *---------------------------------------------------------------------
 */

/**
 * ---------------------------------------------------
 * INCLUDES
 * ---------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header/lexema.h"
#include "header/tokens.h"
#include "header/tabSimbolos.h"
#include "header/errosLexicos.h"
#include "header/tabTransicoes.h"
#include "header/geradorSaidas.h"

/**
 * ---------------------------------------------------
 * TIPOS
 * ---------------------------------------------------
 */

typedef struct
{
   unsigned int qnt_col_linha_anterior;
   tPos pos;
} tCursor;

typedef struct
{
    int  existe_barra_n; // Armazena 1 se encontrar '\n'
    int  qnt_char_apos_barra_n;
    tPos pos_barra_n;
} tControleBloco;

/**
 * ---------------------------------------------------
 * VARIÁVEIS GLOBAIS
 * ---------------------------------------------------
 */

FILE                    *f_in;
tPos                    pos_inicial_simbolo;
tCursor                 cursor;
tLexema                 lexema;
tTabSimbolo             tab_simbolo;
tTabTkReconhecido       tab_token_reconhecido;
tTabErroLexIdentificado tab_erro_identificado;
char                    *ref_inicio_lexema;

/**
 * ---------------------------------------------------
 * PROTÓTIPOS DE FUNÇÕES
 * ---------------------------------------------------
 */

tToken analisadorLexico   (void);
void   leiaProximoSimbolo (char *prox_simbolo);
void   devolva            (int n);

/**
 * ---------------------------------------------------
 * FUNÇÃO PRINCIPAL MAIN
 * ---------------------------------------------------
 * Função main p/ simular o analisador sintático
 * solicitando 1 token por vez ao analisador léxico.
 * @param int argc, char **arqv
 * @return int
 */

int main (int argc, char **argv)
{
    // Verifica a quantidade de argumentos
    if (argc != 2)
        printf
        ("uso:\n"
            "\texecucao: ./Portugol nomearquivo.ptg\n"
        "onde:\n"
            "\tnomearquivo.ptg\teh um arquivo contendo o algoritmo na linguagem Portugol\n"
        );
    else
    {
        // Abre fluxo com arquivo de entrada
        if ((f_in = fopen(argv[1], "r")) == NULL)
        {
            printf("O arquivo escolhido nao existe\n");
            exit(1);
        }

        // Inicializa lexema e guarda o endereço inicial do lexema.nome alocado
        if (inicializeLexema(&lexema) == NULL)
        {
            printf("Espaco de memoria insuficiente p/ inicializar o lexema\n");
            exit(1);
        }

        if (inicializeTabErroLex(&tab_erro_identificado) == -1)
        {
            printf("Espaco de memoria insuficiente p/ inicializar tabela de erro\n");
            exit(1);
        }

        if (inicializeTabTkReconhecido(&tab_token_reconhecido) == -1)
        {
            printf("Espaco de memoria insuficiente p/ inicializar tabela de token\n");
            exit(1);
        }

        cursor.qnt_col_linha_anterior = 0;
        cursor.pos.lin = 1;
        cursor.pos.col = 0;

        // Chamada ao léxico solicitando tokens
        while (feof(f_in) == 0)
            analisadorLexico();
         
        
        if (gereArquivoErro(f_in, argv[1], &tab_erro_identificado) == -1)
        {
            printf("Erro ao gerar arquivo de erros\n");
            exit(1);
        }

        if (gereArquivoToken(argv[1], &tab_token_reconhecido, tab_simbolo, &lexema.maior_lex,
            (tab_erro_identificado.indice_ult_registro + 1)) == -1)
        {
            printf("Erro ao gerar arquivo de tokens reconhecidos\n");
            exit(1);
        }

        if (gereArquivoTabSimbolo(argv[1], tab_simbolo, &lexema.maior_lex) == -1)
        {
            printf("Erro ao gerar arquivo da tabela de simbolos\n");
            exit(1);
        }

        finalizeLexema(&lexema);
        finalizeTabSimbolo(tab_simbolo);
        finalizeTabErroLex(&tab_erro_identificado);
        finalizeTabTKReconhecido(&tab_token_reconhecido);
        fclose(f_in);
    }

    return 0;

} // end-main (int argc, char **argv)

/**
 * Função para ler o próximo símbolo do arquivo armazenando
 * na variável prox_simbolo passada como referência.
 * @param char *prox_simbolo
 * @return void
 */

void leiaProximoSimbolo (char *prox_simbolo)
{
    if ((*prox_simbolo = fgetc(f_in)) == '\n')
    {
        cursor.qnt_col_linha_anterior = cursor.pos.col;
        cursor.pos.col = 0;
        cursor.pos.lin ++;
    }
    else
        cursor.pos.col ++;

} // end-leiaProximoSimbolo (char *prox_simbolo)

/**
 * Função para devolver n símbolos p/ entrada
 * @param int n
 * @return void
 */

void devolva (int n)
{
    fseek(f_in, n, SEEK_CUR);

    if ((cursor.pos.col += n) < 0)
    {
        cursor.pos.lin --;
        cursor.pos.col = cursor.qnt_col_linha_anterior - cursor.pos.col;
    }

} // end-devolva (int n)

/**
 * Função do analisador léxico. Retorna um token por vez ao
 * analisador sintático, simulado na função main, identificado
 * a partir do arquivo de entrada. Cada token é instalado na
 * tabela de token, erros instalados na tabela de erros, e
 * identificadores (tk_IDEN, tk_DECIMAL, tk_CADEIA, tk_INTEIRO)
 * armazenado na tabela de símbolos. O analisador segue a ideia
 * de uma máquina de estados, visível no switch e no header
 * (tabTransicoes.h).
 * @param void
 * @return tToken
 */

tToken analisadorLexico ()
{
    char                 simbolo;
    int                  estado = 0;
    tToken               token = -1;
    tIdentificador       identificador;
    tControleBloco       controle_bloco;
    tTkReconhecido       token_reconhecido;
    tErroLexIdentificado erro;

    token_reconhecido.pos_tab_simbolo = -1;

    controle_bloco.existe_barra_n = 0;
    controle_bloco.qnt_char_apos_barra_n = 0;
    controle_bloco.pos_barra_n.lin = 0;
    controle_bloco.pos_barra_n.col = 0;

    while (1)
    {
        switch (estado)
        {
            case 0:
                pos_inicial_simbolo.lin = cursor.pos.lin;
                pos_inicial_simbolo.col = cursor.pos.col + 1;
                break;
            //------------------------------------------------------------------
            case 1:
            case 4:
            case 7:
            case 9:
            case 11:
                concateneSimboloLexema(&lexema, &simbolo);
                break;
            //------------------------------------------------------------------
            case 3:
                erro.simbolo = simbolo;
                erro.lin = cursor.pos.lin;
                erro.col = cursor.pos.col;
                erro.id  = tErro_delimitador_esperado;
                instaleErroLex(&tab_erro_identificado, &erro);
            case 2:
                devolva(-1);
                reinicieLexema(&lexema);
                token = tk_INTEIRO;
                if (gereIdentificador(&identificador, lexema.nome, &token, &pos_inicial_simbolo) == -1)
                {
                    printf("Espaco de memoria insuficiente p/ gerar identificador\n");
                    exit(1);
                }
                if ((token_reconhecido.pos_tab_simbolo = instaleIdenTabSimbolo(tab_simbolo, &identificador)) == -1)
                {
                    printf("Espaco de memoria insuficiente p/ instalar identificador na tabela de simbolos\n");
                    exit(1);
                }
                break;
            //------------------------------------------------------------------
            case 5:
                erro.simbolo = simbolo;
                erro.lin = cursor.pos.lin;
                erro.col = cursor.pos.col;
                erro.id  = tErro_delimitador_esperado;
                instaleErroLex(&tab_erro_identificado, &erro);
            case 6:
                devolva(-1);
                reinicieLexema(&lexema);
                token = tk_DECIMAL;
                if (gereIdentificador(&identificador, lexema.nome, &token, &pos_inicial_simbolo) == -1)
                {
                    printf("Espaco de memoria insuficiente p/ gerar identificador\n");
                    exit(1);
                }
                if ((token_reconhecido.pos_tab_simbolo = instaleIdenTabSimbolo(tab_simbolo, &identificador)) == -1)
                {
                    printf("Espaco de memoria insuficiente p/ instalar identificador na tabela de simbolos\n");
                    exit(1);
                }
                break;
            //------------------------------------------------------------------
            case 8:
                erro.simbolo = '.';
                erro.lin = pos_inicial_simbolo.lin;
                erro.col = pos_inicial_simbolo.col;
                erro.id  = tErro_ponto_isolado;
                instaleErroLex(&tab_erro_identificado, &erro);
                devolva(-2);
                reinicieLexema(&lexema);
                break;
            //------------------------------------------------------------------
            case 10:
                devolva(-1);
                if (simbolo == EOF)
                {
                    fseek(f_in, 1, SEEK_CUR);
                }
                reinicieLexema(&lexema);
                if ((token = palavraReservadaOuIden(lexema.nome)) == -1)
                {
                    printf("Espaco de memoria insuficiente p/ identificar palavra reservada\n");
                    exit(1);
                }
                if (token == tk_IDEN)
                {
                    if (gereIdentificador(&identificador, lexema.nome, &token, &pos_inicial_simbolo) == -1)
                    {
                        printf("Espaco de memoria insuficiente p/ gerar identificador\n");
                        exit(1);
                    }
                    if ((token_reconhecido.pos_tab_simbolo = instaleIdenTabSimbolo(tab_simbolo, &identificador)) == -1)
                    {
                        printf("Espaco de memoria insuficiente p/ instalar identificador na tabela de simbolos\n");
                        exit(1);
                    }
                }
                break;
            //------------------------------------------------------------------
            case 12:
                erro.simbolo = '"';
                erro.lin = pos_inicial_simbolo.lin;
                erro.col = pos_inicial_simbolo.col;
                erro.id  = tErro_cadeia_nao_fechada;
                instaleErroLex(&tab_erro_identificado, &erro);
                devolva(-1);
            case 13:
                concateneSimboloLexema(&lexema, "\"");
                reinicieLexema(&lexema);
                token = tk_CADEIA;
                if (gereIdentificador(&identificador, lexema.nome, &token, &pos_inicial_simbolo) == -1)
                {
                    printf("Espaco de memoria insuficiente p/ gerar identificador\n");
                    exit(1);
                }
                if ((token_reconhecido.pos_tab_simbolo = instaleIdenTabSimbolo(tab_simbolo, &identificador)) == -1)
                {
                    printf("Espaco de memoria insuficiente p/ instalar identificador na tabela de simbolos\n");
                    exit(1);
                }
                break;
            //------------------------------------------------------------------
            case 15:
                token = tk_menor_igual;
                break;
            //------------------------------------------------------------------
            case 16:
                token = tk_atrib;
                break;
            //------------------------------------------------------------------
            case 17:
                token = tk_diferente;
                break;
            //------------------------------------------------------------------
            case 18:
                devolva(-1);
                token = tk_menor;
                break;
            //------------------------------------------------------------------
            case 20:
                token = tk_maior_igual;
                break;
            //------------------------------------------------------------------
            case 21:
                devolva(-1);
                token = tk_maior;
                break;
            //------------------------------------------------------------------
            case 23:
                token = tk_decr;
                break;
            //------------------------------------------------------------------
            case 24:
                devolva(-1);
                token = tk_menos;
                break;
            //------------------------------------------------------------------
            case 26:
                token = tk_incr;
                break;
            //------------------------------------------------------------------
            case 27:
                devolva(-1);
                token = tk_mais;
                break;
            //------------------------------------------------------------------
            case 28:
                token = tk_igual;
                break;
            //------------------------------------------------------------------
            case 29:
                token = tk_vezes;
                break;
            //------------------------------------------------------------------
            case 30:
                token = tk_pt_virg;
                break;
            //------------------------------------------------------------------
            case 31:
                token = tk_virg;
                break;
            //------------------------------------------------------------------
            case 32:
                token = tk_dois_pts;
                break;
            //------------------------------------------------------------------
            case 33:
                token = tk_fecha_par;
                break;
            //------------------------------------------------------------------
            case 35:
                devolva(-1);
                token = tk_abre_par;
                break;
            //------------------------------------------------------------------
            case 36:
            case 37:

                // Tratamento p/ erro de comentário de bloco não fechado
                if (simbolo == '\n' && controle_bloco.existe_barra_n == 0)
                {
                    controle_bloco.pos_barra_n = cursor.pos;
                    controle_bloco.existe_barra_n = 1;
                }
                else if (controle_bloco.existe_barra_n)
                    controle_bloco.qnt_char_apos_barra_n ++;

                break;
            //------------------------------------------------------------------
            case 38:
                erro.simbolo = '(';
                erro.lin = pos_inicial_simbolo.lin;
                erro.col = pos_inicial_simbolo.col;
                erro.id  = tErro_comentario_bloco_nao_fechado;
                instaleErroLex(&tab_erro_identificado, &erro);

                // Recuperação de erro p/ comentário de bloco não fechado
                fseek(f_in, -(++controle_bloco.qnt_char_apos_barra_n), SEEK_CUR);
                cursor.pos.lin = --controle_bloco.pos_barra_n.lin;
                break;
            //------------------------------------------------------------------
            case 40:
                devolva(-1);
                token = tk_dividido;
                break;
            //------------------------------------------------------------------
            case 42:
                token = tk_EOF;
                break;
            //------------------------------------------------------------------
            case 43:
                erro.simbolo = simbolo;
                erro.lin = pos_inicial_simbolo.lin;
                erro.col = pos_inicial_simbolo.col;
                erro.id  = tErro_caractere_invalido;
                instaleErroLex(&tab_erro_identificado, &erro);
                devolva(-1);
                break;
            //------------------------------------------------------------------
            // Default p/ estados: 14 - 19 - 22 - 25 - 34 - 39 - 41
            default:
                break;
        }

        if (token != -1)
        {
            token_reconhecido.lin = pos_inicial_simbolo.lin;
            token_reconhecido.col = pos_inicial_simbolo.col;
            token_reconhecido.id  = token;
            
            if (instaleToken(&tab_token_reconhecido, &token_reconhecido) == -1)
            {
                printf("Espaco de memoria insuficiente p/ armazenar token\n");
                exit(1);
            }
            return token;
        }

        leiaProximoSimbolo(&simbolo);
        estado = transicao[estado][char2Simbolo(&simbolo)];
    
    }

} // end-analisadorLexico (void)