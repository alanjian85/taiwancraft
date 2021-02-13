#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
	float m_Yaw, m_Pitch, m_Roll, m_Fov;
	int m_ScreenWidth, m_ScreenHeight;
	glm::vec3 m_Position;

public:
	Camera(glm::vec3 position, float yaw, float pitch, float roll, float fov, int screenWidth, int screenHeight) :
		   m_Position(position), m_Yaw(yaw), m_Pitch(pitch), m_Roll(roll), m_Fov(fov), m_ScreenWidth(screenWidth), 
		   m_ScreenHeight(screenHeight) {}

	Camera& setPosition(glm::vec3 position) { m_Position = position; return *this; }
	Camera& setYaw(float yaw) { m_Yaw = yaw; return *this; }
	Camera& setPitch(float pitch) { m_Pitch = pitch; return *this; }
	Camera& setRoll(float roll) { m_Roll = roll; return *this; }
	Camera& setFov(float fov) { m_Fov = fov; }
	Camera& setScreenWidth(int screnWidth) { m_ScreenWidth = m_ScreenWidth; }
	Camera& setScreenHeight(int screnHeight) { m_ScreenHeight = m_ScreenHeight; }

	float getYaw() const { return m_Yaw; }
	float getPitch() const { return m_Pitch; }
	float getRoll() const { return m_Roll; }
	glm::vec3 getPosition() const { return m_Position; }
	
	glm::vec3 getDirection() const
	{
		glm::vec3 direction;
		direction.x = glm::cos(glm::radians(m_Pitch)) * glm::cos(glm::radians(m_Yaw));
		direction.y = glm::sin(glm::radians(m_Pitch));
		direction.z = glm::cos(glm::radians(m_Pitch)) * glm::sin(glm::radians(m_Yaw));
		return direction;
	}
	
	glm::vec3 getUpDir() const
	{
		return glm::vec3(-glm::sin(glm::radians(m_Roll)), glm::cos(glm::radians(m_Roll)), 0.0f);
	}	

	glm::mat4 getCameraMatrix()
	{
		auto projection = glm::perspective(glm::radians(m_Fov), float(m_ScreenWidth) / float(m_ScreenHeight), 0.1f, 100.0f);
		auto view = glm::lookAt(m_Position, m_Position + getDirection(), getUpDir());
		return projection * view;
	}
};

#endif