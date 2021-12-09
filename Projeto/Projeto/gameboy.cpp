/* ===================================================================================
	Departamento Eng. Informatica - FCTUC
	Computacao Grafica - 2021/22
	Projeto Meta 1 - Gon�alo Tavares Ant�o Folhas Ferreira 2019214765
======================================================================================= */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
#include "RgbImage.h"

void initMaterials(int material);
void alphaChange();
extern GLfloat alpha;

//#include "C:\Users\35192\Documents\UNI\3rd Year\1st Semester\CG\Projeto\Projeto\Debug\RgbImage.h"

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define PI		 3.14159
#define SHIPMAX_X  2.99
#define SHIPMIN_X  -2.99

#define SHIPSCALEMAX_X  0.25
#define SHIPSCALEMAX_Y  0.5
#define SHIPSCALEMIN_X  0.07
#define SHIPSCALEMIN_Y  0.35

//------------------------------------------------------------ Skybox
//GLUquadricObj* esfera = gluNewQuadric();

//------------------------------------------------------------ Focos

bool 		Focos[] = {1};		//.. Dois Focos ligados ou desligados
GLfloat		aberturaFoco = 10.0;		//.. angulo inicial do foco
GLfloat		anguloINC = 3.0;		//.. incremento
GLfloat		anguloMIN = 3.0;		//.. minimo
GLfloat		anguloMAX = 70.0;		//.. maximo


//------------------------------------------------------------ Texto
char     texto[30];

//================================================================================
//===========================================================Variaveis e constantes

GLfloat tam = 5;
GLfloat b = 1;
GLint	msec = 10;

GLfloat rotAngleX = 0.0, rotAngleY = 0.0, rotInc = -1;
GLfloat A = 0.0, B = 0.0, ABInc = -0.03;
GLfloat ship_x = 0, ship_y = 0, shipInc = 0.5;
GLfloat ship_scale_x = 0.1, ship_scale_y = 0.4, shipScaleInc = 0.02;
GLfloat ship_max_y = 2.99, ship_min_y = -2.99;

GLint crossValTop = 0;
GLint crossValLeft = 0;
GLint crossValRight = 0;
GLint crossValBot = 0;
GLint AVal = 0, BVal = 0;
GLint fullScreenX = 0, fullScreenY = 0, fullscreen = 0;


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

//���������������������� ( A & B Buttons) ��������������������������������������������������

		//�������������������� (Esquerda)
		-tam, -tam, tam,	// 
		-tam, tam, tam,	// 
		-tam, tam, -tam,	// 
		-tam, -tam, -tam,	// 
		//�������������������� (Direita)
		tam, -tam, tam,	// 
		tam, tam, tam,	//  
		tam, tam, -tam,	//  
		tam, -tam, -tam,	//  
		//��������������������� (Cima)
		-tam, tam, tam,	// 
		-tam, tam, -tam,	//  
		tam, tam, -tam,	// 
		tam, tam, tam,	// 
		//��������������������� (Baixo)
		-tam, -tam, tam,	//  
		-tam, -tam, -tam,	//  
		tam, -tam, -tam,	// 
		tam, -tam, tam,	// 
		//��������������������� (Frente)
		-tam, -tam, tam,	//  
		-tam, tam, tam,	// 
		tam, tam, tam,	//  
		tam, -tam, tam,	//  
		//��������������������� (Tras)
		-tam, -tam, -tam,	//  
		-tam, tam, -tam,	//  
		tam, tam, -tam,	// 
		tam, -tam, -tam,	// 

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


