#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>
#include <vector>
#include <string>

class Shader {
public:
	static void loadShader(std::string name, std::string vertFile, std::string fragFile, std::string geomeFilePath = "");
	static Shader& getShader(std::string name);

	static std::unordered_map<std::string, Shader> Shaders;

private:
	GLuint m_Id;
	mutable std::unordered_map<std::string, GLuint> m_UniformLocationCache;

public:
	void bind() const;

	//scalar
	Shader set(std::string name, GLint value) const { glProgramUniform1i(m_Id, getUniformLocation(name), value); return *this; }
	Shader set(std::string name, GLuint value) const { glProgramUniform1ui(m_Id, getUniformLocation(name), value); return *this; }
	Shader set(std::string name, bool value) const { glProgramUniform1i(m_Id, getUniformLocation(name), value); return *this; }
	Shader set(std::string name, GLfloat value) const { glProgramUniform1f(m_Id, getUniformLocation(name), value); return *this; }
	Shader set(std::string name, GLdouble value) const { glProgramUniform1d(m_Id, getUniformLocation(name), value); return *this; }
	//vector
	Shader set(std::string name, glm::ivec2 value) const { glProgramUniform2iv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::ivec3 value) const { glProgramUniform3iv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::ivec4 value) const { glProgramUniform4iv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::uvec2 value) const { glProgramUniform2uiv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::uvec3 value) const { glProgramUniform3uiv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::uvec4 value) const { glProgramUniform4uiv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::vec2 value) const { glProgramUniform2fv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::vec3 value) const { glProgramUniform3fv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::vec4 value) const { glProgramUniform4fv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::dvec2 value) const { glProgramUniform2dv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::dvec3 value) const { glProgramUniform3dv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::dvec4 value) const { glProgramUniform4dv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); return *this; }
	//matrix
	Shader set(std::string name, glm::mat2 value) const { glProgramUniformMatrix2fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::mat3 value) const { glProgramUniformMatrix3fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::mat4 value) const { glProgramUniformMatrix4fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::mat2x3 value) const { glProgramUniformMatrix2x3fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::mat2x4 value) const { glProgramUniformMatrix2x4fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::mat3x2 value) const { glProgramUniformMatrix3x2fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::mat3x4 value) const { glProgramUniformMatrix3x4fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::mat4x2 value) const { glProgramUniformMatrix4x2fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); return *this; }
	Shader set(std::string name, glm::mat4x3 value) const { glProgramUniformMatrix4x3fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); return *this; }

private:
	void checkCompileError(unsigned int object, std::string type);
	GLuint getUniformLocation(std::string name) const;
	void compile(const char* vertexCode, const char* fragmentCode, const char* geometryCode = nullptr);
};

#endif