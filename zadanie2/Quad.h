#ifndef _QUAD_H_
#define _QUAD_H_

#include "Includes.h"

#include "Shader.h"
#include "Texture.h"

class Quad
{
private:
	std::vector<glm::vec3> vertices;
	GLuint vbo;
	GLuint vao;

	ShaderProgram shaderProgram;
	Texture *texture;

public:
	Quad();
	void setup(glm::vec2 size, ShaderProgram shader, Texture* texture);
	void draw();
	~Quad();
};

#endif