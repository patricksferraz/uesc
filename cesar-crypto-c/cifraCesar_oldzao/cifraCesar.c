/********************************************************
*                                                       *
* T�tulo: Criptografia de Cesar                         *
*********************************************************
* Autor: Patrick Silva Ferraz [201420380]               *
*********************************************************
* Data cria��o: 14/09/2015                              *
* �ltima modifica��o: 22/09/2015                        *
*********************************************************
* Descri��o: Programa realiza o problema 4 do projeto   *
* 2015.1 (C�digo de Cesar). O usu�rio tem 5 op��es:     *
*                                                       *
* 1-criar nova mensagem para salvar no arquivo          *
* 2-criptrografar uma mensagem no arquivo existente,    *
* 3-descriptografar uma mensagem no arquivo existente.  *
* 4-remover arquivo                                     *
* 5-Sair                                                *
*********************************************************
* ENTRADAS/SA�DA das fun��es realizadas pelo programa:  *
*                                                       *
*   1- (Nome arquivo, tamanho mensagem, e a mensagem)   *
*      ex: (Codigo de Cesar)-ENTRADA                    *
*           Retorna um arquivo com essa mensagem        *
*                                                       *
*   2- (Nome arquivo e a ordem; ele criptografa):       *
*      ex: Ordem 3 (Codigo de Cesar)-ENTRADA            *
*                  (FrgljrcghcFhvdu)-SA�DA              *
*                                                       *
*   3- (Nome arquivo e a ordem; ele descriptografa)     *
*      ex: O mesmo anterior, ele retorna para mensa-    *
*          gem original.                                *
*                                                       *
*   4- (Nome arquivo, ele o apaga)                      *
*                                                       *
* Obs: O programa desconsidera caracteres especiais e   *
* n�meros, ou seja, tanto na crip ou descrip, ele re-   *
* tornara o proprio n�mero/caractere especial. Os es-   *
* pa�os s�o contatos a partir da posi��o 96 na tabela   *
* ASCII.                                                *
*                                                       *
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define N 100 //Defini��o para string "Nome arquivo"

///Prototipos das fun��es///
void f_titulo(void);//Prototipo da fun��o de titulo para interface
int f_varqe(char *);//Prototipo da fun��o para verificar se arquvio existe
void f_newarq(void);//Prototipo da fun��o para criar nova mensagem em arquivo
int f_lcripDescrip(char *, char *);//Prototipo da fun��o para le dados de entrada do usu�rio para crip ou descriptografia
void f_crip(void);//Prototipo da fun��o criptografar
void f_descrip(void);//Prototipo da fun��o descriptografar
void f_remove(void);//Prototipo da fun��o remover arquivo


/*************************** INICIO DO MAIN *********************************/

int main(){
    int op=0;//Opera��o para op��o de entrada do usu�rio no menu

    do{//La�o do While para repetir menu simultaneamente at� a entrada ser 5 "sair".
        system("CLS");//Limpa tela apos realizar cada escolha do usu�rio
        fflush(stdin);//Limpa fluxo do teclado para evitar entradas indesejadas
        f_titulo();//Fun��o titulo de interface do programa

/*Menu de escolha do usu�rio*/
        printf("\n*****************************************\n");
        printf("(1) Criar nova mensagem no arquivo:\n");
        printf("(2) Criptografar mensagem do arquivo:\n");
        printf("(3) Descriptografar mensagem do arquivo:\n");
        printf("(4) Remover arquivo\n");
        printf("(5) Fechar programa");
        printf("\n*****************************************\n\n");
        printf("Entre com sua escolha: ");
        scanf("%d", &op);//Atribui a opera��o de escolha do usu�rio

/*La�o das opera��es escolhidas pelo usu�rio*/
        switch (op){
            case 1:
                system("CLS");
                f_titulo();
                f_newarq();//Chamada fun��o criar novo arquivo
                break;
            case 2:
                system("CLS");
                f_titulo();
                f_crip();//Chamada a fun��o criptografia
                break;
            case 3:
                system("CLS");
                f_titulo();
                f_descrip();//Chamada a fun��o descriptografia
                break;
            case 4:
                system("CLS");
                f_titulo();
                f_remove();//Chamada a fun��o remover arquivo
                break;
            case 5:
                system("CLS");
                f_titulo();
                printf("\n\t\tFechando programa\n\n");
                break;
            default:
                system("CLS");
                f_titulo();
                printf("\n\t\tEntrada invalida\n\n");
                system("pause");//Pausa para o usu�rio ver mensagem
                break;
        }
    }while(op!=5);
/*Fim do la�o de escolha e finalizando programa*/


system("pause");
return 0;
}

