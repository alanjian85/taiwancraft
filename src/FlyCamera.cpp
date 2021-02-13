#include "FlyCamera.h"

#include <glm/gtc/matrix_transform.hpp>

glm::vec3 FlyCamera::getDirection() const
{
	glm::vec3 direction;
	direction.x = glm::cos(m_Pitch) * glm::cos(m_Yaw);
	direction.y = glm::sin(m_Pitch);
	direction.z = glm::cos(m_Pitch) * glm::sin(m_Yaw);
	return direction;
}

glm::mat4 FlyCamera::getViewMatrix() const
{
	return glm::lookAt(m_Position, m_Position + getDirection(), m_UpDir);
}