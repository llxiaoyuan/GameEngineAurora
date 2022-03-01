#pragma once

#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include<Graphics.hpp>

/// <summary>
/// ¼ÆÊ±Æ÷
/// </summary>
class Timer
{
public:

	Timer();

	Timer(const float& timeLimit);

	void update();

	bool reached();

	void restart();

	void setTimeLimit(const float& timeLimit);

	float timeLimit;

	float curTime;

private:

};

#endif // !_TIMER_HPP_
