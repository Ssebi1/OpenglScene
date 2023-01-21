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
#include "SofaFoot.h"



SofaFoot::SofaFoot() {}


void SofaFoot::CreateVBO(GLuint& VaoId, GLuint& VboId, GLuint& EboId)
{
	// varfurile 
	GLfloat Vertices[] =
	{
		// coordonate                   // culori			// normale
		// varfuri "ground"
		0.0f,  0.0f, 0.0f, 1.0f, 0.25f, 0.2f, 0.15f,  0.0f, 0.0f, 1.0f, // fata stanga jos
		20.0f,  0.0f, 0.0f, 1.0f,0.25f, 0.2f, 0.15f,  0.0f, 0.0f, 1.0f, // fata dreapta jos
		20.0f,  0.0f,  40.0f, 1.0f,  0.25f, 0.2f, 0.15f,  0.0f, 0.0f, 1.0f, // fata dreapta sus
		0.0f,  0.0f,  40.0f, 1.0f, 0.25f, 0.2f, 0.15f,  0.0f, 0.0f, 1.0f, // fata stanga sus
		0.0f,  -20.0f, 0.0f, 1.0f, 0.25f, 0.2f, 0.15f,  0.0f, 0.0f, 1.0f, // spate stanga  jos
		20.0f,  -20.0f, 0.0f, 1.0f, 0.25f, 0.2f, 0.15f,  0.0f, 0.0f, 1.0f, // spate dreapta jos
		20.0f,  -20.0f,  40.0f, 1.0f,  0.35f, 0.3f, 0.15f,  0.0f, 0.0f, 1.0f, // spate dreapta sus
		0.0f,  -20.0f,  40.0f, 1.0f,  0.35f, 0.3f, 0.15f,  0.0f, 0.0f, 1.0f, // spate stanga sus
	};

	// indicii pentru varfuri
	GLubyte Indices[] =
	{
		// front
			0, 1, 2, 2, 3, 0,
		// top
			2, 3, 6, 3, 6, 7,
		// left
			0, 4, 3, 3, 4, 7,
		// right
			1, 2, 6, 6, 1, 5
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

void SofaFoot::draw(GLuint& VaoId, GLuint codCol, GLuint matrixLocation, GLuint codColLocation, glm::vec3 translation) {
	glBindVertexArray(VaoId);
	glUniform1i(codColLocation, codCol);
	glm::mat4 myMatrix = glm::mat4(1.0f);
	myMatrix = glm::translate(myMatrix, translation);
	myMatrix = glm::scale(myMatrix, glm::vec3(2.0f, 2.0f, 4.0f));
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, 6*4, GL_UNSIGNED_BYTE, 0);
}