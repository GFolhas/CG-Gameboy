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

GLfloat tam = 5;
GLfloat b = 1;



static GLfloat vertices[] = {
	//�������������������� (Esquerda)
		-tam,  -tam,  tam,	// 0 
		-tam,   tam,  tam,	// 1 
		-tam,   tam, -tam,	// 2 
		-tam,  -tam, -tam,	// 3 
	//�������������������� (Direita)
		 tam,  -tam,  tam,	// 4 
		 tam,   tam,  tam,	// 5 
		 tam,   tam, -tam,	// 6 
		 tam,  -tam, -tam,	// 7 
	//��������������������� (Cima)
		-tam,  tam,  tam,	// 8 
		-tam,  tam, -tam,	// 9 
		 tam,  tam, -tam,	// 10 
		 tam,  tam,  tam,	// 11
	//��������������������� (Baixo)
		-tam,  -tam,  tam,	// 12 
		-tam,  -tam, -tam,	// 13 
		 tam,  -tam, -tam,	// 14
		 tam,  -tam,  tam,	// 15 
	//��������������������� (Frente)
		-tam, -tam,  tam,	// 16 
		-tam,  tam,  tam,	// 17 
		 tam,  tam,  tam,	// 18 
		 tam, -tam,  tam,	// 19 
	//��������������������� (Tras)
		-tam,  -tam, -tam,	// 20 
		-tam,   tam, -tam,	// 21 
		 tam,   tam, -tam,	// 22
		 tam,  -tam, -tam,	// 23 

		//��������������������� (Bot�o Frente)
		b, b, tam*2,
		b, 2*b, tam*2,
		0, 2*b, tam*2,
		0, b, tam*2,
		-b,	b,	tam * 2,
		-b,	0,	tam * 2,
		0,	0,	tam * 2,
		0, -b, tam * 2,
		b, -b, tam * 2,
		b, 0,  tam * 2,
		2*b, 0, tam*2,
		2*b, b, tam*2,

		//��������������������� (Bot�o Esq)
		//bottom 
		0,	0,	tam * 2,
		0, -b, tam * 2,
		0, -b, tam * 2-b,
		0,	0,	tam * 2-b,
		//mid
		-b,	0,	tam * 2-b,
		-b,	b,	tam * 2-b,
		-b,	b,	tam * 2,
		-b,	0,	tam * 2,

		//top
		0, b, tam * 2-b,
		0, 2 * b, tam * 2-b,
		0, 2 * b, tam * 2,
		0, b, tam * 2,

		//��������������������� (Bot�o TopBot)
		//leftop
		0, b, tam * 2 - b,
		-b,	b,	tam * 2 - b,
		-b,	b,	tam * 2,
		0, b, tam * 2,

		//leftbot
		0,	0,	tam * 2,
		-b,	0,	tam * 2,
		-b,	0,	tam * 2 - b,
		0,	0,	tam * 2 - b,
		
		//midtop
		0, 2 * b, tam * 2 - b,
		b, 2 * b, tam * 2 - b,
		b, 2 * b, tam * 2,
		0, 2 * b, tam * 2,
		
		//midbot
		0, -b, tam * 2 - b,
		b, -b, tam * 2 - b,
		b, -b, tam * 2,
		0, -b, tam * 2,
		
		//rightop
		b, b, tam * 2 - b,
		2*b, b, tam * 2 - b,
		2*b, b, tam * 2,
		b, b, tam * 2,
		
		//rightbot
		b, 0, tam * 2 - b,
		2*b, 0, tam * 2 - b,
		2*b, 0, tam * 2,
		b, 0, tam * 2,

		//��������������������� (Bot�o Dir)

		b, -b, tam * 2 - b,
		b,	0,	tam * 2 - b,
		b,	0,	tam * 2,
		b, -b, tam * 2,

		2*b,	b,	tam * 2 - b,
		2*b,	0,	tam * 2 - b,
		2*b,	0,	tam * 2,
		2*b,	b,	tam * 2,

		b, b, tam * 2 - b,
		b, 2 * b, tam * 2 - b,
		b, 2 * b, tam * 2, 
		b, b, tam * 2,

};





