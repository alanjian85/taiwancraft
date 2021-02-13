#ifndef BUFFERS_H
#define BUFFERS_H

#include "glad/glad.h"

class VertexBuffer
{
public:
	VertexBuffer(float* vertices, GLuint size);
	~VertexBuffer();

	void bind() const;
	void unBind() const;

private:
	GLuint m_Id;
};

class IndexBuffer
{
public:
	IndexBuffer(GLuint* indices, int count);
	~IndexBuffer();

	void bind() const;
	void unBind() const;
private:
	GLuint m_Id;
};

#endif
