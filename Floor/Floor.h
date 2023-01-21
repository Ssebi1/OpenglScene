class Floor
{
public:

	GLuint VaoId, VboId, EboId;

	Floor();
	void CreateVBO(GLuint &VaoId, GLuint &VboId, GLuint &EboId);
	void draw(GLuint& VaoId, GLuint codCol, GLuint matrixLocation, GLuint codColLocation);

};

