/**
 * @author Patrick Silva Ferraz <patrick.ferraz@outlook.com>
 * Matricula 201420380
 * Universidade Estadual de Santa Cruz - Computação Gráfica
 * Atividade Prática 3
 **/

/**
 * INCLUDES
 */
#ifdef __GAMEPONG__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * MACROS
 */

// @var OVER_TOP_Y é o overflow do topo da tela
// @var RX e RY são as coordenadas máximas no eixo x e y p.ex X (-400, 400)
// @var SPEED_JOGADOR é a velocidade de deslocamento do jogador
// @var SPEED_BOLA é a velocidade de deslocamento da bola
// @var TAM_SCORE é o tamanho da string SCORE, ou seja, 2 caracteres + \0
#define OVER_TOP_Y 50
#define RX 400
#define RY 300
#define TAM_JOGADOR 60
#define SPEED_JOGADOR 20
#define SPEED_BOLA 4
#define TAM_SCORE 3
#define MAX_SCORE 10

// CORES
#define COLOR_GREEN glColor3f (0.0, 1.0, 0.0);
#define COLOR_BLACK glColor3f (0.0, 0.0, 0.0);
#define COLOR_RED glColor3f   (1.0, 0.0, 0.0);

/**
 * PROTÓTIPOS DAS FUNÇÕES
 */
void Inicializa 	      (void);
void desenhaMesa 	      (void);
void desenhaBola 	      (void);
void atualizaPosBola      (void);
void ajusteAnguloJogador1 (void);
void ajusteAnguloJogador2 (void);
void desenhaJogador       (void);
void desenho 		      (void);
void desenhaApresentacao  (void);
void desenhaMenu 	      (void);
void desenhaReinicio      (void);
void desenhaCreditos      (void);
void pontoJogador	      (int jogador);
void desenhaTexto         (const char *string, int x, int y);
void tecladoJogador1      (unsigned char tecla, int x, int y);
void tecladoJogador2      (GLint tecla, int x, int y);

/**
 * VARIÁVEIS GLOBAIS
 */

// Variáveis p/ margem da tela
GLfloat marginLeft  = -RX + 5.0;
GLfloat marginTop   =  RY - 5.0;
GLfloat marginRight =  RX - 5.0;
GLfloat marginDown  = -RY + 5.0;

// Variáveis globais para posição dos jogadores em X
GLfloat posXJogador1 = -RX + 30.0;
GLfloat posXJogador2 =  RX - 30.0;
GLfloat posXBola     =  posXJogador1 + 5;

// Variáveis globais para posição dos jogadores e score em Y
GLfloat posYScore    =  RY - 25.0;
GLfloat posYJogador1 = -30.0;
GLfloat posYJogador2 = -30.0;
GLfloat posYBola     = posYJogador1 + 25;

// Variáveis globais para velocidade da bola
GLfloat speedBolaX = SPEED_BOLA;
GLfloat speedBolaY = SPEED_BOLA;

// Variáveis globais de fragmentação do jogador para ajuste angular da bola
GLfloat baseBloco2 = TAM_JOGADOR * 0.2;
GLfloat baseBloco3 = TAM_JOGADOR * 0.4;
GLfloat baseBloco4 = TAM_JOGADOR * 0.6;
GLfloat baseBloco5 = TAM_JOGADOR * 0.8;

// Variáveis globais para score
GLint scoreJogador1 = 0;
GLint scoreJogador2 = 0;

// Variáveis para propriedades do jogo
int estadoJogo = 0;      // 0 = inicial; 1 = jogo; 2 = concluido; 3 = encerramento
int bolaMovimento = 0;   // 0 = bola parada; 1 = bola em movimento
int jogadorVencedor = 0; // Indicador do jogador vencedor// p.ex 1 = jogador 1 ..
int primeiraJogada = 1;
char score[TAM_SCORE];   // Variável para pontuação de cada jogador com até 2 dígitos
char dirBolaX = 'D';     // D = direita; E = esquerda
char dirBolaY;           // C = cima; B = baixo

/**
 * FUNÇÃO PRINCIPAL
 */
