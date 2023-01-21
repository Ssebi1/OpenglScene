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
#include "ClockLine2.h"
#include <GLFW/glfw3.h>
#include <ctime>

using namespace std;

ClockLine2::ClockLine2() {}


void ClockLine2::CreateVBO(GLuint& VaoId, GLuint& VboId, GLuint& EboId)
{
	// varfurile 
	GLfloat Vertices[] =
	{
		// coordonate                   // culori			// normale
		// varfuri "ground"
		-10.0f,  -1430.0f, 800.0f, 1.0f,  1.0f, 0.7f, 0.2f,  0.0f, 0.0f, 1.0f,
		10.0f,  -1430.0f, 800.0f, 1.0f,  1.0f, 0.7f, 0.2f,  0.0f, 0.0f, 1.0f,
		10.0f,  -1430.0f, 900.0f, 1.0f,  1.0f, 0.7f, 0.2f,  0.0f, 0.0f, 1.0f,
		-10.0f,  -1430.0f, 900.0f, 1.0f,  1.0f, 0.7f, 0.2f,  0.0f, 0.0f, 1.0f
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
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (GLvoid*)0);
	// atributul 1 = culoare
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
	// atributul 2 = normale
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
}

void ClockLine2::draw(GLuint& VaoId, GLuint codCol, GLuint matrixLocation, GLuint codColLocation, float counter) {
	glBindVertexArray(VaoId);
	glUniform1i(codColLocation, codCol);
	const float PI = 3.141592;
	glm::mat4 myMatrix = glm::mat4(1.0f);

	float CLOCK_HOUR = 6.27f;
	time_t now = time(0);
	tm* ltm = localtime(&now);

	myMatrix = glm::translate(myMatrix, glm::vec3(0.0f, 0.0f, 800.0f));
	myMatrix = glm::rotate(myMatrix, (12 - ltm->tm_hour) * (CLOCK_HOUR / 12) - (CLOCK_HOUR / 12 / 60)*ltm->tm_min, glm::vec3(0.0f, 1.0f, 0.0f));
	myMatrix = glm::translate(myMatrix, glm::vec3(0.0f, 0.0f, -800.0f));
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}