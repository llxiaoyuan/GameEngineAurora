#pragma once

#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include"Graphics.hpp"

class Timer
{
public:

	Timer();

	Timer(const float& timeLimit);

	bool update();

	void restart();

	void setTimeLimit(const float& timeLimit);

private:

	float timeLimit;

	float curTime;

};

#endif // !_TIMER_HPP_