int main (int argc, char** argv)
{
	// Inicializa a GLUT
    glutInit(&argc, argv); //para sistemas X-Windows

	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// Especifica a posição inicial da janela GLUT
	//glutInitWindowPosition(200,150); //Por default (0,0)

	// Especifica o tamanho inicial em pixels da janela GLUT
	//glutInitWindowSize(800,800);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Patrick Ferraz - Atividade Pratica III");

	// Registra a função de redesenho da janela de visualização
	glutDisplayFunc(desenho);

	// Registra a função para tratamento das teclas ASCII
	glutKeyboardFunc(tecladoJogador1);

	// Registra a função para tratamento das teclas NÂO ASCII
	glutSpecialFunc(tecladoJogador2);

	// Amplia para FullScreen
	glutFullScreen();

	// Chama a função responsável por fazer as inicializações
 	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop(); // O controle do programa passa a GLUT

	return 0;

} // end-main (int argc, char** argv)

/**
 * DECLARAÇÕES DAS FUNÇÕES
 */

/**
 * Função responsável por inicializar parâmetros e variáveis
 * @param void
 * @return void
 */
void Inicializa (void)
{
	// Define a janela de visualização 2D
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-RX, RX, -RY, RY);//Exibição Bidimensional
} // end-Inicializa (void)

/**
 * Função responsável por desenhar a mesa PRETA c/ rede VERDE
 * @param void
 * @return void
 */
void desenhaMesa (void)
{
    // Defini a cor PRETA e desenha a mesa com margens
    COLOR_BLACK;
    glBegin(GL_QUADS);
        glVertex2f(marginLeft,  marginDown);
        glVertex2f(marginRight, marginDown);
        glVertex2f(marginRight, marginTop);
        glVertex2f(marginLeft,  marginTop);
    glEnd();

    // Defini a cor VERDE e desenha a rede no meio da mesa
    COLOR_GREEN;
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0, marginDown);
        glVertex2f(0, marginTop);
    glEnd();
} // end-desenhaMesa (void)

/**
 * Função responsável por definir dimensão da bola
 * @param void
 * @return void
 */
void desenhaBola (void)
{
    glLineWidth(15.0); // Largura da linha
    glBegin(GL_LINE_LOOP);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 10.0);
    glEnd();

} // end-desenhaBola (void)

/**
 * Função responsável por atualizar posição da bola
 * @param void
 * @return void
 */
void atualizaPosBola (void)
{

    if (primeiraJogada)
    {
    	// Sorteia direção da bola. Número par = Cima
        if (rand() % 2 == 0) dirBolaY = 'C';
        else          		 dirBolaY = 'B';
        // Verifica direção da bola de acordo com pos no campo
        if (posXBola < 0) dirBolaX = 'D';
        else			  dirBolaX = 'E';

        primeiraJogada = 0;
    }
    if ((estadoJogo == 1) && bolaMovimento)
    {
    	// Movimentação da bola para direito até encontrar o jogador ou marcar ponto
        if (dirBolaX == 'D')
        {
            if      ((posXBola + speedBolaX) <= posXJogador2) posXBola += speedBolaX;
            else if (posYBola  < posYJogador2 - 9 || posYBola  > posYJogador2 + 69) pontoJogador(1);
            else
            {
        		dirBolaX = 'E';
            	ajusteAnguloJogador2();
            }
        }
        // Movimentação da bola para esquerda até encontrar o jogador ou marcar ponto
        else if (dirBolaX == 'E')
        {
            if      ((posXBola - speedBolaX) >= posXJogador1) posXBola -= speedBolaX;
            else if (posYBola  < posYJogador1 - 9 || posYBola  > posYJogador1 + 69) pontoJogador(2);
            else
            {
        		dirBolaX = 'D';
            	ajusteAnguloJogador1();
            }
        }

        // Reflexão da bola nas paredes inferior e superiores do campo
        if      (dirBolaY == 'B' && (posYBola - speedBolaY) >= marginDown) posYBola -= speedBolaY;
        else if (dirBolaY == 'B') dirBolaY = 'C';
        if      (dirBolaY == 'C' && (posYBola + speedBolaY) <= (marginTop - 10)) posYBola += speedBolaY;
        else if (dirBolaY == 'C') dirBolaY = 'B';
    }
    else
    {
    	// Bola acompanha o jogador enquanto jogo não inicia
        if   (posXBola < 0.0) posYBola = posYJogador1 + 25;
        else posYBola = posYJogador2 + 25;
    }

    glutPostRedisplay();

} // end-atualizaPosBola (void)