//���������������������� ( A & B Buttons) ��������������������������������������������������

		//�������������������������������������� x=tam (Esquerda)
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		//�������������������������������������� x=tam (Direita)
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		//�������������������������������������� y=tam (Cima)
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		//�������������������������������������� y=tam (Baixo)
		0.0, -1.0, 0.0,
		0.0, -1.0, 0.0,
		0.0, -1.0, 0.0,
		0.0, -1.0, 0.0,
		//�������������������������������������� z=tam (Frente)
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		//�������������������������������������� z=tam (Tras)
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,

};
//------------------------------------------------------------ Cores
// static GLfloat cor[] = { };
static GLfloat cor[] = {
		//�������������������������������������� x=tam (Esquerda)
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.3,
		0.2,  0.1,  0.3,
		//�������������������������������������� x=tam (Direita)
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.3,
		0.2,  0.1,  0.3,
		//�������������������������������������� y=tam (Cima)
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.3,
		0.2,  0.1,  0.3,
		0.2,  0.1,  0.4,
		//�������������������������������������� y=tam (Baixo)
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.3,
		0.2,  0.1,  0.3,
		0.2,  0.1,  0.4,
		//�������������������������������������� z=tam (Frente)
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		0.2,  0.1,  0.4,
		//�������������������������������������� z=tam (Tras)
		0.2,  0.1,  0.3,
		0.2,  0.1,  0.3,
		0.2,  0.1,  0.3,
		0.2,  0.1,  0.3,
		//�������������������� (Bot�o Frente)
		0.2,  0.3,  0.4,
		0.2,  0.3,  0.4,
		0.2,  0.3,  0.4,
		0.2,  0.3,  0.4,
		0.2,  0.3,  0.4,
		0.2,  0.3,  0.4,
		0.2,  0.3,  0.4,
		0.2,  0.3,  0.4,
		0.2,  0.3,  0.4,
		0.2,  0.3,  0.4,
		0.2,  0.3,  0.4,
		0.2,  0.3,  0.4,
		//�������������������� (Bot�o esq)
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,

		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,

		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		//�������������������� (Bot�o ups and downs)
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,

		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,

		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,

		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,

		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,

		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		//�������������������� (Bot�o dir)
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,

		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,

		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		0.2,  0.2,  0.3,
		

//���������������������� ( A & B Buttons) ��������������������������������������������������

		0.2, 0.2, 0.3,
		0.2, 0.2, 0.3,
		0.2, 0.2, 0.3,
		0.2, 0.2, 0.3,

		0.2, 0.2, 0.3,
		0.2, 0.2, 0.3,
		0.2, 0.2, 0.3,
		0.2, 0.2, 0.3,

		0.2, 0.2, 0.3,
		0.2, 0.2, 0.3,
		0.2, 0.2, 0.3,
		0.2, 0.2, 0.3,

		0.2, 0.2, 0.3,
		0.2, 0.2, 0.3,
		0.2, 0.2, 0.3,
		0.2, 0.2, 0.3,

		0.2, 0.3, 0.4,
		0.2, 0.3, 0.4,
		0.2, 0.3, 0.4,
		0.2, 0.3, 0.4,

		0.2, 0.2, 0.3,
		0.2, 0.2, 0.3,
		0.2, 0.2, 0.3,
		0.2, 0.2, 0.3,

};


