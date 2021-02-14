#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
private:
	GLuint m_Id;
public:
	Shader(std::string vertexPath, std::string fragmentPath)
	{
		std::ifstream vertexFile(vertexPath), fragmentFile(fragmentPath);
		std::ostringstream vertexStream, fragmentStream;
		std::string vertexString, fragmentString;
		const char* vertexCString, * fragmentCString;
		
		if (vertexFile.fail() || vertexFile.bad()) 
			std::cerr << "[ERROR] Failed to load vertex shader at " << vertexPath << '\n';
		vertexStream << vertexFile.rdbuf();
		vertexString = vertexStream.str();
		vertexCString = vertexString.c_str();

		if (fragmentFile.fail() || fragmentFile.bad())
			std::cerr << "[ERROR] Failed to load fragment shader at " << fragmentPath << '\n';
		fragmentStream << fragmentFile.rdbuf();
		fragmentString = fragmentStream.str();
		fragmentCString = fragmentString.c_str();

		GLint status;
		GLchar infoLog[512];

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexCString, nullptr);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
		if (!status) {
			glGetShaderInfoLog(vertexShader, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "[ERROR] Failed to compile vertex shader\n" << infoLog << '\n';
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentCString, nullptr);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
		if (!status) {
			glGetShaderInfoLog(fragmentShader, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "[ERROR] Failed to compile fragment shader\n" << infoLog << '\n';
		}

		m_Id = glCreateProgram();
		glAttachShader(m_Id, vertexShader);
		glAttachShader(m_Id, fragmentShader);
		glLinkProgram(m_Id);
		glGetProgramiv(m_Id, GL_LINK_STATUS, &status);
		if (!status) {
			glGetProgramInfoLog(m_Id, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "[ERROR] Failed to link shader program\n" << infoLog << '\n';
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void use() const { glUseProgram(m_Id); }

	void set(std::string name, glm::mat4 value) { 
		glProgramUniformMatrix4fv(m_Id, glGetUniformLocation(m_Id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
};

#endif