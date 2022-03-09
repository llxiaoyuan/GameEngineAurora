#include<Aurora/Actor.hpp>

const glm::vec3& Actor::getPosition() const
{
	return position;
}

void Actor::setPosition(const float& x, const float& y)
{
	position[0] = x;
	position[1] = y;
}

void Actor::setPosition(const glm::vec3& pos)
{
	position = pos;
}

void Actor::setX(const float& x)
{
	position[0] = x;
}

void Actor::setY(const float& y)
{
	position[1] = y;
}

const float& Actor::getX() const
{
	return position[0];
}

const float& Actor::getY() const
{
	return position[1];
}
