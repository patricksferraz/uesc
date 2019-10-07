/********************************************************
*                                                       *
* Título: Criptografia de Cesar                         *
*********************************************************
* Autor: Patrick Silva Ferraz [201420380]               *
*********************************************************
* Data criação: 14/09/2015                              *
* Última modificação: 22/09/2015                        *
*********************************************************
* Descrição: Programa realiza o problema 4 do projeto   *
* 2015.1 (Código de Cesar). O usuário tem 5 opções:     *
*                                                       *
* 1-criar nova mensagem para salvar no arquivo          *
* 2-criptrografar uma mensagem no arquivo existente,    *
* 3-descriptografar uma mensagem no arquivo existente.  *
* 4-remover arquivo                                     *
* 5-Sair                                                *
*********************************************************
* ENTRADAS/SAÍDA das funções realizadas pelo programa:  *
*                                                       *
*   1- (Nome arquivo, tamanho mensagem, e a mensagem)   *
*      ex: (Codigo de Cesar)-ENTRADA                    *
*           Retorna um arquivo com essa mensagem        *
*                                                       *
*   2- (Nome arquivo e a ordem; ele criptografa):       *
*      ex: Ordem 3 (Codigo de Cesar)-ENTRADA            *
*                  (FrgljrcghcFhvdu)-SAÍDA              *
*                                                       *
*   3- (Nome arquivo e a ordem; ele descriptografa)     *
*      ex: O mesmo anterior, ele retorna para mensa-    *
*          gem original.                                *
*                                                       *
*   4- (Nome arquivo, ele o apaga)                      *
*                                                       *
* Obs: O programa desconsidera caracteres especiais e   *
* números, ou seja, tanto na crip ou descrip, ele re-   *
* tornara o proprio número/caractere especial. Os es-   *
* paços são contatos a partir da posição 96 na tabela   *
* ASCII.                                                *
*                                                       *
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define N 100 //Definição para string "Nome arquivo"

///Prototipos das funções///
void f_titulo(void);//Prototipo da função de titulo para interface
int f_varqe(char *);//Prototipo da função para verificar se arquvio existe
void f_newarq(void);//Prototipo da função para criar nova mensagem em arquivo
int f_lcripDescrip(char *, char *);//Prototipo da função para le dados de entrada do usuário para crip ou descriptografia
void f_crip(void);//Prototipo da função criptografar
void f_descrip(void);//Prototipo da função descriptografar
void f_remove(void);//Prototipo da função remover arquivo


/*************************** INICIO DO MAIN *********************************/

int main(){
    int op=0;//Operação para opção de entrada do usuário no menu

    do{//Laço do While para repetir menu simultaneamente até a entrada ser 5 "sair".
        system("CLS");//Limpa tela apos realizar cada escolha do usuário
        fflush(stdin);//Limpa fluxo do teclado para evitar entradas indesejadas
        f_titulo();//Função titulo de interface do programa

/*Menu de escolha do usuário*/
        printf("\n*****************************************\n");
        printf("(1) Criar nova mensagem no arquivo:\n");
        printf("(2) Criptografar mensagem do arquivo:\n");
        printf("(3) Descriptografar mensagem do arquivo:\n");
        printf("(4) Remover arquivo\n");
        printf("(5) Fechar programa");
        printf("\n*****************************************\n\n");
        printf("Entre com sua escolha: ");
        scanf("%d", &op);//Atribui a operação de escolha do usuário

/*Laço das operações escolhidas pelo usuário*/
        switch (op){
            case 1:
                system("CLS");
                f_titulo();
                f_newarq();//Chamada função criar novo arquivo
                break;
            case 2:
                system("CLS");
                f_titulo();
                f_crip();//Chamada a função criptografia
                break;
            case 3:
                system("CLS");
                f_titulo();
                f_descrip();//Chamada a função descriptografia
                break;
            case 4:
                system("CLS");
                f_titulo();
                f_remove();//Chamada a função remover arquivo
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
                system("pause");//Pausa para o usuário ver mensagem
                break;
        }
    }while(op!=5);
/*Fim do laço de escolha e finalizando programa*/


system("pause");
return 0;
}

