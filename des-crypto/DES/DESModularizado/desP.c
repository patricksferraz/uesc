/*
 *---------------------------------------------------------------------
 *
 *   File    : desP.c
 *   Created : 2017-10-28
 *   Modified: 2017-10-28
 *
 *   Algoritmo de criptografia da rede de Feistel
 *
 *---------------------------------------------------------------------
 */

/**
 * --------------------------------------------------------------------
 * INCLUDES
 * --------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header/conversores.h"
//#include "header/geradores.h"
#include "header/permutadores.h"
#include "header/shiftCircular.h"
#include "header/valoresBinarios.h"

/**
 * --------------------------------------------------------------------
 * MACROS
 * --------------------------------------------------------------------
 */

#define ROUNDS 16
#define TAM_MEIO_BLOCO 4

/**
 * --------------------------------------------------------------------
 * VARIÁVEIS GLOBAIS
 * --------------------------------------------------------------------
 */

FILE *f_log;

/**
 * --------------------------------------------------------------------
 * PROTÓTIPOS DE FUNÇÕES
 * --------------------------------------------------------------------
 */

tBloco8B leiaProxBloco  (FILE *f_in);
void     escrevaBloco   (tBloco8B *bloco, FILE *f_out);
void     cifreECB       (t32UBits *bit, FILE *f_in, FILE *f_out);
void     cifreCBC       (t32UBits *bit, FILE *f_in, FILE *f_out);
void     decifreECB     (t32UBits *bit, FILE *f_in, FILE *f_out);
void     decifreCBC     (t32UBits *bit, FILE *f_in, FILE *f_out);
void     apliqueFeistel (tBloco8B *bloco);

/**
 * --------------------------------------------------------------------
 * FUNÇÃO PRINCIPAL MAIN
 * --------------------------------------------------------------------
 */

