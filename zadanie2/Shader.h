#ifndef _SHADER_H_
#define _SHADER_H_

#include "Includes.h"

class ShaderProgram
{
public:
	ShaderProgram() { id = 0; }
	ShaderProgram(int sProgram) { id = sProgram; }
	GLuint getID() { return id; }
	void bind() { glUseProgram(id); }
	void unbind() { glUseProgram(0); }
private:
	GLuint id;
};

namespace Uniforms {
	void sendUniform1i(ShaderProgram shaderProgram, std::string name, int variable);
	void sendUniform1f(ShaderProgram shaderProgram, std::string name, float variable);
	void sendUniform3fv(ShaderProgram shaderProgram, std::string name, glm::vec3 variable);
	void sendUniform4fv(ShaderProgram shaderProgram, std::string name, glm::mat4 variable);
	void sendMVP(ShaderProgram shaderProgram, glm::mat4 model, glm::mat4 view, glm::mat4 projection);
}

class Shader
{
private:
	void readShaderFromFile( std::string file, GLuint shader);
	GLuint shaderProgram;
public:
	Shader();
	Shader(std::string vFile, std::string fFile);

	void initialize(std::string vFile, std::string fFile);
	void bind();
	void unbind();
	ShaderProgram getShaderProgram();
	~Shader();
};

#endif