static GLfloat normais[] = {
		//�������������������������������������� x=tam (Esquerda)
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		//�������������������������������������� x=tam (Direita)
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
			//�������������������������������������� y=tam (Cima)
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		//�������������������������������������� y=tam (Baixo)
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		//�������������������������������������� z=tam (Frente)
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		//�������������������������������������� z=tam (Tras)
		0.0,   0.0,  -1.0,
		0.0,   0.0,  -1.0,
		0.0,   0.0,  -1.0,
		0.0,   0.0,  -1.0,
		//�������������������������������������� z=tam (bot�o)
		0.0,   0.0,   1.0,
		0.0,   0.0,   1.0,
		0.0,   0.0,   1.0,
		0.0,   0.0,   1.0,
		0.0,   0.0,   1.0,
		0.0,   0.0,   1.0,
		0.0,   0.0,   1.0,
		0.0,   0.0,   1.0,
		0.0,   0.0,   1.0,
		0.0,   0.0,   1.0,
		0.0,   0.0,   1.0,
		0.0,   0.0,   1.0,
		//�������������������������������������� botao esq
		-1.0,   0.0,   0.0,
		-1.0,   0.0,   0.0,
		-1.0,   0.0,   0.0,
		-1.0,   0.0,   0.0,

		-1.0,   0.0,   0.0,
		-1.0,   0.0,   0.0,
		-1.0,   0.0,   0.0,
		-1.0,   0.0,   0.0,

		-1.0,   0.0,   0.0,
		-1.0,   0.0,   0.0,
		-1.0,   0.0,   0.0,
		-1.0,   0.0,   0.0,
		//�������������������������������������� botao ups and downs
		//leftop
		 0.0,   1.0,   0.0,
		 0.0,   1.0,   0.0,
		 0.0,   1.0,   0.0,
		 0.0,   1.0,   0.0,

		 //leftbot
		 0.0,   -1.0,   0.0,
		 0.0,   -1.0,   0.0,
		 0.0,   -1.0,   0.0,
	     0.0,   -1.0,   0.0,

		 //midtop
		 0.0,   1.0,   0.0,
		 0.0,   1.0,   0.0,
		 0.0,   1.0,   0.0,
		 0.0,   1.0,   0.0,

		 //midbot
		 0.0,   -1.0,   0.0,
		 0.0,   -1.0,   0.0,
		 0.0,   -1.0,   0.0,
		 0.0,   -1.0,   0.0,

		 //rightop
		 0.0,   1.0,   0.0,
		 0.0,   1.0,   0.0,
		 0.0,   1.0,   0.0,
		 0.0,   1.0,   0.0,

		 //rightbot
		 0.0,   -1.0,   0.0,
		 0.0,   -1.0,   0.0,
		 0.0,   -1.0,   0.0,
		 0.0,   -1.0,   0.0,

		 //�������������������������������������� botao dir

		 1.0,   0.0,   0.0,
		 1.0,   0.0,   0.0,
		 1.0,   0.0,   0.0,
		 1.0,   0.0,   0.0,

		 1.0,   0.0,   0.0,
		 1.0,   0.0,   0.0,
		 1.0,   0.0,   0.0,
		 1.0,   0.0,   0.0,

		 1.0,   0.0,   0.0,
		 1.0,   0.0,   0.0,
		 1.0,   0.0,   0.0,
		 1.0,   0.0,   0.0,



};
//------------------------------------------------------------ Cores
// static GLfloat cor[] = { };
static GLfloat cor[] = {
		//�������������������������������������� x=tam (Esquerda)
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		//�������������������������������������� x=tam (Direita)
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		//�������������������������������������� y=tam (Cima)
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		//�������������������������������������� y=tam (Baixo)
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		//�������������������������������������� z=tam (Frente)
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		//�������������������������������������� z=tam (Tras)
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		//�������������������� (Bot�o Frente)
		1.0,  0.0,  0.0,	// 24
		1.0,  0.0,  0.0,	// 25
		1.0,  0.0,  0.0,	// 26
		1.0,  0.0,  0.0,	// 27
		1.0,  0.0,  0.0,	// 28
		1.0,  0.0,  0.0,	// 29
		1.0,  0.0,  0.0,	// 30
		1.0,  0.0,  0.0,	// 31
		1.0,  0.0,  0.0,	// 32
		1.0,  0.0,  0.0,	// 33
		1.0,  0.0,  0.0,	// 34
		1.0,  0.0,  0.0,	// 35
		//�������������������� (Bot�o esq)
		0.0,  0.0,  1.0,	// 36
		0.0,  0.0,  1.0,	// 37
		0.0,  0.0,  1.0,	// 38
		0.0,  0.0,  1.0,	// 39

		0.0,  0.0,  1.0,	// 40
		0.0,  0.0,  1.0,	// 41
		0.0,  0.0,  1.0,	// 42
		0.0,  0.0,  1.0,	// 43

		0.0,  0.0,  1.0,	// 44
		0.0,  0.0,  1.0,	// 45
		0.0,  0.0,  1.0,	// 46
		0.0,  0.0,  1.0,	// 47
		//�������������������� (Bot�o ups and downs)
		0.0,  1.0,  0.0,	// 48
		0.0,  1.0,  0.0,	// 49
		0.0,  1.0,  0.0,	// 50
		0.0,  1.0,  0.0,	// 51

		0.0,  1.0,  0.0,	// 52
		0.0,  1.0,  0.0,	// 53
		0.0,  1.0,  0.0,	// 54
		0.0,  1.0,  0.0,	// 55

		0.0,  1.0,  0.0,	// 56
		0.0,  1.0,  0.0,	// 57
		0.0,  1.0,  0.0,	// 58
		0.0,  1.0,  0.0,	// 59

		0.0,  1.0,  0.0,	// 60
		0.0,  1.0,  0.0,	// 61
		0.0,  1.0,  0.0,	// 62
		0.0,  1.0,  0.0,	// 63

		0.0,  1.0,  0.0,	// 64
		0.0,  1.0,  0.0,	// 65
		0.0,  1.0,  0.0,	// 66
		0.0,  1.0,  0.0,	// 67

		0.0,  1.0,  0.0,	// 68
		0.0,  1.0,  0.0,	// 69
		0.0,  1.0,  0.0,	// 70
		0.0,  1.0,  0.0,	// 71
		//�������������������� (Bot�o dir)
		0.0,  0.0,  1.0,	// 72
		0.0,  0.0,  1.0,	// 73
		0.0,  0.0,  1.0,	// 74
		0.0,  0.0,  1.0,	// 75

		0.0,  0.0,  1.0,	// 76
		0.0,  0.0,  1.0,	// 77
		0.0,  0.0,  1.0,	// 78
		0.0,  0.0,  1.0,	// 79

		0.0,  0.0,  1.0,	// 80
		0.0,  0.0,  1.0,	// 81
		0.0,  0.0,  1.0,	// 82
		0.0,  0.0,  1.0,	// 83
		

};

	

