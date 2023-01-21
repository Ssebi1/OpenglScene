class ClockFront1
{
public:

	GLuint VaoId, VboId, EboId;

	ClockFront1();
	void CreateVBO(GLuint& VaoId, GLuint& VboId, GLuint& EboId);
	void draw(GLuint ProgramId, GLuint& VaoId, GLuint codCol, GLuint matrixLocation, GLuint codColLocation);

};