/****************************** FIM DO MAIN *********************************/


///**Funções utilizadas durante o programa**///

///*Função titulo para interface do programa...
void f_titulo(void){

        printf("\n\t*****************************************\n");
        printf("\t*   Criptografia de Cesar    Ver.:1.0   *");
        printf("\n\t*****************************************\n");

}///...Fim da função*

///*Função verifica se arquivo existe, caso afirmativo pergunta se quer substituir, retorna 0 para parada e 1 para continuar...
int f_varqe(char *vArq){

    int cond;//operação para substituir
    FILE *flx;//Fluxo para testar se o arquivo para gravação existe

/*Teste= Abre arquivo como leitura para verificar se existe...
Caso afirmativo solicita inteiro 1 substituir 2 Abortar e qualquer
outra entrada = invalida. Laço retorna 1 para seguir com a operação
e retorna 0 para abortar operação e retornar menu, onde a função foi
chamada*/

    if((flx=fopen(vArq,"r"))!=NULL){//Verificar se o arquivo existe
        fclose(flx);//Fecha o fluxo que está aberto
        printf("\nArquivo existente, deseja substituir [1=Sim 2=Nao]:\n");
        scanf("%d", &cond);
        switch (cond){//Verifica a condição do usuário
        case 1:
            return 1;//Retorno 1 para seguir com operação
        case 2:
            return 0;//Retorna 0 para ignorar passos e retornar menu
        default:
            system("CLS");
            f_titulo();
            printf("\n\t\tOpcao invalida\n\n");
            system("PAUSE");
            return 0;}//Retorna 0 para ignorar passos e retornar menu
    }
    else//Caso abertura para leitura retorne NULL, arquivo não existe
        return 1;//Se não existir o arquivo, retorna 1 para seguir

/*Final do Teste*/

}///...Fim da função*

///*Função para criar nova mensagem em arquivo...
void f_newarq(void){

    FILE *nArq;//Fluxo para gravar mensagem no arquivo
    char nNAe[N], *mensagem, txt[]=".txt";//Nome arquivo, mensagem a ser gravada e vetor .txt para cocatenar
    int t, cond2;//Tamanho t para alocação dinamica da mensagem, cond chama função varqe(ver se arquivo existe)

    printf("\nDigite o tamanho da mensagem:\n");
    scanf("%d", &t);
    mensagem=malloc(t*sizeof(char));//Alocação dinamica para mensagem t vezes
    if(mensagem==NULL){
        printf("\n\t\tERRO AO ALOCAR MEMORIA\n\n");
        system("pause");
        exit(1);}//Fecha o programa

    fflush(stdin);//Limpa fluxo teclado para evitar entradas indesejadas
    printf("\nDigite o nome do arquivo que deseja criar:\n");
    gets(nNAe);
    strcat(nNAe, txt);//Cocatena o nome do arquivo nNAe com .txt

/*Chama função de verificação se arquivo de gravação existe e retorna
condição para continuação ou não. (1=Continuar 0=abortar)*/

    if((cond2=f_varqe(nNAe))==1){//Se cond2==1 continua com a gravação da mensagem

    if((nArq=fopen(nNAe,"w"))==NULL){//Cria o arquivo para escrita
        printf("\n\t\tErro ao criar arquivo\n\n");
        exit(1);}//Fecha o programa

/*Inicio da gravação no arquivo. For=limpa tela, descarrega fluxo teclado
para evitar dados indesejados, descarrega fluxo arquivo para que o usuário
não perca dados caso ocorra interrupção indesejada e encerra com CTRL_Z*/

    for(system("CLS"), f_titulo(),fflush(stdin) ;!feof(stdin) ;fflush(nArq)){
        printf("\nDigite a mensagem para gravar no arquivo (Pressione simultaneamente CTRL_Z e clique em ENTER para encerrar):\n");
        gets(mensagem);
        if(feof(stdin))//If utilizado para evitar duplicação da ultima mensagem no arquivo
            break;
        else{
            fputs(mensagem, nArq);//Grava string no arquivo
            fputs("\n", nArq);}//Pula linha no arquivo
    }

/*Fim do laço for*/

    fclose(nArq);//Fecha o fluxo
    }
/*Fechando arquivo e laço If*/

    free(mensagem);//Liberando memoria de alocação dinamica

}///...Fim da função*

