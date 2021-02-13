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
	std::unordered_map<std::string, GLuint> m_UniformLocationCache;

public:
	void bind() const;

	//scalar
	void set(std::string name, GLint value) { glProgramUniform1i(m_Id, getUniformLocation(name), value); }
	void set(std::string name, GLuint value) { glProgramUniform1ui(m_Id, getUniformLocation(name), value); }
	void set(std::string name, bool value) { glProgramUniform1i(m_Id, getUniformLocation(name), value); }
	void set(std::string name, GLfloat value) { glProgramUniform1f(m_Id, getUniformLocation(name), value); }
	void set(std::string name, GLdouble value) { glProgramUniform1d(m_Id, getUniformLocation(name), value); }
	//vector
	void set(std::string name, glm::ivec2 value) { glProgramUniform2iv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); }
	void set(std::string name, glm::ivec3 value) { glProgramUniform3iv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); }
	void set(std::string name, glm::ivec4 value) { glProgramUniform4iv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); }
	void set(std::string name, glm::uvec2 value) { glProgramUniform2uiv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); }
	void set(std::string name, glm::uvec3 value) { glProgramUniform3uiv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); }
	void set(std::string name, glm::uvec4 value) { glProgramUniform4uiv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); }
	void set(std::string name, glm::vec2 value) { glProgramUniform2fv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); }
	void set(std::string name, glm::vec3 value) { glProgramUniform3fv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); }
	void set(std::string name, glm::vec4 value) { glProgramUniform4fv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); }
	void set(std::string name, glm::dvec2 value) { glProgramUniform2dv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); }
	void set(std::string name, glm::dvec3 value) { glProgramUniform3dv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); }
	void set(std::string name, glm::dvec4 value) { glProgramUniform4dv(m_Id, getUniformLocation(name), 1, glm::value_ptr(value)); }
	//matrix
	void set(std::string name, glm::mat2 value) { glProgramUniformMatrix2fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); }
	void set(std::string name, glm::mat3 value) { glProgramUniformMatrix3fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); }
	void set(std::string name, glm::mat4 value) { glProgramUniformMatrix4fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); }
	void set(std::string name, glm::mat2x3 value) { glProgramUniformMatrix2x3fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); }
	void set(std::string name, glm::mat2x4 value) { glProgramUniformMatrix2x4fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); }
	void set(std::string name, glm::mat3x2 value) { glProgramUniformMatrix3x2fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); }
	void set(std::string name, glm::mat3x4 value) { glProgramUniformMatrix3x4fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); }
	void set(std::string name, glm::mat4x2 value) { glProgramUniformMatrix4x2fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); }
	void set(std::string name, glm::mat4x3 value) { glProgramUniformMatrix4x3fv(m_Id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); }

private:
	void checkCompileError(unsigned int object, std::string type);
	GLuint getUniformLocation(std::string name);
	void compile(const char* vertexCode, const char* fragmentCode, const char* geometryCode = nullptr);
};

#endif