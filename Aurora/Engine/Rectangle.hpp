#pragma once

#ifndef _RECTANGLE_HPP_
#define _RECTANGLE_HPP_

#include<glm/glm.hpp>

class Rectangle
{
public:

	Rectangle();

	Rectangle(const float& x, const float& y, const float& width, const float& height);

	bool overLap(const Rectangle&) const;
	
	bool in(const glm::vec2& dot) const;

	const float& getX();

	const float& getY();

	const float& getWidth() const;

	const float& getHeight() const;

	void setX(const float& x);

	void setY(const float& y);

	void setWidth(const float& width);

	void setHeight(const float& height);

private:

	float x;

	float y;

	float width;

	float height;

};

#endif // !_RECTANGLE_HPP_
