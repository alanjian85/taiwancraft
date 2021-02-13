#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "Shader.h"
#include "Player.h"
#include "Time.h"
#include "Cube.h"

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

	glEnable(GL_DEPTH_TEST);

	Shader::loadShader("cube", ASSETS_DIR"shaders/cube.vert", ASSETS_DIR"shaders/cube.frag");
	Drawable::addDrawable<Cube>("cube");

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		Time::update();

		handleFrameEvent(window);

		Shader::getShader("cube").set("cameraMatrix", player.getCameraMatrix());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Shader::getShader("cube").bind();
		Drawable::getDrawable("cube").render();
		
		glfwSwapBuffers(window);
	}
	
	glfwTerminate();
	return 0;
}