#include "Camera.h"

glm::vec3 Camera::getDirection() const
{
	glm::vec3 direction;
	direction.x = glm::cos(glm::radians(m_Pitch)) * glm::cos(glm::radians(m_Yaw));
	direction.y = glm::sin(glm::radians(m_Pitch));
	direction.z = glm::cos(glm::radians(m_Pitch)) * glm::sin(glm::radians(m_Yaw));
	return direction;
}