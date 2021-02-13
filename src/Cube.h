#ifndef CUBE_H
#define CUBE_H

#include "Drawable.h"

class Cube : public Drawable {
public:
	Cube() : Drawable()
	{
		const GLfloat vertices[] = {
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
			 0,  1,  2,
			 1,  2,  3,
			//back 
			 4,  5,  6,
			 5,  6,  7,
			//right
			 8,  9, 10,
			 9, 10, 11,
			//left
			12, 13, 14,
			13, 14, 15,
			//up
			16, 17, 18,
			17, 18, 19,
			//bottom
			20, 21, 22,
			21, 22, 23
		};


		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		m_NumIndex = 36;
	}
};

#endif