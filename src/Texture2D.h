#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <unordered_map>

#include <glad/glad.h>
#include <stb_image.h>

class Texture2D {
private:
	GLuint m_Id;
	static std::unordered_map<std::string, Texture2D> textures;
public:
	static Texture2D getTexture(std::string name)
	{
		return textures[name];
	}

	static void loadTexture(std::string name, std::string path, GLuint filterMode)
	{
		Texture2D texture;
		stbi_set_flip_vertically_on_load(true);
		int wm_Idth, height, channel;
		unsigned char* image = stbi_load(path.c_str(), &wm_Idth, &height, &channel, 0);
		glGenTextures(1, &texture.m_Id);
		glBindTexture(GL_TEXTURE_2D, texture.m_Id);
		GLenum format = GL_RED;
		if (channel == 3) format = GL_RGB;
		if (channel == 4) format = GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, wm_Idth, height, 0, format, GL_UNSIGNED_BYTE, image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		textures[name] = texture;
	}

	void bind(GLuint unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_Id);
	}
};

#endif