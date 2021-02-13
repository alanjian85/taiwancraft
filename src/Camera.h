#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
	float m_Yaw, m_Pitch, m_Roll;
	glm::vec3 m_Position;

public:
	Camera(glm::vec3 position, float yaw, float pitch, float roll) :
		   m_Position(position), m_Yaw(yaw), m_Pitch(pitch), m_Roll(roll) {}

	Camera& setPosition(glm::vec3 position) { m_Position = position; return *this; }
	Camera& setYaw(float yaw) { m_Yaw = yaw; return *this; }
	Camera& setPitch(float pitch) { m_Pitch = pitch; return *this; }
	Camera& setRoll(float roll) { m_Roll = roll; return *this; }

	float getYaw() const { return m_Yaw; }
	float getPitch() const { return m_Pitch; }
	float getRoll() const { return m_Roll; }
	glm::vec3 getPosition() const { return m_Position; }
	glm::vec3 getDirection() const;
	glm::vec3 getUpDir() const
	{
		return glm::vec3(-glm::sin(glm::radians(m_Roll)), glm::cos(glm::radians(m_Roll)), 0.0f);
	}

	glm::mat4 getViewMatrix() { return glm::lookAt(m_Position, m_Position + getDirection(), getUpDir()); };
};

#endif