static GLfloat texturas[] = {

//gameboy body
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
1, 0, 1, 1.3, 0, 1.3, 0, 0,

//crossbutton
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,

//A button
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
1, 0, 1, 1, 0, 1, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,

//B button
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
1, 0, 1, 1, 0, 1, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0
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
static GLuint     esqA[] = { 84, 85, 86, 87 };
static GLuint     dirA[] = { 88, 89, 90, 91 };
static GLuint     cimaA[] = { 92, 93, 94, 95 };
static GLuint     baixoA[] = { 96, 97, 98, 99 };
static GLuint     frenteA[] = { 100, 101, 102, 103 };
static GLuint     trasA[] = { 104, 105, 106, 107 };

//------------------------------------------------------------ Objectos (sistema coordenadas)
GLint		wScreen = 800, hScreen = 600;			//.. janela (pixeis)
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------------------ Visualizacao/Observador 
GLfloat  rVisao = 7.5, aVisao = 0.5*PI, incVisao = 0.05;
GLfloat  obsP[] = { rVisao * cos(aVisao), 0.0, rVisao * sin(aVisao)};
GLfloat  angZoom = 45;
GLfloat  incZoom = 3;

RgbImage imag;
GLuint   texture[5];

GLfloat intensidadeDia = 0.0;
GLfloat luzGlobalCorAmb[4] = { intensidadeDia, intensidadeDia,intensidadeDia, 1.0 };   // 
GLint   ligaTeto = 1;		 //:::   'T'  
GLfloat intensidadeT = 0.3;  //:::   'I'  
GLint   luzR = 1;		 	 //:::   'R'  
GLint   luzG = 1;			 //:::   'G'  
GLint   luzB = 1;			 //:::   'B'  
GLfloat localPos[4] = { 0.0, 5.0, 0.0, 1.0 };
GLfloat localCorAmb[4] = { 0.2, 0.2, 0.2, 0.0 };
GLfloat localCorDif[4] = { luzR, luzG, luzB, 1.0 };
GLfloat localCorEsp[4] = { luzR, luzG, luzB, 1.0 };

GLfloat Pos1[] = { 0.0f, 1.0f,  1.0f, 1.0f };   // Foco 1
bool foco = true;
bool direct = true;




void initTexturas()
{
	//----------------------------------------- Chao - tapete
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("C:/Users/35192/Documents/UNI/3rd Year/1st Semester/CG/Projeto/Projeto/Debug/color.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//----------------------------------------- Esfera - skybox envolvente
	/*glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	imag.LoadBmpFile("C:/Users/35192/Documents/UNI/3rd Year/1st Semester/CG/Projeto/Projeto/Debug/skybox.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());*/

	//----------------------------------------- A button
	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	imag.LoadBmpFile("C:/Users/35192/Documents/UNI/3rd Year/1st Semester/CG/Projeto/Projeto/Debug/A.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

 
	//----------------------------------------- B button
	glGenTextures(1, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	imag.LoadBmpFile("C:/Users/35192/Documents/UNI/3rd Year/1st Semester/CG/Projeto/Projeto/Debug/B.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

}



void initLights(void) {



	GLfloat Foco_direccao[] = { 0, 0, -1, 0 };	//��� -Z
	GLfloat Foco1_cor[] = { 0, 1,  0, 1 };	//��� Cor da luz 1
	GLfloat Foco_ak = 1.0;
	GLfloat Foco_al = 0.05f;
	GLfloat Foco_aq = 0.0f;
	GLfloat Foco_Expon = 2.0;		// Foco, SPOT_Exponent

	//�����������������������������������������������Foco Esquerda
	glLightfv(GL_LIGHT1, GL_POSITION, Pos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Foco1_cor);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, aberturaFoco);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, Foco_Expon);


	//����������������������������������������������������� Ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);

	//����������������������������������������������������� Teto
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);


}



//================================================================================
//=========================================================================== INIT
void inicializa(void)
{
	glClearColor(BLACK);		//������������������������������Apagar
	glEnable(GL_DEPTH_TEST);	//������������������������������Profundidade
	glShadeModel(GL_SMOOTH);	//������������������������������Interpolacao de cores	
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	initLights();
	initTexturas();

	glVertexPointer(3, GL_FLOAT, 0, vertices); //���������������VertexArrays: vertices + normais + cores
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cor);
	glEnableClientState(GL_COLOR_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texturas);   // coordenadas textura
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

}


void desenhaTexto(char* string, GLfloat x, GLfloat y, GLfloat z) {
	glRasterPos3f(x, y, z);
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *string++);
}



void drawEixos()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
	//glColor4f(RED);
	initMaterials(15); // 2 is good, 13 too
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(20, 0, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
	//glColor4f(GREEN);
	initMaterials(14);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 20, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
	//glColor4f(BLUE);
	initMaterials(13);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 20);
	glEnd();

}

void drawCube() {
	initMaterials(16);
	glPushMatrix(); {
		glScalef(1.0, 1.7, 0.3);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
		glDisable(GL_TEXTURE_2D);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);   // desenhar a face de cima do gameboy
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esq);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, dir);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	}glPopMatrix();


}


void drawScreen() {
	initMaterials(12);
	glBegin(GL_POLYGON);  // Dark outline on the screen
		//glColor3f(0, 0, 0);
		glNormal3d(0, 0, 1);
		glVertex3f(4, -0.5, 1.6);
		glVertex3f(4, 7.5, 1.6);
		glVertex3f(-4, 7.5, 1.6);
		glVertex3f(-4, -0.5, 1.6);
	glEnd();

	initMaterials(0);
	glBegin(GL_POLYGON);  // Screen
		//glColor3f(0.2, 0.5, 0.1);
		glNormal3d(0, 0, 1);
		glVertex3f(3.5, 0, 1.7);
		glVertex3f(3.5, 7, 1.7);
		glVertex3f(-3.5, 7, 1.7);
		glVertex3f(-3.5, 0, 1.7);
	glEnd();

}


void drawGlass() {
	initMaterials(1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);  // Screen
		glNormal3d(0, 0, 1);
		glVertex3f(3.5, 0, 1.7);
		glVertex3f(3.5, 7, 1.7);
		glVertex3f(-3.5, 7, 1.7);
		glVertex3f(-3.5, 0, 1.7);
	glEnd();
	glDisable(GL_BLEND);
}


void drawShip() {
	initMaterials(4);
	glPushMatrix(); {
		glTranslatef(ship_x, ship_y, 0);
		glScalef(ship_scale_x, ship_scale_y, 1);
		glBegin(GL_POLYGON);  // My ship
			//glColor3f(0, 0.8, 0.9);
			glColor3f(1, 0, 0);
			//glVertex3f(4, -0.5, 1.75);
			glVertex3f(4, 7.5, 1.75);
			glVertex3f(0, 10, 1.75);
			glVertex3f(-4, 7.5, 1.75);
			//glVertex3f(-4, -0.5, 1.75);
		glEnd();
	}glPopMatrix();

}


