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

private:
	void checkCompileError(unsigned int object, std::string type);
	GLuint getUniformLocation(std::string name);
	void compile(const char* vertexCode, const char* fragmentCode, const char* geometryCode = nullptr);
};

#endif