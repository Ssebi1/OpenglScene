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
#include "Wall.h"
#include <SOIL.h>


Wall::Wall() {}


void Wall::CreateVBO(GLuint& VaoId, GLuint& VboId, GLuint& EboId)
{
	// varfurile 
	GLfloat Vertices[] =
	{
		// coordonate                   // culori			// normale               // texturi
		// varfuri "ground"
		-1500.0f,  -1500.0f, 0.0f, 1.0f,  0.95f, 0.94f, 0.8f,  .0f, .0f, 1.0f,        0.0f, 0.0f,
		1500.0f,  -1500.0f, 0.0f, 1.0f,  0.95f, 0.94f, 0.8f,  .0f, .0f, 1.0f,         1.0f, 0.0f,
		1500.0f,  -1500.0f,  1500.0f, 1.0f,  0.95f, 0.94f, 0.8f, -0.2f, .0f, 1.0f,     1.0f, 1.0f,
		-1500.0f,  -1500.0f,  1500.0f, 1.0f,  0.95f, 0.94f, 0.8f,  -0.2f, .0f, 1.0f,    0.0f, 1.0f
	};

	// indicii pentru varfuri
	GLubyte Indices[] =
	{
		// fetele "ground"
			1, 2, 0,   2, 0, 3
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
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)0);
	// atributul 1 = culoare
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
	// atributul 2 = normale
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
	// atributul 3 = coordonate textura
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(10 * sizeof(GLfloat)));
}

void Wall::draw(GLuint ProgramId, GLuint &VaoId ,GLuint codCol, GLuint matrixLocation, GLuint codColLocation) {
	glBindVertexArray(VaoId);
	glUniform1i(codColLocation, codCol);
	glm::mat4 myMatrix = glm::mat4(1.0f);
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}