#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 20

void f_menu(int);
int f_cifrar(char*, int);
char f_cifrando(char, int);
int f_descifrar(char*, int);
char f_descifrando(char, int);

int main(){
    int op;

    do{
        printf("\n------Cifra de Cesar------");
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
    char nomeArquivo[M];
    int chave;

    switch(op){
        case 1:
            fflush(stdin);
            printf("\nDigite o nome do arquivo para cifrar: ");
            gets(nomeArquivo);
            printf("\nDigite a chave: ");
            scanf("%d", &chave);
            if(!f_cifrar(nomeArquivo, chave))
                printf("\nCifrado com sucesso");
            break;
        case 2:
            fflush(stdin);
            printf("\nDigite o nome do arquivo para descifrar: ");
            gets(nomeArquivo);
            printf("\nDigite a chave: ");
            scanf("%d", &chave);
            if(!f_descifrar(nomeArquivo, chave))
                printf("\nDescifrado com sucesso");
            break;
        case 0:
            printf("\nFechando aplicacao");
            break;
        default:
            printf("\nEntrada invalida");
    }
}

int f_cifrar(char *nomeArquivo, int chave){
    FILE *arquivo, *arqCifrado;
    char c;

    if((arquivo = fopen(strcat(nomeArquivo, ".txt"), "r")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }


    if((arqCifrado = fopen("cifrado.txt", "w")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }

    for(c = fgetc(arquivo); !feof(arquivo); fputc(c, arqCifrado), c = fgetc(arquivo)){
        if(isalpha(c))
            c = f_cifrando(c, chave);
    }

    fclose(arquivo);
    fclose(arqCifrado);
    return 0;
}

char f_cifrando(char c, int chave){
    if(chave == 0)
        return c;
    if(isalpha(c+1))
        return f_cifrando(++c, --chave);
    return f_cifrando(c-25, --chave);
}

int f_descifrar(char *nomeArquivo, int chave){
    FILE *arqCifrado, *arqDescifrado;
    char c;

    if((arqCifrado = fopen(strcat(nomeArquivo, ".txt"), "r")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }

    if((arqDescifrado = fopen("descifrado.txt", "w")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }

    for(c = fgetc(arqCifrado); !feof(arqCifrado); fputc(c, arqDescifrado), c = fgetc(arqCifrado)){
        if(isalpha(c))
            c = f_descifrando(c, chave);
    }

    fclose(arqDescifrado);
    fclose(arqCifrado);
    return 0;
}

char f_descifrando(char c, int chave){
    if(chave == 0)
        return c;
    if(isalpha(c-1))
        return f_descifrando(--c, --chave);
    return f_descifrando(c+25, --chave);
}
