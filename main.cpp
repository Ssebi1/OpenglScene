#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "loadShaders.h"
#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Floor.h"
#include "Wall.h"
#include "Wall2.h"
#include "ClockFront1.h"
#include "ClockLine1.h"
#include "ClockMargin.h"
#include "WallBorder.h"
#include "WallBorder2.h"
#include "SofaFoot.h"
#include "SofaElement.h"
#include "SofaElement2.h"
#include "TableStand.h"
#include "TableLeg.h"
#include "ClockLine2.h"

using namespace std;

// identificatori 
GLuint
VaoIds[200],
VboIds[200],
EboIds[200],
ColorBufferId,
ProgramId,
myMatrixLocation,
matrUmbraLocation,
viewLocation,
projLocation,
matrRotlLocation,
lightColorLocation,
lightPosLocation,
viewPosLocation,
codColLocation;

float counter = 0.0f;

Floor floor1;
Wall wall;
Wall2 wall2;
ClockFront1 clockFront1;
ClockLine1 clockLine1;
ClockLine2 clockLine2;
ClockMargin clockMargin;
WallBorder wallBorder;
WallBorder2 wallBorder2;

SofaFoot sofaFoot1, sofaFoot2, sofaFoot3, sofaFoot4;
SofaElement sofaElement1, sofaElement2, sofaElement3, sofaElement4;
SofaElement2 sofaElement21, sofaElement22;

TableLeg tableLeg1, tableLeg2, tableLeg3, tableLeg4;

TableLeg tableSurface1, tableSurface2;

int codCol;
float PI = 3.141592;

// matrice utilizate
glm::mat4 myMatrix, matrRot;

// elemente pentru matricea de vizualizare
float Refx = 0.0f, Refy = 0.0f, Refz = 800.0f;
float alpha = PI / 16, BETA = PI / 2, dist = 400.0f;
float Obsx, Obsy, Obsz;
float Vx = 0.0, Vy = 0.0, Vz = 1.0;
glm::mat4 view;

// elemente pentru matricea de proiectie
float width = 800, height = 600, xwmin = -800.f, xwmax = 800, ywmin = -600, ywmax = 600, znear = 0.1, zfar = 1, fov = 45;
glm::mat4 projection;

// sursa de lumina
float xL = -200.f, yL = -300.f, zL = 1400.f;

// matricea umbrei
float matrUmbra[4][4];

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'l':
		Vx -= 0.1;
		break;
	case 'r':
		Vx += 0.1;
		break;
	case '+':
		dist += 5;
		break;
	case '-':
		dist -= 5;
		break;
	}
	if (key == 27)
		exit(0);
}
void processSpecialKeys(int key, int xx, int yy)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		BETA -= 0.05;
		break;
	case GLUT_KEY_RIGHT:
		BETA += 0.05;
		break;
	case GLUT_KEY_UP:
		alpha += 0.05;
		break;
	case GLUT_KEY_DOWN:
		alpha -= 0.05;
		break;
	}
}

void DestroyVBO(void)
{
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	for (int i = 0; i < 200; i++) {
		glDeleteBuffers(1, &VboIds[i]);
		glDeleteBuffers(1, &EboIds[i]);
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &VaoIds[i]);
	}
}

void CreateShaders(void)
{
	ProgramId = LoadShaders("shader.vert", "shader.frag");
	glUseProgram(ProgramId);
}

void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

