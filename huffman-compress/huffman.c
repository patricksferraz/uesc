#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 20

typedef struct N{
    struct N *esquerda;
    char simbolo;
    int frequencia;
    struct N *direita;
}No;

void f_menu(int);
No* f_alocaMemoria();
int f_comprimir(char*);
void f_registrarSimbolo(No*, No*, char);
int f_descomprimir(char*, char*);

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
    char nomeArquivo[M], nomeArquivoArvore[M];

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
            printf("\nDigite o nome do arquivo arvore: ");
            gets(nomeArquivoArvore);
            if(!f_descomprimir(nomeArquivo, nomeArquivoArvore))
                printf("\nDescomprimido com sucesso");
            break;
        case 0:
            printf("\nFechando aplicacao");
            break;
        default:
            printf("\nEntrada invalida");
    }
}

No* f_alocaMemoria(){
    No* no;

    if((no = (No*)calloc(1, sizeof(No))) == NULL){
        printf("\nErro ao alocar memoria");
        exit(1);
    }

    return no;
}

int f_comprimir(char *nomeArquivo){
    FILE *arquivo, *arqComprimido, *arqArvore;
    No *no, *primNoFolha, noTemp, *noProx, *noRaiz, *noPai;
    char c;
    int i;

    if((arquivo = fopen(strcat(nomeArquivo, ".txt"), "r")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }

    if((arqComprimido = fopen("arqComprimido.txt", "w")) == NULL){
        printf("\nErro ao criar arquivo");
        return 1;
    }

    if((arqArvore = fopen("arqArvore.txt", "w")) == NULL){
        printf("\nErro ao criar arquivo");
        return 1;
    }

    primNoFolha = f_alocaMemoria();

    c = fgetc(arquivo);
    primNoFolha->simbolo = c;
    primNoFolha->frequencia++;

    for(c = fgetc(arquivo); !feof(arquivo); c = fgetc(arquivo)){
        f_registrarSimbolo(no, primNoFolha, c);
    }

    for(no = primNoFolha; no->direita != NULL; no = no->direita){
        printf("%c", no->simbolo);
        printf("%d\n", no->frequencia);
    }

    for(noProx = no = primNoFolha; no != NULL; noProx = no = no->direita)
        while(noProx != NULL){
            if(noProx->frequencia > noProx->direita->frequencia){
                noTemp.frequencia = noProx->frequencia;
                noTemp.simbolo = noProx->simbolo;
                noProx->frequencia = noProx->direita->frequencia;
                noProx->simbolo = noProx->direita->simbolo;
                noProx->direita->frequencia = noTemp.frequencia;
                noProx->direita->simbolo = noTemp.simbolo;
                noProx = noProx->direita;
            }
        }

    for(no = primNoFolha; no->direita != NULL; no = no->direita){
        printf("%c", no->simbolo);
        printf("%d\n", no->frequencia);
    }

    for(no = primNoFolha->direita; no->direita != NULL; primNoFolha = no, no = primNoFolha->direita){
        free(primNoFolha);
    }

    fclose(arquivo);
    fclose(arqComprimido);
    fclose(arqArvore);
    return 0;
}

void f_registrarSimbolo(No *no, No *primNoFolha, char c){

    for(no = primNoFolha; ; no = no->direita){
        if(no->simbolo == c){
            no->frequencia++;
            break;
        }else if(no->direita == NULL){
            no->direita = f_alocaMemoria();
            no->direita->esquerda = no;
            no = no->direita;
            no->simbolo = c;
            no->frequencia++;
            break;
        }
    }
}

int f_descomprimir(char *nomeArquivo, char *nomeArquivoArvore){
    FILE *arqComprimido, *arqDescomprimido, *arqArvore;
    No *no;

    if((arqComprimido = fopen(strcat(nomeArquivo, ".txt"), "r")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }

    if((arqArvore = fopen(strcat(nomeArquivoArvore, ".txt"), "r")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }

    if((arqDescomprimido = fopen("arqDescomprimido.txt", "w")) == NULL){
        printf("\nErro ao criar arquivo");
        return 1;
    }

    free(no);
    fclose(arqComprimido);
    fclose(arqArvore);
    fclose(arqDescomprimido);
    return 0;
}
