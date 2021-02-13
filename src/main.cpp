#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "Shader.h"
#include "Player.h"
#include "Time.h"
#include "Cube.h"
#include "Texture2D.h"

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

void resizeEvent(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	player.onResizeEvent(width, height);
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
	glfwSetWindowSizeCallback(window, resizeEvent);

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glEnable(GL_DEPTH_TEST);

	Shader::loadShader("cube", ASSETS_DIR"shaders/cube.vert", ASSETS_DIR"shaders/cube.frag");
	Drawable::addDrawable<Cube>("cube");
	Texture2D::loadTexture("dirt", ASSETS_DIR"textures/dirt.png", GL_NEAREST);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		Time::update();

		handleFrameEvent(window);

		Texture2D::getTexture("dirt").bind(0);
		Shader::getShader("cube").set("dirt", 0)
								 .set("cameraMatrix", player.getCameraMatrix());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Shader::getShader("cube").bind();
		Drawable::getDrawable("cube").render();
		
		glfwSwapBuffers(window);
	}
	
	glfwTerminate();
	return 0;
}