#pragma once

#ifndef _ACTOR_HPP_
#define _ACTOR_HPP_

#include<glm/glm.hpp>

#include"SpriteRenderer.hpp"

class SpriteRenderer;

//演员类
class Actor
{
public:

	Actor() :position(0, 0, 0) {}

	virtual ~Actor() {}

	//更新
	virtual void update(const float& dt) = 0;

	//渲染
	virtual void render(SpriteRenderer& renderer) = 0;

	//获取位置
	const glm::vec3& getPosition() const;

	//设置位置
	void setPosition(const float& x, const float& y);

	//设置位置
	void setPosition(const glm::vec3& pos);

	//设置x坐标
	void setX(const float& x);

	//设置y坐标
	void setY(const float& y);

	//获取x坐标
	const float& getX() const;

	//获取y坐标
	const float& getY() const;

protected:

	glm::vec3 position;

};

#endif // !_ACTOR_HPP_
