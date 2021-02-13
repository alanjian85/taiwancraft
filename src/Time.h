#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>

class Time {
private:
	static float m_LastTime, m_FrameTime;

public:
	static void update()
	{
		float currTime = float(glfwGetTime());
		m_FrameTime = currTime - m_LastTime;
		m_LastTime = currTime;
	}
	static float getFrameTime() { return m_FrameTime; }
};

#endif