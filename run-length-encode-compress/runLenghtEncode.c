#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 20

void f_menu(int);
int f_comprimir(char*);
int f_descomprimir(char*);

int main(){
    int op;

    do{
        printf("\nCompressao Run lenght Encode");
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
    char c, anterior;
    int cont;

    if((arquivo = fopen(strcat(nomeArquivo, ".txt"), "r")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }

    if((arqComprimido = fopen("arqComprimido.txt", "w")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }

    for(anterior = fgetc(arquivo), cont = 1; !feof(arquivo); anterior = c){
        if((c = fgetc(arquivo)) == anterior){
            cont++;
        }else if(cont == 1){
            fputc(anterior, arqComprimido);
        }else{
            fprintf(arqComprimido, "#%d%c", cont, anterior);
            cont = 1;
        }
    }

    fclose(arquivo);
    fclose(arqComprimido);
    return 0;
}

int f_descomprimir(char *nomeArquivo){
    FILE *arqComprimido, *arqDescomprimido;
    char c, temp;
    int qnt = 0;

    if((arqComprimido = fopen(strcat(nomeArquivo, ".txt"), "r")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }

    if((arqDescomprimido = fopen("arqDescomprimido.txt", "w")) == NULL){
        printf("\nErro ao abrir arquivo");
        return 1;
    }

    for(c = fgetc(arqComprimido); !feof(arqComprimido);){
        if(c == '#'){
            temp = c;
            if(isdigit(c = fgetc(arqComprimido)))
                for(qnt = c-'0', c = fgetc(arqComprimido); qnt>1; qnt--)
                    fputc(c, arqDescomprimido);
            else
                fputc(temp, arqDescomprimido);
        }else{
            fputc(c, arqDescomprimido);
            c = fgetc(arqComprimido);
        }
    }

    fclose(arqDescomprimido);
    fclose(arqComprimido);
    return 0;
}