///*Função para le dados para crip ou descriptografia...
int f_lcripDescrip(char *arq1, char *arq2){

/*Essa função eh chamada dentro da função crip e descrip para validação dos
dados de entrada do usuário e retorna para as funções crip e descrip a ordem,
se estiver ok e 0, se ocorreu entradas invalida ou incorretas. A entrada dessa
função são dois char (Nome dos arquivos), que serão passados por referência
pelas funções crip e descrip*/

    FILE *tAbert;//Testa abertura para leitura
    char txt[]=".txt";//Cocatena .txt nas strings arq1 e arq2(Nome dos arquivos)
    int o, cond3;//o = ordem para retorno e cond3 para teste de existencia de arquivo

    printf("\nDigite a ordem k (Inteiro positivo): \n");
    scanf("%d", &o);
        if(o<1 || o>25){//Teste se a Ordem de entrada eh válida
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
        return 0;}//Retorna 0 para abortar operação
    fclose(tAbert);//Fecha o arquivo caso retorno não seja NULL, ou seja, não entra no If

    printf("\nDigite nome do arquivo a criar: \n");
    gets(arq2);
    strcat(arq2,txt);//Cocatena a string arq2 com .txt

    if((cond3=f_varqe(arq2))==0)//Chama função de verificação se arquivo de gravação existe
        return 0;//Retorna 0 para ignorar passos e retornar menu

    return o;//retorna a ORDEM, caso todas entradas sejam validadas

}///...Fim da função*

///*Função para criptografar arquivo...
void f_crip(void){

    FILE *lArqc, *gArqc;//Fluxos para arq leitura e arq escrita
    char cl, nAl[N], nAe[N];//cl= leitura de caractere para criptografar e nomes arquivos
    int k;//k = Ordem

/*chama a função para nome arquivo e retorna a ordem*/

    if((k=f_lcripDescrip(&nAl,&nAe))!=0){//Pasagem por referência para atribuir os nomes aos arquivos, se o retorno for !=0 indica que foi validado e realiza as operações

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

/*Inicio do laço for (Verifica se os caracteres estão entre A~Z e a~z
na tabela ASCII e os converte), Inicio: ler char cl, enquanto não chega
ao final do arquivo: cifra, grava no arquivo escrita, grava na tela e
captura o prox caractere do arquivo leitura*/

    system("CLS");//Limpa tela para exibir somente a mensagem salva
    f_titulo();//Coloca a função de interface
    printf("\n\nOs dados cifrados e salvos no arquivo sao:\n\n");

    for(cl=fgetc(lArqc) ;!feof(lArqc) ;fputc(cl, gArqc),fputc(cl, stdout),cl=fgetc(lArqc)){
        if(cl==' ')//' ' contado a partir da posição 96
            cl=96+k;
        else{ if(cl=='z')//Se o char for 'z' conta na tabela 'A'
                 cl=64+k;
              else{ if(ispunct(cl) || isdigit(cl) || iscntrl(cl))//Identifica se eh caracter especial, digito ou CTRL, ENTER, SHIFT, ETC.
                        cl=cl;
                    else{ if((islower(cl) && islower(cl+k)) || (isupper(cl) && isupper(cl+k)))//Verifica se o char e o char + a ordem retornam elementos do mesmo alfabeto (M e m)
                              cl=cl+k;
                          else{ if(isalpha(cl))//Caso nenhuma das opções se enquadrem então se eh um char ele ultrapassa a posição dos alfabetos (M e m), ex: 'Z'
                                   cl=(cl+k)-26;}}}}//Subtrai -26 para retornar novamente ao alfabeto minusculo/maiusculo
   }
   printf("\n\n");//Dois enter para facilitar leitura do usuário
   system("pause");//Pause para mostrar dados em tela

/*fim do laço for.*/

//Fechando arquivos
    fclose(lArqc);
    fclose(gArqc);
    }

/*Fim do laço IF(Laço de conmfirmação de validade dos dados de entrada do usuário)*/

}///...Fim da função*

