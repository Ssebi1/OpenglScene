class ClockLine1
{
public:

	GLuint VaoId, VboId, EboId;

	ClockLine1();
	void CreateVBO(GLuint& VaoId, GLuint& VboId, GLuint& EboId);
	void draw(GLuint& VaoId, GLuint codCol, GLuint matrixLocation, GLuint codColLocation);

};