int main (int argc, char **argv)
{
    // Variáveis
    tBloco8B chave;
    t32UBits bit;
    FILE *f_in;
    FILE *f_out;
    size_t tam_meio_bloco = TAM_MEIO_BLOCO;
    int i;
    int j;
    
    // Verifica a quantidade de argumentos
    if (argc < 4 || argc > 5)
        printf("DES 1.0 (30 Novembro 2017)."
            "\n\nUSO: %s arquivo [-ação] k [-operação] [-opção]"
            "\n\nONDE:"
            "\n\tarquivo\t\t:arquivo TEXTO para ser criptografado."
            "\n\t\t\t|arquivo BINÁRIO para ser descriptografado."
            "\n\tk\t\t:chave de oito-caracteres (ASCII) ou dezesseis-caracteres (HEX)."
            "\n\nPadrão da criptografia/descriptografia é modo de operação Electronic Code Book sem geração de log."
            "\nCaso definido uma opção de log, o log de chaves também será gerado."
            "\n\nAÇÃO:"
            "\n\t-c\t\t:criptografar entrada."
            "\n\t-d\t\t:descriptografar entrada."
            "\n\t-ch\t\t:criptografar entrada com dezesseis digitos hexadecimal [0-F]."
            "\n\t-dh\t\t:descriptografar entrada com dezesseis digitos hexadecimal [0-F]."
            "\n\nOPERAÇÃO:"
            "\n\t-cbc\t\t:defini modo de operação Cipher Block Chaining."
            "\n\nOPÇÕES:"
            "\n\t-logb\t\t:gerar log de operação em binário."
            "\n\t-logh\t\t:gerar log de operação em hexadecimal."
            "\n\nEXEMPLOS:"
            "\n\t%s mensagem.txt -c CHAVEOIT -cbc -logb"
            "\n\t%s mensagem-txt.des -d CHAVEOIT -cbc -logb"
            "\n\t%s mensagem.txt -ch df01ff234abc3d4f -cbc -logh"
            "\n\t%s mensagem-txt.des -dh df01ff234abc3d4f -cbc -logh\n\n", argv[0], argv[0], argv[0], argv[0], argv[0]);
    else
    {
        // armazenandoChave
        if (strlen(argv[3]) != 8)
        {
            printf("Erro, favor digitar uma chave de 8 Bytes\n");
            exit(1);
        }
        else
            for (i = 0, j = tam_meio_bloco; i < tam_meio_bloco; i++, j++)
            {
                chave.l = (chave.l << 8) | argv[3][i];
                chave.r = (chave.r << 8) | argv[3][j];
            }
        // end-armazenandoChave

        // Verifica a operação para cifrar
        if (strcmp(argv[2], "-c") == 0)
        {
            // abreFluxoComArquivos
            if ((f_in = fopen(argv[1], "r")) == NULL)
            {
                printf("O arquivo escolhido para cifrar nao existe\n");
                exit(1);
            }
            
            if ((f_out = fopen(strcat( argv[1], ".fn" ), "wb")) == NULL)
            {
                printf("Erro ao criar arquivo cifrado\n");
                exit(1);
            }
            // end-abreFluxoComArquivos

            // Inicializa 32 posições binárias
            inicialize32Ub(&bit);

            // Aplica cifra modo de operação ECB
            if (argv[4] && strcmp(argv[4], "-cbc") == 0)
            {
                cifreCBC(&bit, f_in, f_out);
                printf("Log de operacao armazenado no arquivo criptografiaCBC.log\n");
            }
            else
            {
                cifreECB(&bit, f_in, f_out);
                printf("Log de operacao armazenado no arquivo criptografiaECB.log\n");
            }
            
            // Fecha fluxo com arquivos
            fclose(f_in);
            fclose(f_out);
            
        }
        // Verifica a operação para decifrar
        else if (strcmp(argv[2], "-d") == 0)
        {
            // abreFluxoComArquivos
            if ((f_in = fopen(argv[1], "rb")) == NULL)
            {
                printf("O arquivo escolhido para decifrar nao existe\n");
                exit(1);
            }
            
            if ((f_out = fopen(strcat( argv[1], ".txt" ), "w")) == NULL)
            {
                printf("Erro ao criar arquivo decifrado\n");
                exit(1);
            }
            // end-abreFluxoComArquivos

            // Inicializa 32 posições binárias
            inicialize32Ub(&bit);

            // Aplica decifra modo de operação ECB
            if (argv[4] && strcmp(argv[4], "-cbc") == 0)
            {
                decifreCBC(&bit, f_in, f_out);
                printf("Log de operacao armazenado no arquivo descriptografiaCBC.log\n");
            }
            else
            {
                decifreECB(&bit, f_in, f_out);
                printf("Log de operacao armazenado no arquivo descriptografiaECB.log\n");
            }

            // Fecha fluxo com arquivos
            fclose(f_in);
            fclose(f_out);            
        }
        else
            printf("DES 1.0 (30 Novembro 2017)."
                "\n\nUSO: %s arquivo [-ação] k [-operação] [-opção]"
                "\n\nONDE:"
                "\n\tarquivo\t\t:arquivo TEXTO para ser criptografado."
                "\n\t\t\t|arquivo BINÁRIO para ser descriptografado."
                "\n\tk\t\t:chave de oito-caracteres (ASCII) ou dezesseis-caracteres (HEX)."
                "\n\nPadrão da criptografia/descriptografia é modo de operação Electronic Code Book sem geração de log."
                "\nCaso definido uma opção de log, o log de chaves também será gerado."
                "\n\nAÇÃO:"
                "\n\t-c\t\t:criptografar entrada."
                "\n\t-d\t\t:descriptografar entrada."
                "\n\t-ch\t\t:criptografar entrada com dezesseis digitos hexadecimal [0-F]."
                "\n\t-dh\t\t:descriptografar entrada com dezesseis digitos hexadecimal [0-F]."
                "\n\nOPERAÇÃO:"
                "\n\t-cbc\t\t:defini modo de operação Cipher Block Chaining."
                "\n\nOPÇÕES:"
                "\n\t-logb\t\t:gerar log de operação em binário."
                "\n\t-logh\t\t:gerar log de operação em hexadecimal."
                "\n\nEXEMPLOS:"
                "\n\t%s mensagem.txt -c CHAVEOIT -cbc -logb"
                "\n\t%s mensagem-txt.des -d CHAVEOIT -cbc -logb"
                "\n\t%s mensagem.txt -ch df01ff234abc3d4f -cbc -logh"
                "\n\t%s mensagem-txt.des -dh df01ff234abc3d4f -cbc -logh\n\n", argv[0], argv[0], argv[0], argv[0], argv[0]);
    }

    return 0;
} // end-main (int argc, char **argv)

