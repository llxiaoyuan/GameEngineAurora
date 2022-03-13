#include<Aurora/Actor.hpp>

const glm::vec3& Actor::getPosition() const
{
	return position;
}

void Actor::setPosition(const float& x, const float& y)
{
	position.x = x;
	position.y = y;
}

void Actor::setPosition(const glm::vec3& pos)
{
	position = pos;
}

void Actor::setX(const float& x)
{
	position.x = x;
}

void Actor::setY(const float& y)
{
	position.y = y;
}

const float& Actor::getX() const
{
	return position.x;
}

const float& Actor::getY() const
{
	return position.y;
}
