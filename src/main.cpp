#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Camera.h"

#define SHADERS_DIR ASSETS_DIR"shaders/"

static Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), -90.0f, 0.0f, 0.0f, 45.0f, 800, 600, 0.1f, 100.0f);

void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
	const float CAMERA_SENSITIVITY = 0.1f;
	
	static double lastx = xpos, lasty = ypos;
	
	double deltax = xpos - lastx, deltay = lasty - ypos;

	camera.setYaw(camera.getYaw() + float(deltax) * CAMERA_SENSITIVITY)
		  .setPitch(camera.getPitch() + float(deltay) * CAMERA_SENSITIVITY);

	lastx = xpos; lasty = ypos;

	camera.setPitch(glm::clamp(camera.getPitch(), -89.0f, 89.0f));
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Taiwancraft", nullptr, nullptr);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, cursorCallback);
	GLFWimage icon;
	icon.pixels = stbi_load(ASSETS_DIR"icon.png", &icon.width, &icon.height, nullptr, 4);
	glfwSetWindowIcon(window, 1, &icon);
	stbi_image_free(icon.pixels);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	const GLfloat vertices[] = {
		-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 
		 0.0f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f
	};
	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, reinterpret_cast<void*>(sizeof(GLfloat) * 0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, reinterpret_cast<void*>(sizeof(GLfloat) * 2));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	Shader shader(SHADERS_DIR"shader.vert", SHADERS_DIR"shader.frag");
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		shader.use();
		shader.set("viewMatrix", camera.getViewMatrix());
		shader.set("projectionMatrix", camera.getProjectionMatrix());
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}