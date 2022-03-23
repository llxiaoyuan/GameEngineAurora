#pragma once

#ifndef _MOUSE_HPP_
#define _MOUSE_HPP_

#include<glm/glm.hpp>
#include<GLFW/glfw3.h>

#include"Graphics.hpp"

//鼠标类
class Mouse
{
public:

	Mouse() = delete;

	Mouse(const Mouse&) = delete;

	//获取鼠标位置
	static const glm::vec2& getPosition();

	//获取左键状态
	static const bool& isLeftDown();

	//获取右键状态
	static const bool& isRightDown();

	static const bool& isLeftRepeat();

	static const bool& isRightRepeat();

	static void reFresh();

private:

	static glm::vec2 pos;

	static bool leftDown;

	static bool leftRepeat;

	static bool rightDown;

	static bool rightRepeat;

	friend class Aurora;
	
	friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


};

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

#endif // !_MOUSE_HPP_