//=========================================================== FACES DA MESA
GLboolean   frenteVisivel = 1;
static GLuint     esq[] = { 0, 1, 2,  3 }; // regra da mao direita
static GLuint     dir[] = { 4, 7, 6,  5 };
static GLuint     cima[] = { 8, 11, 10,  9 };
static GLuint     baixo[] = { 12, 13, 14, 15 };
static GLuint     frente[] = { 16, 19, 18,  17 };
static GLuint     tras[] = { 20, 21, 22,  23 };
static GLuint	  bfrente[] = { 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
//static GLuint	  besq[] = { 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36 };
static GLuint	  besq1[] = { 36, 37, 38, 39};
static GLuint	  besq2[] = {40, 41, 42, 43};
static GLuint	  besq3[] = { 44, 45, 46, 47 };
static GLuint	  bltop[] = { 48, 49, 50, 51 };
static GLuint	  blbot[] = { 52, 53, 54, 55 };
static GLuint	  bmtop[] = { 56, 57, 58, 59};
static GLuint	  bmbot[] = { 60, 61, 62, 63 };
static GLuint	  brtop[] = { 64, 65, 66, 67 };
static GLuint	  brbot[] = { 68, 69, 70, 71 };
static GLuint	  bdir1[] = { 72, 73, 74, 75 };
static GLuint	  bdir2[] = { 76, 77, 78, 79 };
static GLuint	  bdir3[] = { 80, 81, 82, 83 };

//------------------------------------------------------------ Objectos (sistema coordenadas)
GLint		wScreen = 800, hScreen = 600;			//.. janela (pixeis)
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------------------ Visualizacao/Observador 
GLfloat  rVisao = 7.5, aVisao = 0.5*PI, incVisao = 0.05;
GLfloat  obsP[] = { rVisao * cos(aVisao), 0.0, rVisao * sin(aVisao)};
GLfloat  angZoom = 45;
GLfloat  incZoom = 3;



//================================================================================
//=========================================================================== INIT
void inicializa(void)
{
	glClearColor(BLACK);		//������������������������������Apagar
	glEnable(GL_DEPTH_TEST);	//������������������������������Profundidade
	glShadeModel(GL_SMOOTH);	//������������������������������Interpolacao de cores	

	glVertexPointer(3, GL_FLOAT, 0, vertices); //���������������VertexArrays: vertices + normais + cores
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cor);
	glEnableClientState(GL_COLOR_ARRAY);
	//++++++++++++++++++++++++ cores ??j

	//glVertexPointer(3, GL_FLOAT, 0, button);
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glColorPointer(3, GL_FLOAT, 0, cor);
	//glEnableClientState(GL_COLOR_ARRAY);
}



