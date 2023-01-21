class Wall
{
public:

	GLuint VaoId, VboId, EboId;

	Wall();
	void CreateVBO(GLuint& VaoId, GLuint& VboId, GLuint& EboId);
	void draw(GLuint ProgramId, GLuint& VaoId ,GLuint codCol, GLuint matrixLocation, GLuint codColLocation);

};

