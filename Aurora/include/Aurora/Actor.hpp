#pragma once

#ifndef _ACTOR_HPP_
#define _ACTOR_HPP_

#include<glm/glm.hpp>

#include"SpriteRenderer.hpp"

class SpriteRenderer;

//��Ա��
class Actor
{
public:

	Actor() :position(0, 0, 0) {}

	virtual ~Actor() {}

	//����
	virtual void update(const float& dt) = 0;

	//��Ⱦ
	virtual void render(SpriteRenderer& renderer) = 0;

	//��ȡλ��
	const glm::vec3& getPosition() const;

	//����λ��
	void setPosition(const float& x, const float& y);

	//����λ��
	void setPosition(const glm::vec3& pos);

	//����x����
	void setX(const float& x);

	//����y����
	void setY(const float& y);

	//��ȡx����
	const float& getX() const;

	//��ȡy����
	const float& getY() const;

protected:

	glm::vec3 position;

};

#endif // !_ACTOR_HPP_
