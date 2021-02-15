#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Time.h"
#include "EventHandler.h"
#include "Player.h"

#define SHADERS_DIR ASSETS_DIR"shaders/"
#define TEXTURES_DIR ASSETS_DIR"textures/"

class MainEventHandler : public EventHandler {
private:
	void m_OnFrameUpdate(GLFWwindow* window) override {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			player->enabled = false;
		}
	}
	void m_OnMouseButtonPress(GLFWwindow* window, int button, int action, int mods) override {
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			player->justCaptured = true;
			player->enabled = true;
		}
	}
	void m_OnWindowResize(GLFWwindow* window, int width, int height) override {
		glViewport(0, 0, width, height);
		player->screenWidth = width;
		player->screenHeight = height;
	}
public:
	Player* player;
};

int main() {
	const int INITIAL_WINDOW_WIDTH = 800;
	const int INITIAL_WINDOW_HEIGHT = 600;

	MainEventHandler mainEventHandler;
	Player player(glm::vec3(0.0f, 0.0f, 3.0f), -90.0f, 0.0f, 0.0f, 45.0f, INITIAL_WINDOW_WIDTH,  
				  INITIAL_WINDOW_HEIGHT, 0.1f, 100.0f, 5.0f, 0.1f);
	mainEventHandler.player = &player;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Taiwancraft", nullptr, nullptr);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, EventHandler::onCursorPosChange);
	glfwSetMouseButtonCallback(window, EventHandler::onMouseButtonPress);
	glfwSetWindowSizeCallback(window, EventHandler::onWindowResize);
	GLFWimage icon;
	stbi_set_flip_vertically_on_load(false);
	icon.pixels = stbi_load(ASSETS_DIR"icon.png", &icon.width, &icon.height, nullptr, 4);
	glfwSetWindowIcon(window, 1, &icon);
	stbi_image_free(icon.pixels);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	Shader shader(SHADERS_DIR"shader.vert", SHADERS_DIR"shader.frag");
	std::vector<Mesh::Vertex> vertices = {
		Mesh::Vertex{ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f) },
		Mesh::Vertex{ glm::vec3( 0.0f,  0.5f, 0.0f), glm::vec2(0.5f, 1.0f) },
		Mesh::Vertex{ glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f) }
	};
	Mesh triangle(vertices, 
				  std::vector<std::pair<Texture, Mesh::TextureType>>(1, 
				  std::pair<Texture, Mesh::TextureType>(Texture(TEXTURES_DIR"dirt_side.png", 
				  Texture::MinFilter::NEAREST, Texture::MagFilter::NEAREST), Mesh::TextureType::DIFFUSE)));
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		Time::update();
		EventHandler::onFrameUpdate(window);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.set("viewMatrix", player.getViewMatrix())
			  .set("projectionMatrix", player.getProjectionMatrix());
		triangle.draw(shader);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}