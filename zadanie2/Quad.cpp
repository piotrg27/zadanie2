#include "Quad.h"

Quad::Quad()
{
}

void Quad::setup(glm::vec2 size, ShaderProgram shader, Texture *texture)
{
	this->texture = texture;
	shaderProgram = shader;

	vertices.push_back(glm::vec3(-1, -1, 0));
	vertices.push_back(glm::vec3(-1, 1, 0));
	vertices.push_back(glm::vec3(1, 1, 0));

	vertices.push_back(glm::vec3(1, 1, 0));
	vertices.push_back(glm::vec3(1, -1, 0));
	vertices.push_back(glm::vec3(-1, -1, 0));

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Quad::draw()
{
	glUseProgram(shaderProgram.getID());
	texture->bind();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}

Quad::~Quad()
{
}
