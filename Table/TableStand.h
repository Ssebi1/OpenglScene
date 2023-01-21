class TableStand
{
public:

	GLuint VaoId, VboId, EboId;

	TableStand();
	void CreateVBO(GLuint& VaoId, GLuint& VboId, GLuint& EboId);
	void draw(GLuint& VaoId, GLuint codCol, GLuint matrixLocation, GLuint codColLocation, glm::vec3 translation, glm::vec3 scale);

};

