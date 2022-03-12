#pragma once

#include<Aurora/ShapeRenderer.hpp>
#include<Aurora/Graphics.hpp>

#include<string>

#include"Parser.hpp"
#include"Command.hpp"

using namespace std;

float x;
float y;
float len = 0;
float angle = 0;//Ω«∂»÷∆
bool pen = true;
constexpr float tPi = 6.28318530717958647692f;

void setPos(float xPos, float yPos)
{
	x = xPos + Graphics::getWidth() / 2;
	y = yPos + Graphics::getHeight() / 2;
}

void rotate(float ang)
{
	angle += ang;
}

void DrawLine(ShapeRenderer& renderer)
{
	float targetX = x + cos(angle / 360.f * tPi) * len;
	float targetY = y + sin(angle / 360.f * tPi) * len;

	if (pen) {

		renderer.drawLine(x, y, targetX, targetY, 0, 0, 0);
		renderer.drawLine(x + 1, y, targetX + 1, targetY, 0, 0, 0);
		renderer.drawLine(x, y + 1, targetX, targetY + 1, 0, 0, 0);
		renderer.drawLine(x - 1, y, targetX - 1, targetY, 0, 0, 0);
		renderer.drawLine(x, y - 1, targetX, targetY - 1, 0, 0, 0);

	}

	x = targetX;
	y = targetY;

}

class Logo
{
public:

	vector<string> tokens;

	string text;

	Logo()
	{

	}

	Logo(const string& text)
	{
		this->text = text;
		setPos(0, 0);
	}

	void setText(const std::string& str)
	{
		this->text = str;
		setPos(0, 0);
	}

	void Draw(ShapeRenderer& renderer);

};

void execute(vector<Command> commands,ShapeRenderer& renderer)
{
	for (size_t i = 0; i < commands.size(); i++)
	{
		Command command = commands[i];
		string name = command.name;
		string arg=command.arg;
		if (name == "repeat")
		{
			for (size_t j = 0; j < stoull(arg); j++)
			{
				execute(command.commands, renderer);
			}
		}
		else if (name == "fd")
		{
			len = stof(arg);
			DrawLine(renderer);
		}
		else if (name == "bd")
		{
			len = -stof(arg);
			DrawLine(renderer);
		}
		else if (name == "lt")
		{
			angle += stof(arg);
		}
		else if (name == "rt")
		{
			angle -= stof(arg);
		}
		else if (name == "pd")
		{
			pen = true;
		}
		else if (name == "pu")
		{
			pen = false;
		}
	}
}

void Logo::Draw(ShapeRenderer& renderer)
{
	Parser parser(text);
	
	vector<Command> commands;

	commands = parser.parse();

	execute(commands, renderer);

	

}