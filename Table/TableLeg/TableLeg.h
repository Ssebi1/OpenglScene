class TableLeg
{
public:

	GLuint VaoId, VboId, EboId;

	TableLeg();
	void CreateVBO(GLuint& VaoId, GLuint& VboId, GLuint& EboId);
	void draw(GLuint& VaoId, GLuint codCol, GLuint matrixLocation, GLuint codColLocation, glm::vec3 translation, glm::vec3 scale);

};

