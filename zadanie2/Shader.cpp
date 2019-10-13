#include "Shader.h"


void Shader::readShaderFromFile(std::string file, GLuint shader)
{
	std::ifstream fileStream(file.c_str());
	if (fileStream.good())
	{
		std::stringstream content;
		content << fileStream.rdbuf();
		int len = std::strlen(content.str().c_str());
		char* fileBuffer = new char[len+1];
		strcpy_s(fileBuffer, len+1, content.str().c_str());
		glShaderSource(shader, 1, &fileBuffer, 0);
		fileStream.close();
	}
	else {
		std::cout << "Error, file not found" << std::endl;
	}
}

Shader::Shader() {

}

Shader::Shader( std::string vFile, std::string fFile)
{
	initialize( vFile, fFile);
}

void Shader::initialize( std::string vFile, std::string fFile)
{
	GLuint vShader = glCreateShader( GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader( GL_FRAGMENT_SHADER);

	readShaderFromFile(vFile, vShader);
	readShaderFromFile(fFile, fShader);

	GLint compile_status = GL_FALSE;
	int infoLogLength;

	glCompileShader( vShader);
	glGetShaderiv( vShader, GL_COMPILE_STATUS, &compile_status);
	glGetShaderiv( vShader, GL_INFO_LOG_LENGTH, &infoLogLength);
	char *vShaderLog = new char[infoLogLength];
	glGetShaderInfoLog( vShader, infoLogLength, NULL, vShaderLog);

	if(compile_status == GL_TRUE) {

		std::cout << vFile << ": Shader compiled!" << std::endl;
	}
	else {
		std::cout << vShaderLog << " : " << vFile << std::endl;;
	}

	compile_status = GL_FALSE;
	infoLogLength = 0;

	glCompileShader( fShader);
	glGetShaderiv( fShader, GL_COMPILE_STATUS, &compile_status);
	glGetShaderiv( fShader, GL_INFO_LOG_LENGTH, &infoLogLength);
	char *fShaderLog = new char[infoLogLength];
	glGetShaderInfoLog( fShader, infoLogLength, NULL, fShaderLog);
	if (compile_status == GL_TRUE) {

		std::cout << fFile << ": Shader compiled!" << std::endl;
	}
	else {
		std::cout << fShaderLog << " : " << fFile << std::endl;;
	}

	delete vShaderLog;
	delete fShaderLog;

	shaderProgram = glCreateProgram();

	glAttachShader( shaderProgram, vShader);
	glAttachShader( shaderProgram, fShader);
	glLinkProgram(shaderProgram);

}

ShaderProgram Shader::getShaderProgram() {
	return ShaderProgram(shaderProgram);
}

void Shader::bind()
{
	glUseProgram(shaderProgram);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Uniforms::sendUniform1i(ShaderProgram shaderProgram, std::string name, int variable)
{
	glUniform1i(glGetUniformLocation(shaderProgram.getID(), name.c_str()), variable);
}

void Uniforms::sendUniform1f(ShaderProgram shaderProgram, std::string name, float variable)
{
	glUniform1f(glGetUniformLocation(shaderProgram.getID(), name.c_str()), variable);
}

void Uniforms::sendUniform3fv(ShaderProgram shaderProgram, std::string name, glm::vec3 variable)
{
	glUniform3fv(glGetUniformLocation(shaderProgram.getID(), name.c_str()), 1, &variable[0]);
}

void Uniforms::sendUniform4fv(ShaderProgram shaderProgram, std::string name, glm::mat4 variable)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getID(), name.c_str()), 1, GL_FALSE, &variable[0][0]);
}

void Uniforms::sendMVP(ShaderProgram shaderProgram, glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	shaderProgram.bind();
	sendUniform4fv(shaderProgram, "modelMatrix", model);
	sendUniform4fv(shaderProgram, "viewMatrix", view);
	sendUniform4fv(shaderProgram, "projectionMatrix", projection);
	shaderProgram.unbind();
}

Shader::~Shader()
{
	glDeleteShader(shaderProgram);
}
