#ifndef CUBE_H
#define CUBE_H

#include "Drawable.h"
#include "Buffers.h"
#include "VertexArray.h"

class Cube : public Drawable {
public:
	Cube() : Drawable()
	{
		float vertices[] = {
		//	positions			   normal				//uv
			//front
            -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  1.0f, 0.0f,

			//back
			-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  1.0f, 0.0f,

			//right
			 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			//left
			-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			//up
			-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  1.0f, 0.0f,

			//bottom
			-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  1.0f, 0.0f
		};										  

		const GLuint indices[] = {
			//front
			 2,  0,  1,
			 3,  2,  1,
			//back 
			 6,  5,  4,
			 7,  5,  6,
			//right
			10,  8, 9,
			11, 10, 9,
			//left
			14, 13, 12,
			15, 13, 14,
			//up
			17, 16, 18,
			17, 18, 19,
			//bottom
			20, 21, 22,
			22, 21, 23
		};
		
		VertexArray vertexArray;
		BufferObject vertexBuffer(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
		//BufferObject indexBuffer(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));

		VertexBufferLayout layout;

		// in vertices 
		// |       position   |  |      normal      | |   uv     |
		// -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
		//          3 float              3 float          2 float
		layout.push<float>(3); // position
		layout.push<float>(3); // normal
		layout.push<float>(2); // uv

		//vertexArray.addBuffer(vertexBuffer, indexBuffer, layout);

		// Draw
		vertexArray.bind();
		//indexBuffer.bind();


		m_NumIndex = sizeof(indices) / sizeof(GLuint);
	}
};

#endif