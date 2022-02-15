#pragma once

#ifndef _STAR_HPP_
#define _STAR_HPP_

#include<vector>
#include<ShapeRenderer.hpp>

class Star
{
public:

	static void update(const float& speed);

	static void render(const float& speed);

	static void add();

private:

	static std::vector<Star> pool;

	static float airDrag;

	static float airDragHeavy;

	float spinRadius;

	bool visible;

	bool heavy;

	glm::vec2 pos;

	glm::vec2 prePos;

	glm::vec2 speed;

};

#endif // !_STAR_HPP_