void drawCrossButton() {
	initMaterials(9);
	glPushMatrix(); {
		glTranslatef(-2.5, -4, 1.5);
		glRotatef(rotAngleX, 1, 0, 0);
		glRotatef(rotAngleY, 0, 1, 0);
		glTranslatef(-0.4, -0.4, -tam-2.6); // bring to origin
		glScaled(0.8, 0.8, 0.8);
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
}

void drawAB(float xt, float yt, float zt) {

	// Button A
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture[1]);
	initMaterials(9);
	glPushMatrix(); {
		glTranslatef(xt, yt, zt + A);
		glRotatef(45, 0, 0, -1);
		glScaled(0.1, 0.1, 0.05);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cimaA);   // desenhar a face de cima do bot�o A
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esqA);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, dirA);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixoA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frenteA);
		glDisable(GL_TEXTURE_2D);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, trasA);
	}glPopMatrix();
	//glDisable(GL_TEXTURE_2D);

	// Button B
	glPushMatrix(); {
		glTranslatef(xt*2, yt+0.5, zt + B);
		glRotatef(45, 0, 0, -1);
		glScaled(0.1, 0.1, 0.05);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cimaA);   // desenhar a face de cima do bot�o B
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esqA);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, dirA);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixoA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frenteA);
		glDisable(GL_TEXTURE_2D);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, trasA);
	}glPopMatrix();
}

/*
void drawEsfera()
{
	//------------------------- Esfera
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	//glTranslatef(2, 4, 2);
	glRotatef(-90, 1, 0, 0);
	gluQuadricDrawStyle(esfera, GLU_FILL);
	gluQuadricNormals(esfera, GLU_SMOOTH);
	gluQuadricTexture(esfera, GL_TRUE);
	gluSphere(esfera, 60.0, 100, 100);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
*/


void all() {

	if (crossValTop) {
		rotAngleX = rotAngleX + rotInc;
		if (rotAngleX < -10) { rotInc = -rotInc; if (ship_y < ship_max_y) ship_y += shipInc; printf("[Y] Ship Position > %f\n", ship_y);}
		if (rotAngleX > 0) { rotInc = -rotInc;  rotAngleX = 0; crossValTop = !crossValTop; }
	}

	if (crossValBot) {
		rotAngleX = rotAngleX - rotInc;
		if (rotAngleX > 10) { rotInc = -rotInc; if (ship_y > ship_min_y) ship_y -= shipInc; printf("[Y] Ship Position > %f\n", ship_y); }
		if (rotAngleX < 0) { rotInc = -rotInc; rotAngleX = 0; crossValBot = !crossValBot; }
	}

	if (crossValLeft) {
		rotAngleY = rotAngleY + rotInc;
		if (rotAngleY < -10) { rotInc = -rotInc; if (ship_x > SHIPMIN_X) ship_x -= shipInc; printf("[X] Ship Position > %f\n", ship_x); }
		if (rotAngleY > 0) { rotInc = -rotInc;  rotAngleY = 0; crossValLeft = !crossValLeft; }
	}

	if (crossValRight) {
		rotAngleY = rotAngleY - rotInc;
		if (rotAngleY > 10) { rotInc = -rotInc; if (ship_x < SHIPMAX_X) ship_x += shipInc; printf("[X] Ship Position > %f\n", ship_x); }
		if (rotAngleY < 0) { rotInc = -rotInc; rotAngleY = 0; crossValRight = !crossValRight; }
	}

	if (AVal) {
		A = A - ABInc;
		if (A < -0.3) {
			ABInc = -ABInc;
			if (fullscreen) {
				glutFullScreenToggle();
				fullScreenX = 0; fullScreenY = 0;  wScreen = 800; hScreen = 600;
				ship_scale_x += 0.03;
				ship_scale_y += 0.03;
				ship_max_y = 2.99;
				ship_min_y = -2.99;
				fullscreen = 0;
			}
		}
		if (A > 0) { ABInc = -ABInc; A = 0; AVal = !AVal; }
	}
	

	if (BVal) {
		B = B - ABInc;
		if (B < -0.3) { 
			ABInc = -ABInc;
			if (!fullscreen) {
				//glutFullScreen();
				glutFullScreenToggle();
				fullScreenX = -2075; fullScreenY = -3000;  wScreen = 5500; hScreen = 5500;
				ship_scale_x -= 0.03;
				ship_scale_y -= 0.03;
				ship_max_y = 1.49;
				ship_min_y = -1.49;
				fullscreen = 1;
			}
		}
		if (B > 0) { ABInc = -ABInc; B = 0; BVal = !BVal; }
	}


	glScalef(0.2, 0.2, 0.2);
	//drawEsfera();
	drawScreen();
	drawShip();
	drawCube();
	drawAB(1.5, -4.25, 1.75);
	drawCrossButton();
	glTranslatef(0, 0, 0.1);
	drawGlass();
	glTranslatef(0, 0, -0.1);
}