/**
 * ----------------------------------------------------------------------
 * DEFINIÇÕES DE FUNÇÕES
 * ----------------------------------------------------------------------
 */

/**
 * Função ler próximo bloco de 8Bytes do arquivo
 * @param FILE *f_in
 * @return tBloco8B
 * obs: melhorar eficiência
 */

tBloco8B leiaProxBloco (FILE *f_in)
{
    tBloco8B bloco;
    int msb = MSB;
    size_t tam_bloco_lido;
    size_t tam_1byte = sizeof(char);
    size_t tam_meio_bloco = TAM_MEIO_BLOCO;

    if ((tam_bloco_lido = fread(&bloco.l, tam_1byte, tam_meio_bloco, f_in)) != tam_meio_bloco)
        bloco.l &= ~(msb >> (((tam_meio_bloco - tam_bloco_lido) << 3) - 1));
    
    if ((tam_bloco_lido = fread(&bloco.r, tam_1byte, tam_meio_bloco, f_in)) != tam_meio_bloco)
        bloco.r &= ~(msb >> (((tam_meio_bloco - tam_bloco_lido) << 3) - 1));

    return bloco;
} // end-leiaProxBloco (FILE *f_in)

/**
 * Função escreve bloco de 8Bytes no arquivo
 * @param tBloco8B *bloco, FILE *f_in
 * @return void
 */

void escrevaBloco (tBloco8B *bloco, FILE *f_out)
{
    size_t tam_1byte = sizeof(char);
    size_t tam_meio_bloco = TAM_MEIO_BLOCO;

    fwrite(&bloco->l, tam_1byte, tam_meio_bloco, f_out);
    fwrite(&bloco->r, tam_1byte, tam_meio_bloco, f_out);
} // end-escrevaBloco (tBloco8B *bloco, FILE *f_out)

/**
 * Função cifra a mensagem contida em um arquivo
 * Modo de operação ECB - Electronic Code Book Mode
 * @param tBloco8B *chave, t32UBits *bit, FILE *f_in
 * @return void
 */

void cifreECB (t32UBits *bit, FILE *f_in, FILE *f_out)
{
    tBloco8B bloco;

    if ((f_log = fopen("criptografiaECB.log", "w")) == NULL)
    {
        printf("Erro ao criar arquivo criptografia.log\n");
        exit(1);
    }

    // Texto inicial para log
    fprintf(f_log, "Li\t\t\t\t\tRi\t\t\t\t\tIP^-1(Li)\t\t\t\tIP^-1(Ri)\n");

    while (feof(f_in) == 0)
    {
        // Ler próximo bloco
        bloco = leiaProxBloco(f_in);

        // Escreve no arquivo log
        fImprima4BBin(bloco.l, bit, f_log);
        fprintf(f_log, "\t");
        fImprima4BBin(bloco.r, bit, f_log);
        fprintf(f_log, "\t");
        
        // Aplica permutação inicial
        ipBloco8B(&bloco, bit);
        // Aplica Feistel
        apliqueFeistel(&bloco);        
        // Aplica permutação inversa
        ipInversaBloco8B(&bloco, bit);

        // Escreve no arquivo log
        fImprima4BBin(bloco.l, bit, f_log);
        fprintf(f_log, "\t");
        fImprima4BBin(bloco.r, bit, f_log);
        fprintf(f_log, "\t");
        fprintf(f_log, "\n");

        escrevaBloco(&bloco, f_out);
    }

    // Escreve no log texto final e fecha fluxo
    fprintf(f_log, "b31\t\t\t     b00\tb31\t\t\t     b00\tb31\t\t\t     b00\tb31\t\t\t     b00\t\n");
    fclose(f_log);

} // end-cifreECB (t32UBits *bit, FILE *f_in, FILE *f_out)

