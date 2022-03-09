#pragma once

#ifndef _RECT_HPP_
#define _RECT_HPP_

#include<glm/glm.hpp>

//������
class Rect
{
public:

	Rect();

	Rect(const float& x, const float& y, const float& width, const float& height);

	//�������������Ƿ��ص�
	bool overLap(const Rect&) const;

	//���ص��Ƿ��ھ�����
	bool in(const glm::vec2& dot) const;

	//����x����
	const float& getX();

	//����y����
	const float& getY();

	//��ȡ��
	const float& getWidth() const;

	//��ȡ��
	const float& getHeight() const;

	//����x����
	void setX(const float& x);

	//����y����
	void setY(const float& y);

	//���ÿ�
	void setWidth(const float& width);

	//���ø�
	void setHeight(const float& height);

private:

	float x;

	float y;

	float width;

	float height;

};


#endif // !_RECTANGLE_HPP_
