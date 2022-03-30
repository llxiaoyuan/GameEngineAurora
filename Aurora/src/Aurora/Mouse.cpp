#include<Aurora/Mouse.hpp>

glm::vec2 Mouse::pos = glm::vec2(0, 0);

bool Mouse::leftRepeat = false;
bool Mouse::rightRepeat = false;

float Mouse::dx = 0;
float Mouse::dy = 0;

Event Mouse::leftDownEvent;
Event Mouse::leftUpEvent;

Event Mouse::rightDownEvent;
Event Mouse::rightUpEvent;

Event Mouse::moveEvent;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Mouse::moveEvent();
	Mouse::dx = (float)xpos - Mouse::pos.x;
	Mouse::dy = (float)ypos - Mouse::pos.y;
	Mouse::pos = glm::vec2(xpos, Graphics::getHeight() - ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			Mouse::leftDownEvent();
			Mouse::leftRepeat = true;
		}
		if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			Mouse::rightDownEvent();
			Mouse::rightRepeat = true;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			Mouse::leftUpEvent();
			Mouse::leftRepeat = false;
		}
		if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			Mouse::rightUpEvent();
			Mouse::rightRepeat = false;
		}
	}
	
}

const glm::vec2& Mouse::getPosition()
{
	return pos;
}

const bool& Mouse::getLeftRepeat()
{
	return leftRepeat;
}

const bool& Mouse::getRightRepeat()
{
	return rightRepeat;
}

void Mouse::removeLeftDownEvent(const int& id)
{
	leftDownEvent.removeHandler(id);
}

void Mouse::removeLeftUpEvent(const int& id)
{
	leftUpEvent.removeHandler(id);
}

void Mouse::removeRightDownEvent(const int& id)
{
	rightDownEvent.removeHandler(id);
}

void Mouse::removeRightUpEvent(const int& id)
{
	rightUpEvent.removeHandler(id);
}

void Mouse::removeMoveEvent(const int& id)
{
	moveEvent.removeHandler(id);
}
