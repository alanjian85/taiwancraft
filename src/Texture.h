#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <iostream>

#include <stb_image.h>
#include <glad/glad.h>

class Texture {
public:
	enum class MagFilter : GLenum;
	enum class MinFilter : GLenum;
	enum class Wrap : GLenum;
private:
	GLuint m_Id;

	bool isMipmap(MinFilter filter) {
		if (filter == MinFilter::LINEAR_MIPMAP_LINEAR || filter == MinFilter::LINEAR_MIPMAP_NEAREST ||
			filter == MinFilter::NEAREST_MIPMAP_LINEAR || filter == MinFilter::NEAREST_MIPMAP_NEAREST)
			return true;
		else 
			return false;
	}
public:
	enum class MagFilter : GLenum {
		LINEAR = GL_LINEAR,
		NEAREST = GL_NEAREST,
	};

	enum class MinFilter : GLenum {
		LINEAR = GL_LINEAR,
		NEAREST = GL_NEAREST,
		LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
		LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
		NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST
	};

	enum class Wrap : GLenum {
		REPEAT = GL_REPEAT,
		MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
		CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
	};

	Texture(std::string path, MinFilter minFilter = MinFilter::LINEAR, 
			MagFilter magFilter = MagFilter::LINEAR, Wrap wrapS = Wrap::REPEAT, 
			Wrap wrapT = Wrap::REPEAT) {
		stbi_set_flip_vertically_on_load(true);
		glGenTextures(1, &m_Id);
		int width, height, channel;
		unsigned char* image = stbi_load(path.c_str(), &width, &height, &channel, 0);
		if (image) {
			GLenum format = GL_RED;
			switch (channel) {
			case 1: format = GL_RED; break;
			case 3: format = GL_RGB; break;
			case 4: format = GL_RGBA; break;
			}
			glBindTexture(GL_TEXTURE_2D, m_Id);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(minFilter));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(magFilter));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLenum>(wrapS));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLenum>(wrapT));
			if (isMipmap(minFilter)) glGenerateMipmap(GL_TEXTURE_2D);
		}

	}
	void bind() const { glBindTexture(GL_TEXTURE_2D, m_Id); }
	
	void setMinFilter(MinFilter filter) {
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(filter));
		if (isMipmap(filter)) glGenerateMipmap(GL_TEXTURE_2D);
	}

	void setMagFilter(MagFilter filter) {
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(filter));
	}

	void setWrapS(Wrap wrap) {
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLenum>(wrap));
	}

	void setWrapT(Wrap wrap) {
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLenum>(wrap));
	}
};

#endif