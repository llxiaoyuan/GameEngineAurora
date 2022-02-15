#include"LoopTimer.hpp"

LoopTimer::LoopTimer(const float& time):
	time(time),curTime(0)
{

}

void LoopTimer::update(const float& dt)
{
	curTime += dt;
}

bool LoopTimer::reached()
{
	return curTime >= time;
}

void LoopTimer::restart()
{
	curTime = 0;
}