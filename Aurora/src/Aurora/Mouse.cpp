#include<Aurora/Mouse.hpp>

glm::vec2 Mouse::pos = glm::vec2(0, 0);
bool Mouse::leftDown = false;
bool Mouse::rightDown = false;

bool Mouse::leftUp = false;
bool Mouse::rightUp = false;

bool Mouse::leftRepeat = false;
bool Mouse::rightRepeat = false;

bool Mouse::moved = false;

float Mouse::dx = 0;
float Mouse::dy = 0;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Mouse::moved = true;
	Mouse::dx = xpos - Mouse::pos.x;
	Mouse::dy = ypos - Mouse::pos.y;
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
			Mouse::leftUp = true;
			Mouse::leftRepeat = false;
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			Mouse::rightUp = true;
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

const bool& Mouse::isLeftUp()
{
	return leftUp;
}

const bool& Mouse::isRightUp()
{
	return rightUp;
}

const bool& Mouse::isLeftRepeat()
{
	return leftRepeat;
}

const bool& Mouse::isRightRepeat()
{
	return rightRepeat;
}

const bool& Mouse::getMoved()
{
	return moved;
}

void Mouse::reFresh()
{
	leftDown = false;
	rightDown = false;
	leftUp = false;
	rightUp = false;
	moved = false;
}
