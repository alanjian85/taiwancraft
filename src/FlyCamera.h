#ifndef FLY_CAMERA_H
#define FLY_CAMERA_H

#include "Camera.h"

class FlyCamera : public Camera {
private:
	float m_Yaw, m_Pitch;
	glm::vec3 m_Position, m_UpDir;
public:
	glm::vec3 getPosition() const { return m_Position; }
	glm::vec3 getUpDir() const { return m_UpDir; }
	glm::mat4 getViewMatrix() const;
	glm::vec3 getDirection() const;
};

#endif