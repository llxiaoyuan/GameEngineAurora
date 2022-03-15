#pragma once

#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include"Graphics.hpp"

//��ʱ����
class Timer
{
public:

	Timer();

	Timer(const float& timeLimit);

	//����ʱ��
	bool update();

	//���¿�ʼ��ʱ
	void restart();

	//���ü�ʱ���ļ�ʱʱ��
	void setTimeLimit(const float& timeLimit);

private:

	float timeLimit;

	float curTime;

};

#endif // !_TIMER_HPP_
