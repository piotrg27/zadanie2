#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Includes.h"

class Texture
{
private:
	unsigned char *data;
	GLuint id;
	glm::vec2 size;
	GLuint framebuffer;
public:
	Texture();
	void create(glm::vec2 size, float *data);
	void create(glm::vec2 size, unsigned char *data);
	void bind();
	glm::vec2 getSize();
	~Texture();
};

#endif // _TEXTURE2D_H_