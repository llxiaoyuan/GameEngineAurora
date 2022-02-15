#pragma once

#ifndef _ACTOR_HPP_
#define _ACTOR_HPP_

#include<glm/glm.hpp>

class Actor
{
public:

	Actor() {}

	virtual ~Actor() {}

	virtual void update(const float& dt) = 0;

	virtual void render() = 0;

	glm::vec3 position;

};

#endif // !_ACTOR_HPP_
