#pragma once

struct pointerPrototype
{
	int id = -1;
	float texcoordX = 0;
	float texcoordY = 0;
	float prevTexcoordX = 0;
	float prevTexcoordY = 0;
	float deltaX = 0;
	float deltaY = 0;
	bool down = false;
	bool moved = false;
	int r = 30;
	int g = 0;
	int b = 300;
};