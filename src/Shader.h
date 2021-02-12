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
public:
	void bind() const;
	void unBind() const;
	void compile(const char* vertexCode, const char* fragmentCode, const char* geometryCode = nullptr);

private:
	GLuint m_Id;
	void checkCompileError(unsigned int object, std::string type);
	GLuint getUniformLocation(std::string name);

	std::unordered_map<std::string, GLuint> m_UniformLocationCache;
};

#endif