/* ===================================================================================
	Departamento Eng. Informatica - FCTUC
	Computacao Grafica - 2021/22
	................................................ JHenriques / APerrotta
	Trabalho 3 - Visualizacao
======================================================================================= */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define PI		 3.14159

//================================================================================
//===========================================================Variaveis e constantes

GLfloat tam = 0.5;
GLfloat big = 1.5;
static GLfloat vertices[] = {
	//…………………………………………………………………………………………………… (Esquerda)
		-tam,  -tam,  tam,	// 0 
		-tam,   tam,  tam,	// 1 
		-tam,   tam, -tam,	// 2 
		-tam,  -tam, -tam,	// 3 
	//…………………………………………………… (Direita)
		 tam,  -tam,  tam,	// 4 
		 tam,   tam,  tam,	// 5 
		 tam,   tam, -tam,	// 6 
		 tam,  -tam, -tam,	// 7 
	//……………………………………………………… (Cima)
		-tam,  tam,  tam,	// 8 
		-tam,  tam, -tam,	// 9 
		 tam,  tam, -tam,	// 10 
		 tam,  tam,  tam,	// 11 
	//……………………………………………………… (Baixo)
		 tam,  -tam,  tam,	// 12 
		 tam,  -tam, -tam,	// 13
		-tam,  -tam, -tam,	// 14 
		-tam,  -tam,  tam,	// 15 
};

static GLfloat normais[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  //…………………………………………………………………………………………………… x=tam (Direita)
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
 		1.0,  0.0,  0.0,
		 //…………………………………………………………………………………………………… y=tam (Cima)
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		//…………………………………………………………………………………………………… y=tam (Baixo)
	   0.0,  -1.0,  0.0,
	   0.0,  -1.0,  0.0,
	   0.0,  -1.0,  0.0,
	   0.0,  -1.0,  0.0,
};
//------------------------------------------------------------ Cores
// static GLfloat cor[] = { };
static GLfloat cor[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
	  0.0,  0.0,  0.0,
	  1.0,  0.0,  0.0,
	  1.0,  0.0,  0.0,
	  0.0,  0.0,  0.0,
	  //…………………………………………………………………………………………………… x=tam (Direita)
		0.0,  0.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  0.0,  0.0,
		//…………………………………………………………………………………………………… y=tam (Cima)
	   0.0,  0.0,  1.0,
	   0.0,  0.0,  1.0,
	   0.0,  0.0,  1.0,
	   0.0,  0.0,  1.0,
	   //…………………………………………………………………………………………………… y=tam (Baixo)
	  0.0,  0.0,  1.0,
	  0.0,  0.0,  1.0,
	  0.0,  0.0,  1.0,
	  0.0,  0.0,  1.0,
};
// nao está feito !!
// falta fazer
	

//=========================================================== FACES DA MESA
GLboolean   frenteVisivel = 1;
static GLuint     cima[] = { 8, 11, 10,  9 };   // regra da mao direita
static GLuint     esq[] = { 0, 1, 2,  3 };//++++++++++++ falta a esquerda 
static GLuint     dir[] = { 4, 7, 6,  5 };//++++++++++++ falta a direita 
static GLuint	  baixo[] = { 12, 13, 14, 15 };


//------------------------------------------------------------ Objectos (sistema coordenadas)
GLint		wScreen = 800, hScreen = 600;			//.. janela (pixeis)
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------------------ Visualizacao/Observador 
GLfloat  rVisao = 10, aVisao = 0.5 * PI, incVisao = 0.05;
GLfloat  obsP[] = { rVisao * cos(aVisao), 3.0, rVisao * sin(aVisao) };
GLfloat  angZoom = 45;
GLfloat  incZoom = 3;



//================================================================================
//=========================================================================== INIT
void inicializa(void)
{
	glClearColor(BLACK);		//………………………………………………………………………………Apagar
	glEnable(GL_DEPTH_TEST);	//………………………………………………………………………………Profundidade
	glShadeModel(GL_SMOOTH);	//………………………………………………………………………………Interpolacao de cores	

	glVertexPointer(3, GL_FLOAT, 0, vertices); //………………………………………VertexArrays: vertices + normais + cores
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cor);
	glEnableClientState(GL_COLOR_ARRAY);
	//++++++++++++++++++++++++ cores ??j
}



void drawEixos()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
	glColor4f(RED);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(10, 0, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
	glColor4f(GREEN);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 10, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
	glColor4f(BLUE);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 10);
	glEnd();

}

