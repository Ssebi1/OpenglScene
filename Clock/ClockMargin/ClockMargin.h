class ClockMargin
{
public:

	GLuint VaoId, VboId, EboId;

	ClockMargin();
	void CreateVBO(GLuint& VaoId, GLuint& VboId, GLuint& EboId);
	void draw(GLuint& VaoId, GLuint codCol, GLuint matrixLocation, GLuint codColLocation, float counter);

};