/****************************** FIM DO MAIN *********************************/


///**Fun��es utilizadas durante o programa**///

///*Fun��o titulo para interface do programa...
void f_titulo(void){

        printf("\n\t*****************************************\n");
        printf("\t*   Criptografia de Cesar    Ver.:1.0   *");
        printf("\n\t*****************************************\n");

}///...Fim da fun��o*

///*Fun��o verifica se arquivo existe, caso afirmativo pergunta se quer substituir, retorna 0 para parada e 1 para continuar...
int f_varqe(char *vArq){

    int cond;//opera��o para substituir
    FILE *flx;//Fluxo para testar se o arquivo para grava��o existe

/*Teste= Abre arquivo como leitura para verificar se existe...
Caso afirmativo solicita inteiro 1 substituir 2 Abortar e qualquer
outra entrada = invalida. La�o retorna 1 para seguir com a opera��o
e retorna 0 para abortar opera��o e retornar menu, onde a fun��o foi
chamada*/

    if((flx=fopen(vArq,"r"))!=NULL){//Verificar se o arquivo existe
        fclose(flx);//Fecha o fluxo que est� aberto
        printf("\nArquivo existente, deseja substituir [1=Sim 2=Nao]:\n");
        scanf("%d", &cond);
        switch (cond){//Verifica a condi��o do usu�rio
        case 1:
            return 1;//Retorno 1 para seguir com opera��o
        case 2:
            return 0;//Retorna 0 para ignorar passos e retornar menu
        default:
            system("CLS");
            f_titulo();
            printf("\n\t\tOpcao invalida\n\n");
            system("PAUSE");
            return 0;}//Retorna 0 para ignorar passos e retornar menu
    }
    else//Caso abertura para leitura retorne NULL, arquivo n�o existe
        return 1;//Se n�o existir o arquivo, retorna 1 para seguir

/*Final do Teste*/

}///...Fim da fun��o*

///*Fun��o para criar nova mensagem em arquivo...
void f_newarq(void){

    FILE *nArq;//Fluxo para gravar mensagem no arquivo
    char nNAe[N], *mensagem, txt[]=".txt";//Nome arquivo, mensagem a ser gravada e vetor .txt para cocatenar
    int t, cond2;//Tamanho t para aloca��o dinamica da mensagem, cond chama fun��o varqe(ver se arquivo existe)

    printf("\nDigite o tamanho da mensagem:\n");
    scanf("%d", &t);
    mensagem=malloc(t*sizeof(char));//Aloca��o dinamica para mensagem t vezes
    if(mensagem==NULL){
        printf("\n\t\tERRO AO ALOCAR MEMORIA\n\n");
        system("pause");
        exit(1);}//Fecha o programa

    fflush(stdin);//Limpa fluxo teclado para evitar entradas indesejadas
    printf("\nDigite o nome do arquivo que deseja criar:\n");
    gets(nNAe);
    strcat(nNAe, txt);//Cocatena o nome do arquivo nNAe com .txt

/*Chama fun��o de verifica��o se arquivo de grava��o existe e retorna
condi��o para continua��o ou n�o. (1=Continuar 0=abortar)*/

    if((cond2=f_varqe(nNAe))==1){//Se cond2==1 continua com a grava��o da mensagem

    if((nArq=fopen(nNAe,"w"))==NULL){//Cria o arquivo para escrita
        printf("\n\t\tErro ao criar arquivo\n\n");
        exit(1);}//Fecha o programa

/*Inicio da grava��o no arquivo. For=limpa tela, descarrega fluxo teclado
para evitar dados indesejados, descarrega fluxo arquivo para que o usu�rio
n�o perca dados caso ocorra interrup��o indesejada e encerra com CTRL_Z*/

    for(system("CLS"), f_titulo(),fflush(stdin) ;!feof(stdin) ;fflush(nArq)){
        printf("\nDigite a mensagem para gravar no arquivo (Pressione simultaneamente CTRL_Z e clique em ENTER para encerrar):\n");
        gets(mensagem);
        if(feof(stdin))//If utilizado para evitar duplica��o da ultima mensagem no arquivo
            break;
        else{
            fputs(mensagem, nArq);//Grava string no arquivo
            fputs("\n", nArq);}//Pula linha no arquivo
    }

/*Fim do la�o for*/

    fclose(nArq);//Fecha o fluxo
    }
/*Fechando arquivo e la�o If*/

    free(mensagem);//Liberando memoria de aloca��o dinamica

}///...Fim da fun��o*

