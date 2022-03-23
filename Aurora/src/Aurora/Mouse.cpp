#include<Aurora/Mouse.hpp>

glm::vec2 Mouse::pos = glm::vec2(0, 0);
bool Mouse::leftDown = false;
bool Mouse::rightDown = false;

bool Mouse::leftRepeat = false;
bool Mouse::rightRepeat = false;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Mouse::pos = glm::vec2(xpos, Graphics::getHeight() - ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			Mouse::leftRepeat = true;
			Mouse::leftDown = true;
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			Mouse::rightRepeat = true;
			Mouse::rightDown = true;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			Mouse::leftRepeat = false;
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			Mouse::rightRepeat = false;
		}
	}
}

const glm::vec2& Mouse::getPosition()
{
	return pos;
}

const bool& Mouse::isLeftDown()
{
	return leftDown;
}

const bool& Mouse::isRightDown()
{
	return rightDown;
}

const bool& Mouse::isLeftRepeat()
{
	return leftRepeat;
}

const bool& Mouse::isRightRepeat()
{
	return rightRepeat;
}

void Mouse::reFresh()
{
	leftDown = false;
	rightDown = false;
}