void display(void) {

	//================================================================= APaga ecran e lida com profundidade (3D)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//================================================================= N�o modificar !!!!!!!!!!!!
	glDisable(GL_LIGHTING);
	glViewport(fullScreenX, fullScreenY, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-xC, xC, -xC, xC, -zC, zC);
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//================================================================= N�o modificar !!!!!!!!!!!!
	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);



	//����������������������������������������������������������Texto
	glColor3f(1, 1, 1);
	if (foco) { sprintf_s(texto, 30, "Foco 'F' - ON"); }
	else { sprintf_s(texto, 30, "Foco 'F' - OFF"); }
	desenhaTexto(texto, -12, 1, -14);
	if (direct) { sprintf_s(texto, 30, "Lighting 'L' - ON"); }
	else { sprintf_s(texto, 30, "Lighting 'L' - OFF"); }
	desenhaTexto(texto, -12, 1, -8);
	sprintf_s(texto, 30, "Transparency 'T' - %.2f", alpha);
	desenhaTexto(texto, -12, 1, -2);


	//================================================================= N�o modificar !!!!!!!!!!!!
	glViewport(fullScreenX, fullScreenY, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//================================================================= N�o modificar !!!!!!!!!!!!
	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);




	//============================================Esferasverde e vermelha
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	//�������������������������������Verde
	if (Focos[0]) {
		glPushMatrix();
		glColor3f(0.0f, 1.0f, 0.0f);
		glTranslatef(Pos1[0], Pos1[1], Pos1[2]);
		//glutSolidSphere(0.1f, 100, 100);
		glPopMatrix();
	}



	//============================================ Grelha de polionos (dim*dim)
	//============================================ O ponto minimo   e (0,0), o maximo (2,2)
	//============================================ A textura minimo e (0,0), o maximo (1,1)
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);


	//����������������������������������������������������������Objectos
	drawEixos();
	all();
	
	//. . . . . . . . . . . . . . . . . . . . .  Actualizacao
	glutSwapBuffers();
}


void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}


//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {


	switch (key) {

		//--------------------------- CrossButton Keyboard


		case 'T':
		case 't':
			alphaChange();
			glutPostRedisplay();
			break;


		case 'W':
		case 'w':
			crossValTop = !crossValTop;
			glutPostRedisplay();
			break;

		case 'A':
		case 'a':
			crossValLeft = !crossValLeft;
			glutPostRedisplay();
			break;
		
		case 'D':
		case 'd':
			crossValRight = !crossValRight;
			glutPostRedisplay();
			break;

		case 'S':
		case 's':
			crossValBot = !crossValBot;
			glutPostRedisplay();
			break;
		

		//--------------------------- A & B Button

		case 'Z':
		case 'z':
			AVal = !AVal;
			glutPostRedisplay();
			break;

		case 'X':
		case 'x':
			BVal = !BVal;
			glutPostRedisplay();
			break;



		//--------------------------- Lighting

		case 'L':
		case 'l':
			if (direct) {
				direct = false;
				glDisable(GL_LIGHT0);
			}
			else {
				direct = true;
				glEnable(GL_LIGHT0);
			}
			glutPostRedisplay();
			break;
			
		case 'F':
		case 'f':
			if (foco) {
				foco = false;
				glDisable(GL_LIGHT1);
			}
			else {
				glEnable(GL_LIGHT1);
				foco = true;
			}
			break;


		//--------------------------- Escape

		case 27:
			exit(0);
			break;
	}

}


void teclasNotAscii(int key, int x, int y) {

	if (!fullscreen) {

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
}



//======================================================= MAIN
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("gameboy color - WASD (arrow movement) - X and Z (A & B buttons) - UpDownLeftRight (spin gameboy) - F (Foco) - L (Directional Lighting)");

	inicializa();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}


