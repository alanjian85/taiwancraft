#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
	glm::vec3 m_Position;
	float m_Yaw, m_Pitch, m_Roll, m_Fov, m_Near, m_Far;
	int m_ScreenWidth, m_ScreenHeight;
public:
	Camera(glm::vec3 position, float yaw, float pitch, float roll,
		   float fov, int screenWidth, int screenHeight, float near, float far) :
		   m_Position(position), m_Yaw(yaw), m_Pitch(pitch), m_Roll(roll), 
		   m_Fov(fov), m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight),
		   m_Near(near), m_Far(far) {}

	glm::vec3 getPosition() const { return m_Position; }
	float getYaw() const { return m_Yaw; }
	float getPitch() const { return m_Pitch; }
	float getRoll() const { return m_Roll; }
	float getFov() const { return m_Fov; }
	float getNear() const { return m_Near; }
	float getFar() const { return m_Far; }

	Camera& setPosition(glm::vec3 position) { m_Position = position; return *this; }
	Camera& setYaw(float yaw) { m_Yaw = yaw; return *this; }
	Camera& setPitch(float pitch) { m_Pitch = pitch; return *this; }
	Camera& setRoll(float roll) { m_Roll = roll; return *this; }
	Camera& setFov(float fov) { m_Fov = fov; return *this; }
	Camera& setScreenWidth(int width) { m_ScreenWidth = width; return *this; }
	Camera& setScreenHeight(int height) { m_ScreenHeight = height; return *this; }
	Camera& setNear(float near) { m_Near = near; return *this; }
	Camera& setFar(float far) { m_Far = far; return *this; }

	glm::vec3 getDirection() const
	{
		glm::vec3 direction;
		direction.x = glm::cos(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
		direction.y = glm::sin(glm::radians(m_Pitch));
		direction.z = glm::sin(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
		return direction;
	}

	glm::vec3 getUpDir() const { return glm::vec3(-glm::sin(m_Roll), glm::cos(m_Roll), 0.0f); }

	glm::mat4 getViewMatrix() const { return glm::lookAt(m_Position, m_Position + getDirection(), getUpDir()); }
	glm::mat4 getProjectionMatrix() const { 
		return glm::perspective(m_Fov, float(m_ScreenWidth) / float(m_ScreenHeight), m_Near, m_Far);
	}
};

#endif