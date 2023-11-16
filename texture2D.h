#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <glad/glad.h>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture2D {
private:
	int width, height, nbChannels;
	unsigned int texture;

public:
	Texture2D(const char* path, bool flip = false, bool isRGBA = false, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, GLint minFilter = GL_NEAREST_MIPMAP_NEAREST, GLint magFilter = GL_NEAREST);

	void use() {
		glBindTexture(GL_TEXTURE_2D, texture);
	};

	void setWrapS(GLint param) {
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param);
		glBindTexture(GL_TEXTURE_2D, 0);
	};

	void setWrapT(GLint param) {
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param);
		glBindTexture(GL_TEXTURE_2D, 0);
	};

	void setMinFilter(GLint param) {
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
		glBindTexture(GL_TEXTURE_2D, 0);
	};

	void setMagFilter(GLint param) {
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
		glBindTexture(GL_TEXTURE_2D, 0);
	};
};
#endif