#ifndef MESH_H
#define MESH_H

#include <vector>
#include <map>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "Shader.h"

class Mesh {
public:
	struct Vertex;
	enum class TextureType;
private:
	std::vector<std::pair<Texture, TextureType>> m_Textures;
	GLuint m_Vao;
	GLsizei m_NumIndices;
	void genMeshHelper(std::vector<Vertex> vertices, std::vector<GLuint> indices) {
		GLuint vbo, ebo;

		glGenVertexArrays(1, &m_Vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(m_Vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}
public:
	enum class TextureType {
		DIFFUSE,
		SPECULAR
	};
	
	struct Vertex {
		glm::vec3 position;
		glm::vec2 uv;
	};

	Mesh(std::vector<Vertex> vertices,
		 std::vector<GLuint> indices,
		 std::vector<std::pair<Texture, TextureType>> textures) 
		 : m_Textures(textures) {
		m_NumIndices = indices.size();
		genMeshHelper(vertices, indices);
	}

	Mesh(std::vector<Vertex> vertices,
		 std::vector<std::pair<Texture, TextureType>> textures)
		 : m_Textures(textures) {
		m_NumIndices = vertices.size();
		std::vector<GLuint> indices;
		for (GLuint i = 0; i < vertices.size(); ++i)
			indices.push_back(i);
		genMeshHelper(vertices, indices);
	}

	void draw(Shader shader)
	{
		std::map<std::string, int> textureCount;
		for (int i = 0; i < m_Textures.size(); ++i) {
			std::string type;
			switch (m_Textures[i].second) {
			case TextureType::DIFFUSE: type = "diffuse"; break;
			case TextureType::SPECULAR: type = "specular"; break;
			}
			glActiveTexture(GL_TEXTURE0 + i);
			m_Textures[i].first.bind();
			shader.set(type + std::to_string(++textureCount[type]), i);
		}
		shader.use();
		glBindVertexArray(m_Vao);
		glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, reinterpret_cast<void*>(0));
	}
};

#endif