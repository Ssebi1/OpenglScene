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
#include "WallBorder.h"



WallBorder::WallBorder() {}


void WallBorder::CreateVBO(GLuint& VaoId, GLuint& VboId, GLuint& EboId)
{
	// varfurile 
	GLfloat Vertices[] =
	{
		// coordonate                   // culori			// normale
		// varfuri "ground"
		-1500.0f,  -1470.0f, 0.0f, 1.0f, 0.75f, 0.30f, 0.1f,  0.0f, 0.0f, 1.0f, // fata stanga jos
		1500.0f,  -1470.0f, 0.0f, 1.0f, 0.75f, 0.30f, 0.1f,  0.0f, 0.0f, 1.0f, // fata dreapta jos
		1500.0f,  -1470.0f,  40.0f, 1.0f,  0.75f, 0.30f, 0.1f,  0.0f, 0.0f, 1.0f, // fata dreapta sus
		-1500.0f,  -1470.0f,  40.0f, 1.0f,  0.75f, 0.30f, 0.1f,  0.0f, 0.0f, 1.0f, // fata stanga sus
		-1500.0f,  -1500.0f, 0.0f, 1.0f, 0.75f, 0.30f, 0.1f,  0.0f, 0.0f, 1.0f,
		1500.0f,  -1500.0f, 0.0f, 1.0f, 0.75f, 0.30f, 0.1f,  0.0f, 0.0f, 1.0f,
		1500.0f,  -1500.0f,  40.0f, 1.0f,  0.75f, 0.30f, 0.1f,  0.0f, 0.0f, 1.0f,
		-1500.0f,  -1500.0f,  40.0f, 1.0f,  0.75f, 0.30f, 0.1f,  0.0f, 0.0f, 1.0f,
	};

	// indicii pentru varfuri
	GLubyte Indices[] =
	{
		// front
			0, 1, 2, 2, 3, 0,
		// top
			2, 3, 6, 3, 6, 7
	};

	glGenVertexArrays(1, &VaoId);
	glGenBuffers(1, &VboId);
	glGenBuffers(1, &EboId);
	glBindVertexArray(VaoId);

	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	// atributul 0 = pozitie
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (GLvoid*)0);
	// atributul 1 = culoare
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
	// atributul 2 = normale
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
}

void WallBorder::draw(GLuint& VaoId, GLuint codCol, GLuint matrixLocation, GLuint codColLocation) {
	glBindVertexArray(VaoId);
	glUniform1i(codColLocation, codCol);
	glm::mat4 myMatrix = glm::mat4(1.0f);
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, 0);
}