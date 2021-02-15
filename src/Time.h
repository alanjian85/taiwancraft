#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>

class Time {
private:
	static float delta;

public:
	static float getDelta() { return delta; }

	static void update()
	{
		static float lastTime = 0.0f;

		float currTime = glfwGetTime();
		delta = currTime - lastTime;
		lastTime = currTime;
	}
};

#endif