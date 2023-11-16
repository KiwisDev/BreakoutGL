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
	Texture2D(const char* path, bool flip = false, bool isRGBA = false, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, GLint minFilter = GL_NEAREST_MIPMAP_NEAREST, GLint magFilter = GL_NEAREST) {
		width = 0, height = 0, nbChannels = 0;
		stbi_set_flip_vertically_on_load(flip);
		unsigned char* data = stbi_load(path, &width, &height, &nbChannels, 0);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, (isRGBA) ? GL_RGBA : GL_RGB, width, height, 0, (isRGBA) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "Failed to load texture" << std::endl;
		}

		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);
	};

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