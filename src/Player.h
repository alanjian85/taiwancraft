#ifndef PLAYER_H
#define PLAYER_H

#include "EventHandler.h"
#include "Camera.h"

class Player : public EventHandler, public Camera {
private:
	double lastx, lasty;

	void m_OnFrameUpdate(GLFWwindow* window) override {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) position += getDirection() * moveSpeed * Time::getDelta();
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) position -= getDirection() * moveSpeed * Time::getDelta();
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) position += getRightDir() * moveSpeed * Time::getDelta();
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) position -= getRightDir() * moveSpeed * Time::getDelta();
	}

	void m_OnCursorPosChange(GLFWwindow* window, double xpos, double ypos) override {
		if (justCaptured) {
			lastx = xpos;
			lasty = ypos;
			justCaptured = false;
		}

		double deltax = xpos - lastx, deltay = lasty - ypos;

		yaw += deltax * rotateSpeed;
		pitch += deltay * rotateSpeed;

		pitch = glm::clamp(pitch, -89.0f, 89.0f);

		lastx = xpos;  lasty = ypos;
	}
public:
	float moveSpeed, rotateSpeed;
	bool justCaptured = true;

	Player(glm::vec3 position, float yaw, float pitch, float roll,
		   float fov, int screenWidth, int screenHeight, float near, float far,
		   float moveSpeed, float rotateSpeed) :
		   Camera(position, yaw, pitch, roll, fov, screenWidth, screenHeight, near, far) 
	{
		this->moveSpeed = moveSpeed;
		this->rotateSpeed = rotateSpeed;
	}
};

#endif