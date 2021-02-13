#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "Shader.h"
#include "Player.h"
#include "Time.h"

static int screenWidth = 800, screenHeight = 600;
static Player player(glm::vec3(0.0f, 0.0f, 3.0f), 2.5f, 0.1f, screenWidth, screenHeight);

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	player.onCursorMove(int(xpos), int(ypos));
}

void handleFrameEvent(GLFWwindow* window)
{
	player.onFrameEvent(window);
}

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "Test", nullptr, nullptr);
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, cursorPosCallback);

	glfwMakeContextCurrent(window);
	gladLoadGL();

	Shader::loadShader("triangle", ASSETS_DIR"shaders/triangle.vert", ASSETS_DIR"shaders/triangle.frag");

	const GLfloat triangleVertices[] = {
	//	position	   color
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
	};

	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, reinterpret_cast<void*>(sizeof(GLfloat) * 0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, reinterpret_cast<void*>(sizeof(GLfloat) * 3));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		Time::update();

		handleFrameEvent(window);

		Shader::getShader("triangle").set("cameraMatrix", player.getCameraMatrix());

		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		Shader::getShader("triangle").bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(window);
	}
	
	glfwTerminate();
	return 0;
}