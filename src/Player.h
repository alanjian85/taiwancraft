#ifndef PLAYER_H
#define PLAYER_H

#include "Camera.h"
#include "Time.h"

#include <GLFW/glfw3.h>

class Player {
private:
	float m_MoveSpeed, m_RotateSpeed;
	Camera m_Camera;
public:
	Player(glm::vec3 position, float moveSpeed, float rotateSpeed, int screenWidth, int screenHeight) :
		   m_Camera(position, -90.0f, 0.0f, 0.0f, 45.0f, screenWidth, screenHeight),
		   m_MoveSpeed(moveSpeed), m_RotateSpeed(rotateSpeed) {}

	void onFrameEvent(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) m_Camera.setPosition(m_Camera.getPosition() + m_Camera.getDirection() * m_MoveSpeed * Time::getFrameTime());
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) m_Camera.setPosition(m_Camera.getPosition() - m_Camera.getDirection() * m_MoveSpeed * Time::getFrameTime());
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
			m_Camera.setPosition(m_Camera.getPosition() + glm::normalize(glm::cross(m_Camera.getDirection(), m_Camera.getUpDir())) * m_MoveSpeed * Time::getFrameTime());
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
			m_Camera.setPosition(m_Camera.getPosition() - glm::normalize(glm::cross(m_Camera.getDirection(), m_Camera.getUpDir())) * m_MoveSpeed * Time::getFrameTime());
	}

	void onCursorMove(int xpos, int ypos)
	{
		static int lastx = xpos, lasty = ypos;

		int deltax = xpos - lastx;
		int deltay = lasty - ypos;

		m_Camera.setYaw(m_Camera.getYaw() + deltax * m_RotateSpeed)
				.setPitch(m_Camera.getPitch() + deltay * m_RotateSpeed);

		m_Camera.setPitch(glm::clamp(m_Camera.getPitch(), -89.0f, 89.0f));

		lastx = xpos;
		lasty = ypos;
	}

	glm::mat4 getCameraMatrix() { return m_Camera.getCameraMatrix(); }
};

#endif