void drawCube() {

	// BACK
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.1, 0.4);
	glVertex3f(0.5, -0.5, -0.5);      // P1 is red
	glVertex3f(0.5, 0.5, -0.5);      // P2 is green
	glVertex3f(-0.5, 0.5, -0.5);      // P3 is blue
	glVertex3f(-0.5, -0.5, -0.5);      // P4 is purple
	glEnd();

	// White side - FRONT
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.1, 0.4);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.1, 0.4);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glEnd();

	// Green side - LEFT
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.1, 0.4);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	// Blue side - TOP
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.1, 0.4);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.1, 0.4);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
}


void drawScreen() {
	glBegin(GL_POLYGON);  // Dark outline on the screen
	glColor3f(0, 0, 0);
	glVertex3f(0.4, -0.05, 0.16);
	glVertex3f(0.4, 0.75, 0.16);
	glVertex3f(-0.4, 0.75, 0.16);
	glVertex3f(-0.4, -0.05, 0.16);
	glEnd();

	glBegin(GL_POLYGON);  // Screen
	glColor3f(0.2, 0.5, 0.1);
	glVertex3f(0.35, 0, 0.17);
	glVertex3f(0.35, 0.7, 0.17);
	glVertex3f(-0.35, 0.7, 0.17);
	glVertex3f(-0.35, 0, 0.17);
	glEnd();

}



void drawScene() {

	//=================================================== Qual o lado visivel ???
	if (frenteVisivel);
	 //++++++++++++++++++++   falta fazer

	//==================================== MESA	
	//++++++++++++++++++   ?? escala, rotacao, translacao ??
	glPushMatrix();
		glScalef(2, 2, 2);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);   // desenhar uma das faces da mesa
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esq);//+++++++++++++++++ face esquerda
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, dir);//+++++++++++++++++ face direita
	glPopMatrix();

		
	//==================================== Chaleira Amarela
	glColor4f(YELLOW);
	glPushMatrix();
		glTranslated(0, 2, 0);
		//+++++++++++++++++++++ escala, rotacao, translacao ??
		//glutWireTeapot(1);
	glPopMatrix();

}

void display(void) {

	//================================================================= APaga ecran e lida com profundidade (3D)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//================================================================= Não modificar !!!!!!!!!!!!
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//================================================================= Não modificar !!!!!!!!!!!!

	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);
	   

	//…………………………………………………………………………………………………………………………………………………………Objectos
	drawScreen();
	glScalef(1.0, 1.7, 0.3);
	drawCube();
	//drawEixos();
	//drawScene();
	
	//. . . . . . . . . . . . . . . . . . . . .  Actualizacao
	glutSwapBuffers();
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {


	switch (key) {

		case 'a':
			obsP[1] = (obsP[1] + 0.8);
			aVisao = (aVisao + 0.8);
			obsP[0] = rVisao * cos(aVisao);
			obsP[2] = rVisao * sin(aVisao);
			glutPostRedisplay();
			break;

		case 's':
			obsP[1] = (obsP[1] - 0.8);
			aVisao = (aVisao - 0.8);
			obsP[0] = rVisao * cos(aVisao);
			obsP[2] = rVisao * sin(aVisao);
			glutPostRedisplay();
			break;

		//++++++++++++++++++++++++++++  TECLAS
		//  F		lado da frente ou de tras visivel
		//  A/S		movimeto eixo x
		//	E/D		rodar esquerda/direita
		//	R		rar continuamente 
		//++++++++++++++++++++++++++++  TECLAS

		//++++++++++++++++++++++++++++  
		// E possivel inventar outra coisa qualquer !!!


		//--------------------------- Escape
	case 27:
		exit(0);
		break;
	}

}


void teclasNotAscii(int key, int x, int y) {
	//.. observador pode andar à volda da cena  (setas esquerda / direita)
	//.. observador pode andar para cima e para baixo (setas cima / baixo )

	if (key == GLUT_KEY_UP)
		obsP[1] = (obsP[1] + 0.8);
	if (key == GLUT_KEY_DOWN)
		obsP[1] = (obsP[1] - 0.8);

	if (key == GLUT_KEY_LEFT)
		aVisao = (aVisao + 0.3);
	if (key == GLUT_KEY_RIGHT)
		aVisao = (aVisao - 0.3);

	obsP[0] = rVisao * cos(aVisao);
	obsP[2] = rVisao * sin(aVisao);

		
	glutPostRedisplay();
}


//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("gameboy");

	inicializa();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}


