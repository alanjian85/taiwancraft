#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow *window = glfwCreateWindow(800, 600, "Test", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}