#pragma once

#ifndef _RECT_HPP_
#define _RECT_HPP_

#include<glm/glm.hpp>

class Rect
{
public:

	Rect();

	Rect(const float& x, const float& y, const float& width, const float& height);

	bool overLap(const Rect&) const;

	bool in(const glm::vec2& dot) const;

	const float& getX() const;

	const float& getY() const;

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