void Initialize(void)
{
	myMatrix = glm::mat4(1.0f);
	matrRot = glm::rotate(glm::mat4(1.0f), PI / 8, glm::vec3(0.0, 0.0, 1.0));
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	int id = 1;

	// Floor
	Floor floor1 = Floor();
	floor1.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	// Wall
	Wall wall = Wall();
	wall.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	// Wall2
	Wall2 wall2 = Wall2();
	wall2.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	// Clock front 1
	ClockFront1 clockFront1 = ClockFront1();
	clockFront1.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	// Clock Line 1
	ClockLine1 clockLine1 = ClockLine1();
	clockLine1.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	// Clock Line 2
	ClockLine2 clockLine2 = ClockLine2();
	clockLine2.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	// Wall border
	WallBorder wallBorder = WallBorder();
	wallBorder.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	// Wall border 2
	WallBorder2 wallBorder2 = WallBorder2();
	wallBorder2.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	// Sofa foot
	SofaFoot sofaFoot1 = SofaFoot();
	sofaFoot1.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	SofaFoot sofaFoot2 = SofaFoot();
	sofaFoot1.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	SofaFoot sofaFoot3 = SofaFoot();
	sofaFoot1.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	SofaFoot sofaFoot4 = SofaFoot();
	sofaFoot1.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	// Sofa elements
	SofaElement sofaElement1 = SofaElement();
	sofaElement1.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	SofaElement sofaElement2 = SofaElement();
	sofaElement2.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	SofaElement sofaElement3 = SofaElement();
	sofaElement3.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	SofaElement sofaElement4 = SofaElement();
	sofaElement4.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	// Sofa elements 2
	SofaElement2 sofaElement21 = SofaElement2();
	sofaElement21.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	SofaElement2 sofaElement22 = SofaElement2();
	sofaElement22.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	// Table legs
	TableLeg tableLeg1 = TableLeg();
	tableLeg1.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	TableLeg tableLeg2 = TableLeg();
	tableLeg1.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	TableLeg tableLeg3 = TableLeg();
	tableLeg1.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	TableLeg tableLeg4 = TableLeg();
	tableLeg1.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	// Table surface
	TableLeg tableSurface1 = TableLeg();
	tableSurface1.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;

	TableLeg tableSurface2 = TableLeg();
	tableSurface2.CreateVBO(VaoIds[id], VboIds[id], EboIds[id]);
	id++;


	CreateShaders();
	// locatii pentru shader-e
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	matrUmbraLocation = glGetUniformLocation(ProgramId, "matrUmbra");
	viewLocation = glGetUniformLocation(ProgramId, "view");
	projLocation = glGetUniformLocation(ProgramId, "projection");
	lightColorLocation = glGetUniformLocation(ProgramId, "lightColor");
	lightPosLocation = glGetUniformLocation(ProgramId, "lightPos");
	viewPosLocation = glGetUniformLocation(ProgramId, "viewPos");
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);
}
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//pozitia observatorului
	Obsx = Refx + dist * cos(alpha) * cos(BETA);
	Obsy = Refy + dist * cos(alpha) * sin(BETA);
	Obsz = Refz + dist * sin(alpha);

	// matrice de vizualizare + proiectie
	glm::vec3 Obs = glm::vec3(Obsx, Obsy, Obsz);   // se schimba pozitia observatorului	
	glm::vec3 PctRef = glm::vec3(Refx, Refy, Refz); // pozitia punctului de referinta
	glm::vec3 Vert = glm::vec3(Vx, Vy, Vz); // verticala din planul de vizualizare 
	view = glm::lookAt(Obs, PctRef, Vert);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	projection = glm::infinitePerspective(fov, GLfloat(width) / GLfloat(height), znear);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);

	// matricea pentru umbra
	float D = -2.5f;
	matrUmbra[0][0] = zL + D; matrUmbra[0][1] = 0; matrUmbra[0][2] = 0; matrUmbra[0][3] = 0;
	matrUmbra[1][0] = 0; matrUmbra[1][1] = zL + D; matrUmbra[1][2] = 0; matrUmbra[1][3] = 0;
	matrUmbra[2][0] = -xL; matrUmbra[2][1] = -yL; matrUmbra[2][2] = D; matrUmbra[2][3] = -1;
	matrUmbra[3][0] = -D * xL; matrUmbra[3][1] = -D * yL; matrUmbra[3][2] = -D * zL; matrUmbra[3][3] = zL;
	glUniformMatrix4fv(matrUmbraLocation, 1, GL_FALSE, &matrUmbra[0][0]);

	// Variabile uniforme pentru iluminare
	glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightPosLocation, xL, yL, zL);
	glUniform3f(viewPosLocation, Obsx, Obsy, Obsz);

	int id = 1;

	// draw floor
	floor1.draw(VaoIds[id++], 0, myMatrixLocation, codColLocation);

	// draw wall
	wall.draw(ProgramId, VaoIds[id++], 0, myMatrixLocation, codColLocation);

	// draw wall2
	wall2.draw(ProgramId, VaoIds[id++],0, myMatrixLocation, codColLocation);

	// draw clock front 1
	clockFront1.draw(ProgramId, VaoIds[id++], 0, myMatrixLocation, codColLocation);

	// clock line 1
	clockLine1.draw(VaoIds[id++], 0, myMatrixLocation, codColLocation);

	// clock line 2
	clockLine2.draw(VaoIds[id++], 0, myMatrixLocation, codColLocation, counter);

	// wall border
	wallBorder.draw(VaoIds[id++], 0, myMatrixLocation, codColLocation);

	// wall border 2
	wallBorder2.draw(VaoIds[id++], 0, myMatrixLocation, codColLocation);

	// sofa foot
	sofaFoot1.draw(VaoIds[id], 0, myMatrixLocation, codColLocation, glm::vec3(700.0f, -1200.0f, 0.0f));
	sofaFoot1.draw(VaoIds[id++], 1, myMatrixLocation, codColLocation, glm::vec3(700.0f, -1200.0f, 0.0f));

	sofaFoot2.draw(VaoIds[id], 0, myMatrixLocation, codColLocation, glm::vec3(400.0f, -1200.0f, 0.0f));
	sofaFoot2.draw(VaoIds[id++], 1, myMatrixLocation, codColLocation, glm::vec3(400.0f, -1200.0f, 0.0f));
	
	sofaFoot3.draw(VaoIds[id], 0, myMatrixLocation, codColLocation, glm::vec3(400.0f, -800.0f, 0.0f));
	sofaFoot3.draw(VaoIds[id++], 1, myMatrixLocation, codColLocation, glm::vec3(400.0f, -800.0f, 0.0f));
	
	sofaFoot4.draw(VaoIds[id], 0, myMatrixLocation, codColLocation, glm::vec3(700.0f, -800.0f, 0.0f));
	sofaFoot4.draw(VaoIds[id++], 1, myMatrixLocation, codColLocation, glm::vec3(700.0f, -800.0f, 0.0f));

	// sofa elements
	sofaElement1.draw(VaoIds[id], 1, myMatrixLocation, codColLocation, glm::vec3(370.0f, -800.0f, 160.0f), glm::vec3(22.0f, 22.0f, 3.0f));
	sofaElement1.draw(VaoIds[id++], 0, myMatrixLocation, codColLocation, glm::vec3(370.0f, -800.0f, 160.0f), glm::vec3(22.0f, 22.0f, 3.0f));
	sofaElement2.draw(VaoIds[id++], 0, myMatrixLocation, codColLocation, glm::vec3(370.0f, -1200.0f, 200.0f), glm::vec3(22.0f, 3.0f, 16.0f));
	sofaElement3.draw(VaoIds[id++], 0, myMatrixLocation, codColLocation, glm::vec3(310.0f, -800.0f, 160.0f), glm::vec3(3.0f, 22.0f, 8.0f));
	sofaElement3.draw(VaoIds[id++], 0, myMatrixLocation, codColLocation, glm::vec3(810.0f, -800.0f, 160.0f), glm::vec3(3.0f, 22.0f, 8.0f));

	// sofa elements 2
	sofaElement22.draw(VaoIds[id++], 0, myMatrixLocation, codColLocation, glm::vec3(810.0f, -760.0f, 480.0f), glm::vec3(2.0f, 24.0f, 0.5f));
	sofaElement22.draw(VaoIds[id++], 0, myMatrixLocation, codColLocation, glm::vec3(310.0f, -760.0f, 480.0f), glm::vec3(2.0f, 24.0f, 0.5f));

	// table legs
	tableLeg1.draw(VaoIds[id], 0, myMatrixLocation, codColLocation, glm::vec3(-150.0f, -860.0f, 0.0f), glm::vec3(2.0f, 2.0f, 10.0f));
	tableLeg1.draw(VaoIds[id++], 1, myMatrixLocation, codColLocation, glm::vec3(-150.0f, -860.0f, 0.0f), glm::vec3(2.0f, 2.0f, 10.0f));

	tableLeg2.draw(VaoIds[id], 0, myMatrixLocation, codColLocation, glm::vec3(100.0f, -860.0f, 0.0f), glm::vec3(2.0f, 2.0f, 10.0f));
	tableLeg2.draw(VaoIds[id++], 1, myMatrixLocation, codColLocation, glm::vec3(100.0f, -860.0f, 0.0f), glm::vec3(2.0f, 2.0f, 10.0f));

	tableLeg3.draw(VaoIds[id], 0, myMatrixLocation, codColLocation, glm::vec3(100.0f, -1160.0f, 0.0f), glm::vec3(2.0f, 2.0f, 10.0f));
	tableLeg3.draw(VaoIds[id++], 1, myMatrixLocation, codColLocation, glm::vec3(100.0f, -1160.0f, 0.0f), glm::vec3(2.0f, 2.0f, 10.0f));

	tableLeg4.draw(VaoIds[id], 0, myMatrixLocation, codColLocation, glm::vec3(-150.0f, -1160.0f, 0.0f), glm::vec3(2.0f, 2.0f, 10.0f));
	tableLeg4.draw(VaoIds[id++], 1, myMatrixLocation, codColLocation, glm::vec3(-150.0f, -1160.0f, 0.0f), glm::vec3(2.0f, 2.0f, 10.0f));

	// table surface
	tableSurface1.draw(VaoIds[id], 1, myMatrixLocation, codColLocation, glm::vec3(-200.0f, -855.0f, 370.0f), glm::vec3(20.0f, 20.0f, 1.0f));
	tableSurface1.draw(VaoIds[id++], 0, myMatrixLocation, codColLocation, glm::vec3(-200.0f, -855.0f, 370.0f), glm::vec3(20.0f, 20.0f, 1.0f));

	glutSwapBuffers();
	glFlush();
}
void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 900);
	glutCreateWindow("OPENGL");
	glewInit();
	Initialize();
	glutIdleFunc(RenderFunction);
	glutDisplayFunc(RenderFunction);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}

