#include"Rectangle.hpp"

ae::Rectangle::Rectangle():
	x(0),y(0),width(0),height(0)
{

}

ae::Rectangle::Rectangle(const float& x, const float& y, const float& width, const float& height):
	x(x),y(y),width(width),height(height)
{

}

bool ae::Rectangle::overLap(const ae::Rectangle& r) const
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

bool ae::Rectangle::in(const glm::vec2& dot) const
{
	return (dot[0] > x && dot[1] > y && dot[0] < x + width && dot[1] < y + height);
}

const float& ae::Rectangle::getX()
{
	return x;
}

const float& ae::Rectangle::getY()
{
	return y;
}

const float& ae::Rectangle::getWidth() const
{
	return width;
}

const float& ae::Rectangle::getHeight() const
{
	return height;
}

void ae::Rectangle::setX(const float& x)
{
	this->x = x;
}

void ae::Rectangle::setY(const float& y)
{
	this->y = y;
}

void ae::Rectangle::setWidth(const float& width)
{
	this->width = width;
}

void ae::Rectangle::setHeight(const float& height)
{
	this->height = height;
}
