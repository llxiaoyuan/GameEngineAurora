#include<Aurora/Rect.hpp>

Rect::Rect():
	x(0),y(0),width(0),height(0)
{

}

Rect::Rect(const float& x, const float& y, const float& width, const float& height):
	x(x),y(y),width(width),height(height)
{

}

bool Rect::overLap(const Rect& r) const
{
	const float x1 = x;
	const float y1 = y;
	const float x2 = x + width;
	const float y2 = y + height;

	const float xx1 = r.x;
	const float yy1 = r.y;
	const float xx2 = r.x + r.width;
	const float yy2 = r.y + r.height;

	return !(x2 <= xx1 || x1 >= xx2 || y2 <= yy1 || y1 >= yy2);
}

bool Rect::in(const glm::vec2& dot) const
{
	return (dot[0] > x && dot[1] > y && dot[0] < x + width && dot[1] < y + height);
}

const float& Rect::getX()
{
	return x;
}

const float& Rect::getY()
{
	return y;
}

const float& Rect::getWidth() const
{
	return width;
}

const float& Rect::getHeight() const
{
	return height;
}

void Rect::setX(const float& x)
{
	this->x = x;
}

void Rect::setY(const float& y)
{
	this->y = y;
}

void Rect::setWidth(const float& width)
{
	this->width = width;
}

void Rect::setHeight(const float& height)
{
	this->height = height;
}