/**
 * Função responsável por ajustar o angulo que a bola irá percorrer
 * após colidir com jogador 2
 * @param void
 * return void
 */

/**
 * Função responsável por ajustar o angulo que a bola irá percorrer
 * após colidir com jogador 1
 * @param void
 * return void
 */
void ajusteAnguloJogador1 (void)
{
	// Verificação do angulo de reflexão da bola
    if (((posYBola >= posYJogador1 - 9) && (posYBola < posYJogador1 + baseBloco2)) ||
    	((posYBola >= posYJogador1 + baseBloco5) && (posYBola <= posYJogador1 + 69)))
    	speedBolaY = speedBolaX * 1.73205080757;	// Correção do angulo p/ 30 graus (x*sqrt(3))

	else if (((posYBola >= posYJogador1 + baseBloco2) && (posYBola < posYJogador1 + baseBloco3)) ||
    	((posYBola >= posYJogador1 + baseBloco4) && (posYBola < posYJogador1 + baseBloco5)))
		speedBolaY = speedBolaX * 0.57735026919;	// Correção do angulo p/ 60 graus (x*1/sqrt(3))

	else if ((posYBola >= posYJogador1 + baseBloco3) && (posYBola < posYJogador1 + baseBloco4))
		speedBolaY = 0;								// Correção do angulo p/ 90 graus

} // end-ajusteAnguloJogador1 (void)

void ajusteAnguloJogador2 (void)
{
	// Verificação do angulo de reflexão da bola
    if (((posYBola >= posYJogador2 - 9) && (posYBola < posYJogador2 + baseBloco2)) ||
    	((posYBola >= posYJogador2 + baseBloco5) && (posYBola <= posYJogador2 + 69)))
    	speedBolaY = speedBolaX * 1.73205080757;	// Correção do angulo p/ 30 graus (x*sqrt(3))

	else if (((posYBola >= posYJogador2 + baseBloco2) && (posYBola < posYJogador2 + baseBloco3)) ||
    	((posYBola >= posYJogador2 + baseBloco4) && (posYBola < posYJogador2 + baseBloco5)))
		speedBolaY = speedBolaX * 0.57735026919;	// Correção do angulo p/ 60 graus (x*1/sqrt(3))

	else if ((posYBola >= posYJogador2 + baseBloco3) && (posYBola < posYJogador2 + baseBloco4))
		speedBolaY = 0;								// Correção do angulo p/ 90 graus

} // end-ajusteAnguloJogador2 (void)

/**
 * Função responsável por definir dimensão do jogador
 * @param void
 * return void
 */
void desenhaJogador (void)
{
    glLineWidth(10.0); // Largura da linha
	glBegin(GL_LINE_LOOP);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, TAM_JOGADOR);
    glEnd();

} // end-desenhaJogador (void)

/** 
 * Função desenha todo layout do jogo
 * @param void
 * @return void
 */
void desenho (void)
{
    GLfloat oneFourthMesa; // Variável para definir 1/4 da mesa
    
	glClearColor(0.0, 1.0, 0.0, 0); //Especifica um cor para o fundo
	glClear(GL_COLOR_BUFFER_BIT); //Manda limpar o fundo
	
	desenhaMesa(); // Desenha a mesa inicialmente de forma estática
    
    COLOR_GREEN; // Altera a cor para VERDE
    
    // Desenha a bola na tela
    glPushMatrix();
    	atualizaPosBola();
        glTranslated(posXBola, posYBola, 0.0);
        desenhaBola();
    glPopMatrix();

    // Desenha o jogador 1 no L/E da mesa
    glPushMatrix();
        glTranslated(posXJogador1, posYJogador1, 0.0);
        desenhaJogador();
    glPopMatrix();
    
    // Desenha o jogador 2 no L/D da mesa
    glPushMatrix();
        glTranslated(posXJogador2, posYJogador2, 0.0);
        desenhaJogador();
    glPopMatrix();
    
    oneFourthMesa = RX >> 1; // Op com bit RX >> 1 == RX/2
    
    // Desenha o score do jogador 1 no L/D
    glPushMatrix();
        glTranslated(-oneFourthMesa, posYScore, 0.0);
        snprintf(score, TAM_SCORE, "%d", scoreJogador1);
        desenhaTexto(score, 0, 0);
    glPopMatrix();
    
    // Desenha o score do jogador 2 no L/E
    glPushMatrix();
        glTranslated(oneFourthMesa, posYScore, 0.0);
        snprintf(score, TAM_SCORE, "%d", scoreJogador2);
        desenhaTexto(score, 0, 0);
    glPopMatrix();

    // Desenha menu do jogo quando a partida não foi iniciada
    if      (estadoJogo == 0) desenhaApresentacao();
    else if (estadoJogo == 1 && bolaMovimento == 0) desenhaMenu();
    else if (estadoJogo == 2) desenhaReinicio();
    else if (estadoJogo == 3) desenhaCreditos();
    
    glutSwapBuffers();

} // end-desenho (void)

