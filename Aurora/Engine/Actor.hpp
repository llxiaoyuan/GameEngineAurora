#pragma once

#ifndef _ACTOR_HPP_
#define _ACTOR_HPP_

#include<glm/glm.hpp>

#include"SpriteRenderer.hpp"

class SpriteRenderer;

class Actor
{
public:

	Actor() :position(0, 0, 0) {}

	virtual ~Actor() {}

	virtual void update(const float& dt) = 0;

	virtual void render(SpriteRenderer& renderer) = 0;

	const glm::vec3& getPosition() const;

	void setPosition(const float& x, const float& y);

	void setPosition(const glm::vec3& pos);

	void setX(const float& x);

	void setY(const float& y);

	const float& getX() const;

	const float& getY() const;

protected:

	glm::vec3 position;

};

#endif // !_ACTOR_HPP_
