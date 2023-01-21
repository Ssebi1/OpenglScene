class WallBorder2
{
public:

	GLuint VaoId, VboId, EboId;

	WallBorder2();
	void CreateVBO(GLuint& VaoId, GLuint& VboId, GLuint& EboId);
	void draw(GLuint& VaoId, GLuint codCol, GLuint matrixLocation, GLuint codColLocation);

};