/**
 * Função decifra a mensagem contida em um arquivo
 * Modo de operação ECB - Electronic Code Book Mode
 * @param tBloco8B *chave, t32UBits *bit, FILE *f_in
 * @return void
 */

void decifreECB (t32UBits *bit, FILE *f_in, FILE *f_out)
{
    tBloco8B bloco;

    if ((f_log = fopen("descriptografiaECB.log", "w")) == NULL)
    {
        printf("Erro ao criar arquivo descriptografia.log\n");
        exit(1);
    }

    // Texto inicial para log
    fprintf(f_log, "Li\t\t\t\t\tRi\t\t\t\t\tIP^-1(Li)\t\t\t\tIP^-1(Ri)\n");

    while (feof(f_in) == 0)
    {
        bloco = leiaProxBloco(f_in);

        // Escreve no arquivo log
        fImprima4BBin(bloco.l, bit, f_log);
        fprintf(f_log, "\t");
        fImprima4BBin(bloco.r, bit, f_log);
        fprintf(f_log, "\t");
        
        // Aplica permutação inicial
        ipBloco8B(&bloco, bit);
        // Aplica Feistel
        apliqueFeistel(&bloco);        
        // Aplica permutação inversa
        ipInversaBloco8B(&bloco, bit);

        // Escreve no arquivo log
        fImprima4BBin(bloco.l, bit, f_log);
        fprintf(f_log, "\t");
        fImprima4BBin(bloco.r, bit, f_log);
        fprintf(f_log, "\t");
        fprintf(f_log, "\n");

        escrevaBloco(&bloco, f_out);
    }

    // Escreve no log texto final e fecha fluxo
    fprintf(f_log, "b31\t\t\t     b00\tb31\t\t\t     b00\tb31\t\t\t     b00\tb31\t\t\t     b00\t\n");
    fclose(f_log);

} // end-decifreECB (t32UBits *bit, FILE *f_in, FILE *f_out)

/**
 * Função cifra a mensagem contida em um arquivo
 * Modo de operação ECB - Electronic Code Book Mode
 * @param tBloco8B *chave, t32UBits *bit, FILE *f_in
 * @return void
 */

void cifreCBC (t32UBits *bit, FILE *f_in, FILE *f_out)
{
    tBloco8B vi;
    tBloco8B bloco;

    if ((f_log = fopen("criptografiaCBC.log", "w")) == NULL)
    {
        printf("Erro ao criar arquivo criptografia.log\n");
        exit(1);
    }

    // Texto inicial para log
    fprintf(f_log, "Li\t\t\t\t\tRi\t\t\t\t\tIP^-1(Li)\t\t\t\tIP^-1(Ri)\n");

    // inicializaVI
    vi.l = 0x55555555;
    vi.r = 0x55555555;

    while (feof(f_in) == 0)
    {
        // Ler próximo bloco
        bloco = leiaProxBloco(f_in);

        // Escreve no arquivo log
        fImprima4BBin(bloco.l, bit, f_log);
        fprintf(f_log, "\t");
        fImprima4BBin(bloco.r, bit, f_log);
        fprintf(f_log, "\t");

        // aplicaVI
        bloco.l ^= vi.l;
        bloco.r ^= vi.r;
        
        // Aplica permutação inicial
        ipBloco8B(&bloco, bit);
        // Aplica Feistel
        apliqueFeistel(&bloco);        
        // Aplica permutação inversa
        ipInversaBloco8B(&bloco, bit);

        // Escreve no arquivo log
        fImprima4BBin(bloco.l, bit, f_log);
        fprintf(f_log, "\t");
        fImprima4BBin(bloco.r, bit, f_log);
        fprintf(f_log, "\t");
        fprintf(f_log, "\n");

        // Swap VI para proximo bloco
        vi.l = bloco.l;
        vi.r = bloco.r;

        escrevaBloco(&bloco, f_out);
    }

    // Escreve no log texto final e fecha fluxo
    fprintf(f_log, "b31\t\t\t     b00\tb31\t\t\t     b00\tb31\t\t\t     b00\tb31\t\t\t     b00\t\n");
    fclose(f_log);

} // end-cifreCBC (t32UBits *bit, FILE *f_in, FILE *f_out)

