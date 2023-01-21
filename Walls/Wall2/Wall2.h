class Wall2
{
public:

	GLuint VaoId, VboId, EboId;

	Wall2();
	void CreateVBO(GLuint& VaoId, GLuint& VboId, GLuint& EboId);
	void draw(GLuint ProgramId, GLuint& VaoId, GLuint codCol, GLuint matrixLocation, GLuint codColLocation);

};

