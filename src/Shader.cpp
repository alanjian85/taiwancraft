#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::unordered_map<std::string, Shader> Shader::Shaders;

void Shader::loadShader(const char* name, const char* vertFilePath, const char* fragFilePath, const char* geomeFilePath)
{
	std::string vertCode, fragCode, geomeCode;
	try
	{
		std::ifstream vertexFile(vertFilePath);
		std::ifstream fragmentFile(fragFilePath);

		std::stringstream vShaderStream, fShaderStream, gShaderStream;
		vShaderStream << vertexFile.rdbuf();
		fShaderStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();
		
		vertCode = vShaderStream.str();
		fragCode = fShaderStream.str();

		if (geomeFilePath != nullptr)
		{
			std::ifstream geometryFile(geomeFilePath);
			gShaderStream << geometryFile.rdbuf();
			geometryFile.close();
			geomeCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "Load Shader Failed ! " << std::endl;
	}

	Shader shader;
	shader.compile(vertCode.c_str(), fragCode.c_str(), geomeCode.c_str());
	Shaders[name] = shader;
}

Shader& Shader::getShader(const char* name)
{
	return Shader::Shaders[name];
}

void Shader::bind() const
{
	glUseProgram(this->m_Id);
}

void Shader::unBind() const
{
	glUseProgram(0);
}

void Shader::compile(const char* vertexCode, const char* fragmentCode, const char* geometryCode)
{
	unsigned int sVertex, sFragment, sGeometry;

	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexCode, NULL);
	glCompileShader(sVertex);
	checkCompileError(sVertex, "VERTEX");

	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentCode, NULL);
	glCompileShader(sFragment);
	checkCompileError(sFragment, "FRAGMENT");

	if (geometryCode != nullptr)
	{
		sGeometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(sGeometry, 1, &geometryCode, NULL);
		glCompileShader(sGeometry);
		checkCompileError(sGeometry, "GEOMETRY");
	}

	this->m_Id = glCreateProgram();
	glAttachShader(this->m_Id, sVertex);
	glAttachShader(this->m_Id, sFragment);
	glLinkProgram(this->m_Id);
	checkCompileError(this->m_Id, "PROGRAM");

	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
}

void Shader::checkCompileError(unsigned int object, std::string type)
{
	int success;
	char infoLog[1024];
	if (type == "PROGRAM")
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}

GLuint Shader::getUniformLocation(std::string name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	
	GLuint location = glGetUniformLocation(m_Id, name.c_str());
	m_UniformLocationCache[name] = location;
	return location;
}
