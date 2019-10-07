#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 20
#define TAM_JANELA 8
#define TAM_BUFFER 4

void f_menu(int);
int f_comprimir(char*);
int f_descomprimir(char*);

int main(){
    int op;

    do{
        printf("\nCompressao de Huffman");
        printf("\n[1] - Comprimir");
        printf("\n[2] - Descomprimir");
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

    switch(op){
        case 1:
            fflush(stdin);
            printf("\nDigite o nome do arquivo para comprimir: ");
            gets(nomeArquivo);
            if(!f_comprimir(nomeArquivo))
                printf("\nComprimido com sucesso");
            break;
        case 2:
            fflush(stdin);
            printf("\nDigite o nome do arquivo para descomprimir: ");
            gets(nomeArquivo);
            if(!f_descomprimir(nomeArquivo))
                printf("\nDescomprimido com sucesso");
            break;
        case 0:
            printf("\nFechando aplicacao");
            break;
        default:
            printf("\nEntrada invalida");
    }
}

int f_comprimir(char *nomeArquivo){
    FILE *arquivo, *arqComprimido;
    char c, janela[TAM_JANELA] = "", buffer[TAM_BUFFER] = "";
    int i, inicio = 0, qnt = 0;

    if((arquivo = fopen(strcat(nomeArquivo, ".txt"), "r")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }

    if((arqComprimido = fopen("arqComprimido.txt", "w")) == NULL){
        printf("\nErro ao criar arquivo");
        return 1;
    }

    for(i = 0, c = fgetc(arquivo); !feof(arquivo); c = fgetc(arquivo), i++){
        if(i < TAM_BUFFER)
            buffer[i] = c;
        else{
            fseek(arquivo, -sizeof(char), 1);
            break;
        }
    }

    while(!feof(arquivo)){
        for(i = 0; i < TAM_BUFFER; i++)
            for(j = inicio; j < TAM_JANELA; j++){
                if(buffer[i] == janela[j]){
                    inicio = j;
                    qnt++;
                    break;
                }
            }
    }

    fclose(arquivo);
    fclose(arqComprimido);
    return 0;
}

int f_descomprimir(char *nomeArquivo){
    FILE *arqComprimido, *arqDescomprimido;

    if((arqComprimido = fopen(strcat(nomeArquivo, ".txt"), "r")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }

    if((arqDescomprimido = fopen("arqDescomprimido.txt", "w")) == NULL){
        printf("\nErro ao criar arquivo");
        return 1;
    }

    fclose(arqComprimido);
    fclose(arqDescomprimido);
    return 0;
}

