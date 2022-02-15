#pragma once

#ifndef _LOOP_TIMER_HPP_
#define _LOOP_TIMER_HPP_

class LoopTimer
{
public:

	const float time;
	
	float curTime;

	LoopTimer(const float& time);

	void update(const float& dt);

	bool reached();

	void restart();

};

#endif // !_LOOP_TIMER_HPP_