/**
 * Função decifra a mensagem contida em um arquivo
 * Modo de operação ECB - Electronic Code Book Mode
 * @param tBloco8B *chave, t32UBits *bit, FILE *f_in
 * @return void
 */

void decifreCBC (t32UBits *bit, FILE *f_in, FILE *f_out)
{
    tBloco8B vi;
    tBloco8B aux;
    tBloco8B bloco;

    if ((f_log = fopen("descriptografiaCBC.log", "w")) == NULL)
    {
        printf("Erro ao criar arquivo descriptografia.log\n");
        exit(1);
    }

    // Texto inicial para log
    fprintf(f_log, "Li\t\t\t\t\tRi\t\t\t\t\tIP^-1(Li)\t\t\t\tIP^-1(Ri)\n");

    // inicializaVI
    vi.l = 0x55555555;
    vi.r = 0x55555555;

    while (feof(f_in) == 0)
    {
        bloco = leiaProxBloco(f_in);

        // Escreve no arquivo log
        fImprima4BBin(bloco.l, bit, f_log);
        fprintf(f_log, "\t");
        fImprima4BBin(bloco.r, bit, f_log);
        fprintf(f_log, "\t");

        // Armazena bloco p/ prox VI
        aux.l = bloco.l;
        aux.r = bloco.r;
        
        // Aplica permutação inicial
        ipBloco8B(&bloco, bit);
        // Aplica Feistel
        apliqueFeistel(&bloco);        
        // Aplica permutação inversa
        ipInversaBloco8B(&bloco, bit);

        // aplicaVI
        bloco.l ^= vi.l;
        bloco.r ^= vi.r;
        // Swap VI para proximo bloco
        vi.l = aux.l;
        vi.r = aux.r;

        // Escreve no arquivo log
        fImprima4BBin(bloco.l, bit, f_log);
        fprintf(f_log, "\t");
        fImprima4BBin(bloco.r, bit, f_log);
        fprintf(f_log, "\t");
        fprintf(f_log, "\n");

        escrevaBloco(&bloco, f_out);
    }

    // Escreve no log texto final e fecha fluxo
    fprintf(f_log, "b31\t\t\t     b00\tb31\t\t\t     b00\tb31\t\t\t     b00\tb31\t\t\t     b00\t\n");
    fclose(f_log);
    
} // end-decifreCBC (t32UBits *bit, FILE *f_in, FILE *f_out)

/**
 * Função para aplicar Feistel ao bloco com as chaves
 * @param FILE *f_in
 * @return tBloco8B
 * obs: melhorar eficiência
 */

void apliqueFeistel (tBloco8B *bloco)
{
    unsigned int fun;
    unsigned int left;
    unsigned int right;
    int i;

    for (i = 0; i < ROUNDS; i++)
    {     
        // Aplica feistel por shift left circular
        fun = bloco->r;
        leftShiftCircular4B(&fun, 1);
        right = fun ^ bloco->l;
        left = bloco->r;
        
        //Swap para próximo round
        bloco->r = right;
        bloco->l = left;
    }

    // Swap para saida
    bloco->r = left;
    bloco->l = right;
    
}