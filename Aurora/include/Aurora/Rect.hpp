#pragma once

#ifndef _RECT_HPP_
#define _RECT_HPP_

#include<glm/glm.hpp>

//矩形类
class Rect
{
public:

	Rect();

	Rect(const float& x, const float& y, const float& width, const float& height);

	//返回两个矩形是否重叠
	bool overLap(const Rect&) const;

	//返回点是否在矩形内
	bool in(const glm::vec2& dot) const;

	//返回x坐标
	const float& getX() const;

	//返回y坐标
	const float& getY() const;

	//获取宽
	const float& getWidth() const;

	//获取高
	const float& getHeight() const;

	//设置x坐标
	void setX(const float& x);

	//设置y坐标
	void setY(const float& y);

	//设置宽
	void setWidth(const float& width);

	//设置高
	void setHeight(const float& height);

private:

	float x;

	float y;

	float width;

	float height;

};


#endif // !_RECTANGLE_HPP_
