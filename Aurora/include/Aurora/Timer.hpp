#pragma once

#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include"Graphics.hpp"

//计时器类
class Timer
{
public:

	Timer();

	Timer(const float& timeLimit);

	//更新时间
	bool update();

	//重新开始计时
	void restart();

	//设置计时器的计时时间
	void setTimeLimit(const float& timeLimit);

private:

	float timeLimit;

	float curTime;

};

#endif // !_TIMER_HPP_
