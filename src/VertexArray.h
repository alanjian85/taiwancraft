#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "Buffers.h"
#include "VertexBufferLayout.h"

#include "glad/glad.h"

#include <vector>

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);
	void addBuffer(const VertexBuffer& vbo, const IndexBuffer& ibo, const VertexBufferLayout& layout);

	void bind() const;
	void unBind() const;

private:
	GLuint m_Id;
	void addBufferHelper(const VertexBufferLayout& layout);
};

class BufferObject {
private:
	GLuint m_Id, m_Target;
public:
	BufferObject(unsigned int target, void* array, size_t size) : m_Target(target)
	{
		glGenBuffers(1, &m_Id);
		glBindBuffer(target, m_Id);
		glBufferData(target, size, array, GL_STATIC_DRAW);
	}

	void bind() const
	{
		glBindBuffer(m_Target, m_Id);
	}
};




// Vertex Buffer Layout

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}

		std::cout << "No Size Type ! " << std::endl;
		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> elements;
	unsigned int m_Stride;

public:
	VertexBufferLayout()
		: m_Stride(0) {}

	inline const std::vector<VertexBufferElement> getElements() const { return elements; }
	inline const unsigned int getStride() const { return m_Stride; }

	template<typename T> void push(unsigned int count) { static_assert(false); }

	template<> inline void push<float>(unsigned int count)
	{
		elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
	}

	template<> inline void push<unsigned int>(unsigned int count)
	{
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
	}

	template<> inline void push<unsigned char>(unsigned int count)
	{
		elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}
};


#endif 