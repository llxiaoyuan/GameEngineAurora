#pragma once

#ifndef _RECTANGLE_HPP_
#define _RECTANGLE_HPP_

#include<glm/glm.hpp>

class Rectangle
{
public:

	Rectangle();

	Rectangle(const float& x, const float& y, const float& width, const float& height);

	const bool overLap(const Rectangle&) const;
	
	const bool in(const glm::vec2& dot) const;

	float x;

	float y;

	const float& getWidth() const;

	const float& getHeight() const;

private:


	float width;

	float height;

};

#endif // !_RECTANGLE_HPP_
