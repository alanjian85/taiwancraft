#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	glm::vec3 position;
	float yaw, pitch, roll, fov, near, far;
	int screenWidth, screenHeight;

	Camera(glm::vec3 position, float yaw, float pitch, float roll,
		   float fov, int screenWidth, int screenHeight, float near, float far) {
		this->position = position;
		this->yaw = yaw;
		this->pitch = pitch;
		this->roll = roll;
		this->fov = fov;
		this->near = near;
		this->far = far;
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;
	}

	glm::vec3 getDirection() const
	{
		glm::vec3 direction;
		direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
		direction.y = glm::sin(glm::radians(pitch));
		direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
		return direction;
	}
	glm::vec3 getRightDir() const { return glm::normalize(glm::cross(getDirection(), getSpaceUp())); }
	glm::vec3 getUpDir() const { return glm::normalize(glm::cross(getRightDir(), getDirection())); }

	glm::vec3 getSpaceUp() const { return glm::vec3(-glm::sin(roll), glm::cos(roll), 0.0f); }

	glm::mat4 getViewMatrix() const { return glm::lookAt(position, position + getDirection(), getSpaceUp()); }
	glm::mat4 getProjectionMatrix() const { 
		return glm::perspective(fov, float(screenWidth) / float(screenHeight), near, far);
	}
};

#endif