/**
 * Desenha a apresentação do jogo
 * @param void
 * @return void
 */
void desenhaApresentacao (void)
{
    COLOR_BLACK;
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0, marginDown);
        glVertex2f(0, marginTop);
    glEnd();

    COLOR_RED;
    glPushMatrix();
        glTranslated(-200.0, 100.0, 0.0);
        desenhaTexto("Pong eh um jogo eletronico de esporte em duas dimensoes que simula um tenis de mesa.", 0, 0);
        desenhaTexto("O Jogador 1 controla a paleta (barra vertical) do lado esquerdo com a teclas:", 0, -25);
        desenhaTexto("W (cima) e S (baixo).", 50, -50);
        desenhaTexto("Competindo contra o Jogador 2 que controla a paleta do lado direito com as teclas:", 0, -75);
        desenhaTexto("\"seta para cima\" e \"seta para baixo\" (baixo).", 50, -100);
        desenhaTexto("Os jogadores usam suas paletas para acertar a esfera (bola) e manda-la para o oponente.", 0, -125);
        desenhaTexto("Ganha o jogador que conseguir alcancar 10 pontos primeiro, com a diferenca de 2 pontos.", 0, -150);
        COLOR_GREEN;
        desenhaTexto("Pressione <ESPACO> para iniciar", 0, -200);
        desenhaTexto("Pressione <ESC> para sair", 0, -225);
    glPopMatrix();

} // end-desenhaApresentacao (void)

/**
 * Desenha o menu do jogo na janela
 * @param void
 * @return void
 */
void desenhaMenu (void)
{
    glPushMatrix();
        glTranslated(5.0, 0.0, 0.0);
        desenhaTexto("Pressione <ESPACO> para continuar", 0, 0);
        desenhaTexto("Pressione <ESC> para desistir", 0, -25);
    glPopMatrix();

} // end-desenhaMenu (void)

/**
 * Desenha o menu para reinicio
 * @param void
 * @return void
 */
void desenhaReinicio (void)
{
    COLOR_BLACK;
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0, marginDown);
        glVertex2f(0, marginTop);
    glEnd();

    COLOR_RED;
    glPushMatrix();
        glTranslated(-200.0, 100.0, 0.0);
        desenhaTexto("Obrigado por jogar!", 0, 0);
        desenhaTexto("PLACAR:", 0, -25);
        snprintf(score, TAM_SCORE, "%d", scoreJogador1);
        desenhaTexto(score, 50, -50);
        snprintf(score, TAM_SCORE, "%d", scoreJogador2);
        desenhaTexto(score, 100, -50);
        if (jogadorVencedor == 1)
            desenhaTexto("Jogador 1 foi o vencedor.", 0, -75);
        else if (jogadorVencedor == 2)
            desenhaTexto("Jogador 2 foi o vencedor.", 0, -75);
        COLOR_GREEN;
        desenhaTexto("Pressione <ESPACO> para novo jogor", 0, -125);
        desenhaTexto("Pressione <ESC> para sair", 0, -150);
    glPopMatrix();

} // end-desenhaReinicio (void)

/**
 * Desenha os créditos do jogo
 * @param void
 * @return void
 */
