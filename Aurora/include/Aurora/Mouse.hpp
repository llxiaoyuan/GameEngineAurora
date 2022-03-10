#pragma once

#ifndef _MOUSE_HPP_
#define _MOUSE_HPP_

#include<glm/glm.hpp>
#include<GLFW/glfw3.h>

//�����
class Mouse
{
public:

	//��ȡ���λ��
	static const glm::vec2& getPosition();

	//��ȡ���״̬
	static const bool& isLeftDown();

	//��ȡ�Ҽ�״̬
	static const bool& isRightDown();

private:

	static glm::vec2 pos;

	static bool leftDown;

	static bool rightDown;

	friend class Aurora;

	static void ini();
	
	friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


};

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

#endif // !_MOUSE_HPP_