void drawEixos()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
	glColor4f(RED);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(20, 0, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
	glColor4f(GREEN);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 20, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
	glColor4f(BLUE);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 20);
	glEnd();

}

void drawCube() {

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);   // desenhar a face de cima do gameboy
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esq);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, dir);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);

	/*
	// BACK
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.1, 0.4);
	glVertex3f(0.5, -0.5, -0.5);      // P1 is red
	glVertex3f(0.5, 0.5, -0.5);      // P2 is green
	glVertex3f(-0.5, 0.5, -0.5);      // P3 is blue
	glVertex3f(-0.5, -0.5, -0.5);      // P4 is purple
	glEnd();

	// FRONT
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.1, 0.4);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	// RIGHT
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.1, 0.4);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glEnd();

	// LEFT
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.1, 0.4);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	// TOP
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.1, 0.4);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	// BOTTOM
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.1, 0.4);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
	*/
}


void drawScreen() {
	glBegin(GL_POLYGON);  // Dark outline on the screen
	glColor3f(0, 0, 0);
	glVertex3f(4, -0.5, 1.6);
	glVertex3f(4, 7.5, 1.6);
	glVertex3f(-4, 7.5, 1.6);
	glVertex3f(-4, -0.5, 1.6);
	glEnd();

	glBegin(GL_POLYGON);  // Screen
	glColor3f(0.2, 0.5, 0.1);
	glVertex3f(3.5, 0, 1.7);
	glVertex3f(3.5, 7, 1.7);
	glVertex3f(-3.5, 7, 1.7);
	glVertex3f(-3.5, 0, 1.7);
	glEnd();

}


void drawCrossButton() {
	glPushMatrix(); {
		glTranslatef(-2.5, -4, 0);
		glScaled(4, 4, 4);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, besq1);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, besq2);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, besq3);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, bltop);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, blbot);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, bmtop);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, bmbot);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, brtop);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, brbot);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, bdir1);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, bdir2);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, bdir3);
		glTranslated(0, 0, 0.01);
		glDrawElements(GL_POLYGON, 12, GL_UNSIGNED_INT, bfrente);
	}glPopMatrix();

	/*glPushMatrix(); {
		glTranslatef(2.5, -4, 0);
		glRotatef(45, 0, 0, -1);
		glScalef(2, 2, 2);
		drawCube();

	}glPopMatrix();*/

	/*
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.4, 0.5);
	glVertex3f(-0.25, -0.28, 0.18); // corner 5
	glVertex3f(-0.17, -0.28, 0.18); // corner 6
	glVertex3f(-0.17, -0.36, 0.18); // corner 7
	glVertex3f(-0.25, -0.36, 0.18); // corner 8
	glVertex3f(-0.25, -0.44, 0.18); // corner 9
	glVertex3f(-0.33, -0.44, 0.18); // corner 10
	glVertex3f(-0.33, -0.36, 0.18); // corner 11
	glVertex3f(-0.41, -0.36, 0.18); // corner 12
	glVertex3f(-0.41, -0.28, 0.18); // corner 1
	glVertex3f(-0.33, -0.28, 0.18); // corner 2
	glVertex3f(-0.33, -0.20, 0.18); // corner 3
	glVertex3f(-0.25, -0.20, 0.18); // corner 4
	glEnd();
	*/
	
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


	//================================================================= N�o modificar !!!!!!!!!!!!
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//================================================================= N�o modificar !!!!!!!!!!!!

	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);
	   

	//����������������������������������������������������������Objectos
	glScalef(0.1, 0.1, 0.1);
	//drawScreen();
	drawCrossButton();
	glScalef(1.0, 1.7, 0.3);
	//drawCube();
	drawEixos();
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
	//.. observador pode andar � volda da cena  (setas esquerda / direita)
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