void desenhaCreditos (void)
{
    COLOR_BLACK;
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0, marginDown);
        glVertex2f(0, marginTop);
    glEnd();

    COLOR_RED;
    glPushMatrix();
        glTranslated(-200.0, 100.0, 0.0);
        desenhaTexto("Obrigado por jogar!", 0, 0);
        desenhaTexto("Jogo desenvolvido durante a graduacao em Ciencia da Computacao", 0, -25);
        desenhaTexto("na Universidade Estadual de Santa Cruz.", 0, -50);
        desenhaTexto("Disciplina: Computacao Grafica", 0, -75);
        desenhaTexto("Docente: Vania Cordeiro", 0, -100);
        desenhaTexto("Discente: Patrick Silva Ferraz", 0, -125);
        COLOR_GREEN;
        desenhaTexto("Pressione <ESC> para sair", 0, -225);
    glPopMatrix();

} // end-desenhaCreditos (void)

/**
 * Função responsável por redefinir a pontuação dos jogadores
 * verifica se o MAX_SCORE foi atingido por um jogador e com a 
 * vantagem de 2 pontos
 * @param int jogador
 * return void
 */
void pontoJogador(int jogador)
{
	unsigned int max_score = MAX_SCORE;

    if(jogador == 1)
    {
        scoreJogador1 ++;
        if (scoreJogador1 >= max_score && scoreJogador1 - scoreJogador2 >= 2)
        {
            jogadorVencedor = 1;
            estadoJogo = 2;
        }
        posXBola = posXJogador1 + 5;
        posYBola = posYJogador1 + 25;
    }
    else
    {
        scoreJogador2 ++;
        if (scoreJogador2 >= max_score && scoreJogador2 - scoreJogador1 >= 2)
        {
            jogadorVencedor = 2;
            estadoJogo = 2;
        }
        posXBola = posXJogador2 - 5;
        posYBola = posYJogador2 + 25;
    }
    
    bolaMovimento = 0;
    primeiraJogada = 1;

} // end-pontoJogador(int jogador)

/**
 * Desenha um texto na janela
 * @param *string é a palavra que será desenhada
 * @return void
 */
void desenhaTexto (const char *string, int x, int y)
{
    glPushMatrix();
        glRasterPos2f(x, y); // Posição em uma linha
        while (*string)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++); // Desenha a palavra em tamanho 24
    glPopMatrix();

} // end-desenhaTexto (const char *string)

/**
 * Função chamada para gerenciar eventos de teclas ASCII
 * @param unsigned char tecla, int x, int y
 * @return void
 */
void tecladoJogador1 (unsigned char tecla, int x, int y)
{
    GLfloat newPos;
	GLfloat speed_jogador = SPEED_JOGADOR;

	switch (tecla) {

		case 119: // W
			newPos = posYJogador1 + speed_jogador;
			if(newPos < (marginTop - OVER_TOP_Y))
                posYJogador1 = newPos;
			break;
		case 115: // S
            newPos = posYJogador1 - speed_jogador;
			if(newPos > marginDown)
                posYJogador1 = newPos;
			break;
		case 27: // ESC
        if (estadoJogo == 3) exit(1);
            estadoJogo = 3;
            break;
        case 32: // ESPAÇO
            if (estadoJogo != 3)
            {
                if (estadoJogo == 2)
                    scoreJogador1 = scoreJogador2 = 0;
                estadoJogo = 1;
                bolaMovimento = 1;
            }
            break;
        default:
            break;
    }

    glutPostRedisplay();
} // end-tecladoJogador1 (unsigned char tecla, int x, int y)

/**
 * Função chamada para gerenciar eventos de teclas Especiais
 * @param GLint tecla, int x, int y
 * @return void
 */
void tecladoJogador2 (GLint tecla, int x, int y)
{
    GLfloat newPos;
    GLfloat speed_jogador = SPEED_JOGADOR;

	switch (tecla)
	{
		case GLUT_KEY_UP: // SETA PARA CIMA
            newPos = posYJogador2 + speed_jogador;
			if(newPos < (marginTop - OVER_TOP_Y))
                posYJogador2 = newPos;
            break;
		case GLUT_KEY_DOWN: // SETA PARA BAIXO
            newPos = posYJogador2 - speed_jogador;
			if(newPos > marginDown)
                posYJogador2 = newPos;
			break;
		default:
            break;
	}

	glutPostRedisplay();
} // end-tecladoJogador2 (GLint tecla, int x, int y)