///*Função para descriptografar arquivo...
void f_descrip(void){

    FILE *lArqd, *gArqd;//Fluxos para arq leitura e arq escrita
    char cl, nAl[N], nAe[N];//cl= leitura de caractere para criptografar e nomes arquivos
    int k;//k = Ordem

/*chama a função para nome arquivo e retorna a ordem*/

    if((k=f_lcripDescrip(&nAl,&nAe))!=0){//Pasagem por referência para atribuir os nomes aos arquivos, se o retorno for !=0 indica que foi validado e realiza as operações

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

/*Inicio do laço for (Verifica se os caracteres estão entre A~Z e a~z
na tabela ASCII e os converte), Inicio: pega char cl, enquanto não chega
ao final do arquivo: decifra, grava no arquivo escrita, grava na tela e
captura o prox caractere do arquivo leitura*/

    system("CLS");//Limpa tela para exibir somente a mensagem salva
    f_titulo();//Coloca a função interface
    printf("\n\nOs dados decifrados e salvos no arquivo sao:\n\n");

    for(cl=fgetc(lArqd) ;!feof(lArqd) ;fputc(cl, gArqd),fputc(cl, stdout),cl=fgetc(lArqd)){
        if((cl-k)==96)//Verifica se ao decifrar o char retorna antes do alfabeto minusculo que seria o ' '
            cl=' ';
        else{ if((islower(cl) && islower(cl-k)) || (isupper(cl) && isupper(cl-k)))//Verifica se o caracter e a subtração pela ordem continua no mesmo alfabeto
                 cl=cl-k;
              else{ if(isalpha(cl))//Verifica se inicialmete o caracter era alfa
                        cl=(cl-k)+26;//Qnd decifra retorna caracter especial, então soma +26 para retornar ao alfabeto M/m
                    else//Caso não seja nenhuma das opções anteriores, então eh um caracter especial ou numero
                        cl=cl;}}
    }
    printf("\n\n");//Dois enter para facilitar leitura do usuário
    system("pause");//Pause para mostrar dados em tela

 /*fim do laço for.*/

//Fechando arquivos
    fclose(lArqd);
    fclose(gArqd);
    }

/*Fim do laço IF(Laço de conmfirmação de validade dos dados de entrada do usuário)*/

}///...Fim da função*

///*Função para remover arquivo existente...
void f_remove(void){

    FILE *rArq;//Fluxo para verificar se arquivo existe
    char rAq[N], txt[]=".txt";//Nome do arquivo e vetor para cocatenar
    int  r;//r = opção de remoção

    fflush(stdin);//Libera fluxo do teclado evitando entradas indesejadas
    printf("\nDigite o nome do arquivo:\n");
    gets(rAq);
    strcat(rAq,txt);//Cocatena nome arquivo com .txt

/*Laço para verificar se arquivo existe e remove-lo*/

    if((rArq=fopen(rAq,"r"))!=NULL){//Testa se arquivo existe
        fclose(rArq);//Se o arquivo existe, então fecha o fluxo
        printf("\nDeseja realmente remover o arquivo %s? [1=SIM 2=NAO]\n", rAq);
        scanf("%d", &r);
        if(r==1){
            if(remove(rAq)){//Se ocorrer um erro na remoção, informa ao usuário
                printf("\n\t\tErro ao remover arquivo\n\n");
                system("pause");}}}
    else{//Se a abertura retornar NULL, então arquivo não existe
        printf("\n\t\tArquivo %s nao existe\n\n", rAq);
        system("pause");}

/*Fim do laço*/

}///...Fim da função*