///*Fun��o para le dados para crip ou descriptografia...
int f_lcripDescrip(char *arq1, char *arq2){

/*Essa fun��o eh chamada dentro da fun��o crip e descrip para valida��o dos
dados de entrada do usu�rio e retorna para as fun��es crip e descrip a ordem,
se estiver ok e 0, se ocorreu entradas invalida ou incorretas. A entrada dessa
fun��o s�o dois char (Nome dos arquivos), que ser�o passados por refer�ncia
pelas fun��es crip e descrip*/

    FILE *tAbert;//Testa abertura para leitura
    char txt[]=".txt";//Cocatena .txt nas strings arq1 e arq2(Nome dos arquivos)
    int o, cond3;//o = ordem para retorno e cond3 para teste de existencia de arquivo

    printf("\nDigite a ordem k (Inteiro positivo): \n");
    scanf("%d", &o);
        if(o<1 || o>25){//Teste se a Ordem de entrada eh v�lida
            printf("\n\t\tOrdem invalida\n\n");
            system("pause");
            return 0;}//Retorna 0 para ignorar passos e retornar menu

    fflush(stdin);//Limpa fluxo para evitar dados indesejados
    printf("\nDigite nome do arquivo de leitura: \n");
    gets(arq1);
    strcat(arq1,txt);//Cocatena a string arq1 com .txt

    if((tAbert=fopen(arq1,"r"))==NULL){//Testa abertura para verificar se arquivo leitura existe
        system("CLS");
        f_titulo();
        printf("\n\t\tErro ao abrir arquivo %s, ou nao existe\n\n", arq1);
        system("pause");//Mostra dados na tela
        return 0;}//Retorna 0 para abortar opera��o
    fclose(tAbert);//Fecha o arquivo caso retorno n�o seja NULL, ou seja, n�o entra no If

    printf("\nDigite nome do arquivo a criar: \n");
    gets(arq2);
    strcat(arq2,txt);//Cocatena a string arq2 com .txt

    if((cond3=f_varqe(arq2))==0)//Chama fun��o de verifica��o se arquivo de grava��o existe
        return 0;//Retorna 0 para ignorar passos e retornar menu

    return o;//retorna a ORDEM, caso todas entradas sejam validadas

}///...Fim da fun��o*

///*Fun��o para criptografar arquivo...
void f_crip(void){

    FILE *lArqc, *gArqc;//Fluxos para arq leitura e arq escrita
    char cl, nAl[N], nAe[N];//cl= leitura de caractere para criptografar e nomes arquivos
    int k;//k = Ordem

/*chama a fun��o para nome arquivo e retorna a ordem*/

    if((k=f_lcripDescrip(&nAl,&nAe))!=0){//Pasagem por refer�ncia para atribuir os nomes aos arquivos, se o retorno for !=0 indica que foi validado e realiza as opera��es

//Teste de ERRO de leitura e escrita

    if((lArqc=fopen(nAl,"r"))==NULL){
    printf("\n\t\tErro ao ler arquivo %s\n\n", nAl);
    system("pause");
    exit(1);//Fecha o programa
    }
    if((gArqc=fopen(nAe,"w"))==NULL){
    printf("\n\t\tErro ao criar arquivo %s\n\n", nAe);
    system("pause");
    exit(1);//Fecha o programa
    }

/*Inicio do la�o for (Verifica se os caracteres est�o entre A~Z e a~z
na tabela ASCII e os converte), Inicio: ler char cl, enquanto n�o chega
ao final do arquivo: cifra, grava no arquivo escrita, grava na tela e
captura o prox caractere do arquivo leitura*/

    system("CLS");//Limpa tela para exibir somente a mensagem salva
    f_titulo();//Coloca a fun��o de interface
    printf("\n\nOs dados cifrados e salvos no arquivo sao:\n\n");

    for(cl=fgetc(lArqc) ;!feof(lArqc) ;fputc(cl, gArqc),fputc(cl, stdout),cl=fgetc(lArqc)){
        if(cl==' ')//' ' contado a partir da posi��o 96
            cl=96+k;
        else{ if(cl=='z')//Se o char for 'z' conta na tabela 'A'
                 cl=64+k;
              else{ if(ispunct(cl) || isdigit(cl) || iscntrl(cl))//Identifica se eh caracter especial, digito ou CTRL, ENTER, SHIFT, ETC.
                        cl=cl;
                    else{ if((islower(cl) && islower(cl+k)) || (isupper(cl) && isupper(cl+k)))//Verifica se o char e o char + a ordem retornam elementos do mesmo alfabeto (M e m)
                              cl=cl+k;
                          else{ if(isalpha(cl))//Caso nenhuma das op��es se enquadrem ent�o se eh um char ele ultrapassa a posi��o dos alfabetos (M e m), ex: 'Z'
                                   cl=(cl+k)-26;}}}}//Subtrai -26 para retornar novamente ao alfabeto minusculo/maiusculo
   }
   printf("\n\n");//Dois enter para facilitar leitura do usu�rio
   system("pause");//Pause para mostrar dados em tela

/*fim do la�o for.*/

//Fechando arquivos
    fclose(lArqc);
    fclose(gArqc);
    }

/*Fim do la�o IF(La�o de conmfirma��o de validade dos dados de entrada do usu�rio)*/

}///...Fim da fun��o*

