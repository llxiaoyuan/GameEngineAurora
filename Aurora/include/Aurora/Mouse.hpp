#pragma once

#ifndef _MOUSE_HPP_
#define _MOUSE_HPP_

#include<glm/glm.hpp>
#include<GLFW/glfw3.h>

#include"Graphics.hpp"
#include"Event.hpp"

// Û±Í¿‡
class Mouse
{
public:

	Mouse() = delete;

	Mouse(const Mouse&) = delete;

	static const glm::vec3& getPosition();

	static const bool& getLeftRepeat();

	static const bool& getRightRepeat();

	static const float& getDeltaX();

	static const float& getDeltaY();

	template<class ObjT, class FuncT>
	static int addLeftDownEvent(ObjT obj, FuncT func);

	template<class ObjT, class FuncT>
	static int addLeftUpEvent(ObjT obj, FuncT func);

	template<class ObjT, class FuncT>
	static int addRightDownEvent(ObjT obj, FuncT func);

	template<class ObjT, class FuncT>
	static int addRightUpEvent(ObjT obj, FuncT func);

	template<class ObjT, class FuncT>
	static int addMoveEvent(ObjT obj, FuncT func);

	static void removeLeftDownEvent(const int& id);

	static void removeLeftUpEvent(const int& id);

	static void removeRightDownEvent(const int& id);

	static void removeRightUpEvent(const int& id);

	static void removeMoveEvent(const int& id);

private:

	static glm::vec3 pos;

	static Event leftDownEvent;

	static Event leftUpEvent;

	static Event rightDownEvent;

	static Event rightUpEvent;

	static bool leftRepeat;

	static bool rightRepeat;

	static Event moveEvent;

	static float dx;

	static float dy;

	friend class Aurora;
	
	friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


};

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

template<class ObjT, class FuncT>
inline int Mouse::addLeftDownEvent(ObjT obj, FuncT func)
{
	return leftDownEvent.addHandler(obj, func);
}

template<class ObjT, class FuncT>
inline int Mouse::addLeftUpEvent(ObjT obj, FuncT func)
{
	return leftUpEvent.addHandler(obj, func);
}

template<class ObjT, class FuncT>
inline int Mouse::addRightDownEvent(ObjT obj, FuncT func)
{
	return rightDownEvent.addHandler(obj, func);
}

template<class ObjT, class FuncT>
inline int Mouse::addRightUpEvent(ObjT obj, FuncT func)
{
	return rightUpEvent.addHandler(obj, func);
}

template<class ObjT, class FuncT>
inline int Mouse::addMoveEvent(ObjT obj, FuncT func)
{
	return moveEvent.addHandler(obj, func);
}

#endif // !_MOUSE_HPP_
