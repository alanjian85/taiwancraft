#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
	virtual glm::mat4 getViewMatrix() const = 0;
};

#endif