///*Fun��o para descriptografar arquivo...
void f_descrip(void){

    FILE *lArqd, *gArqd;//Fluxos para arq leitura e arq escrita
    char cl, nAl[N], nAe[N];//cl= leitura de caractere para criptografar e nomes arquivos
    int k;//k = Ordem

/*chama a fun��o para nome arquivo e retorna a ordem*/

    if((k=f_lcripDescrip(&nAl,&nAe))!=0){//Pasagem por refer�ncia para atribuir os nomes aos arquivos, se o retorno for !=0 indica que foi validado e realiza as opera��es

//Teste de ERRO de leitura e escrita

    if((lArqd=fopen(nAl,"r"))==NULL){
    printf("\n\t\tErro ao ler arquivo %s\n\n", nAl);
    system("pause");
    exit(1);//Fecha o programa
    }
    if((gArqd=fopen(nAe,"w"))==NULL){
    printf("\n\t\tErro ao criar arquivo %s\n\n", nAe);
    exit(1);//Fecha o programa
    }

/*Inicio do la�o for (Verifica se os caracteres est�o entre A~Z e a~z
na tabela ASCII e os converte), Inicio: pega char cl, enquanto n�o chega
ao final do arquivo: decifra, grava no arquivo escrita, grava na tela e
captura o prox caractere do arquivo leitura*/

    system("CLS");//Limpa tela para exibir somente a mensagem salva
    f_titulo();//Coloca a fun��o interface
    printf("\n\nOs dados decifrados e salvos no arquivo sao:\n\n");

    for(cl=fgetc(lArqd) ;!feof(lArqd) ;fputc(cl, gArqd),fputc(cl, stdout),cl=fgetc(lArqd)){
        if((cl-k)==96)//Verifica se ao decifrar o char retorna antes do alfabeto minusculo que seria o ' '
            cl=' ';
        else{ if((islower(cl) && islower(cl-k)) || (isupper(cl) && isupper(cl-k)))//Verifica se o caracter e a subtra��o pela ordem continua no mesmo alfabeto
                 cl=cl-k;
              else{ if(isalpha(cl))//Verifica se inicialmete o caracter era alfa
                        cl=(cl-k)+26;//Qnd decifra retorna caracter especial, ent�o soma +26 para retornar ao alfabeto M/m
                    else//Caso n�o seja nenhuma das op��es anteriores, ent�o eh um caracter especial ou numero
                        cl=cl;}}
    }
    printf("\n\n");//Dois enter para facilitar leitura do usu�rio
    system("pause");//Pause para mostrar dados em tela

 /*fim do la�o for.*/

//Fechando arquivos
    fclose(lArqd);
    fclose(gArqd);
    }

/*Fim do la�o IF(La�o de conmfirma��o de validade dos dados de entrada do usu�rio)*/

}///...Fim da fun��o*

///*Fun��o para remover arquivo existente...
void f_remove(void){

    FILE *rArq;//Fluxo para verificar se arquivo existe
    char rAq[N], txt[]=".txt";//Nome do arquivo e vetor para cocatenar
    int  r;//r = op��o de remo��o

    fflush(stdin);//Libera fluxo do teclado evitando entradas indesejadas
    printf("\nDigite o nome do arquivo:\n");
    gets(rAq);
    strcat(rAq,txt);//Cocatena nome arquivo com .txt

/*La�o para verificar se arquivo existe e remove-lo*/

    if((rArq=fopen(rAq,"r"))!=NULL){//Testa se arquivo existe
        fclose(rArq);//Se o arquivo existe, ent�o fecha o fluxo
        printf("\nDeseja realmente remover o arquivo %s? [1=SIM 2=NAO]\n", rAq);
        scanf("%d", &r);
        if(r==1){
            if(remove(rAq)){//Se ocorrer um erro na remo��o, informa ao usu�rio
                printf("\n\t\tErro ao remover arquivo\n\n");
                system("pause");}}}
    else{//Se a abertura retornar NULL, ent�o arquivo n�o existe
        printf("\n\t\tArquivo %s nao existe\n\n", rAq);
        system("pause");}

/*Fim do la�o*/

}///...Fim da fun��o*
