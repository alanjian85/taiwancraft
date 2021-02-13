#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_Id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_Id);
}

void VertexArray::addBufferHelper(const VertexBufferLayout& layout)
{
	const auto& elements = layout.getElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
}

void VertexArray::addBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout)
{
	bind();
	vbo.bind();
	addBufferHelper(layout);
}

void VertexArray::addBuffer(const VertexBuffer& vbo, const IndexBuffer& ibo, const VertexBufferLayout& layout)
{
	bind();
	vbo.bind();
	ibo.bind();
	addBufferHelper(layout);
}

void VertexArray::bind() const
{
	glBindVertexArray(m_Id);
}

void VertexArray::unBind() const
{
	glBindVertexArray(0);
}