#pragma once

#ifndef _MOUSE_HPP_
#define _MOUSE_HPP_

#include<glm/glm.hpp>
#include<GLFW/glfw3.h>

#include"Graphics.hpp"

// Û±Í¿‡
class Mouse
{
public:

	Mouse() = delete;

	Mouse(const Mouse&) = delete;

	static const glm::vec2& getPosition();

	static const bool& isLeftDown();

	static const bool& isRightDown();

	static const bool& isLeftUp();

	static const bool& isRightUp();

	static const bool& isLeftRepeat();

	static const bool& isRightRepeat();

	static const bool& getMoved();

	static void reFresh();

private:

	static glm::vec2 pos;

	static bool leftDown;

	static bool leftUp;

	static bool leftRepeat;

	static bool rightDown;

	static bool rightUp;

	static bool rightRepeat;

	static bool moved;

	static float dx;

	static float dy;

	friend class Aurora;
	
	friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


};

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

#endif // !_MOUSE_HPP_
