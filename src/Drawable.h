#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Buffers.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

class Drawable {
protected:
	GLuint m_Vao, m_Vbo, m_Ebo;
	
	GLsizei m_NumIndex;
private:
	static std::unordered_map<std::string, Drawable*> drawables;
public:
	Drawable();

	void render()
	{
		glBindVertexArray(m_Vao);
		glDrawElements(GL_TRIANGLES, m_NumIndex, GL_UNSIGNED_INT, reinterpret_cast<void*>(0));
	}

	static Drawable& getDrawable(std::string name)
	{
		return *drawables[name];
	}

	template<typename T>
	static void addDrawable(std::string name)
	{
		drawables[name] = new T;
	}
};

#endif