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
#include "ClockFront1.h"


const int NR_POINTS = 50;
const float PI = 3.141592f;
float cx = 0.0f, cy = 0.0f, radius = 200.0; // elemente pentru cerc: centru, raza

ClockFront1::ClockFront1() {}


void ClockFront1::CreateVBO(GLuint& VaoId, GLuint& VboId, GLuint& EboId)
{
	//coordonatele varfurilor
	glm::vec4 vf_coord[NR_POINTS];
	for (int i = 0; i < NR_POINTS; i++) // sunt NR_POINTS varfuri
	{
		// se foloseste reprezentarea parametrica pentru a genera varfurile (puncte situate pe cerc)
		vf_coord[i] =
			glm::vec4(
				cx + radius * cos(2 * PI * i / NR_POINTS),
				0.0f,
				cy + radius * sin(2 * PI * i / NR_POINTS),
				1.0f);
	};

	// culorile varfurilor
	glm::vec4 vf_col[NR_POINTS];
	for (int i = 0; i < NR_POINTS; i++)
	{
		vf_col[i] = glm::vec4(
			0.15f, 0.15f, 0.15f, 1.0f);
	};

	// indicii
	GLuint vf_ind[NR_POINTS + 3 * (NR_POINTS - 2)]; // NR_POINTS(contur) + 3 * (NR_POINTS - 2)(triunghiuri)
	// indexare pentru trasarea conturului
	for (int i = 0; i < NR_POINTS; i++) // primii NR_POINTS(=N) indici corespund varfurilor
		vf_ind[i] = i;
	// indexare pentru desenarea interiorului; grupuri de cate trei, 
	// pentru triunghiul i sunt folosite varfurile (0, i+1, i+2) sunt alocati indicii N+3*i, N+3*i+1, N+3*i+2
	for (int i = 0; i < NR_POINTS - 2; i++)
	{
		vf_ind[NR_POINTS + 3 * i] = 0;
		vf_ind[NR_POINTS + 3 * i + 1] = i + 1;
		vf_ind[NR_POINTS + 3 * i + 2] = i + 2;
	}

	// se creeaza un buffer nou pentru varfuri
	glGenBuffers(1, &VboId);
	// buffer pentru indici
	glGenBuffers(1, &EboId);
	// se creeaza / se leaga un VAO (Vertex Array Object)
	glGenVertexArrays(1, &VaoId);

	// legare VAO
	glBindVertexArray(VaoId);

	// buffer-ul este setat ca buffer curent
	glBindBuffer(GL_ARRAY_BUFFER, VboId);

	// buffer-ul va contine atat coordonatele varfurilor, cat si datele de culoare
	glBufferData(GL_ARRAY_BUFFER, sizeof(vf_coord) + sizeof(vf_col), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vf_coord), vf_coord);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vf_coord), sizeof(vf_col), vf_col);

	// buffer-ul pentru indici
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vf_ind), vf_ind, GL_STATIC_DRAW);

	// se activeaza lucrul cu atribute; atributul 0 = pozitie, atributul 1 = culoare, acestea sunt indicate corect in VBO
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(vf_coord));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void ClockFront1::draw(GLuint ProgramId, GLuint& VaoId, GLuint codCol, GLuint matrixLocation, GLuint codColLocation) {
	glBindVertexArray(VaoId);
	glUniform1i(codColLocation, codCol);
	glm::mat4 myMatrix = glm::mat4(1.0f);
	myMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1450.0f, 800.0f));
	glUniformMatrix4fv(glGetUniformLocation(ProgramId, "myMatrix"), 1, GL_FALSE, &myMatrix[0][0]);

	glDrawElements(GL_TRIANGLES,
		3 * (NR_POINTS - 2),
		GL_UNSIGNED_INT,
		(GLvoid*)((NR_POINTS) * sizeof(GLuint)));
}