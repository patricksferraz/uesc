#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 20

void f_menu(int);
int f_cifrar(char*);
char f_cifrando(char, int);
int f_descifrar(char*, char*);
char f_descifrando(char, int);

int main(){
    int op;

    do{
        printf("\n----Cifra de Chave Unica----");
        printf("\n[1] - Cifrar");
        printf("\n[2] - Descifrar");
        printf("\n[0] - Sair");
        printf("\n----------------------------");
        printf("\nDigite a escolha: ");
        scanf("%d", &op);
        f_menu(op);
    }while(op!=0);

    return 0;
}

void f_menu(int op){
    char nomeArquivo[M], nomeArquivoChave[M];

    switch(op){
        case 1:
            fflush(stdin);
            printf("\nDigite o nome do arquivo para cifrar: ");
            gets(nomeArquivo);
            if(!f_cifrar(nomeArquivo))
                printf("\nCifrado com sucesso");
            break;
        case 2:
            fflush(stdin);
            printf("\nDigite o nome do arquivo para descifrar: ");
            gets(nomeArquivo);
            printf("\nDigite o nome do arquivo com as chaves: ");
            gets(nomeArquivoChave);
            if(!f_descifrar(nomeArquivo, nomeArquivoChave))
                printf("\nDescifrado com sucesso");
            break;
        case 0:
            printf("\nFechando aplicacao");
            break;
        default:
            printf("\nEntrada invalida");
    }
}

int f_cifrar(char *nomeArquivo){
    FILE *arquivo, *arqCifrado, *arqChave;
    char c;
    int chave;

    if((arquivo = fopen(strcat(nomeArquivo, ".txt"), "r")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }


    if((arqCifrado = fopen("cifrado.txt", "w")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }

    if((arqChave = fopen("arqChave.txt", "w")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }

    for(c = fgetc(arquivo); !feof(arquivo); fputc(c, arqCifrado), c = fgetc(arquivo)){
        if(isalpha(c)){
            chave = rand()%26;
            c = f_cifrando(c, chave);
            fputc(chave, arqChave);
        }
    }

    fclose(arquivo);
    fclose(arqCifrado);
    fclose(arqChave);
    return 0;
}

char f_cifrando(char c, int chave){
    if(chave == 0)
        return c;
    if(isalpha(c+1))
        return f_cifrando(++c, --chave);
    return f_cifrando(c-25, --chave);
}

int f_descifrar(char *nomeArquivo, char *nomeArquivoChave){
    FILE *arqCifrado, *arqDescifrado, *arqChave;
    char c;
    int chave;

    if((arqCifrado = fopen(strcat(nomeArquivo, ".txt"), "r")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }

    if((arqChave = fopen(strcat(nomeArquivoChave, ".txt"), "r")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }

    if((arqDescifrado = fopen("descifrado.txt", "w")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }

    for(c = fgetc(arqCifrado); !feof(arqCifrado); fputc(c, arqDescifrado), c = fgetc(arqCifrado)){
        if(isalpha(c)){
            chave = fgetc(arqChave);
            c = f_descifrando(c, chave);
        }
    }

    fclose(arqDescifrado);
    fclose(arqCifrado);
    fclose(arqChave);
    return 0;
}

char f_descifrando(char c, int chave){
    if(chave == 0)
        return c;
    if(isalpha(c-1))
        return f_descifrando(--c, --chave);
    return f_descifrando(c+25, --chave);
}
