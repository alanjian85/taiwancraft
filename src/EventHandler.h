#ifndef event_HANDLER_H
#define event_HANDLER_H

#include <vector>

#include <GLFW/glfw3.h>

class EventHandler {
private:
	static std::vector<EventHandler*> eventHandlers;
protected:
	virtual void m_OnCursorPosChange(GLFWwindow* window, double xpos, double ypos) {}
	virtual void m_OnMouseButtonPress(GLFWwindow* window, int button, int action, int mods) {}
	virtual void m_OnFrameUpdate(GLFWwindow* window) {}
	virtual void m_OnWindowResize(GLFWwindow* window, int width, int height) {}
public:
	static void onCursorPosChange(GLFWwindow* window, double xpos, double ypos) {
		for (auto i : eventHandlers)
			if (i->enabled) 
				i->m_OnCursorPosChange(window, xpos, ypos);
	}

	static void onMouseButtonPress(GLFWwindow* window, int button, int action, int mods) {
		for (auto i : eventHandlers)
			if (i->enabled) 
				i->m_OnMouseButtonPress(window, button, action, mods);
	}

	static void onFrameUpdate(GLFWwindow* window) {
		for (auto i : eventHandlers)
			if (i->enabled) 
				i->m_OnFrameUpdate(window);
	}

	static void onWindowResize(GLFWwindow* window, int width, int height) {
		for (auto i : eventHandlers)
			if (i->enabled)
				i->m_OnWindowResize(window, width, height);
	}

	EventHandler() { eventHandlers.push_back(this); }
	bool enabled = true;
};

#endif